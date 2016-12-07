/**
 *<center>
 *               Avocent Corporation. Proprietary Information.
 * \n<em>
 *      This software is supplied under the terms of a license agreement or
 *      nondisclosure agreement with Avocent Corporation, or its subsidiary, and
 *      may not be copied, disseminated, or distributed except in accordance
 *      with the terms of that agreement.
 *
 *      3541 Gateway Boulevard Fremont, CA 94538 U.S.A.
 *
 *                  US phone: 510.771.6100
 *
 *        Copyright (C) 2001-2011 Avocent Corporation
 *</em> </center>
 *----------------------------------------------------------------------------*/

#include <CMPIUtil.h>
#include "clpjob.h"


#include "../class/incEX/CIM_ConcreteJob.h"
#include "incEX/CIM_ConcreteJobAgent.h"
#include "incEX/CIM_SoftwareInstallationServiceAgent.h"

#include <AgentUtil.h>
#include "LogUtil.h"

#include "incEX/IBM_ConfigurationDataServiceAgent.h"

#include <pthread.h>
//#include <sys/time.h> 
#include <time.h>
#include <stdio.h>
#include "../StringRegisterTable.h"
#include "../../../../../../../imm_powermgr/imm_powermgr/powermgr.h"
#include <libaim.h>
#include <flash_mgr/fmapi.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include "pm_lib.h"

#define MAX_SYSPROF_JOBS 4
#define SYSPROF_CLI_OK 0
#define SYSPROF_TASK_RUNNING 1000
#define SYSPROF_LDAP_INIT_FAIL 100
#define SYSPROF_LDAP_SET_OPT_FAIL 101
#define SYSPROF_LDAP_BIND_FAIL 102
#define SYSPROF_LDAP_SEARCH_FILTER_NULL 103
#define SYSPROF_LDAP_RS_PROFILE_FAIL 104
    
#define JOBSTATE_COMPLETED_WITHERROR 32769
#define JOBSTATE_LDAP_ERROR 32770
#define SYSPROF_NOJOB_SEQ 0

#define REPORT_FILENAME "results.out"
#define VAR_SPDIR "/var/systemprofiles"

extern const char sysprof_aim_seq[][32];
extern const char sysprof_aim_status[][32];
	
typedef struct _AgentData_CLPJob{
    UINT8	u8pID[32];
    BOOLEAN bDeleteOnCompletion;
    UINT16	u16JobState;
    UINT32  u32TimeBeforeRemoval;

    //added for oob update Job
    UINT16 u16OperationalStatus;
    UINT16 u16JobStatusCode;

} AgentData_CLPJob;

typedef struct
{
    int nCurrJobNum;
    AgentData_CLPJob *psData;
    int fd;
    CLPShareJobData *ps_CLPJobData;        
} sCLPJobs;

extern bool GetPowerScheduleOnInfo(struct tm *psTimeInfo);

int CIM_ConcreteJob_InstAgent_ChangeState(int i32JobId, UINT16 u16JobStatus);
int CIM_ConcreteJob_InstAgent_UpdateInstallStatus(int i32JobId, UINT16 u16JobState, UINT16 u16OperationalStatus, UINT16 u16JobStatus);

const char *CIM_SoftwareUpdate_Instance_Name = "update";

typedef struct
{
    CLPInstallStatusCode code;
    const char *pStrDscrp;
}sUpdateJob_Status_Description;

sUpdateJob_Status_Description CIM_UpdateJob_Status_Description[]=
{
        {CLP_STATUS_INIT,                     "null"},
        {CLP_STATUS_DOWNLADING,         "Download Progress -"},
        {CLP_STATUS_UPDATE,                 "Update Progress -"},
        {CLP_STATUS_DONE,                    "Reset:Process Completed"},
        {CLP_STATUS_COMPLETE,               "Process Completed"},
        {CLP_STATUS_SFTP_USER_FAIL,      "Sftp user authentication fail for downloading"},

        {CLP_STATUS_TFTP_FIREWALL_FORBID,   "Firewall configuration forbid tftp downloading"},     
        {CLP_STATUS_INVALID_URI,                    "Invalid URI"},
        {CLP_STATUS_INVALID_FTPSERV,            "IMM could not connect to sftp/tftp server"},
        {CLP_STATUS_INVALID_FILE,                   "IMM could not find the specified file on the sftp/tftp server"},
        {CLP_STATUS_TIMEOUT,                        "Timeout happens when downloading specified file from ftp server"},
        
        {CLP_STATUS_UNKNOWN_ERROR,            "Unknown error happens when download specified file from ftp server"},
        {CLP_STATUS_TASK_RUNNING,               "Another Update is in progress"},
        {CLP_STATUS_CIM_RESET,                     "CIM internal reset"},
        {CLP_STATUS_PKG_MISMATCH,               "Update firmware does not match target object"},
        {CLP_STATUS_FMAPI_ERROR,                "FMAPI error"},

        {CLP_STATUS_INVALID_FTP,                "FTP transfer is not supported"},
        {CLP_STATUS_UPDATE_TIMEOUT,         "Timeout happens when Flash Manager update target object"}
};

