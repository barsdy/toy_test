/**
 *<center>
 *               Avocent Corporation. Proprietary Information.
 * \n<em>
 *      This software is supplied under the terms of a license agreement or
 *      nondisclosure agreement with Avocent Corporation, or its subsidiary, and
 *      may not be copied, disseminated, or distributed except in accordance
 *      with the terms of that agreement.
 *
 *        Copyright &copy; 2010 Avocent Corporation. All rights reserved.
 *</em> </center>
**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <CMPIUtil.h>
#include <MemoryService.h>
#include <emerson/cemgr/swe_function_table.h>
#include "../class/incEX/CIM_SoftwareInstallationService.h"
#include "../class/incEX/IBM_PCIAdapterBundleSoftwareIdentity.h"
#include "incEX/CIM_SoftwareInstallationServiceAgent.h"
#include "incEX/CIM_SoftwareIdentityAgent.h"
#include "incEX/IBM_PCIAdapterBundleSoftwareIdentityAgent.h"
#include <AgentUtil.h>
#include <CMPIBroker.h>
#include <CMPITables.h>
#include <system-core/fmapi/fmapi.h>
#include "../StringRegisterTable.h"
#include <errno.h>

#include <emerson/pm/pm_lib.h>
#include <emerson/pm/pm_system.h>

#include "incEX/clpjob.h"
#include "LogUtil.h"
#include "MethodNames.h"

#include <emerson/filetrans/filetrans.h>
#include <emerson/filetrans/xferd.h>

#define MAX_DOWNLOAD_PENDING_SECONDS        (2*60)              // 2 minutes

extern const CMPIUint8 *CLASSNAME_CIM_ConcreteJob;
extern const CMPIUint8 *CLASSNAME_CIM_SoftwareIdentity;
extern const CMPIUint8 *CLASSNAME_Lenovo_ManagementController;
extern const CMPIUint8 *CLASSNAME_Lenovo_ComputerSystem;

extern const char *CIM_SoftwareUpdate_Instance_Name;
const char *CIM_SoftwareUpdate_Progress_File = "/tmp/cim_update_complete.txt";

extern int CIM_ConcreteJob_InstAgent_CreateJob();
extern int CIM_ConcreteJob_InstAgent_ChangeState(int i32JobId, UINT16 u16JobStatus);
extern void CleanAllSoftwareUpdaetRunningJobs();
extern int CIM_ConcreteJob_InstAgent_UpdateInstallStatus(int i32JobId, UINT16 u16JobState, UINT16 u16OperationalStatus, UINT16 u16JobStatus);

int AddObjectPath(CMPIArgs *out, int jobID);
int FolkToInstall(const CMPIContext *ctx, int i32JobID, char *pau8URI, char **ppau8Location, unsigned int uiCount, int i32Timeout,
                  const char* pau8firmwareType, const char* pau8firmwareOperation);

UINT32 CIM_SoftwareInstallationService_InstAgent_GetMaxIndex(void *pAgentDataPtr)
{
    return (0);
}

UINT32 CIM_SoftwareInstallationService_InstAgent_GetNext(
                                                          UINT32 u32CurrIndex,
                                                          void *pAgentDataPtr)
{
    UINT32 u32NextIndex = 0;
    UINT32 u32MaxIndex = 0;

#if CIM_SOFTWAREINSTALLATIONSERVICE_INIT_SUPPORT
    if (pAgentDataPtr == NULL)
    {
        return (INSTANCE_INDEX_INVALID);
    }
#endif

    u32MaxIndex = CIM_SoftwareInstallationService_InstAgent_GetMaxIndex(pAgentDataPtr);

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

void *CIM_SoftwareInstallationService_InstAgent_GetProperty(
                                                             UINT32 u32InstanceIndex,
                                                             UINT32 u32PropertyID,
                                                             UINT32 *pu32Type,
                                                             void *pAgentDataPtr)
{
    void *pValue = NULL;

    if (pu32Type == NULL)
    {
        return (NULL);
    }

    /* default value for pu32Type and pValue */
    *pu32Type = AGENT_INVALID_TYPE;

    switch (u32PropertyID)
    {
        case CIM_SOFTWAREINSTALLATIONSERVICE_NAME:
            *pu32Type = AGENT_CHARS;
            pValue = (void *) Strdup((char *)GET_STRING_PTR(IDS_CIM_SOFTWAREINSTALLATIONSERVICE_NAME));
            break;

        case CIM_SOFTWAREINSTALLATIONSERVICE_SYSTEMCREATIONCLASSNAME:
            *pu32Type = AGENT_CHARS;
            pValue = (void *) Strdup((char *)CIMClassUtil_GetBMCSystemCreationClassName());
            break;

        case CIM_SOFTWAREINSTALLATIONSERVICE_SYSTEMNAME:
            *pu32Type = AGENT_CHARS;
            pValue = (void *) Strdup((char *)CIMClassUtil_GetBMCSystemName());
            break;

        default:
            *pu32Type = AGENT_INVALID_TYPE;
            break;

    }
    return (pValue);
}

#if CIM_SOFTWAREINSTALLATIONSERVICE_INIT_SUPPORT /* You can turn on this flag in CIM_SoftwareInstallationServiceAgent.h */
/*
 * 0: Generate all properties
 * 1: Only generate key properties
 */
void *CIM_SoftwareInstallationService_InstAgent_Init(BOOLEAN bOnlyKeyProperties)
{
    /* Please write init memory space here */
    return ((void *) NULL);
}

void CIM_SoftwareInstallationService_InstAgent_Destroy(void *pAgentDataPtr)
{
    /* Please write destroy process here */
}
#endif


#define INTERNAL_SFTP_UPLOAD_FULLNAME "/pstorage/upload/imm-fw"
#define INTERNAL_SFTP_UPLOAD_PORTNUM  115

CMPIUint32 Lenovo_SoftwareInstallationService_InstAgent_RequestUpdate(
                                                                    const CMPIContext *ctx,
                                                                    UINT32 u32InstanceIndex,
                                                                    const CMPIArgs *in,
                                                                    CMPIArgs *out);
{
    char cUsername[64] = "";
    CMPIValue uCmpiFullname = {0};
    CMPIValue uCmpiPortnum = {0};
    CMPIStatus ret;

    memset(&ret, 0x00, sizeof(CMPIStatus));

    logTraceCIM(LOG_LEV_DEBUG, "[%s]Get into method RequestUpdate.", __FUNCTION__);

    CMPIGetUserNameFromContext(ctx, cUsername);
    if (0 != FMRegisterUser("CIM", cUsername, NULL))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- FMRegisterUser() returned Error.", __FUNCTION__);
        return 3;
    }

    uCmpiFullname.string = GET_BROKER_EFT->newString(GET_BROKER_PTR, (char *)(INTERNAL_SFTP_UPLOAD_FULLNAME), &ret);
    if (!uCmpiFullname.string)
    {
        logTraceCIM(LOG_LEV_ERROR, "[%s]Failed to call newString() for fullname, rc: %d.", __FUNCTION__,  rc.rc);
        return 2;
    }
    out->ft->addArg(out, "Fullname", &uCmpiFullname, CMPI_string);
    uCmpiFullname.string->ft->release(uCmpiFullname.string);

    uCmpiPortnum.uint16 = INTERNAL_SFTP_UPLOAD_PORTNUM;
    out->ft->addArg(out, "Port", &uCmpiPortnum, CMPI_uint16);

    logTraceCIM(LOG_LEV_DEBUG, "[%s]Success execute method RequestUpdate.", __FUNCTION__);

    return 0;
}


