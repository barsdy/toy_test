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

#include <emerson/cemgr/cemgrAPI.h>

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

#include "../instAgent/incEX/IBM_AlertConfigurationSettingAgent.h"
#include <emerson/cemgr/swe_function_table.h>
#include "LogUtil.h"


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

#define MAX_ENABLEDOOBALERTS_LEN 128
#define MAX_ENABLEDOOBALERTFILTERS_LEN 256
extern BOOL IBM_AlertConfigurationSetting_InstAgent_GetOOBAlertType(UINT32 *pu32EnabledOOBAlerts, int iEnabledOOBAlerts, UINT8 *pu8Alert);
extern BOOL IBM_AlertConfigurationSetting_InstAgent_GetOOBAlertFilterType(UINT32 *pu32EnabledOOBAlertFilters, int iEnabledOOBAlertFilters, UINT32 *pu32SubCate);

/* IBM_AlertConfigurationSetting class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_AlertConfigurationSetting = (CMPIUint8 *)CLASSNAMETEXT_IBM_AlertConfigurationSetting;

/* Property List */
static const char * const IBM_AlertConfigurationSettingPropertyList[] = 
{
    PROPERTYNAME_EnabledOOBAlertFilters,
    PROPERTYNAME_EnabledOOBAlerts
};

/* Key property List */
static const char * const IBM_AlertConfigurationSettingKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};

#define ALERT_CRIT_MASK  ((ALERT_NONE|ALERT_CRIT_OTHER|ALERT_CRIT_TEMP|ALERT_CRIT_VOLT|ALERT_CRIT_POWER|     \
                        ALERT_CRIT_DISK|ALERT_CRIT_FAN|ALERT_CRIT_CPU|ALERT_CRIT_MEMORY|                    \
                        ALERT_CRIT_HW_INCOMP|ALERT_CRIT_REDUNDANT_POWER)&0x0FFFFFFF)

#define ALERT_WARN_MASK  ((ALERT_WARN_OTHER|ALERT_WARN_TEMP|ALERT_WARN_VOLT|ALERT_WARN_POWER|ALERT_WARN_FAN| \
                        ALERT_WARN_CPU|ALERT_WARN_MEMORY|ALERT_WARN_REDUND_POWER)&0x0FFFFFFF)