static const char *GetUpdateJobStatusDescription(CLPInstallStatusCode code)
{
    int i=0;
    for (; i<sizeof(CIM_UpdateJob_Status_Description)/sizeof(CIM_UpdateJob_Status_Description[0]); i++)
    {
        if (code == CIM_UpdateJob_Status_Description[i].code)
            return CIM_UpdateJob_Status_Description[i].pStrDscrp;
    }
    return CIM_UpdateJob_Status_Description[0].pStrDscrp;
}

//#define JOB_SEM_NAME "/tmp/JobSharedMemoryMutex"
//#define JOB_SHD_MEM "/SharedJobData"
void printSharedJobData(CLPJobData *ps_CLPJobData)
{
    CLPJobData *ptr;
    int i;
    
    for(i = 0; i < MAX_JOB_NUM; i++)
    {
        ptr = ps_CLPJobData+i;

        if(ptr->ullTimeLastModify != 0)
        {
            printf("[%d]: %d, %d, %lld, %lld\n", 
                    i,
                   ptr->bDeleteOnCompletion, 
                   ptr->u16JobState, 
                   ptr->ullTimeBeforeRemoval, 
                   ptr->ullTimeLastModify);
        }
    }
    return;
}

BOOLEAN IsCleanSoftwareUpdaetRunningJobs()
{
    BOOLEAN bResult = TRUE;
    bool bReturnAIM = false;
    int iPID = 0;
    
    //logTraceCIM(LOG_LEV_DEBUG, "%s()- Function Entry.", __FUNCTION__);

    bReturnAIM = aim_config_get_int(CIM_SOFTWARE_UPDATE_PID, &iPID);
    if (bReturnAIM)
    {
        if (iPID != 0)
        {
            char szBuf[1024] = { 0 };
            FILE *fReturn = NULL;

            memset(szBuf, 0, sizeof(szBuf));

            snprintf(szBuf, sizeof(szBuf), "/proc/%d/status", iPID);
            //logTraceCIM(LOG_LEV_INFO, "%s()- Process id : %d.", __FUNCTION__, iPID);
            fReturn = fopen(szBuf, "r");
            if (fReturn)
            {
                if (!feof(fReturn))
                {
                    size_t number = 0;
                    
                    memset(szBuf, 0, sizeof(szBuf));
                    
                    fseek(fReturn, 0L, SEEK_SET);
                    number = fread(szBuf, sizeof(char), sizeof(szBuf), fReturn);                    

                    if (number)
                    {
                        char *pcSFCBD = NULL;
                        
                        pcSFCBD = strstr(szBuf, "sfcbd");
                        if (pcSFCBD)
                        {
                            bResult = FALSE;
                        }
                    }
                    else
                    {
                        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call fread(). The return of ferror() is %d and the feof() is %d.", __FUNCTION__, ferror(fReturn), feof(fReturn));
                    }
                }
                else
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- feof() is %d.", __FUNCTION__, feof(fReturn));
                }
                
                fclose(fReturn);
            }
            else
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call fopen(%s, r)", __FUNCTION__, szBuf);
            }
        }
    }

    //logTraceCIM(LOG_LEV_DEBUG, "%s()- Function End.", __FUNCTION__);

    return bResult;
}