#define INSTALL_ONE_FW_TO_ALL_ADAPTERS "None"
#define PLDM_INSTANCEID_PREFIX "PCIAdapterBundleSW_"
CMPIUint32 CIM_SoftwareInstallationService_InstAgent_InstallFromURI(
                                                                    const CMPIContext *ctx,
                                                                    UINT32 u32InstanceIndex,
                                                                    const CMPIArgs *in,
                                                                    CMPIArgs *out)
{
    CMPIUint32 u32Ret = 2;  /*  Error occurred, 2 */
    CMPIStatus rc;
    CMPIObjectPath *pRefObj = NULL;
    UINT16 u16InstallOption = 0;
    char *szURI = NULL;
    unsigned int uiSize = 0;
    unsigned int uiStrArrayCount = 0;
    UINT32 u32Index = 0;
    SoftwareIdentity_AgentData *pInitAgentData = NULL;
    SoftwareIdentity_Data *pData = NULL;
    UINT8 au8FirmwareType[FIRMWARE_TYPE_SIZE] = {0};
    UINT8 au8UpdateOperation[FIRMWARE_UPDATE_OPT_SIZE] = {0};
    INT32 i32JobID = -1;
    UINT16 *pu16Content = NULL;
    unsigned int uiArrSize = 0;
    char *szName = NULL;
    char **ppStrLocation = NULL;

    //When you release the code, don't invoke CMPIEntryTraceLog() here, URI may include the user password and be displayed at debug console.
    //CMPIEntryTraceLog(__FUNCTION__, in);

    /* get parameter InstallOptions */
    rc.rc = CIMAgentUtil_GetMethodParameterValue(in, PARAMNAME_InstallOptions, CMPI_uint16A, &pu16Content, &uiArrSize, __FUNCTION__);
    if (rc.rc != CMPI_RC_OK)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get parameter(%s), return code is %d.", __FUNCTION__, PARAMNAME_InstallOptions, rc.rc);
        goto ERR_EXIT;
    }

    if (uiArrSize > 0)
    {
        u16InstallOption = pu16Content[0]; 
    }
    else
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Element size of parameter(%s) is incorrect(%d).", __FUNCTION__, PARAMNAME_InstallOptions, uiArrSize);
        CIMAgentUtil_FreeArray(PARAMNAME_InstallOptions, CMPI_uint16, pu16Content, uiArrSize, __FUNCTION__);
        goto ERR_EXIT;
    }
    CIMAgentUtil_FreeArray(PARAMNAME_InstallOptions, CMPI_uint16, pu16Content, uiArrSize, __FUNCTION__);

    if ((u16InstallOption != 4) && (u16InstallOption != 0x8000) && (u16InstallOption != 0x8100))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Install option(%d) is not supported.", __FUNCTION__, u16InstallOption);
        u32Ret = 1; //Method is not supported in the implementation., 1
        goto ERR_EXIT;
    }

    if (u16InstallOption == 0x8000)
    {
        UINT8 u8Support = 0;

        if (agentless_get_supported_status(&u8Support, AGENTLESS_OOB_FW_UPDATE) == 0)
        {
            if (u8Support == 0)
            {
                logTraceCIM(LOG_LEV_ERROR, "%s() - Do not support Agentless OOB Firmware update!", __FUNCTION__);
                goto ERR_EXIT;
            }
        }
        else
        {
            logTraceCIM(LOG_LEV_ERROR, "%s() - cannot get support status!", __FUNCTION__);
            goto ERR_EXIT;
        }
    }

    /* get parameter InstallOptionsValues */
    uiStrArrayCount = 0;
    rc.rc = CIMAgentUtil_GetMethodParameterValue(in, PARAMNAME_InstallOptionsValues, CMPI_stringA, &ppStrLocation, &uiStrArrayCount, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get parameter(%s), return code is %d.", __FUNCTION__, PARAMNAME_InstallOptionsValues, rc.rc);
        goto ERR_EXIT;
    }
    else if (rc.rc == CMPI_RC_ERR_NO_SUCH_PROPERTY)
    {
        /* build an artificial ppStrLocation to indicate it's a pldm PCI firmware update */
        if (u16InstallOption == 0x8000)
        {
            logTraceCIM(LOG_LEV_WARNING, "%s()- Update pldm firmware, the install options values is not found, \
                    take as update one firmware to all adapters if applicable!", __FUNCTION__);
            uiStrArrayCount = 1;
            if ((ppStrLocation = Malloc(uiStrArrayCount * sizeof(char *))) == NULL)
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to malloc:[%s]", __FUNCTION__, strerror(errno));
                goto ERR_EXIT;
            }
            memset(ppStrLocation, 0x00, uiStrArrayCount * sizeof(char *));

            if ((ppStrLocation[0] = Malloc(strlen(INSTALL_ONE_FW_TO_ALL_ADAPTERS)+1)) == NULL)
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to malloc:[%s]", __FUNCTION__, strerror(errno));
                goto ERR_EXIT;
            }
            memset(ppStrLocation[0], 0x00, strlen(INSTALL_ONE_FW_TO_ALL_ADAPTERS)+1);
            snprintf(ppStrLocation[0], strlen(INSTALL_ONE_FW_TO_ALL_ADAPTERS)+1, "%s", INSTALL_ONE_FW_TO_ALL_ADAPTERS);
        }
    }

    /* get parameter URI */
    uiSize = 0;
    rc.rc = CIMAgentUtil_GetMethodParameterValue(in, PARAMNAME_URI, CMPI_string, &szURI, &uiSize, __FUNCTION__);
    if (((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY)) || \
            ((rc.rc == CMPI_RC_ERR_NO_SUCH_PROPERTY) && (u16InstallOption != 0x8100)))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get parameter(%s), return code is %d.", __FUNCTION__, PARAMNAME_URI, rc.rc);
        goto ERR_EXIT;
    }

    /* get parameter Target */
    rc.rc = CIMAgentUtil_GetMethodParameterValue(in, PARAMNAME_Target, CMPI_ref, &pRefObj, NULL, __FUNCTION__);
    if (CMPI_RC_OK == rc.rc)
    {
        if (CIMAgentUtil_CheckObjectPathClassName(pRefObj, (char *) CLASSNAME_CIM_SoftwareIdentity, __FUNCTION__))
        {
            szName = CIMAgentUtil_GetKeyValueToStringByKeyName(pRefObj, "InstanceID", __FUNCTION__);
            if (szName)
            {
                u32Index = atoi(((char *)szName) + strlen(INSTANCEID_PREFIX)) - 1;
                //logTraceCIM(LOG_LEV_INFO, "%s()- szName index is : %d.", __FUNCTION__, u32Index);
                pInitAgentData = (SoftwareIdentity_AgentData *) CIM_SoftwareIdentity_InstAgent_Init(FALSE);
                if (pInitAgentData != NULL)
                {
                    if (u32Index >= pInitAgentData->u8Count)
                    {
                        logTraceCIM(LOG_LEV_ERROR, "%s()- CIM_SoftwareIdentity is out of coundary...", __FUNCTION__);
                        goto ERR_EXIT;
                    }
                    pData = pInitAgentData->pData + u32Index;
                    snprintf((char *)au8FirmwareType, sizeof(au8FirmwareType), "%s", pData->au8FirmwareType);
                    snprintf((char *)au8UpdateOperation, sizeof(au8UpdateOperation), "%s", pData->au8UpdateOperation);
                    CIM_SoftwareIdentity_InstAgent_Destroy((void *) pInitAgentData);
                }
                else
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call CIM_SoftwareIdentity_InstAgent_Init().", __FUNCTION__);
                    goto ERR_EXIT;
                }
            }
            else
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get the key(%s) of paramater(%s) in Class(%s).", __FUNCTION__, "InstanceID", PARAMNAME_Target, (char *) CLASSNAME_CIM_SoftwareIdentity);
                goto ERR_EXIT;
            }
        }
        else if (CIMAgentUtil_CheckObjectPathClassName(pRefObj, (char *) CLASSNAME_Lenovo_ManagementController, __FUNCTION__)) 
        {
            szName = CIMAgentUtil_GetKeyValueToStringByKeyName(pRefObj, "CreationClassName", __FUNCTION__);
            if (szName)
            {
                if (strcmp(szName, (char *) CLASSNAME_Lenovo_ManagementController))
                { 
                    logTraceCIM(LOG_LEV_ERROR, "%s()- %s of paramater(%s) is %s, and not match with %s.", __FUNCTION__, "CreationClassName", PARAMNAME_Target, szName, (char *) CLASSNAME_Lenovo_ManagementController);
                    goto ERR_EXIT;
                }
            }
            else
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get the key(%s) of paramater(%s) in Class(%s).", __FUNCTION__, "CreationClassName", PARAMNAME_Target, (char *) CLASSNAME_Lenovo_ManagementController);
                goto ERR_EXIT;
            }
            
            ExistFree(szName);

            szName = CIMAgentUtil_GetKeyValueToStringByKeyName(pRefObj, "Name", __FUNCTION__);
            if (szName)
            {
                if (strcmp(szName, (char *) CIMClassUtil_GetBMCSystemName()))
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- %s of paramater(%s) is %s, and not match with %s.", __FUNCTION__, "Name", PARAMNAME_Target, szName, (char *) CIMClassUtil_GetBMCSystemName());
                    goto ERR_EXIT;
                }
            }
            else
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get the key(%s) of paramater(%s) in Class(%s).", __FUNCTION__, "Name", PARAMNAME_Target, (char *) CLASSNAME_Lenovo_ManagementController);
                goto ERR_EXIT;
            }

            // imm primary
            snprintf((char *)au8FirmwareType, sizeof(au8FirmwareType) - 1, "%s", "sp");
            snprintf((char *)au8UpdateOperation, sizeof(au8UpdateOperation) - 1, "%s", "primary");
        }
        else if (CIMAgentUtil_CheckObjectPathClassName(pRefObj, (char *) CLASSNAME_Lenovo_ComputerSystem, __FUNCTION__)) 
        {
            szName = CIMAgentUtil_GetKeyValueToStringByKeyName(pRefObj, "CreationClassName", __FUNCTION__);
            if (szName)
            {
                if (strcmp(szName, (char *) CLASSNAME_Lenovo_ComputerSystem))
                { 
                    logTraceCIM(LOG_LEV_ERROR, "%s()- %s of paramater(%s) is %s, and not match with %s.", __FUNCTION__, "CreationClassName", PARAMNAME_Target, szName, (char *) CLASSNAME_Lenovo_ComputerSystem);
                    goto ERR_EXIT;
                }
            }
            else
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get the key(%s) of paramater(%s) in Class(%s).", __FUNCTION__, "CreationClassName", PARAMNAME_Target, (char *) CLASSNAME_Lenovo_ComputerSystem);
                goto ERR_EXIT;
            }
            
            ExistFree(szName);

            szName = CIMAgentUtil_GetKeyValueToStringByKeyName(pRefObj, "Name", __FUNCTION__);
            if (szName)
            {
                if (strcmp(szName, (char *) CIMClassUtil_GetSystemName()))
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- %s of paramater(%s) is %s, and not match with %s.", __FUNCTION__, "Name", PARAMNAME_Target, szName, (char *) CIMClassUtil_GetSystemName());
                    goto ERR_EXIT;
                }
            }
            else
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get the key(%s) of paramater(%s) in Class(%s).", __FUNCTION__, "Name", PARAMNAME_Target, (char *) CLASSNAME_Lenovo_ManagementController);
                goto ERR_EXIT;
            }

            if (ppStrLocation == NULL)
            {
                // uefi/dsa, primary
                snprintf((char *)au8FirmwareType, sizeof(au8FirmwareType) - 1, "%s", "host");
                snprintf((char *)au8UpdateOperation, sizeof(au8UpdateOperation) - 1, "%s", "primary");
            }
            else
            {
                /* pldm - update all adapters firmware if applicable */
                snprintf((char *)au8FirmwareType, sizeof(au8FirmwareType), "%s", "pldm");
                /* pldm no need to set update operation */
            }
        }
        else if (CIMAgentUtil_CheckObjectPathClassName(pRefObj, (char *) CLASSNAME_Lenovo_PCIAdapterBundleSoftwareIdentity, __FUNCTION__)) 
        {
            if (!strcmp(ppStrLocation[0],INSTALL_ONE_FW_TO_ALL_ADAPTERS))
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Target:[%s] MUST set InstallValuesOptions by user", __FUNCTION__, pRefObj);
                goto ERR_EXIT;
            }

            szName = CIMAgentUtil_GetKeyValueToStringByKeyName(pRefObj, "InstanceID", __FUNCTION__);
            if (szName)
            {
                int iPldmIndex = -1;
                PCIAdapterBundleSoftwareIdentity_AgentData *pPldmInitAgentData = NULL;
                sscanf(szName + strlen(PLDM_INSTANCEID_PREFIX), "%d", &iPldmIndex);
                if (iPldmIndex < 0)
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- Error format of Instance ID: [%s]", __FUNCTION__, szName);
                    goto ERR_EXIT;
                }
                pPldmInitAgentData = (PCIAdapterBundleSoftwareIdentity_AgentData *)IBM_PCIAdapterBundleSoftwareIdentity_InstAgent_Init(FALSE);
                if (pPldmInitAgentData != NULL)
                {
                    if (iPldmIndex >= pPldmInitAgentData->u8Count)
                    {
                        logTraceCIM(LOG_LEV_ERROR, "%s()- Index:[%d] is out of PCIAdapterBundleSoftwareIndentity coundary[%d]...", \
                                __FUNCTION__, iPldmIndex, pPldmInitAgentData->u8Count);
                        goto ERR_EXIT;
                    }
                    IBM_PCIAdapterBundleSoftwareIdentity_InstAgent_Destroy((void *) pPldmInitAgentData);
                }
                else
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call IBM_PCIAdapterBundleSoftwareIdentity_InstAgent_Init().", __FUNCTION__);
                    goto ERR_EXIT;
                }
            }
            else
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get the key(%s) of paramater(%s) in Class(%s).", __FUNCTION__, "InstanceID", PARAMNAME_Target, (char *) CLASSNAME_Lenovo_PCIAdapterBundleSoftwareIdentity);
                goto ERR_EXIT;
            }

            /* pldm - update one/mutli adapter(s) firmware */
            snprintf((char *)au8FirmwareType, sizeof(au8FirmwareType), "%s", "pldm");
            /* pldm no need to set update operation */
        }
        else
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Get unkown target class: %s", __FUNCTION__, pRefObj);
            goto ERR_EXIT;
        }
    }
    else
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get parameter(%s), return code is %d.", __FUNCTION__, PARAMNAME_Target, rc.rc);
        goto ERR_EXIT;
    }


    //logTraceCIM(LOG_LEV_INFO, "%s()- Firmware type is %s.", __FUNCTION__, au8FirmwareType);
    //logTraceCIM(LOG_LEV_INFO, "%s()- Update operation is %s.", __FUNCTION__, au8UpdateOperation);

    /* if possible, make sure no update is in progress */
    //u32Ret = 4096;    //Job started

    /* create job */
    i32JobID = CIM_ConcreteJob_InstAgent_CreateJob();
    if(-1 == i32JobID)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call CIM_ConcreteJob_InstAgent_CreateJob().", __FUNCTION__);
        goto ERR_EXIT;
    }

    /* create job object path */
    AddObjectPath(out, i32JobID);

    /* start a new process to update */
    // 1. imm2 primary
    // 2. imm2 backup
    // 3. bios primary
    // 4. bios backup
    // 5. dsa
    // 6. sp: imm2
    // 7. host: bios, dsa
    FolkToInstall(ctx, i32JobID, szURI, ppStrLocation, uiStrArrayCount, 18000, (char *)au8FirmwareType, (char *)au8UpdateOperation);

    u32Ret = 4096; //Job started

