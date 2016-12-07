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

#include <string.h>
#include <stdarg.h>
#include <MemoryService.h>
#include <CMPIUtil.h>

#include "ClassUtil.h"
#include "PropertyNames.h"
#include "ClassNames.h"

#ifndef _BROKER_SFCB
#include "MethodNames.h"
#endif
/* Include class header files */
#include <RegisterClass.h>

/* Include agent header files */
#include <RegisterClassAgent.h>

#include "../AssociationTable.h"

#include <emerson/aim/libaim.h>
#include <emerson/securitymgr/sm.h>

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif
#include <emerson/cemgr/swe_function_table.h>
#include <emerson/aem/powermgr.h>

/* IBM_JobSettingData class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_JobSettingData = (CMPIUint8 *)CLASSNAMETEXT_IBM_JobSettingData;

/* Property List */
static const char * const IBM_JobSettingDataPropertyList[] = 
{
    PROPERTYNAME_AssociatedJob,
    PROPERTYNAME_ChangeableType,
    PROPERTYNAME_ConfigurationName,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_JobRunTimes,
    PROPERTYNAME_RunDayOfWeek,
    PROPERTYNAME_RunMonth,
    PROPERTYNAME_RunStartInterval
};

/* Key property List */
static const char * const IBM_JobSettingDataKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_JOBSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_JobSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_JobSettingData;\
    Arg.GetKeyProperty = IBM_JobSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_JobSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_JobSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_JobSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_JobSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_JobSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_JobSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_JOBSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_JobSettingDataAssociations;\
    Arg.AgentInit = IBM_JobSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_JobSettingData_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_JobSettingData;\
    Arg.GetKeyProperty = IBM_JobSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_JobSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_JobSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_JobSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_JobSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_JobSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_JobSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_JOBSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_JobSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_JOBSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_JobSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_JobSettingData;\
    Arg.GetKeyProperty = IBM_JobSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_JobSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_JobSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_JobSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_JobSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_JobSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_JobSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_JOBSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_JobSettingDataAssociations;\
    Arg.AgentInit = IBM_JobSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_JobSettingData_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_JobSettingData;\
    Arg.GetKeyProperty = IBM_JobSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_JobSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_JobSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_JobSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_JobSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_JobSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_JobSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_JOBSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_JobSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_JobSettingData_GetProperty( 
                                         CMPICount nInstIndex,
                                         CMPICount nPropIndex,
                                         void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_JobSettingData_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_JobSettingData_GetKeyProperty( 
                                            CMPICount nInstIndex,
                                            CMPICount nKeyIndex,
                                            void *pAgentDataPtr)
{
    CMPIData data;
        data.state = CMPI_badValue;
    data = IBM_JobSettingData_GetProperty(nInstIndex, nKeyIndex | IBM_JOBSETTINGDATA_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_JobSettingData_GenerateObjectPath( 
                                                       char **properties,
                                                       CMPICount InstIndex,
                                                       void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_JobSettingData_GetInstance( 
                                           CMPIInstanceMI *mi,
                                           const CMPIContext *ctx,
                                           const CMPIResult *rslt,
                                           const CMPIObjectPath *op,
                                           const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_JobSettingData_EnumInstances( 
#else
CMPIStatus IBM_JobSettingData_EnumerateInstances( 
#endif
                                                  CMPIInstanceMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_JobSettingData_EnumInstanceNames( 
#else
CMPIStatus IBM_JobSettingData_EnumerateInstanceNames( 
#endif
                                                      CMPIInstanceMI *mi,
                                                      const CMPIContext *ctx,
                                                      const CMPIResult *rslt,
                                                      const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_JobSettingData_Associators( 
                                           CMPIAssociationMI *mi,
                                           const CMPIContext *ctx,
                                           const CMPIResult *rslt,
                                           const CMPIObjectPath *op,
                                           const char *asscClass,
                                           const char *resultClass,
                                           const char *role,
                                           const char *resultRole,
                                           const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_JobSettingData_AssociatorNames( 
                                               CMPIAssociationMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char *asscClass,
                                               const char *resultClass,
                                               const char *role,
                                               const char *resultRole)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_JobSettingData_References( 
                                          CMPIAssociationMI *mi,
                                          const CMPIContext *ctx,
                                          const CMPIResult *rslt,
                                          const CMPIObjectPath *op,
                                          const char *resultClass,
                                          const char *role,
                                          const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_JobSettingData_ReferenceNames( 
                                              CMPIAssociationMI *mi,
                                              const CMPIContext *ctx,
                                              const CMPIResult *rslt,
                                              const CMPIObjectPath *op,
                                              const char *resultClass,
                                              const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_JobSettingData_CheckSelectorSet( 
                                               const CMPIObjectPath *op,
                                               CMPIBoolean bAllKey,
                                               void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);
    nIndex = CIMClassUtil_CheckSelectorSet(op, bAllKey, INSTANCE_INDEX_INVALID, &Arg, pAgentDataPtr);

    if (nIndex != INSTANCE_INDEX_INVALID)
    {
        nNextIndex = CIMClassUtil_CheckSelectorSet(op, bAllKey, nIndex, &Arg, pAgentDataPtr);

        if (nNextIndex == INSTANCE_INDEX_INVALID)
        {
            return (nIndex);
        }
        else
        {
            return (INSTANCE_INDEX_INVALID);
        }
    }
    return (INSTANCE_INDEX_INVALID);
}


/* Modify RunDayOfWeek, RunStartInterval */
CMPIStatus IBM_JobSettingData_ModifyInstance(
                                      CMPIInstanceMI *mi, 
                                      const CMPIContext *ctx, 
                                      const CMPIResult *rslt, 
                                      const CMPIObjectPath *op,
                                      const CMPIInstance * inst,
                                      const char **properties
                                      )
{
    sClassUtilArg Arg;   
    CMPIStatus rc = {CMPI_RC_ERR_INVALID_PARAMETER, NULL};
   
    CMPICount instIndex = 0;
    CMPIData data;
    CMPIString *dataStr = NULL;
    int iRet;
    INT32 i32RunDayOfWeek = 0;
    UINT32 u32RunStartInterval_Hour = 0;
    UINT32 u32RunStartInterval_Minute = 0;
    INT8 *i8VarName = NULL;
    INT8 *i8VarName2 = NULL;
    INT8 *i8VarName3 = NULL;
    INT8 *i8VarName4 = NULL;
    bool bEnableTag = TRUE;
    sSwMsg_PowerActionscheduledCfg  spoweraction;
    INT32  cycle_tmp_date; 
    BOOLEAN tmp_enable = false;
    CMPIString *psTimeString = NULL;
    const char *psTmpTimeString = NULL;
    char psTmpHour[3] = {'\0'}, psTmpMin[3] = {'\0'};

    memset(&spoweraction, '\0', sizeof(spoweraction));
    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg);

    /* Check SelectorSet */
    instIndex = IBM_JobSettingData_CheckSelectorSet(op, CMPITRUE, NULL);
    if (instIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_JobSettingDataPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  // CMPI_RC_ERR_NO_SUCH_PROPERTY 
        goto ERR_EXIT;
    }

    if (ctx == NULL)
    {
	    rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
	    goto ERR_EXIT;
    }

    /* Read RunDayOfWeek from input property */
    data = inst->ft->getProperty(inst, IBM_JobSettingDataPropertyList[5], &rc);
    if (data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        
        goto ERR_EXIT;    
    }

	dataStr = CMPIData2String(&data);
    if(dataStr == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */   
        goto ERR_EXIT;
    } 		
	i32RunDayOfWeek = atoi(dataStr->ft->getCharPtr(dataStr, &rc));
    //printf("RunDayOfWeek data type:[%X] Value:[%s] %d\n", data.type,   (char *)dataStr->ft->getCharPtr(dataStr, &rc), i32RunDayOfWeek);
    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);
    if((i32RunDayOfWeek < 0) || (i32RunDayOfWeek > 7))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        printf("[JobSetting MI] The week of day is out of range.(0~7)\n");
        goto ERR_EXIT;
    }

    switch (instIndex)
    {
        case 0:
            i8VarName =  POWER_SCHED_CYCLE_UP_ENABLE;
            i8VarName2 = POWER_SCHED_CYCLE_UP_HOUR;
            i8VarName3 = POWER_SCHED_CYCLE_UP_MIN;
            i8VarName4 = POWER_SCHED_CYCLE_UP_WEEK;
            snprintf(spoweraction.szPowerAction, sizeof(spoweraction.szPowerAction), "Power On");
            break;
        case 1:
            i8VarName = POWER_SCHED_CYCLE_DOWN_ENABLE;
            i8VarName2 = POWER_SCHED_CYCLE_DOWN_HOUR;
            i8VarName3 = POWER_SCHED_CYCLE_DOWN_MIN;
            i8VarName4 = POWER_SCHED_CYCLE_DOWN_WEEK;
            snprintf(spoweraction.szPowerAction, sizeof(spoweraction.szPowerAction), "Shut Down");
            break;
        case 2:
            i8VarName = POWER_SCHED_RESTART_ENABLE;
            i8VarName2 = POWER_SCHED_RESTART_HOUR;
            i8VarName3 = POWER_SCHED_RESTART_MIN;
            i8VarName4 = POWER_SCHED_RESTART_WEEK;
            snprintf(spoweraction.szPowerAction, sizeof(spoweraction.szPowerAction), "Shut Down and Restart");
            break;
    }

    iRet = aim_config_get_bool(i8VarName, &bEnableTag);
    if (!iRet)
    {
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
	}

	//Only can modify when related job is suspend
    if (bEnableTag)
    {
        rc.rc = CMPI_RC_ERR_ACCESS_DENIED;
        goto ERR_EXIT;    
    }

    /* Read RunStartInterval from input property */
    data = inst->ft->getProperty(inst, IBM_JobSettingDataPropertyList[7], &rc);
    if (data.state != CMPI_goodValue)
    {
    	//printf("rc.rc = %d, rc.state=%d\n", rc.rc, data.state);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        
        goto ERR_EXIT;    
    }

    if(data.value.dateTime == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        
        goto ERR_EXIT;
    }
    psTimeString =  data.value.dateTime->ft->getStringFormat(data.value.dateTime, &rc);
    psTmpTimeString = psTimeString->ft->getCharPtr(psTimeString, &rc);
    strncpy(psTmpHour, (strchr(psTmpTimeString, '.') - 6), 2);
    strncpy(psTmpMin, (strchr(psTmpTimeString, '.') - 4), 2);
    u32RunStartInterval_Hour = atoi(psTmpHour);
    u32RunStartInterval_Minute = atoi(psTmpMin);
    
    //printf("====dateString=%s \n", psTimeString->ft->getCharPtr(psTimeString, &rc));
	//printf("====u32RunStartInterval_Hour=%u \n", u32RunStartInterval_Hour);
	//printf("====u32RunStartInterval_Minute=%u \n", u32RunStartInterval_Minute);
    CMPIDataRelease(&data);

	//Set RunDayOfWeek
    // 1 means Sunday, ¡K, 7 means Sat.

	if (1 == i32RunDayOfWeek)
	{
	    i32RunDayOfWeek = 7;
	}
	else if (0 != i32RunDayOfWeek)
	{
	    i32RunDayOfWeek = i32RunDayOfWeek - 1;
	}

    iRet = aim_config_get_int(i8VarName4, &cycle_tmp_date);
    if(iRet)
    {
        if(cycle_tmp_date != i32RunDayOfWeek)
            tmp_enable = TRUE;
    }        
    iRet = aim_config_set_int(i8VarName4, i32RunDayOfWeek, TRUE);
    if (!iRet)
    {
        /* Internal Error */
        //printf("modify u32RunDayOfWeek error[%d]\n", iRet);
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }


	//Set RunStartInterval	
	iRet = aim_config_get_int(i8VarName2, &cycle_tmp_date);
    if(iRet)
    {
        if(cycle_tmp_date != u32RunStartInterval_Hour)
            tmp_enable = TRUE;
    }     
   
    iRet = aim_config_set_int(i8VarName2, u32RunStartInterval_Hour, TRUE);
    if (!iRet)
    {
        /* Internal Error */
        //printf("modify u32RunStartInterval_Hour error[%d]\n", varStatus);
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }

	//Set value
	
	iRet = aim_config_get_int(i8VarName3, &cycle_tmp_date);
    if(iRet)
    {
        if(cycle_tmp_date != u32RunStartInterval_Minute)
            tmp_enable = TRUE;
    }    
   
    iRet = aim_config_set_int(i8VarName3, u32RunStartInterval_Minute, TRUE);
    if (!iRet)
    {
        /* Internal Error */
        //printf("modify u32RunStartInterval_Minute error[%d]\n", varStatus);
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }

    if(tmp_enable)
    {
        const char *szWeekString[8] = { "day", "Monday", "Tuesday", "Wednesday", "Thursday",
                                       "Friday", "Saturday", "Sunday"};
        snprintf(spoweraction.szDate, sizeof(spoweraction.szDate), "%s", szWeekString[i32RunDayOfWeek]);
        CMPIGetUserNameFromContext(ctx, spoweraction.szUserID);        
        snprintf(spoweraction.szTime, sizeof(spoweraction.szTime),"%.2d:%.2d",u32RunStartInterval_Hour, u32RunStartInterval_Minute);        
        if(sw_msg_dispatcher(SW_MSGID_RECURRING_POWER_ACTION_SCHEDULED,(void *) &spoweraction) != CEM_RC_OK)
        {
            printf("Generate sw message %d failed!!\n", SW_MSGID_RECURRING_POWER_ACTION_SCHEDULED);
        }   
    } 
   
	rc.rc = CMPI_RC_OK;


ERR_EXIT:
    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}


/* IBM_JobSettingData Class Service Function */
CMPIStatus Lenovo_JobSettingDataService( 
                                      CMPIUint16 actionID,
                                      void *mi,
                                      const CMPIContext *ctx,
                                      CMPIResult *rslt,
                                      const CMPIObjectPath *op,
                                      ...)
{
    CMPIStatus rc = 
    {
        CMPI_RC_ERR_INVALID_HANDLE,
        NULL
    };

    va_list argptr;
    char *className = NULL;

#ifndef _BROKER_SFCB
    char **properties;
    char *asscClass;
    char *resultClass;
    char *role;
    char *resultRole;
	CMPIInstance *inst = NULL;
#endif

    if (actionID == CLASS_SERVICE_ISA_LITE)
    {
        va_start(argptr, op);
        className = va_arg(argptr, char *);
        va_end(argptr);
    }

    rc = CIMClassUtil_CheckClassName(actionID, mi, ctx, rslt, op, 
                                     className,
                                     (char *) CLASSNAME_Lenovo_IBM_JobSettingData,
                                     CIM_SettingDataService);
    if (rc.rc != CMPI_RC_OK)
    {
        return (rc);
    }

    switch (actionID)
    {
        case CLASS_SERVICE_ISA_LITE: 
            /* isa lite */
        case CLASS_SERVICE_ISA: 
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_GETINSTANCE: /* getInstances */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_JobSettingData_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_JobSettingData_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_JobSettingData_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_JOBSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_JobSettingData_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_JOBSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_JobSettingData_InstAgent_Destroy;
        #else
            rc.msg = NULL;
        #endif
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_ASSOCIATORS: /*associators*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_JobSettingData_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_JobSettingData_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_JobSettingData_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_JobSettingData_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_JobSettingData_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_JobSettingData_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_JobSettingData_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_INVOKEMETHOD: 
             /* involk method service */
        case CLASS_SERVICE_GETMETHODNAMES:
             /* get method name service */
        case CLASS_SERVICE_GETPARAMETERS:
             /* get method param name service */
        case CLASS_SERVICE_MODIFYINSTANCE: 
            /* modify instance service */
            va_start( argptr, op ); 																				
            inst = va_arg(argptr, CMPIInstance *);
            properties = va_arg(argptr, char **);
            rc = IBM_JobSettingData_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end( argptr );	
            break;
        case CLASS_SERVICE_GETPROPERTY:   
            /* get property service */
        case CLASS_SERVICE_SETPROPERTY:   
            /* set property service */
        case CLASS_SERVICE_CREATEINSTANCE:
            /* create instance service */
        case CLASS_SERVICE_DELETEINSTANCE: 
            /* delete instance service */
        case CLASS_SERVICE_EXECQUERY:
            /* exec query service */
        case CLASS_SERVICE_ACTIVATEFILTER: 
            /* activate filter service */
        case CLASS_SERVICE_DEACTIVATEFILTER: 
            /* deactivate filter service */
        case CLASS_SERVICE_ENABLEINDICATIONS:
            /* enable indication service */
        case CLASS_SERVICE_DISENABLEINDICATIONS: 
            /* disable indication service */
    #endif
        default:
            rc = CIMClassUtil_DefaultFunction(mi, ctx, rslt, op);
            break;
    }

    return (rc);
}

#ifdef _BROKER_SFCB
/* Not Support function */
GenNotSupportInstanceMICreateInstance(IBM_JobSettingData);
//GenNotSupportInstanceMIModifyInstance(IBM_JobSettingData);
GenNotSupportInstanceMIDeleteInstance(IBM_JobSettingData);
GenNotSupportInstanceMIExecQuery(IBM_JobSettingData);
GenNotSupportInstanceMICleanup(IBM_JobSettingData);

/* MI factory function */
CMInstanceMIStub( IBM_JobSettingData_,
                  Lenovo_JobSettingData_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_JOBSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_JobSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_JobSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_JobSettingData;\
    Arg.GetNextInstIndex = IBM_JobSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_JobSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_JobSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_JobSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_JobSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_JobSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_JobSettingData_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_JobSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_JobSettingData;\
    Arg.GetNextInstIndex = IBM_JobSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_JobSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_JobSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_JobSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_JobSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_JobSettingData Class Service Function */
CMPIStatus Lenovo_JobSettingDataService( 
                                      CMPIUint16 actionID,
                                      void *mi,
                                      const CMPIContext *ctx,
                                      CMPIResult *rslt,
                                      const CMPIObjectPath *op,
                                      ...)
{
    CMPIStatus rc = 
    {
        CMPI_RC_ERR_INVALID_HANDLE,
        NULL
    };

    return (rc);
}

/* Gets the Arg of Class IBM_JobSettingData Function */
sClassUtilArg IBM_JobSettingData_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_JOBSETTINGDATA_ARG( Arg );

    return (Arg);
}

#endif