void CleanAllSoftwareUpdaetRunningJobs()
{
    CLPShareJobData sSharedData = { 0 };
    int i = 0;
    CLPJobData *ptr = NULL;
    char acUpdateType[32];
    bool bReturnAIM = false;
    
    //logTraceCIM(LOG_LEV_DEBUG, "%s()- Function Entry.", __FUNCTION__);

    memset(&sSharedData, 0, sizeof(CLPShareJobData));

    if (clp_GetJobData(&sSharedData) != 0)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s- Failed to call clp_GetJobData().", __FUNCTION__);
        return;
    }

    ptr = sSharedData.auJobData;
    for (i = 0; i < MAX_JOB_NUM; i++)
    {
        ptr = (CLPJobData *) &(sSharedData.auJobData[i]);

        if (ptr->ullTimeLastModify != 0)
        {
            /*  When u16JobState is 4 that means this is a running job. */
            if (4 == ptr->u16JobState)
            {
                int iResult = 0;
                logTraceCIM(LOG_LEV_ERROR, "%s- Set Running Job %d to Exception.%d", __FUNCTION__, (i + 1), ptr->bIsUpdateJob);

                if(ptr->bIsUpdateJob)
                    iResult = CIM_ConcreteJob_InstAgent_UpdateInstallStatus((i + 1), JOBSTATE_EXCEPTION, 0, CLP_STATUS_CIM_RESET);
                else
                    iResult = CIM_ConcreteJob_InstAgent_ChangeState((i + 1), 10);
                
               if (iResult != 0)
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s- Failed to call clp_GetJobData(%d, 10).", __FUNCTION__, (i + 1));
                }
            }
        }      
    }

    memset(acUpdateType, 0, sizeof(acUpdateType));
    bReturnAIM = aim_config_get_str(CIM_SOFTWARE_UPDATE_TYPE, acUpdateType);
    if (!bReturnAIM)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_get_str(%s).", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE);
    }

    if (strlen(acUpdateType) > 0)
    {
        if ((NULL == strstr(acUpdateType, "uefi")) && (NULL == strstr(acUpdateType, "bios")))
        {
            FMCancel(acUpdateType);
        }
        else
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Cannot FMCancel(%s). Please wait the update complete.", __FUNCTION__, acUpdateType);
        }

        bReturnAIM = aim_config_set_str(CIM_SOFTWARE_UPDATE_TYPE, "", false);
        if (!bReturnAIM)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(%s).", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE);
        }
    }
    
    //logTraceCIM(LOG_LEV_DEBUG, "%s()- Function End.", __FUNCTION__);

}

int IsCreatePowerOnScheduleJob()
{
    int iResult = 0;
    struct tm timeinfo;

    if (GetPowerScheduleOnInfo(&timeinfo))
    {
        time_t tNow;
        time_t tTime;
    
        tzset();    
        time(&tNow);
        
        tTime = mktime(&timeinfo);
        if (((time_t) -1) == tTime)
        {
            logTraceCIM(LOG_LEV_ERROR, "[%s] - Date-time of Power Schedule On is error.", __FUNCTION__);
        }
        
        logTraceCIM(LOG_LEV_INFO, "[%s] - tTime is %lu.", __FUNCTION__, tTime);
        if (tTime > tNow)
        {            
            iResult = 1;    //New
        }
        else if ((tTime + 300) > tNow)
        {
            logTraceCIM(LOG_LEV_INFO, "[%s] - (tTime + 300s) is %lu.", __FUNCTION__, tTime + 300);
            iResult = 2;    //Complete and wait to remove
        }
    }
    return iResult;
}

char * getStatusFilePath(UINT8 * pID, char * pszFilePath, unsigned int uiLen)
{
    UINT32 u16JobSeq;
    int iTaskID = 0;

    if (pID == NULL || pszFilePath == NULL)
    {
	 return NULL;
    }

    u16JobSeq = -1;
    sscanf((char *)pID, "SYSPROF-%x", &u16JobSeq);
    if (u16JobSeq <= 0) 
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- error instanceID.", __FUNCTION__);
        return NULL;
    }
    
    iTaskID = getTaskID(u16JobSeq);
    logTraceCIM(LOG_LEV_DEBUG, "%s() task (seq %d) ID %d.\n", __FUNCTION__, u16JobSeq, iTaskID);
    
    if (iTaskID <= 0)
    {
        return NULL;
    }
    else 
    {
        /* currently finished task or history task */
        snprintf(pszFilePath, uiLen, "%s/%s.%d", VAR_SPDIR, REPORT_FILENAME, iTaskID);
    }

    return pszFilePath;
		
}

char * getStatusFileContent(char * pszFilePath)
{
    UINT8 u8Data;
    UINT8 *pu8Array;
    UINT16 u8ArraySize;
	
    FILE *fSysprofileF = NULL;
    char *pContentValue;
	
    /* set output Data, open report file */
    if(NULL == (fSysprofileF = fopen(pszFilePath, "rb")))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call fopen(%s).", __FUNCTION__, pszFilePath);
	return NULL;
    }

     /* set output Data */
    fseek(fSysprofileF, 0L, SEEK_END);
    u8ArraySize = ftell(fSysprofileF);
    
    if(NULL == (pu8Array = Malloc(u8ArraySize+1)) )
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call Malloc().", __FUNCTION__);

        u8ArraySize = 4096;
        if(NULL == (pu8Array = Malloc(u8ArraySize+1)) )
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call Malloc() for 1K array.", __FUNCTION__);
            fclose(fSysprofileF);
	     return NULL;
        }
    }

    memset(pu8Array, 0, u8ArraySize+1);
    fseek(fSysprofileF, 0L, SEEK_SET);
    
    int i = 0;
    while (!feof(fSysprofileF) && i<u8ArraySize)
    {
        u8Data = fgetc(fSysprofileF);
        pu8Array[i] = isprint(u8Data) ? u8Data : ' ';
        i++;
    }
    pu8Array[i] = '\0';
	
    pContentValue = (void *) Strdup((char *)pu8Array);

    CIMFree(pu8Array);
    if (fSysprofileF != NULL)
    {
        fclose(fSysprofileF);
    }

    return pContentValue;
}