ERR_EXIT:

    CIMAgentUtil_FreeArray(PARAMNAME_InstallOptionsValues, CMPI_string, ppStrLocation, uiStrArrayCount, __FUNCTION__);

    ExistFree(szName);

    SafeCMRelease(pRefObj);

    ExistFree(szURI);
    
    return (u32Ret);
}

int AddObjectPath(CMPIArgs *out, int jobID)
{
    CMPIObjectPath *objectpath = NULL;
    CMPIStatus rc;
    CMPIValue value;
    char instanceID[32];

    if (out == NULL)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- out is NULL.", __FUNCTION__);
        return (-1);
    }

    objectpath = GET_BROKER_EFT->newObjectPath(GET_BROKER_PTR, "root/cimv2", (char *)CLASSNAME_CIM_ConcreteJob, &rc);
    
    if(objectpath == NULL)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Object path is NULL.", __FUNCTION__);
        return (-1);
    }
    else
	{
	    memset(instanceID, 0, sizeof(instanceID));
	    snprintf(instanceID, sizeof(instanceID), "CIM:job_%s%d", CIM_SoftwareUpdate_Instance_Name, jobID);

	    value.string = GET_BROKER_EFT->newString(GET_BROKER_PTR,instanceID,&rc);
	    if (value.string)
	    {
	        objectpath->ft->addKey(objectpath, "InstanceID", &value, CMPI_string);
	        value.string->ft->release(value.string);
	    }

	    value.ref = objectpath;
        out->ft->addArg(out, "Job", &value, CMPI_ref);

        SafeCMRelease(objectpath);
	}
	return 0;
}