#define ALERT_SYS_MASK   ((ALERT_SYS_OTHER|ALERT_SYS_REMOTE_LOGIN|ALERT_SYS_OS_TIMEOUT|ALERT_SYS_POWER_ON|   \
                        ALERT_SYS_POWER_OFF|ALERT_SYS_BOOT_FAIL|ALERT_SYS_LOAD_TIMEOUT|                     \
                        ALERT_SYS_PREDICTE_FAIL|ALERT_SYS_EVENT_LOG_75_FULL|ALERT_SYS_NET_EVENT|ALERT_SYS_ALL_AUDIT)&0x0FFFFFFF)

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_ALERTCONFIGURATIONSETTING_INIT_SUPPORT /* You can turn on this flag in IBM_AlertConfigurationSettingAgent.h */
#define PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AlertConfigurationSetting;\
    Arg.GetKeyProperty = IBM_AlertConfigurationSetting_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AlertConfigurationSetting_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AlertConfigurationSetting_GetProperty;\
    Arg.KeyPropertyList = IBM_AlertConfigurationSettingKeyPropertyList;\
    Arg.PropertyList = IBM_AlertConfigurationSettingPropertyList;\
    Arg.propertyNo = sizeof(IBM_AlertConfigurationSettingPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AlertConfigurationSettingKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ALERTCONFIGURATIONSETTINGASSONUM;\
    Arg.AssocArray = G_sLenovo_AlertConfigurationSettingAssociations;\
    Arg.AgentInit = IBM_AlertConfigurationSetting_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AlertConfigurationSetting_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AlertConfigurationSetting;\
    Arg.GetKeyProperty = IBM_AlertConfigurationSetting_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AlertConfigurationSetting_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AlertConfigurationSetting_GetProperty;\
    Arg.KeyPropertyList = IBM_AlertConfigurationSettingKeyPropertyList;\
    Arg.PropertyList = IBM_AlertConfigurationSettingPropertyList;\
    Arg.propertyNo = sizeof(IBM_AlertConfigurationSettingPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AlertConfigurationSettingKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ALERTCONFIGURATIONSETTINGASSONUM;\
    Arg.AssocArray = G_sLenovo_AlertConfigurationSettingAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_ALERTCONFIGURATIONSETTING_INIT_SUPPORT /* You can turn on this flag in IBM_AlertConfigurationSettingAgent.h */
#define PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AlertConfigurationSetting;\
    Arg.GetKeyProperty = IBM_AlertConfigurationSetting_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AlertConfigurationSetting_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AlertConfigurationSetting_GetProperty;\
    Arg.KeyPropertyList = IBM_AlertConfigurationSettingKeyPropertyList;\
    Arg.PropertyList = IBM_AlertConfigurationSettingPropertyList;\
    Arg.propertyNo = sizeof(IBM_AlertConfigurationSettingPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AlertConfigurationSettingKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ALERTCONFIGURATIONSETTINGASSONUM;\
    Arg.AssocArray = G_sLenovo_AlertConfigurationSettingAssociations;\
    Arg.AgentInit = IBM_AlertConfigurationSetting_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AlertConfigurationSetting_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AlertConfigurationSetting;\
    Arg.GetKeyProperty = IBM_AlertConfigurationSetting_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AlertConfigurationSetting_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AlertConfigurationSetting_GetProperty;\
    Arg.KeyPropertyList = IBM_AlertConfigurationSettingKeyPropertyList;\
    Arg.PropertyList = IBM_AlertConfigurationSettingPropertyList;\
    Arg.propertyNo = sizeof(IBM_AlertConfigurationSettingPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AlertConfigurationSettingKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ALERTCONFIGURATIONSETTINGASSONUM;\
    Arg.AssocArray = G_sLenovo_AlertConfigurationSettingAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_AlertConfigurationSetting_GetProperty( 
                                                    CMPICount nInstIndex,
                                                    CMPICount nPropIndex,
                                                    void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_AlertConfigurationSetting_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_AlertConfigurationSetting_GetKeyProperty( 
                                                       CMPICount nInstIndex,
                                                       CMPICount nKeyIndex,
                                                       void *pAgentDataPtr)
{
    CMPIData data;
        data.state = CMPI_badValue;
    data = IBM_AlertConfigurationSetting_GetProperty(nInstIndex, nKeyIndex | IBM_ALERTCONFIGURATIONSETTING_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_AlertConfigurationSetting_GenerateObjectPath( 
                                                                  char **properties,
                                                                  CMPICount InstIndex,
                                                                  void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_AlertConfigurationSetting_GetInstance( 
                                                      CMPIInstanceMI *mi,
                                                      const CMPIContext *ctx,
                                                      const CMPIResult *rslt,
                                                      const CMPIObjectPath *op,
                                                      const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_AlertConfigurationSetting_EnumInstances( 
#else
CMPIStatus IBM_AlertConfigurationSetting_EnumerateInstances( 
#endif
                                                             CMPIInstanceMI *mi,
                                                             const CMPIContext *ctx,
                                                             const CMPIResult *rslt,
                                                             const CMPIObjectPath *op,
                                                             const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_AlertConfigurationSetting_EnumInstanceNames( 
#else
CMPIStatus IBM_AlertConfigurationSetting_EnumerateInstanceNames( 
#endif
                                                                 CMPIInstanceMI *mi,
                                                                 const CMPIContext *ctx,
                                                                 const CMPIResult *rslt,
                                                                 const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_AlertConfigurationSetting_Associators( 
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
    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_AlertConfigurationSetting_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_AlertConfigurationSetting_References( 
                                                     CMPIAssociationMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op,
                                                     const char *resultClass,
                                                     const char *role,
                                                     const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_AlertConfigurationSetting_ReferenceNames( 
                                                         CMPIAssociationMI *mi,
                                                         const CMPIContext *ctx,
                                                         const CMPIResult *rslt,
                                                         const CMPIObjectPath *op,
                                                         const char *resultClass,
                                                         const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_AlertConfigurationSetting_CheckSelectorSet( 
                                                          const CMPIObjectPath *op,
                                                          CMPIBoolean bAllKey,
                                                          void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);
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
CMPIStatus IBM_AlertConfigurationSetting_ModifyInstance(
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

    UINT32 *pu32EnabledOOBAlerts = NULL;
    int iEnabledOOBAlerts = 0;
    UINT32 *pu32EnabledOOBAlertFilters = NULL;
    int iEnabledOOBAlertFilters = 0;
    CMPIArray *pTempArray;
    CMPIData arrayElement;

    sAlertMgrData   sAlertEntryData;
    BOOL IsAlertDataExsit = FALSE;
    UINT8 u8CateTbl[] = {0x0, 0x0, 0x0};
    UINT32 u32SubCateTbl[] = {0x0, 0x0, 0x0};
    int i = 0;
    void *pAgentDataPtr = NULL;

    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg);

#if IBM_ALERTCONFIGURATIONSETTING_INIT_SUPPORT
    pAgentDataPtr = Arg.AgentInit(0);
#endif

    /* Check SelectorSet */
    instIndex = IBM_AlertConfigurationSetting_CheckSelectorSet(op, CMPITRUE, pAgentDataPtr);
    if (instIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_AlertConfigurationSettingPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  // CMPI_RC_ERR_NO_SUCH_PROPERTY 
        goto ERR_EXIT;
    }
    if (ctx == NULL)
    {
	    rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
	    goto ERR_EXIT;
    }

    /* Read EnabledOOBAlerts from input property */
    data = inst->ft->getProperty(inst, IBM_AlertConfigurationSettingPropertyList[1], &rc);
    if (data.state == CMPI_goodValue)
    {
        //logTraceCIM(LOG_LEV_INFO, "%s()- Get PROPERTYNAME_EnabledOOBAlerts.", __FUNCTION__);
        if (data.type == CMPI_uint16)
        {
            iEnabledOOBAlerts = 1;
            pu32EnabledOOBAlerts= Malloc(iEnabledOOBAlerts * sizeof(UINT32));
            if(!pu32EnabledOOBAlerts)
            {
                 CMPIDataRelease(&data);
                 goto ERR_EXIT;
            }
            pu32EnabledOOBAlerts[0] = (UINT32) data.value.uint16;
            
            CMPIDataRelease(&data);
        }
        else if (data.type == CMPI_uint16A)
        {
            /* check CMPIArray size  */
            pTempArray = data.value.array;

            iEnabledOOBAlerts = pTempArray->ft->getSize(pTempArray, &rc);
            //logTraceCIM(LOG_LEV_INFO, "%s()- number of OOBAlerts=%d.", __FUNCTION__, iEnabledOOBAlerts);
            if (rc.rc != CMPI_RC_OK)
            {
                CMPIDataRelease(&data);
                goto ERR_EXIT;
            }

            pu32EnabledOOBAlerts= Malloc(iEnabledOOBAlerts * sizeof(UINT32));
            if(!pu32EnabledOOBAlerts)
            {
                CMPIDataRelease(&data);
                goto ERR_EXIT;
            }
            
            for(i = 0; i< iEnabledOOBAlerts; i++)
            {
                arrayElement = pTempArray->ft->getElementAt(pTempArray, i, &rc);               
                if ((arrayElement.state != CMPI_goodValue) || (rc.rc != CMPI_RC_OK) || (arrayElement.type != CMPI_uint16))
                {
                    CMPIDataRelease(&data);
                    CMPIDataRelease(&arrayElement);
                    goto ERR_EXIT;
                }
                pu32EnabledOOBAlerts[i] = (UINT32) arrayElement.value.uint16;
                
                //logTraceCIM(LOG_LEV_INFO, "%s()- pu32EnabledOOBAlerts=%d.", __FUNCTION__, (UINT32) arrayElement.value.uint16);
                CMPIDataRelease(&arrayElement);
            }
            CMPIDataRelease(&data);
            
        }

        if(FALSE == IBM_AlertConfigurationSetting_InstAgent_GetOOBAlertType(
                        pu32EnabledOOBAlerts, iEnabledOOBAlerts, (UINT8 *) &u8CateTbl))
        {
            rc.rc =CMPI_RC_ERR_INVALID_PARAMETER;
            goto ERR_EXIT;
        }
        else
        {
            IsAlertDataExsit =TRUE;
        }

        //logTraceCIM(LOG_LEV_INFO, "%s()- smash data M-->index=%d, 0x%1x,0x%1x,0x%1x.", __FUNCTION__, instIndex, u8CateTbl[0], u8CateTbl[1], u8CateTbl[2]);
    }

    /* Read EnabledOOBAlertFilters from input property */
    data = inst->ft->getProperty(inst, IBM_AlertConfigurationSettingPropertyList[0], &rc);
    if (data.state == CMPI_goodValue)
    {

        if (data.type == CMPI_uint16)
        {
            iEnabledOOBAlertFilters = 1;
            pu32EnabledOOBAlertFilters= Malloc(iEnabledOOBAlertFilters * sizeof(UINT32));
            if(!pu32EnabledOOBAlertFilters)
            {
                CMPIDataRelease(&data);
                goto ERR_EXIT;
            }
            pu32EnabledOOBAlertFilters[0] = (UINT32) data.value.uint16;
            
            CMPIDataRelease(&data);
        }
        else if (data.type == CMPI_uint16A)
        {
            /* check CMPIArray size  */
            pTempArray = data.value.array;

            iEnabledOOBAlertFilters = pTempArray->ft->getSize(pTempArray, &rc);
            //logTraceCIM(LOG_LEV_INFO, "%s()- number of OOBAlertFilters=%d.", __FUNCTION__, iEnabledOOBAlertFilters);

            if (rc.rc != CMPI_RC_OK)
            {
                CMPIDataRelease(&data);
                goto ERR_EXIT;
            }

            pu32EnabledOOBAlertFilters= Malloc(iEnabledOOBAlertFilters * sizeof(UINT32));
            if (!pu32EnabledOOBAlertFilters)
            {
                CMPIDataRelease(&data);
                goto ERR_EXIT;
            }
            
            for (i = 0; i< iEnabledOOBAlertFilters; i++)
            {
                arrayElement = pTempArray->ft->getElementAt(pTempArray, i, &rc);
                
                if ((arrayElement.state != CMPI_goodValue) || (rc.rc != CMPI_RC_OK))
                {
                    CMPIDataRelease(&data);
                    CMPIDataRelease(&arrayElement);
                    goto ERR_EXIT;
                }

                pu32EnabledOOBAlertFilters[i] = (UINT32) arrayElement.value.uint16;
                //logTraceCIM(LOG_LEV_INFO, "%s()- pu32EnabledOOBAlertFilters=%d.", __FUNCTION__,  (UINT32) arrayElement.value.uint16);

                CMPIDataRelease(&arrayElement);
            }
            CMPIDataRelease(&data);
            
        }

        if(FALSE == IBM_AlertConfigurationSetting_InstAgent_GetOOBAlertFilterType(
                        pu32EnabledOOBAlertFilters, iEnabledOOBAlertFilters,  (UINT32 *)&u32SubCateTbl))
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto ERR_EXIT;
        }
        else
        {
            IsAlertDataExsit =TRUE;
        }
        //logTraceCIM(LOG_LEV_INFO, "%s()- [%d]smash data S-->index=%d, 0x%08x,0x%08x,0x%08x.", __FUNCTION__, instIndex, u32SubCateTbl[0], u32SubCateTbl[1], u32SubCateTbl[2]);
    }

    if (IsAlertDataExsit)
    {
        alertmgr_setting_init(&sAlertEntryData);
        sAlertEntryData.u8CriticalAlert= u8CateTbl[0];
        sAlertEntryData.u8WarningAlert = u8CateTbl[1];
        sAlertEntryData.u8SysinfoAlert = u8CateTbl[2];
        sAlertEntryData.u32SubCriticalAlert= u32SubCateTbl[0] & ALERT_CRIT_MASK;
        sAlertEntryData.u32SubWarningAlert = u32SubCateTbl[1] & ALERT_WARN_MASK;
        sAlertEntryData.u32SubSysinfoAlert = u32SubCateTbl[2] & ALERT_SYS_MASK;
        CMPIGetUserNameFromContext(ctx, sAlertEntryData.szUserID);
        
        if (alertmgr_setting_set((UINT8) instIndex, &sAlertEntryData) != ALERTMGR_OK)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Set Alert Recipient [%d] Filter Info (Sub category) Fail.", __FUNCTION__, instIndex);
            rc.rc =CMPI_RC_ERR_FAILED;
            goto ERR_EXIT;
        }
    }

	rc.rc = CMPI_RC_OK;

ERR_EXIT:

    ExistFree(pu32EnabledOOBAlertFilters);

    ExistFree(pu32EnabledOOBAlerts);

#if IBM_ALERTCONFIGURATIONSETTING_INIT_SUPPORT
    Arg.AgentDestroy(pAgentDataPtr);
#endif

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}



/* IBM_AlertConfigurationSetting Class Service Function */
CMPIStatus Lenovo_AlertConfigurationSettingService( 
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





    
    if (actionID == CLASS_SERVICE_ISA_LITE)
    {
        va_start(argptr, op);
        className = va_arg(argptr, char *);
        va_end(argptr);
    }

    rc = CIMClassUtil_CheckClassName(actionID, mi, ctx, rslt, op, 
                                     className,
                                     (char *) CLASSNAME_Lenovo_IBM_AlertConfigurationSetting,
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
            rc = IBM_AlertConfigurationSetting_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_AlertConfigurationSetting_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_AlertConfigurationSetting_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_ALERTCONFIGURATIONSETTING_INIT_SUPPORT
            rc.msg = (void*) &IBM_AlertConfigurationSetting_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_ALERTCONFIGURATIONSETTING_INIT_SUPPORT
            rc.msg = (void*) &IBM_AlertConfigurationSetting_InstAgent_Destroy;
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
            rc = IBM_AlertConfigurationSetting_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_AlertConfigurationSetting_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_AlertConfigurationSetting_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_AlertConfigurationSetting_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_AlertConfigurationSetting_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_AlertConfigurationSetting_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_AlertConfigurationSetting_InstAgent_GetMaxIndex;
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
            rc = IBM_AlertConfigurationSetting_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_AlertConfigurationSetting);
//GenNotSupportInstanceMIModifyInstance(IBM_AlertConfigurationSetting);
GenNotSupportInstanceMIDeleteInstance(IBM_AlertConfigurationSetting);
GenNotSupportInstanceMIExecQuery(IBM_AlertConfigurationSetting);
GenNotSupportInstanceMICleanup(IBM_AlertConfigurationSetting);

/* MI factory function */
CMInstanceMIStub( IBM_AlertConfigurationSetting_,
                  Lenovo_AlertConfigurationSetting_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_ALERTCONFIGURATIONSETTING_INIT_SUPPORT /* You can turn on this flag in IBM_AlertConfigurationSettingAgent.h */
#define PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg) \
    Arg.AgentGetProperty = IBM_AlertConfigurationSetting_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AlertConfigurationSetting;\
    Arg.GetNextInstIndex = IBM_AlertConfigurationSetting_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_AlertConfigurationSettingKeyPropertyList;\
    Arg.PropertyList = IBM_AlertConfigurationSettingPropertyList;\
    Arg.propertyNo = sizeof(IBM_AlertConfigurationSettingPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AlertConfigurationSettingKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_AlertConfigurationSetting_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AlertConfigurationSetting_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG(Arg) \
    Arg.AgentGetProperty = IBM_AlertConfigurationSetting_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AlertConfigurationSetting;\
    Arg.GetNextInstIndex = IBM_AlertConfigurationSetting_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_AlertConfigurationSettingKeyPropertyList;\
    Arg.PropertyList = IBM_AlertConfigurationSettingPropertyList;\
    Arg.propertyNo = sizeof(IBM_AlertConfigurationSettingPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AlertConfigurationSettingKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_AlertConfigurationSetting Class Service Function */
CMPIStatus Lenovo_AlertConfigurationSettingService( 
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

/* Gets the Arg of Class IBM_AlertConfigurationSetting Function */
sClassUtilArg IBM_AlertConfigurationSetting_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_ALERTCONFIGURATIONSETTING_ARG( Arg );

    return (Arg);
}

#endif