//create clp job for Software Installation Service. should not be used by other function
int CIM_ConcreteJob_InstAgent_CreateJob()
{
    int iResult = -1;
	UINT32 TimeBeforeRemoval = 300;

    iResult = clp_CreateJob(TimeBeforeRemoval);
    return (iResult);
}

int CIM_ConcreteJob_InstAgent_ChangeState(int i32JobId, UINT16 u16JobStatus)
{
    int iResult = -1;

    iResult = clp_JobRequestStateChange(i32JobId, u16JobStatus);

    return (iResult);
}

int CIM_ConcreteJob_InstAgent_UpdateInstallStatus(int i32JobId, UINT16 u16JobState, UINT16 u16OperationalStatus, UINT16 u16JobStatus)
{
    int iResult = -1;

    logTraceCIM(LOG_LEV_DEBUG, "%s()- job %d set state to %d, operational status to 0x%04x, Status code to %d.",
        __FUNCTION__, i32JobId, u16JobState, u16OperationalStatus, u16JobStatus);

    iResult = clp_JobUpdateInstallStatus(i32JobId, u16JobState, u16OperationalStatus, u16JobStatus);

    return (iResult);
}


UINT8 * CIM_ConcreteJob_InstAgent_GetOperationalStatus(UINT16 u16JobState)
{
    UINT8 *pu8Ret = NULL;

    switch (u16JobState)
    {
        case JOBSTATE_NEW:
	    	pu8Ret = (UINT8 *) "15";    //Dormant
		    break;
    	case JOBSTATE_RUNNIG:
		    pu8Ret = (UINT8 *) "2";     //OK
    		break;
	    case JOBSTATE_COMPLETED:
	    	pu8Ret = (UINT8 *) "2,17";  //OK, Completed
		    break;
        case JOBSTATE_TERMINATED:
		    pu8Ret = (UINT8 *) "10";    //Stopped
    		break;
	    case JOBSTATE_KILLED:
	    	pu8Ret = (UINT8 *) "6";     //Error
		    break;
    	case JOBSTATE_EXCEPTION:
		    pu8Ret = (UINT8 *) "6,17";  //Error, Completed
    		break;
    	case JOBSTATE_COMPLETED_WITHERROR:
		    pu8Ret = (UINT8 *) "32769";
    		break;
        case JOBSTATE_ADAPTER_PARTIAL_SUCC:
            pu8Ret = (UINT8 *) "6,17";
            break;
        case JOBSTATE_ADAPTER_ALL_SUCC:
            pu8Ret = (UINT8 *) "2,17";
            break;
	    default:
	    	pu8Ret = (UINT8 *) "0";
		    break;
    }

    return (pu8Ret);
}