//return: -1: parsed error state, should stop
//          0  : parse fail(file not exist,eg), should continue
//          1,2: parsed downloading progress, should continue
int  UpdateDownloadingProgress(int i32JobID, char type, const char *filename, int *perrno)
{
        int percent = 0;

        if(type & XFERD_BIT_TFTP)
        {
            if(!prepare_xfer_tftp_result(filename, '\r', '\n'))
            {
                if(parse_xfer_tftp_result(filename, &percent, perrno)<0)
                    return -1;
                else
                    return percent;
            }
            return 0;

        }
        else 
        {
            if(!prepare_xfer_sftp_result(filename, '\r', '\n'))
            {
                if(parse_xfer_sftp_result(filename, &percent, perrno)<0)
                    return -1;
                else
                    return percent;
            }
            return 0;

        }

}

#define PLDM_ADAPTER_ONBOARD_STRING "onboard"
#define PLDM_ADAPTER_ONBOARD_STRLEN 7
#define PLDM_ADAPTER_ADDON_STRING "addon"
#define PLDM_ADAPTER_ADDON_STRLEN 5

static int GetLocationSlotFromString(int *piLocation, int *piSlot, char *pLocStr)
{
    char *pWalker = pLocStr;

    /* update all adapters if applicable NO need to set location */
    if (!strcmp(pWalker, INSTALL_ONE_FW_TO_ALL_ADAPTERS))
    {
        *piLocation = -1;
        *piSlot = -1;
        return 0;
    }

    /* set location */
    if (!strncmp(pWalker,PLDM_ADAPTER_ONBOARD_STRING, PLDM_ADAPTER_ONBOARD_STRLEN)) 
    {
        *piLocation = 0;
        pWalker += PLDM_ADAPTER_ONBOARD_STRLEN;
    }
    else if (!strncmp(pWalker,PLDM_ADAPTER_ADDON_STRING, PLDM_ADAPTER_ADDON_STRLEN)) 
    {
        *piLocation = 1;
        pWalker += PLDM_ADAPTER_ADDON_STRLEN;
    }
    else
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Unkown Location String:[%s]", __FUNCTION__, *pLocStr);
        return -1;
    }

    /* set slot */
    pWalker++; /* skip '-' */
    *piSlot = -1;
    sscanf(pWalker, "%d", piSlot);
    if (*piSlot < 0)
    {
        *piLocation = -1;
        logTraceCIM(LOG_LEV_ERROR, "%s()- Bad Location-Slot format: [%s]", __FUNCTION__, *pLocStr);
        return -1;
    }

    return 0;
}

#define PORT_LENGTH    16
int ExecuteSoftwareUpdateInstallFromInternal(const CMPIContext *ctx,
                                           int i32JobID,
                                           char *pau8URI,
                                           char **ppau8Location,
                                           unsigned int uiCount,
                                           int i32Timeout,
                                           const char* pau8firmwareType,
                                           const char* pau8firmwareOperation)
{
    UINT32 u32Return_code = 0;
    UINT32 u32PID = 0;
    sSwMsg_McFlashCfg flash_cfg = { 0 };
    struct xferd_request sRequest = { 0 };
    char type[32] = "web";
    char build_id[32] = { 0 };
    int iret=0;
    int iTimeout = i32Timeout/2;
    CLPInstallStatusCode status_code = CLP_STATUS_UNKNOWN_ERROR;
    unsigned short u16OperationalStatus = 0;
    unsigned long u32ErrorCode = 0;
    int i32Error = 0;
    char sSystemCmd[256] = {0};
    char w_interface[64] = {0};
    int port = 0;
    int lastProgress = 0;
    int pendingCount = 0;
    int FMPathLength = 0;
    int URILength = strlen(pau8URI);
    int tftpBuffSize = 0;
    int sftpBuffSize = 0;
    char * pFMPath = NULL;
    char * pCurlCmdBuff = NULL;
    bool bReturnAIM = false;
    int i = 0;
    bool bFlushSuccess = false;

    /* Notice: Only invoking FMCancel() when calling FMRequestSpace() failed or downloading file failed. */
    
    bReturnAIM = aim_config_set_str(CIM_SOFTWARE_UPDATE_TYPE, type, false);
    if (!bReturnAIM)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(%s, %s).", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE, type);
        goto CANCEL_UPDATE_LABEL;
    }

    // Verify image file
    {
        char* str = FMVerifyImageFile(INTERNAL_SFTP_UPLOAD_FULLNAME);
        if (NULL == str)
        {
            FMGetLastError(&u32ErrorCode);
            u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
            status_code = CLP_STATUS_FMAPI_ERROR;
            logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to verity image file.", __FUNCTION__);
            CIMFree(pFMPath);
            goto RETURN_FAIL_LABEL;
        }
        else
        {
            CIMFree(pFMPath);
            pFMPath = strdup(str);
            free(str);
            // Out put look like "imm2_1AOO20A_56485_8.upd"
            logTraceCIM(LOG_LEV_DEBUG, "%s()- Output of FMVerifyImageFile() is build information = %s.", __FUNCTION__, pFMPath);
        }
    }

    // 4. Get firmware buildid and type & Verify
    memset(type, 0, sizeof(type));
    sscanf(pFMPath, "%[^_]_%[^_]_%*s", type, build_id);
    CIMFree(pFMPath);
    u32Return_code = FMVerifyImage(type, build_id);
    switch (u32Return_code)
    {
    case 0:
        logTraceCIM(LOG_LEV_DEBUG, "%s()- Verify success.", __FUNCTION__);
        break;
    case ENOENT:
    case EFAULT:
        FMGetLastError(&u32ErrorCode);
        u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
        status_code = CLP_STATUS_FMAPI_ERROR;
        logTraceCIM(LOG_LEV_ERROR, "%s()- Could not access firmware.", __FUNCTION__);
        goto RETURN_FAIL_LABEL;
    case EINVAL:
        FMGetLastError(&u32ErrorCode);
        u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
        status_code = CLP_STATUS_FMAPI_ERROR;
        logTraceCIM(LOG_LEV_ERROR, "%s()- Build_id is is not meant for the system.", __FUNCTION__);
        goto RETURN_FAIL_LABEL;
    default:
        FMGetLastError(&u32ErrorCode);
        u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
        status_code = CLP_STATUS_FMAPI_ERROR;
        logTraceCIM(LOG_LEV_ERROR, "%s()- Unknown error.", __FUNCTION__);
        goto RETURN_FAIL_LABEL;
    }

    bReturnAIM = aim_config_set_str(CIM_SOFTWARE_UPDATE_TYPE, type, false);
    if (!bReturnAIM)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(%s, %s).", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE, type);
        goto CANCEL_UPDATE_LABEL;
    }

    if (!strcmp(pau8firmwareType, "sp"))
    {
        if (strcmp("imm2", type))
        {
            status_code = CLP_STATUS_PKG_MISMATCH;
            logTraceCIM(LOG_LEV_ERROR, "%s()- File type %s is not match %s. Abort!", __FUNCTION__, type, pau8firmwareType);
            goto CANCEL_UPDATE_LABEL;
        }
    }
    else if (!strcmp(pau8firmwareType, "host"))
    {
        if (!strcmp("imm2", type))
        {
            status_code = CLP_STATUS_PKG_MISMATCH;
            logTraceCIM(LOG_LEV_ERROR, "%s()- File type %s is not match %s. Abort!", __FUNCTION__, type, pau8firmwareType);
            goto CANCEL_UPDATE_LABEL;
        }
    }
    else
    {
        if (strcmp(pau8firmwareType, type))
        {
            if(!strcmp(pau8firmwareType, "bios") && !strcmp(type, "uefi"))
            {
                logTraceCIM(LOG_LEV_DEBUG, "%s()- bios and uefi should be identical.", __FUNCTION__);
            }
            else
            {
                status_code = CLP_STATUS_PKG_MISMATCH;
                logTraceCIM(LOG_LEV_ERROR, "%s()- File type %s is not match %s. Abort!", __FUNCTION__, type, pau8firmwareType);
                goto CANCEL_UPDATE_LABEL;
            }
        }
    }

    /* check consistency between target and firmware type */
    if (ppau8Location == NULL)
    {
        /* target: imm2, uefi or dsa */
        if (strcmp(pau8firmwareType, "imm2") && strcmp(pau8firmwareType, "uefi") && \
                strcmp(pau8firmwareType, "bios") && strcmp(pau8firmwareType, "dsa"))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Non-consistency checked! Firmware type:[%s].", \
                    __FUNCTION__, pau8firmwareType);
            goto CANCEL_UPDATE_LABEL;
        }
    }
    else
    {
        if (strcmp(pau8firmwareType, "pldm"))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Non-consistency checked! Firmware type:[%s].", \
                    __FUNCTION__, pau8firmwareType);
            goto CANCEL_UPDATE_LABEL;
        }
    }

    u16OperationalStatus = CLP_InstallJob_OpStatus_Update;
    status_code = 0;
    CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_RUNNIG, u16OperationalStatus, status_code);

    sleep(5);
    // pau8firmwareOperation
    /* pldm skip this step */
    if ((NULL == ppau8Location) && (0 == FMSetUpdateOperation(type, pau8firmwareOperation, 0)))
    {
        FMGetLastError(&u32ErrorCode);
        u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
        status_code = CLP_STATUS_FMAPI_ERROR;
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to setup firmware operation %s.", __FUNCTION__, pau8firmwareOperation);
        goto CANCEL_UPDATE_LABEL;
    }

    do{
        int iSlot = -1;
        int iLocation = -1;

        /* Get location and slot from ppau8Location. Once per call */
        if ((ppau8Location != NULL) && (GetLocationSlotFromString(&iLocation, &iSlot, ppau8Location[i]) < 0))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Get Location fail!location:[%d], slot:[%d], loc string:[%s].", \
                    __FUNCTION__, iLocation, iSlot, ppau8Location[i]);
            status_code = CLP_STATUS_FMAPI_ERROR;
            u16OperationalStatus = CLP_InstallJob_OpStatus_FMError;
            goto CANCEL_UPDATE_LABEL;
        }

        if (ppau8Location != NULL)
            logTraceCIM(LOG_LEV_DEBUG, "%s()- Get Location! location:[%d], slot:[%d], loc string:[%s].", \
                    __FUNCTION__, iLocation, iSlot, ppau8Location[i]);

        if ((iSlot >= 0) && (iLocation >= 0))
        {
            if (FMSelectAdapter(iSlot, iLocation) != 0)
            {
                FMGetLastError(&u32ErrorCode);
                logTraceCIM(LOG_LEV_ERROR, "%s()- FMSelectAdapater fail on: Location[%d] Slot[%d], Error code:[%d]", \
                        __FUNCTION__, iLocation, iSlot, u32ErrorCode);
                u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
                status_code = CLP_STATUS_FMAPI_ERROR;
                goto CANCEL_UPDATE_LABEL;
            }
        }
        else
        {
            /* core firmware update or update one pldm firmware if it's applicable. */
            logTraceCIM(LOG_LEV_DEBUG, "%s()- prepare set i-[%d] to uiCount-[%d]", __FUNCTION__, i, uiCount);
            i = uiCount;
        }

        logTraceCIM(LOG_LEV_ERROR, "%s()- Ok, let call FMBeginUpdate()\n", __FUNCTION__);
        if ((u32PID = FMBeginUpdate(type,0)) == 0)
        {
            FMGetLastError(&u32ErrorCode);
            u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
            status_code = CLP_STATUS_FMAPI_ERROR;
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call FMBeginUpdate(). Error code:[%d]", __FUNCTION__, u32ErrorCode);
            goto RETURN_FAIL_LABEL;
        }

        /* get updating status */
        i32Timeout /= 2;
        while(i32Timeout > 0)
        {
            u32Return_code = FMGetUpdateStatusByPid(u32PID);
            if(u32Return_code == 0)
            { /* update complete */
                bFlushSuccess = true;
                logTraceCIM(LOG_LEV_ERROR, "%s()- Success to update build for [%s:%s]!", __FUNCTION__, type, pau8firmwareOperation);
                break;
            }
            else if (u32Return_code & 0xC0000000)
            { /* still updating, we don't show percentage, so we do nothing */
                logTraceCIM(LOG_LEV_DEBUG, "%s()- updating status (%u)\n", __FUNCTION__, u32Return_code & 0x000000FF);
                status_code = u32Return_code & 0x000000FF;
                CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_RUNNIG, u16OperationalStatus, status_code);
            }
            else
            { /* error occurs */
                FMGetLastError(&u32ErrorCode);
                status_code = CLP_STATUS_FMAPI_ERROR;
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed on FMGetUpdateStatusByPid(). Error code:[%d]", __FUNCTION__, u32ErrorCode);
                u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
                /* still finish all updates, then return fail */
                break;
            }
            sleep(1);
            i32Timeout--;
        }

        if (0 == i32Timeout)
        { //TIME OUT!!
            status_code = CLP_STATUS_UPDATE_TIMEOUT;
            FMGetLastError(&u32ErrorCode);
            logTraceCIM(LOG_LEV_ERROR, "%s()- Time out! Try to cancel %s firmware update! Error code:[%d]", __FUNCTION__, type, u32ErrorCode);
            goto RETURN_FAIL_LABEL;
        }

    } while (++i < uiCount);

    if (u32ErrorCode) 
    {
        goto RETURN_FAIL_LABEL;
    }

    if (unlink(INTERNAL_SFTP_UPLOAD_FULLNAME))
        logTraceCIM(LOG_LEV_WARNING,"%s() - Remove file: [%s] fail: [%s].", __FUNCTION__, INTERNAL_SFTP_UPLOAD_FULLNAME, strerror(errno));

    u16OperationalStatus = 0x02;

    if ((!strcmp("imm2", type)) && (!strcmp("primary", pau8firmwareOperation)))
        status_code = CLP_STATUS_DONE;
    else
        status_code = CLP_STATUS_COMPLETE;
    
    if (strcmp(type, "pldm"))
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_COMPLETED, u16OperationalStatus, status_code);
    else
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_ADAPTER_ALL_SUCC, u16OperationalStatus, status_code);

    bReturnAIM = aim_config_set_str(CIM_SOFTWARE_UPDATE_TYPE, "", false);
    if (!bReturnAIM)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(%s, """").", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE);
    }

    return 0;

CANCEL_UPDATE_LABEL:
    
    if (unlink(INTERNAL_SFTP_UPLOAD_FULLNAME))
        logTraceCIM(LOG_LEV_WARNING,"%s() - Remove file: [%s] fail: [%s].", __FUNCTION__, INTERNAL_SFTP_UPLOAD_FULLNAME, strerror(errno));

    FMCancel(type);
    CIMFree(pFMPath);

RETURN_FAIL_LABEL:
    /* Only flush multi adapters and partial success, will set Error code to 29 */
    if ((bFlushSuccess == true) || (u32ErrorCode == 29))
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_ADAPTER_PARTIAL_SUCC, u16OperationalStatus, status_code);
    else
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_EXCEPTION, u16OperationalStatus, status_code);

    bReturnAIM = aim_config_set_str(CIM_SOFTWARE_UPDATE_TYPE, "", false);
    if (!bReturnAIM)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(%s, """").", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE);
    }

    return 2;
}