int CIM_ConcreteJob_InstAgent_NewGetAllJobData(
                                              CLPShareJobData *psCLPSharedJobData,
	                                          AgentData_CLPJob *psOutput 
										    )
{
    int iCount = 0;
    int i;
    CLPJobData *psCLPJobData = NULL;
    CLPJobData *ptr = NULL;
    AgentData_CLPJob *psJobData = psOutput;
    int iSeq = 0;
    int iStatus = 0;
    int iPowerOnScheduleState = 0;
    
    if(psCLPSharedJobData == NULL || psJobData == NULL)
    {
        printf("NULL");
        return 0;
    }
    psCLPJobData = (CLPJobData *) psCLPSharedJobData->auJobData;

    iPowerOnScheduleState = IsCreatePowerOnScheduleJob();
    if (iPowerOnScheduleState > 0)
    {
        snprintf((char *) psJobData->u8pID, sizeof(psJobData->u8pID), POWER_ON_SCHEDULE);
        psJobData->bDeleteOnCompletion = TRUE;
        psJobData->u32TimeBeforeRemoval = 300 * 1000000;    //5min
        if (1 == iPowerOnScheduleState)
        {
            psJobData->u16JobState = JOBSTATE_NEW;
        }
        else if (2 == iPowerOnScheduleState)
        {
            psJobData->u16JobState = JOBSTATE_COMPLETED;
        }
            
        psJobData++;
        iCount++;
    }
    
    for (i = 0; i < MAX_JOB_NUM; i++)
    {
        ptr = (CLPJobData *) psCLPJobData + i;

        if (ptr->ullTimeLastModify != 0)
        {
            if(ptr->bIsUpdateJob)
            {
                snprintf((char *)psJobData->u8pID, sizeof(psJobData->u8pID), "_%s%d", CIM_SoftwareUpdate_Instance_Name, i + 1);
                psJobData->u16OperationalStatus = ptr->u16OperationalStatus;
                psJobData->u16JobStatusCode = ptr->u16JobStatusCode;
                logTraceCIM(LOG_LEV_ERROR, "%s()- Initiate  update job %s from stat %d -OpStatus %d- status %d - IsUpdate %d", __FUNCTION__, psJobData->u8pID,
                    ptr->u16JobState, ptr->u16OperationalStatus, ptr->u16JobStatusCode, ptr->bIsUpdateJob);
            }
            else
                snprintf((char *)psJobData->u8pID, sizeof(psJobData->u8pID), "%d", i + 1);

            psJobData->bDeleteOnCompletion = ptr->bDeleteOnCompletion;
            psJobData->u16JobState = ptr->u16JobState;
            psJobData->u32TimeBeforeRemoval = ptr->ullTimeBeforeRemoval;
            
            psJobData++;
            iCount++;
        }      
    }

    logTraceCIM(LOG_LEV_DEBUG, "%s()- sysprof jobs", __FUNCTION__);
	for (i=0; i<MAX_SYSPROF_JOBS; i++) 
	{

        logTraceCIM(LOG_LEV_DEBUG, "%s()- %d: %s", __FUNCTION__, i, sysprof_aim_seq[i]);
        if (!aim_config_get_int((char *)sysprof_aim_seq[i],(int *) &iSeq))
            continue;
        if (iSeq == SYSPROF_NOJOB_SEQ)
            continue;
        if (!aim_config_get_int((char *)sysprof_aim_status[i],(int *) &iStatus))
            continue;

		snprintf((char *)psJobData->u8pID, sizeof(psJobData->u8pID), "SYSPROF-%x", iSeq);  //the job instances for system profiles
		psJobData->bDeleteOnCompletion=FALSE;
		if (i == 0) 
		{
			if (iStatus == SYSPROF_CLI_OK)
			{
				psJobData->u16JobState = JOBSTATE_COMPLETED;
			}
			else if (iStatus == SYSPROF_TASK_RUNNING)
			{
				psJobData->u16JobState = JOBSTATE_RUNNIG;
			}
			else if (iStatus >= SYSPROF_LDAP_INIT_FAIL && iStatus <= SYSPROF_LDAP_RS_PROFILE_FAIL)
			{
				psJobData->u16JobState = JOBSTATE_LDAP_ERROR;
			}
			else
			{
				psJobData->u16JobState = JOBSTATE_COMPLETED_WITHERROR;
			}	
		}
		else
		{
			if (iStatus == SYSPROF_CLI_OK)
			{
				psJobData->u16JobState = JOBSTATE_COMPLETED;
			}
			else if (iStatus >= SYSPROF_LDAP_INIT_FAIL && iStatus <= SYSPROF_LDAP_RS_PROFILE_FAIL)
			{
				psJobData->u16JobState = JOBSTATE_LDAP_ERROR;
			}
			else
			{
				psJobData->u16JobState = JOBSTATE_COMPLETED_WITHERROR;
			}
		}
		psJobData->u32TimeBeforeRemoval = 0;

		psJobData++;
		iCount++;
	}
    return iCount;

}



UINT32 CIM_ConcreteJob_InstAgent_GetMaxIndex(void *pAgentDataPtr)
{
    UINT32 u32MaxIndex = INSTANCE_INDEX_INVALID;
    sCLPJobs *psAgentData = (sCLPJobs *) pAgentDataPtr;
    
    if (psAgentData != NULL)
    {
        if (psAgentData->nCurrJobNum > 0)
        {
            u32MaxIndex = psAgentData->nCurrJobNum - 1;
        }
    }
    
    return (u32MaxIndex);
}

UINT32 CIM_ConcreteJob_InstAgent_GetNext( 
                                          UINT32 u32CurrIndex,
                                          void *pAgentDataPtr)
{
    UINT32 u32NextIndex = 0;
    UINT32 u32MaxIndex = 0;

#if CIM_CONCRETEJOB_INIT_SUPPORT
    if (pAgentDataPtr == NULL)
    {
        return (INSTANCE_INDEX_INVALID);
    }
#endif

    u32MaxIndex = CIM_ConcreteJob_InstAgent_GetMaxIndex(pAgentDataPtr);

    if (INSTANCE_INDEX_INVALID == u32CurrIndex && (INSTANCE_INDEX_INVALID != u32MaxIndex))
    {
        /* return first instance's index */
        u32NextIndex = 0;
    }
    else if (u32CurrIndex >= u32MaxIndex)
    {
        /* no more instances */
        u32NextIndex = INSTANCE_INDEX_END;
    }
    else
    {
        u32NextIndex = u32CurrIndex + 1;
    }

    return (u32NextIndex);
}

void *CIM_ConcreteJob_InstAgent_GetProperty( 
                                             UINT32 u32InstanceIndex,
                                             UINT32 u32PropertyID,
                                             UINT32 *pu32Type,
                                             void *pAgentDataPtr)
{
    void *pValue = NULL;
    UINT8 au8Buffer[128] = {0};
    AgentData_CLPJob *pJobData;
    sCLPJobs *psAgentData = (sCLPJobs *) pAgentDataPtr;
    char szFilePath[128] = {0};
	
    if (pu32Type == NULL)
    {
        return (NULL);
    }

    /* default value for pu32Type and pValue */
    *pu32Type = AGENT_INVALID_TYPE;

    if (psAgentData == NULL)
    {
        return (NULL);
    }

    if (psAgentData->nCurrJobNum < (int) (u32InstanceIndex + 1))
    {
        /* invalid CLP Job ID */
        return (NULL);
    }

    pJobData = psAgentData->psData;
    pJobData += u32InstanceIndex;

    switch (u32PropertyID)
    {
        case CIM_CONCRETEJOB_INSTANCEID:
            *pu32Type = AGENT_CHARS;
    		memset(au8Buffer, 0, sizeof(au8Buffer));
            
            if (0 == strcmp((char *) pJobData->u8pID, POWER_ON_SCHEDULE))
            {
                snprintf((char *) au8Buffer, sizeof(au8Buffer), "CIM:%s", POWER_ON_SCHEDULE);
            }            
        	else if (strstr((char*) pJobData->u8pID, "SYSPROF") == NULL)
        	{
        		snprintf((char*)au8Buffer, sizeof(au8Buffer), "%s%s",GET_STRING_PTR(IDS_CIM_CONCRETEJOB_INSTANCEID), pJobData->u8pID);
        	}
        	else 
        	{
        		snprintf((char*)au8Buffer, sizeof(au8Buffer), "%s", pJobData->u8pID);
        	}
            pValue = (void *) Strdup((char *)au8Buffer);
            break;

        case CIM_CONCRETEJOB_DELETEONCOMPLETION:
            *pu32Type = AGENT_BOOLEAN;
            pValue = (void *)(UINT32) pJobData->bDeleteOnCompletion;
            break;

        case CIM_CONCRETEJOB_ELEMENTNAME:
            *pu32Type = AGENT_CHARS;
			memset(au8Buffer, 0, sizeof(au8Buffer));
            
            if (0 == strcmp((char *) pJobData->u8pID, POWER_ON_SCHEDULE))
            {
                snprintf((char *) au8Buffer, sizeof(au8Buffer), POWER_ON_SCHEDULE);
            }
        	else if (strstr((char*) pJobData->u8pID, "SYSPROF") == NULL)
        	{
        		snprintf((char*)au8Buffer, sizeof(au8Buffer), "%s%s",GET_STRING_PTR(IDS_CIM_CONCRETEJOB_ELEMENTNAME), pJobData->u8pID);
        	}
        	else
        	{
        		snprintf((char*)au8Buffer, sizeof(au8Buffer), "%s", pJobData->u8pID);
        	}
            pValue = (void *) Strdup((char *)au8Buffer);
            break;

        case CIM_CONCRETEJOB_ERRORDESCRIPTION:
			
	    pValue = NULL;  
	            
	    /* not system profiles job instance */
	    if (strstr((char*) pJobData->u8pID, "SYSPROF") == NULL) 
	    {
	        break;
	    }

           if (NULL == getStatusFilePath(pJobData->u8pID, szFilePath, sizeof(szFilePath)))
           {
               break;
           }
	    
           pValue = (void *)getStatusFileContent(szFilePath);

	    if (pValue != NULL)
	    {
	        *pu32Type = AGENT_CHARS;
	    }
	
            break;

        case CIM_CONCRETEJOB_JOBSTATE:
            *pu32Type = AGENT_UINT16;
            pValue = (void *)(UINT32) pJobData->u16JobState;
            break;

        case CIM_CONCRETEJOB_JOBSTATUS:
            if(strstr((char*)pJobData->u8pID, CIM_SoftwareUpdate_Instance_Name))
            {
                memset(au8Buffer, 0, sizeof(au8Buffer));
                if (pJobData->u16JobState == JOBSTATE_RUNNIG)
                {
                    if(pJobData->u16OperationalStatus == 0x8002)
                        snprintf((char *) au8Buffer, sizeof(au8Buffer), "%s [%2d]%%", GetUpdateJobStatusDescription(CLP_STATUS_DOWNLADING), pJobData->u16JobStatusCode);
                    else if(pJobData->u16OperationalStatus == 0x8003)
                        snprintf((char *) au8Buffer, sizeof(au8Buffer), "%s [%2d]%%", GetUpdateJobStatusDescription(CLP_STATUS_UPDATE), pJobData->u16JobStatusCode);
                }
                else if ((pJobData->u16JobState == JOBSTATE_COMPLETED) || (pJobData->u16JobState == JOBSTATE_EXCEPTION))
                        snprintf((char *) au8Buffer, sizeof(au8Buffer), "%s", GetUpdateJobStatusDescription(pJobData->u16JobStatusCode));

                if(au8Buffer[0])
                {
                     pValue = (void *) Strdup((char*)au8Buffer);
                    *pu32Type = AGENT_CHARS;
                }

            }

            break;

        case CIM_CONCRETEJOB_OPERATIONALSTATUS:
            *pu32Type = AGENT_sLIST_UINT16;
            if(strstr((char*)pJobData->u8pID, CIM_SoftwareUpdate_Instance_Name))
            {
                memset(au8Buffer, 0, sizeof(au8Buffer));
                snprintf((char *) au8Buffer, sizeof(au8Buffer), "%d",  pJobData->u16OperationalStatus);
                pValue = (void *) CIMAgentUtil_ParseINTsTosList(au8Buffer);
            }
            else
                pValue = (void *) CIMAgentUtil_ParseINTsTosList(CIM_ConcreteJob_InstAgent_GetOperationalStatus(pJobData->u16JobState));
            break;
            
        case CIM_CONCRETEJOB_STATUSDESCRIPTIONS:
            if(strstr((char*)pJobData->u8pID, CIM_SoftwareUpdate_Instance_Name))
            {
                if ((pJobData->u16JobState == JOBSTATE_EXCEPTION) && ((pJobData->u16OperationalStatus & 0xFF00) == 0x8100))     //FMAPI error, to get FM error description
                {
                    FMGetErrorStringByErrorCode(pJobData->u16OperationalStatus&0xff, (char*)au8Buffer, sizeof(au8Buffer));
                     pValue = (void *) CIMAgentUtil_ParseStringsTosList((UINT8 *)au8Buffer);
               }
            }

            if (NULL != pValue)
            {
                *pu32Type = AGENT_sLIST_CHARS;
            }
            break;

        case CIM_CONCRETEJOB_TIMEBEFOREREMOVAL:
            *pu32Type = AGENT_DateTime;
			pValue = (void *) CIMClassUtil_GenerateDateTimePTRFromBinary((UINT64)pJobData->u32TimeBeforeRemoval, TRUE);
            break;

        default:
            *pu32Type = AGENT_INVALID_TYPE;
            break;

    }

    return (pValue);
}