int ExecuteSoftwareUpdateInstallFromURIJob(const CMPIContext *ctx,
                                           int i32JobID,
                                           char *pau8URI,
                                           char **ppau8Location,
                                           unsigned int uiCount,
                                           int i32Timeout,
                                           const char* pau8firmwareType,
                                           const char* pau8firmwareOperation)
{
#define TFTP_CURL_SIZE 81  //Warning: this size shall be adjusted if you change curl command
#define SFTP_CURL_SIZE 69 //Warning: this size shall be adjusted if you change curl command
    UINT32 u32Return_code = 0;
    UINT32 u32PID = 0;
    sSwMsg_McFlashCfg flash_cfg = { 0 };
    struct xferd_request sRequest = { 0 };
    char type[32] = "web";
    char build_id[32] = { 0 };
    //int iReturn = FILETRANS_SYS_ERROR;
    int iret=0;
    int iTimeout = i32Timeout/2;
    CLPInstallStatusCode status_code = CLP_STATUS_UNKNOWN_ERROR;
    unsigned short u16OperationalStatus = 0;
    unsigned long u32ErrorCode = 0;
    int i32Error = 0;
    char sSystemCmd[256] = {0};
    char w_interface[64] = {0};
    int port = 0;
    int lastProgress = 0;
    int pendingCount = 0;
    int FMPathLength = 0;
    int URILength = strlen(pau8URI);
    int tftpBuffSize = 0;
    int sftpBuffSize = 0;
    char * pFMPath = NULL;
    char * pCurlCmdBuff = NULL;
    bool bReturnAIM = false;
    int i = 0;
    bool bFlushSuccess = false;

    /* Notice: Only invoking FMCancel() when calling FMRequestSpace() failed or downloading file failed. */
    
    /* 0. First we check URI. */
    if ((iret = xferd_parse_uri(pau8URI, &sRequest) )!= 0)
    {
        if(iret == URI_INVALID_SCHEME_ERROR)
            status_code = CLP_STATUS_INVALID_FTP;
        else
            status_code = CLP_STATUS_INVALID_URI;
        logTraceCIM(LOG_LEV_ERROR, "%s()- xferd_parse_uri failed:%d(%s).", __FUNCTION__, iret, (iret == URI_INVALID_SCHEME_ERROR)?"":"FTP transfer is not supported");
        goto RETURN_FAIL_LABEL;
    }
    else
    {
        logTraceCIM(LOG_LEV_DEBUG, "%s()- IP: %s, port: %d and remote file: %s ftp type:0x%x.", __FUNCTION__, sRequest.ipaddr, sRequest.port, sRequest.remote_file, sRequest.uri_type);
    }

    CMPIGetUserNameFromContext(ctx, flash_cfg.c_UserID);
    if (0 != FMRegisterUser("CIM", flash_cfg.c_UserID, NULL))
    {
        status_code = CLP_STATUS_TASK_RUNNING;
        logTraceCIM(LOG_LEV_ERROR, "%s()- FMRegisterUser() returned Error.", __FUNCTION__);
        goto RETURN_FAIL_LABEL;
    }

    bReturnAIM = aim_config_set_str(CIM_SOFTWARE_UPDATE_TYPE, type, false);
    if (!bReturnAIM)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(%s, %s).", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE, type);
        goto CANCEL_UPDATE_LABEL;
    }

    // 1. Request space for flash staging area
    {
        //NOTE: The return is a strdup, so we need to do free. Damn coding style.
        char *str = FMRequestSpace(type, 250000);
        if (str == NULL)
        {
            FMGetLastError(&u32ErrorCode);
            u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
            status_code = CLP_STATUS_FMAPI_ERROR;
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call FMRequestSpace(%s, 250000).", __FUNCTION__, type);
            
            goto CANCEL_UPDATE_LABEL;
        }
        else
        {
            pFMPath = strdup(str);
            CIMFree(str);
            FMPathLength = strlen(pFMPath);

            logTraceCIM(LOG_LEV_DEBUG, "%s()- File path will be %s.", __FUNCTION__, pFMPath);
        }
    }
    
    // 2. Download remote upd file
    if(!xferd_IPv6_working_interface_check(&sRequest, w_interface)){
         logTraceCIM(LOG_LEV_ERROR, "%s()- Firewall fail to call xferd_IPv6_working_interface_check", __FUNCTION__);
        goto CANCEL_UPDATE_LABEL;
    }
    unlink(CIM_SoftwareUpdate_Progress_File);

    if(sRequest.uri_type & XFERD_BIT_TFTP)
    {
        int policy_enable=0;
        if ( aim_config_get_int(POLICY_FORBID_TFTP, &policy_enable) )
        {
            if(policy_enable)
            {
                 status_code = CLP_STATUS_TFTP_FIREWALL_FORBID;
                 logTraceCIM(LOG_LEV_ERROR, "%s()- Firewall forbide tftp transport", __FUNCTION__);
                goto CANCEL_UPDATE_LABEL;
            }
        }
        port = (sRequest.port<=0)?69:(sRequest.port);
        snprintf(sSystemCmd, sizeof(sSystemCmd), "/var/secure/bin/firetool --update-service-port --service-name tftp-client --service-port %d", port);

        tftpBuffSize = FMPathLength+strlen(CIM_SoftwareUpdate_Progress_File)+TFTP_CURL_SIZE+URILength+PORT_LENGTH+1;
        pCurlCmdBuff = Malloc(sizeof(char)*tftpBuffSize);

        if(!pCurlCmdBuff)
        {
            logTraceCIM(LOG_LEV_ERROR,"%s: failed to malloc<%d> char buffer for tfp update",__FUNCTION__,tftpBuffSize);
            goto CANCEL_UPDATE_LABEL;
        }

        memset(pCurlCmdBuff,0,tftpBuffSize);

        snprintf(pCurlCmdBuff,tftpBuffSize, "/usr/bin/curl -o %s tftp://%s%s:%d/%s --tftp-blksize 8192 --connect-timeout 1800 --stderr %s ",
                pFMPath, sRequest.ipaddr, w_interface, port, sRequest.remote_file, CIM_SoftwareUpdate_Progress_File);
    }
    else 
    {
        port = (sRequest.port<=0)?22:(sRequest.port);
        snprintf(sSystemCmd, sizeof(sSystemCmd), "/var/secure/bin/firetool --update-service-port --service-name sftp-client --service-port %d", port);

        sftpBuffSize = FMPathLength+strlen(CIM_SoftwareUpdate_Progress_File)+SFTP_CURL_SIZE+URILength+PORT_LENGTH+1;
        pCurlCmdBuff = Malloc(sizeof(char)*sftpBuffSize);

        if(!pCurlCmdBuff)
        {
            logTraceCIM(LOG_LEV_ERROR,"%s: failed to malloc<%d> char buffer for sftp update",__FUNCTION__,sftpBuffSize);
            goto CANCEL_UPDATE_LABEL;
        }

        memset(pCurlCmdBuff,0,sftpBuffSize);
        
        snprintf(pCurlCmdBuff,sftpBuffSize, "/usr/bin/curl -o %s -u %s:%s sftp://%s%s:%d/%s -k --connect-timeout 1800 --stderr %s ",
                pFMPath, sRequest.user, sRequest.password,  sRequest.ipaddr, w_interface, port, sRequest.remote_file,   CIM_SoftwareUpdate_Progress_File);
    }
   
    logTraceCIM(LOG_LEV_WARNING, "%s()- firetool update service to port %d with interface [%s].", __FUNCTION__, port, w_interface);
    secure_system(sSystemCmd);

    iret = async_secure_system(pCurlCmdBuff);
    logTraceCIM(LOG_LEV_WARNING, "%s()- async_secure_system: download to path[%s], returned %d.", __FUNCTION__, pFMPath, iret);
    CIMFree(pCurlCmdBuff);

    while(iTimeout>0)
    {
        iret = UpdateDownloadingProgress(i32JobID, sRequest.uri_type, CIM_SoftwareUpdate_Progress_File, &i32Error);
        logTraceCIM(LOG_LEV_DEBUG, "%s()- UpdateDownloadingProgress : returned %d:%d.Pending:%d", __FUNCTION__, iret, i32Error, pendingCount);

        if(iret<0)
        {
            if ((i32Error == TFTP_INVALID_HOST_ERROR_CODE) || (i32Error == SFTP_INVALID_HOST_ERROR_CODE))
                status_code = CLP_STATUS_INVALID_FTPSERV;
            else if ((i32Error == TFTP_FILE_NOT_FIND_ERROR_CODE) || (i32Error == SFTP_FILE_NOT_FIND_ERROR_CODE))
                status_code = CLP_STATUS_INVALID_FILE;
            else if ((i32Error == SFTP_PERMISSION_DENIED) || (i32Error == INVALID_USER_PASSWD))
                status_code = CLP_STATUS_SFTP_USER_FAIL;
            else
                status_code = CLP_STATUS_UNKNOWN_ERROR;
            
            logTraceCIM(LOG_LEV_ERROR, "%s()- get failed curl result, %d map to %d.", __FUNCTION__, i32Error, status_code);
            goto CANCEL_UPDATE_LABEL;
        }
        else if(iret==0)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- failed to prepare xferd parse. sleep a while.", __FUNCTION__);
            sleep(3);
            pendingCount += 3; 
        }
        else
        {
            
            status_code = iret>100?100:iret;

            logTraceCIM(LOG_LEV_WARNING, "%s()- downloading percent is %d .", __FUNCTION__,status_code);

            CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_RUNNIG, CLP_InstallJob_OpStatus_Downloading, status_code);
            if(status_code != lastProgress)
            {
                lastProgress = status_code;
                pendingCount = 0;
            }
            if(status_code == 100)
                break;
        }
        sleep(1);
        pendingCount ++; 
        if(pendingCount > MAX_DOWNLOAD_PENDING_SECONDS)
        {
            status_code = CLP_STATUS_TIMEOUT ;
            logTraceCIM(LOG_LEV_ERROR, "%s()- download pending timeout at progress %d. Exit as downloding fail.", __FUNCTION__, status_code);
            goto CANCEL_UPDATE_LABEL;

        }

        iTimeout --;
    }
    if (0 == iTimeout)
    { //TIME OUT!!
        status_code = CLP_STATUS_TIMEOUT;

        logTraceCIM(LOG_LEV_ERROR, "%s()- Time out! Try to cancel  firmware update!", __FUNCTION__);
        goto CANCEL_UPDATE_LABEL;
    }
    
    logTraceCIM(LOG_LEV_ERROR, "%s()- Success to download build file to [%s]!", __FUNCTION__, pFMPath);


    // 3. Verify image file
    {
        char* str = FMVerifyImageFile(pFMPath);
        if (NULL == str)
        {
            FMGetLastError(&u32ErrorCode);
            u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
            status_code = CLP_STATUS_FMAPI_ERROR;
            logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to verity image file.", __FUNCTION__);
            CIMFree(pFMPath);
            goto RETURN_FAIL_LABEL;
        }
        else
        {
            CIMFree(pFMPath);
            pFMPath = strdup(str);
            free(str);
            // Out put look like "imm2_1AOO20A_56485_8.upd"
            logTraceCIM(LOG_LEV_DEBUG, "%s()- Output of FMVerifyImageFile() is build information = %s.", __FUNCTION__, pFMPath);
        }
    }

    // 4. Get firmware buildid and type & Verify
    memset(type, 0, sizeof(type));
    sscanf(pFMPath, "%[^_]_%[^_]_%*s", type, build_id);
    CIMFree(pFMPath);
    u32Return_code = FMVerifyImage(type, build_id);
    switch (u32Return_code)
    {
    case 0:
        logTraceCIM(LOG_LEV_DEBUG, "%s()- Verify success.", __FUNCTION__);
        break;
    case ENOENT:
    case EFAULT:
        FMGetLastError(&u32ErrorCode);
        u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
        status_code = CLP_STATUS_FMAPI_ERROR;
        logTraceCIM(LOG_LEV_ERROR, "%s()- Could not access firmware.", __FUNCTION__);
        goto RETURN_FAIL_LABEL;
    case EINVAL:
        FMGetLastError(&u32ErrorCode);
        u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
        status_code = CLP_STATUS_FMAPI_ERROR;
        logTraceCIM(LOG_LEV_ERROR, "%s()- Build_id is is not meant for the system.", __FUNCTION__);
        goto RETURN_FAIL_LABEL;
    default:
        FMGetLastError(&u32ErrorCode);
        u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
        status_code = CLP_STATUS_FMAPI_ERROR;
        logTraceCIM(LOG_LEV_ERROR, "%s()- Unknown error.", __FUNCTION__);
        goto RETURN_FAIL_LABEL;
    }

    bReturnAIM = aim_config_set_str(CIM_SOFTWARE_UPDATE_TYPE, type, false);
    if (!bReturnAIM)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(%s, %s).", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE, type);
        goto CANCEL_UPDATE_LABEL;
    }

    if (!strcmp(pau8firmwareType, "sp"))
    {
        if (strcmp("imm2", type))
        {
            status_code = CLP_STATUS_PKG_MISMATCH;
            logTraceCIM(LOG_LEV_ERROR, "%s()- File type %s is not match %s. Abort!", __FUNCTION__, type, pau8firmwareType);
            goto CANCEL_UPDATE_LABEL;
        }
    }
    else if (!strcmp(pau8firmwareType, "host"))
    {
        if (!strcmp("imm2", type))
        {
            status_code = CLP_STATUS_PKG_MISMATCH;
            logTraceCIM(LOG_LEV_ERROR, "%s()- File type %s is not match %s. Abort!", __FUNCTION__, type, pau8firmwareType);
            goto CANCEL_UPDATE_LABEL;
        }
    }
    else
    {
        if (strcmp(pau8firmwareType, type))
        {
            if(!strcmp(pau8firmwareType, "bios") && !strcmp(type, "uefi"))
            {
                logTraceCIM(LOG_LEV_DEBUG, "%s()- bios and uefi should be identical.", __FUNCTION__);
            }
            else
            {
                status_code = CLP_STATUS_PKG_MISMATCH;
                logTraceCIM(LOG_LEV_ERROR, "%s()- File type %s is not match %s. Abort!", __FUNCTION__, type, pau8firmwareType);
                goto CANCEL_UPDATE_LABEL;
            }
        }
    }

    /* check consistency between target and firmware type */
    if (ppau8Location == NULL)
    {
        /* target: imm2, uefi or dsa */
        if (strcmp(pau8firmwareType, "imm2") && strcmp(pau8firmwareType, "uefi") && \
                strcmp(pau8firmwareType, "bios") && strcmp(pau8firmwareType, "dsa"))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Non-consistency checked! Firmware type:[%s].", \
                    __FUNCTION__, pau8firmwareType);
            goto CANCEL_UPDATE_LABEL;
        }
    }
    else
    {
        if (strcmp(pau8firmwareType, "pldm"))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Non-consistency checked! Firmware type:[%s].", \
                    __FUNCTION__, pau8firmwareType);
            goto CANCEL_UPDATE_LABEL;
        }
    }

    u16OperationalStatus = CLP_InstallJob_OpStatus_Update;
    status_code = 0;
    CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_RUNNIG, u16OperationalStatus, status_code);

    sleep(5);
    // pau8firmwareOperation
    /* pldm skip this step */
    if ((NULL == ppau8Location) && (0 == FMSetUpdateOperation(type, pau8firmwareOperation, 0)))
    {
        FMGetLastError(&u32ErrorCode);
        u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
        status_code = CLP_STATUS_FMAPI_ERROR;
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to setup firmware operation %s.", __FUNCTION__, pau8firmwareOperation);
        goto CANCEL_UPDATE_LABEL;
    }

    do{
        int iSlot = -1;
        int iLocation = -1;

        /* Get location and slot from ppau8Location. Once per call */
        if ((ppau8Location != NULL) && (GetLocationSlotFromString(&iLocation, &iSlot, ppau8Location[i]) < 0))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Get Location fail!location:[%d], slot:[%d], loc string:[%s].", \
                    __FUNCTION__, iLocation, iSlot, ppau8Location[i]);
            status_code = CLP_STATUS_FMAPI_ERROR;
            u16OperationalStatus = CLP_InstallJob_OpStatus_FMError;
            goto CANCEL_UPDATE_LABEL;
        }

        if (ppau8Location != NULL)
            logTraceCIM(LOG_LEV_DEBUG, "%s()- Get Location! location:[%d], slot:[%d], loc string:[%s].", \
                    __FUNCTION__, iLocation, iSlot, ppau8Location[i]);

        if ((iSlot >= 0) && (iLocation >= 0))
        {
            if (FMSelectAdapter(iSlot, iLocation) != 0)
            {
                FMGetLastError(&u32ErrorCode);
                logTraceCIM(LOG_LEV_ERROR, "%s()- FMSelectAdapater fail on: Location[%d] Slot[%d], Error code:[%d]", \
                        __FUNCTION__, iLocation, iSlot, u32ErrorCode);
                u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
                status_code = CLP_STATUS_FMAPI_ERROR;
                goto CANCEL_UPDATE_LABEL;
            }
        }
        else
        {
            /* core firmware update or update one pldm firmware if it's applicable. */
            logTraceCIM(LOG_LEV_DEBUG, "%s()- prepare set i-[%d] to uiCount-[%d]", __FUNCTION__, i, uiCount);
            i = uiCount;
        }

        logTraceCIM(LOG_LEV_ERROR, "%s()- Ok, let call FMBeginUpdate()\n", __FUNCTION__);
        if ((u32PID = FMBeginUpdate(type,0)) == 0)
        {
            FMGetLastError(&u32ErrorCode);
            u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
            status_code = CLP_STATUS_FMAPI_ERROR;
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call FMBeginUpdate(). Error code:[%d]", __FUNCTION__, u32ErrorCode);
            goto RETURN_FAIL_LABEL;
        }

        /* get updating status */
        i32Timeout /= 2;
        while(i32Timeout > 0)
        {
            u32Return_code = FMGetUpdateStatusByPid(u32PID);
            if(u32Return_code == 0)
            { /* update complete */
                bFlushSuccess = true;
                logTraceCIM(LOG_LEV_ERROR, "%s()- Success to update build for [%s:%s]!", __FUNCTION__, type, pau8firmwareOperation);
                break;
            }
            else if (u32Return_code & 0xC0000000)
            { /* still updating, we don't show percentage, so we do nothing */
                logTraceCIM(LOG_LEV_DEBUG, "%s()- updating status (%u)\n", __FUNCTION__, u32Return_code & 0x000000FF);
                status_code = u32Return_code & 0x000000FF;
                CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_RUNNIG, u16OperationalStatus, status_code);
            }
            else
            { /* error occurs */
                FMGetLastError(&u32ErrorCode);
                status_code = CLP_STATUS_FMAPI_ERROR;
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed on FMGetUpdateStatusByPid(). Error code:[%d]", __FUNCTION__, u32ErrorCode);
                u16OperationalStatus = CLP_InstallJob_OpStatus_FMError|u32ErrorCode;
                /* still finish all updates, then return fail */
                break;
            }
            sleep(1);
            i32Timeout--;
        }

        if (0 == i32Timeout)
        { //TIME OUT!!
            status_code = CLP_STATUS_UPDATE_TIMEOUT;
            FMGetLastError(&u32ErrorCode);
            logTraceCIM(LOG_LEV_ERROR, "%s()- Time out! Try to cancel %s firmware update! Error code:[%d]", __FUNCTION__, type, u32ErrorCode);
            goto RETURN_FAIL_LABEL;
        }

    } while (++i < uiCount);

    if (u32ErrorCode) 
    {
        goto RETURN_FAIL_LABEL;
    }

    u16OperationalStatus = 0x02;

    if ((!strcmp("imm2", type)) && (!strcmp("primary", pau8firmwareOperation)))
        status_code = CLP_STATUS_DONE;
    else
        status_code = CLP_STATUS_COMPLETE;
    
    if (strcmp(type, "pldm"))
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_COMPLETED, u16OperationalStatus, status_code);
    else
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_ADAPTER_ALL_SUCC, u16OperationalStatus, status_code);

    bReturnAIM = aim_config_set_str(CIM_SOFTWARE_UPDATE_TYPE, "", false);
    if (!bReturnAIM)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(%s, """").", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE);
    }

    return 0;

CANCEL_UPDATE_LABEL:
    
    FMCancel(type);
    CIMFree(pFMPath);

RETURN_FAIL_LABEL:
    /* Only flush multi adapters and partial success, will set Error code to 29 */
    if ((bFlushSuccess == true) || (u32ErrorCode == 29))
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_ADAPTER_PARTIAL_SUCC, u16OperationalStatus, status_code);
    else
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_EXCEPTION, u16OperationalStatus, status_code);

    bReturnAIM = aim_config_set_str(CIM_SOFTWARE_UPDATE_TYPE, "", false);
    if (!bReturnAIM)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(%s, """").", __FUNCTION__, CIM_SOFTWARE_UPDATE_TYPE);
    }

    return 2;
}