#if CIM_CONCRETEJOB_INIT_SUPPORT /* You can turn on this flag in CIM_ConcreteJobAgent.h */
/*
 * 0: Generate all properties
 * 1: Only generate key properties
 */
void *CIM_ConcreteJob_InstAgent_Init(BOOLEAN bOnlyKeyProperties)
{
    sCLPJobs *psAgentData = NULL;
    CLPShareJobData sSharedData;
    
    psAgentData = (sCLPJobs *) Malloc(sizeof(sCLPJobs));
    if (psAgentData == NULL)
    {
        return (NULL);
    }

    /* init value */
    psAgentData->nCurrJobNum = 0;
    psAgentData->fd = -1;
    psAgentData->ps_CLPJobData = NULL;
    psAgentData->psData = NULL;

    if (IsCleanSoftwareUpdaetRunningJobs())
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- System shall not have any running software update jobs!", __FUNCTION__);
        CleanAllSoftwareUpdaetRunningJobs();
    }

    /* The clp library (using shared memory) shall be only used by software update. This change is started from CQ XB251343 by discussing with Mike. */
    if (0 != clp_GetJobData(&sSharedData))
    {
        Free(psAgentData);
        return (NULL);
    }

//    printSharedJobData((CLPJobData *) &sSharedData.auJobData);
    
    psAgentData->psData 
    = (AgentData_CLPJob *) Malloc(sizeof (AgentData_CLPJob) * (MAX_JOB_NUM + 1 + MAX_SYSPROF_JOBS));
    if(psAgentData->psData == NULL)
    {
        return (psAgentData);
    }

    psAgentData->nCurrJobNum = CIM_ConcreteJob_InstAgent_NewGetAllJobData((CLPShareJobData *) &sSharedData, psAgentData->psData);
    
    //printf("psAgentData->nCurrJobNum %d\n", psAgentData->nCurrJobNum);