static void delete_zombies_process(int status)
{
    pid_t kidpid;

    logTraceCIM(LOG_LEV_DEBUG, "%s()- Start. status:%d ", __FUNCTION__,status);
    while ((kidpid = waitpid(-1, &status, WNOHANG)) > 0) // -1
    {
        logTraceCIM(LOG_LEV_WARNING, "%s()- Child %ld finish...", __FUNCTION__, (long int) kidpid);
    }
    logTraceCIM(LOG_LEV_DEBUG,"kidpid is %d and status:%d",kidpid,status);
    if(kidpid == -1)
    {
        logTraceCIM(LOG_LEV_DEBUG,"errno %d",errno);
    }
}

int FolkToInstall(const CMPIContext *ctx,
                  int i32JobID,
                  char *pau8URI,
                  char **ppau8Location,
                  unsigned int uiCount,
                  int i32Timeout,
                  const char* pau8firmwareType,
                  const char* pau8firmwareOperation)
{
    pid_t pid = 0;
    struct sigaction sa;
    char *str[3] = { "imm2", "bios", "dsa" };
    int i = 0;

    if (!pau8URI)
    {
        //CIM_ConcreteJob_InstAgent_ChangeState(i32JobID, 10);
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_EXCEPTION, 0, CLP_STATUS_INVALID_URI);

        logTraceCIM(LOG_LEV_ERROR, "%s()- pau8URI is NULL.", __FUNCTION__);
        return -1;
    }

    /* Checking if there is a firmware update running. */
    for (i = 0; i < 3; i++)
    {
        if (FMGetUpdateStatus(str[i]) & 0xC0000000)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- There is already a %s firmware update process running now from SP.", __FUNCTION__, str[i]);
            
            //CIM_ConcreteJob_InstAgent_ChangeState(i32JobID, 10);
            CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_EXCEPTION, 0, CLP_STATUS_TASK_RUNNING);
           return -1;
        }
    }

    memset(&sa, 0, sizeof(sa));
    
    sigfillset(&sa.sa_mask);
    sa.sa_handler = delete_zombies_process;
    sa.sa_flags = 0;
    sigaction(SIGCHLD, &sa, NULL);

    // Fork off the parent process
    pid = fork();

    if (pid < 0)
    {
        //CIM_ConcreteJob_InstAgent_ChangeState(i32JobID, 10);
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_EXCEPTION, 0, CLP_STATUS_UNKNOWN_ERROR);
        logTraceCIM(LOG_LEV_ERROR, "%s()- pid < 0.", __FUNCTION__);
        return  -1;
    }
    else if (pid == 0)//child process
    {
        struct flock fl = {F_WRLCK, SEEK_SET, 0, 0, 0}; /* l_type   l_whence  l_start  l_len  l_pid   */
        INT32 fd = 0;
        char *lock_file = "/tmp/.smash_transfer_firmware_update_file";

        fl.l_pid = getpid();
        //logTraceCIM(LOG_LEV_DEBUG, "%s()- The PID of forked process is %d.", __FUNCTION__, fl.l_pid);

        if ((fd = open(lock_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        {
            //CIM_ConcreteJob_InstAgent_ChangeState(i32JobID, 10);
            CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_EXCEPTION, 0, CLP_STATUS_UNKNOWN_ERROR);
            logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to open lock file %s.", __FUNCTION__, lock_file);
            exit(-1);
        }

        if (fcntl(fd, F_SETLK, &fl) == -1) // try to lock. If fail to lock return fail
        {
            //CIM_ConcreteJob_InstAgent_ChangeState(i32JobID, 10);
            CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_EXCEPTION, 0, CLP_STATUS_TASK_RUNNING);
            logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to lock file %s.", __FUNCTION__, lock_file);
            close(fd);
            exit(-1);
        }

        CleanAllSoftwareUpdaetRunningJobs();
        //CIM_ConcreteJob_InstAgent_ChangeState(i32JobID, 4); //running
        CIM_ConcreteJob_InstAgent_UpdateInstallStatus(i32JobID, JOBSTATE_RUNNIG, CLP_InstallJob_OpStatus_Downloading, 0);
        if (!aim_config_set_int(CIM_SOFTWARE_UPDATE_PID, fl.l_pid, FALSE))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to call aim_config_set_int(%s, %d).", __FUNCTION__, CIM_SOFTWARE_UPDATE_PID, fl.l_pid);
        }

        /* If pau8URI == NULL, it means this is an installaiton from internal SFTP server */
        if (pau8URI)
            ExecuteSoftwareUpdateInstallFromURIJob(ctx,
                                                   i32JobID,
                                                   pau8URI,
                                                   ppau8Location,
                                                   uiCount,
                                                   i32Timeout,
                                                   pau8firmwareType,
                                                   pau8firmwareOperation);
        else
            ExecuteSoftwareUpdateInstallFromInternal(ctx,
                                                   i32JobID,
                                                   pau8URI,
                                                   ppau8Location,
                                                   uiCount,
                                                   i32Timeout,
                                                   pau8firmwareType,
                                                   pau8firmwareOperation);

        if (!aim_config_set_int(CIM_SOFTWARE_UPDATE_PID, 0, FALSE))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to call aim_config_set_int(%s, 0).", __FUNCTION__, CIM_SOFTWARE_UPDATE_PID);
        }

        fl.l_type = F_UNLCK;  /* set to unlock same region */
        if (-1 == fcntl(fd, F_SETLK, &fl))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to unlock!", __FUNCTION__);
        }
        close(fd);
        unlink(lock_file);
        exit(0);
    }
    else if (pid > 0)//parent process
    {
        return 0;
    }
    return -1;
}