//    int ret = munmap(ps_CLPSessionData,  sizeof(newCLPSession_data) * MAX_SESSION_NUM);
    return ((void *) psAgentData);

}

void CIM_ConcreteJob_InstAgent_Destroy(void *pAgentDataPtr)
{

    sCLPJobs *psAgentData = (sCLPJobs *) pAgentDataPtr;    
    if (psAgentData != NULL)
    {
        if(psAgentData->ps_CLPJobData != NULL)
        {
            Free(psAgentData->ps_CLPJobData);
        }

        if (psAgentData->psData != NULL)
        {
            Free(psAgentData->psData);
        }
        Free(psAgentData);
    }
}
#endif

CMPIUint32 CIM_ConcreteJob_InstAgent_RequestStateChange(
                                                        void *pAgentDataPtr,
                                                        UINT32 u32InstanceIndex,
                                                        const CMPIArgs *in,
                                                        CMPIArgs *out)
{
    CMPIUint32 u32Ret = 0;  /* Success, 0 */
    UINT16 u16RequestedState = 0;     //= dataReq.value.uint16;

    CMPIEntryTraceLog(__FUNCTION__, in);

    if (pAgentDataPtr == NULL)
    {
        u32Ret = 2;
        logTraceCIM(LOG_LEV_WARNING, "%s()- Agent Data is NULL, return %d!", __FUNCTION__, u32Ret);
    }
    else
    {
        AgentData_CLPJob *psJobData = NULL;
        psJobData = ((sCLPJobs *) pAgentDataPtr)->psData + u32InstanceIndex;

        if (strcmp((char *) psJobData->u8pID, POWER_ON_SCHEDULE) != 0)
        {
            u32Ret = 4;
            logTraceCIM(LOG_LEV_WARNING, "%s()- Job(%s) does not support RequestStateChange(), return %d!", __FUNCTION__, (char *) psJobData->u8pID, u32Ret);
        }
        else
        {
            CMPIStatus rc =
            {
                CMPI_RC_ERR_FAILED,
                NULL
            };            
            /* Get parameter RequestedState */
            rc.rc = CIMAgentUtil_GetMethodParameterValue(in, "RequestedState", CMPI_uint16, &u16RequestedState, NULL, __FUNCTION__);
            if (rc.rc != CMPI_RC_OK)
            {
                u32Ret = 2;
                logTraceCIM(LOG_LEV_WARNING, "%s()- Failed to get input parameter (rc=%d)for %s!", __FUNCTION__, rc.rc, "RequestedState");
            }
            else
            {

                if (u16RequestedState != 5)
                {
                    u32Ret = 5;
                    logTraceCIM(LOG_LEV_WARNING, "%s()- u16RequestedState(%d) only support value 5, return %d!", __FUNCTION__, u16RequestedState, u32Ret);
                }
                else
                {
                    if (1 == IsCreatePowerOnScheduleJob())
                    {
                        bool bRet = FALSE;
                        bRet = aim_config_set_bool(POWER_SCHED_SPECIFIC_ON_ENABLE, FALSE, TRUE);
                        if (!bRet)
                        {
                            u32Ret = 2;
                            logTraceCIM(LOG_LEV_ERROR, "[%s] - Failed to call aim_config_set_bool(%s, %i), return %d.", __FUNCTION__, POWER_SCHED_SPECIFIC_ON_ENABLE, FALSE, u32Ret);
                        }
                    }
                    else
                    {
                        u32Ret = 4097;
                        logTraceCIM(LOG_LEV_WARNING, "%s()- Job state is not equal 2(New), return %d!", __FUNCTION__, u32Ret);
                    }
                }
            }
        }
    }
    
    return (u32Ret);
}

