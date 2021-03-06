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
#include <emerson/aem/aem_lib.h>

#ifndef _BROKER_SFCB
#include "MethodNames.h"
#endif
/* Include class header files */
#include <RegisterClass.h>

/* Include agent header files */
#include <RegisterClassAgent.h>

#include "../AssociationTable.h"

#include <emerson/tm/tm.h>


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

#define MAX_ACCESSINFO_LEN (253)

/* IBM_NTPRemoteAccess class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_NTPRemoteAccess = (CMPIUint8 *)CLASSNAMETEXT_IBM_NTPRemoteAccess;

/* Property List */
static const char * const IBM_NTPRemoteAccessPropertyList[] = 
{
    PROPERTYNAME_AccessContext,
    PROPERTYNAME_AccessInfo,
    PROPERTYNAME_InfoFormat,
    PROPERTYNAME_OtherAccessContext,
    PROPERTYNAME_PortInfo,
    PROPERTYNAME_PortProtocol
};

/* Key property List */
static const char * const IBM_NTPRemoteAccessKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_NTPREMOTEACCESS_INIT_SUPPORT /* You can turn on this flag in IBM_NTPRemoteAccessAgent.h */
#define PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_NTPRemoteAccess;\
    Arg.GetKeyProperty = IBM_NTPRemoteAccess_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_NTPRemoteAccess_InstAgent_GetNext;\
    Arg.GetProperty = IBM_NTPRemoteAccess_GetProperty;\
    Arg.KeyPropertyList = IBM_NTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_NTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_NTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_NTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_NTPREMOTEACCESSASSONUM;\
    Arg.AssocArray = G_sLenovo_NTPRemoteAccessAssociations;\
    Arg.AgentInit = IBM_NTPRemoteAccess_InstAgent_Init;\
    Arg.AgentDestroy = IBM_NTPRemoteAccess_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_NTPRemoteAccess;\
    Arg.GetKeyProperty = IBM_NTPRemoteAccess_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_NTPRemoteAccess_InstAgent_GetNext;\
    Arg.GetProperty = IBM_NTPRemoteAccess_GetProperty;\
    Arg.KeyPropertyList = IBM_NTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_NTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_NTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_NTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_NTPREMOTEACCESSASSONUM;\
    Arg.AssocArray = G_sLenovo_NTPRemoteAccessAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_NTPREMOTEACCESS_INIT_SUPPORT /* You can turn on this flag in IBM_NTPRemoteAccessAgent.h */
#define PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_NTPRemoteAccess;\
    Arg.GetKeyProperty = IBM_NTPRemoteAccess_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_NTPRemoteAccess_InstAgent_GetNext;\
    Arg.GetProperty = IBM_NTPRemoteAccess_GetProperty;\
    Arg.KeyPropertyList = IBM_NTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_NTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_NTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_NTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_NTPREMOTEACCESSASSONUM;\
    Arg.AssocArray = G_sLenovo_NTPRemoteAccessAssociations;\
    Arg.AgentInit = IBM_NTPRemoteAccess_InstAgent_Init;\
    Arg.AgentDestroy = IBM_NTPRemoteAccess_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_NTPRemoteAccess;\
    Arg.GetKeyProperty = IBM_NTPRemoteAccess_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_NTPRemoteAccess_InstAgent_GetNext;\
    Arg.GetProperty = IBM_NTPRemoteAccess_GetProperty;\
    Arg.KeyPropertyList = IBM_NTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_NTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_NTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_NTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_NTPREMOTEACCESSASSONUM;\
    Arg.AssocArray = G_sLenovo_NTPRemoteAccessAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_NTPRemoteAccess_GetProperty( 
                                          CMPICount nInstIndex,
                                          CMPICount nPropIndex,
                                          void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_NTPRemoteAccess_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_NTPRemoteAccess_GetKeyProperty( 
                                             CMPICount nInstIndex,
                                             CMPICount nKeyIndex,
                                             void *pAgentDataPtr)
{
    CMPIData data = {CMPI_string};
    CMPIStatus rc;

    data.state = CMPI_badValue;

    if (nKeyIndex == 0) /* CreationClassName */
    {
        #ifdef _BROKER_SFCB
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_NTPRemoteAccess, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_NTPRemoteAccess, &rc);
        #endif

        if (data.value.string != NULL)
        {
            data.type = CMPI_string;
            data.state = CMPI_goodValue;
        }
    }
    else
    {
        data.state = CMPI_badValue;
        data = IBM_NTPRemoteAccess_GetProperty(nInstIndex, nKeyIndex | IBM_NTPREMOTEACCESS_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_NTPRemoteAccess_GenerateObjectPath( 
                                                        char **properties,
                                                        CMPICount InstIndex,
                                                        void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_NTPRemoteAccess_GetInstance( 
                                            CMPIInstanceMI *mi,
                                            const CMPIContext *ctx,
                                            const CMPIResult *rslt,
                                            const CMPIObjectPath *op,
                                            const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_NTPRemoteAccess_EnumInstances( 
#else
CMPIStatus IBM_NTPRemoteAccess_EnumerateInstances( 
#endif
                                                   CMPIInstanceMI *mi,
                                                   const CMPIContext *ctx,
                                                   const CMPIResult *rslt,
                                                   const CMPIObjectPath *op,
                                                   const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_NTPRemoteAccess_EnumInstanceNames( 
#else
CMPIStatus IBM_NTPRemoteAccess_EnumerateInstanceNames( 
#endif
                                                       CMPIInstanceMI *mi,
                                                       const CMPIContext *ctx,
                                                       const CMPIResult *rslt,
                                                       const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_NTPRemoteAccess_Associators( 
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
    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_NTPRemoteAccess_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_NTPRemoteAccess_References( 
                                           CMPIAssociationMI *mi,
                                           const CMPIContext *ctx,
                                           const CMPIResult *rslt,
                                           const CMPIObjectPath *op,
                                           const char *resultClass,
                                           const char *role,
                                           const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_NTPRemoteAccess_ReferenceNames( 
                                               CMPIAssociationMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char *resultClass,
                                               const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_NTPRemoteAccess_ModifyInstance(
                                              CMPIInstanceMI *mi,
                                              const CMPIContext *ctx,
                                              const CMPIResult *rslt,
                                              const CMPIObjectPath *op,
                                              const CMPIInstance * inst,
                                              const char **properties
                                             )
{
    CMPIStatus rc =
    {
        CMPI_RC_ERR_FAILED,
        NULL
    };
    CMPICount nIndex = 0;
    void *pAgentDataPtr = NULL;
    sClassUtilArg Arg;
    CMPIData data;
    CMPIString *dataStr = NULL;
    UINT8 au8AccessInfo[MAX_ACCESSINFO_LEN] = {0};
    char *szAccessInfo = NULL;
    int iLenAccessInfo = 0;
    bool bRet = false;
    int iRet = 0;
    UINT8 au8AimVar[MAX_ACCESSINFO_LEN] = {0};
    sSwMsg_TimeSyncCfg timeSync_cfg;
    int iValue = 0;
    UINT8 au8CurrentAccessInfo[MAX_ACCESSINFO_LEN] = {0};

    if (inst == NULL)
    {
        return (rc);
    }

    if (IsBladeServer())
    {
        rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
        return (rc);
    }
    
    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg);

    pAgentDataPtr = IBM_NTPRemoteAccess_InstAgent_Init(0);

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_NTPRemoteAccessPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    /* check static property values if neccessary */
    /* call modify API here */

    if(ctx == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }

    data = inst->ft->getProperty( inst, IBM_NTPRemoteAccessPropertyList[1], &rc); 
    if(data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; /* CMPI_RC_ERR_NO_SUCH_PROPERTY; */
        goto ERR_EXIT;
    }
    
    dataStr = CMPIData2String(&data);
    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY; */
        goto ERR_EXIT;
    }

    memset(au8AccessInfo, 0, sizeof(au8AccessInfo));
    szAccessInfo = (char *)dataStr->ft->getCharPtr(dataStr, &rc);
    iLenAccessInfo = strlen(szAccessInfo);
    memcpy(au8AccessInfo, szAccessInfo, (iLenAccessInfo > (MAX_ACCESSINFO_LEN - 1)) ? (MAX_ACCESSINFO_LEN - 1) : iLenAccessInfo);

    //logTraceCIM(LOG_LEV_INFO, "%s()- AccessInfo data type:[%X] Value:[%s].", __FUNCTION__, data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc));

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

    if (au8AccessInfo == NULL)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Invalid parameter, no such data to set.", __FUNCTION__);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; /* No such data to set; */
        goto ERR_EXIT;
    }

	
    memset(au8AimVar, 0, sizeof(au8AimVar));
    snprintf((char *)au8AimVar, sizeof(au8AimVar), "tm_ntp_str_server%d", nIndex+1);

    //check AccessInfo
    memset(au8CurrentAccessInfo, 0 ,sizeof(au8CurrentAccessInfo));
    bRet = aim_config_get_str_n((char *) au8AimVar, (char *) au8CurrentAccessInfo, sizeof(au8CurrentAccessInfo));
    if (!bRet)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to call aim_config_get_int(%s).", __FUNCTION__, TM_NTP_UPD_FREQ);
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }
    
    if (strncmp((char *) au8AccessInfo, (char *) au8CurrentAccessInfo, MAX_ACCESSINFO_LEN) == 0)
    {        
        logTraceCIM(LOG_LEV_INFO, "%s()- AccessInfo value is the same with current value, no event occure.", __FUNCTION__);
        rc.rc = CMPI_RC_OK;
        goto ERR_EXIT;
    }

    bRet = aim_config_set_str_n((char *) au8AimVar, (char *) au8AccessInfo, TRUE);
    if (!bRet)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to call aim_config_set_str(%s).", __FUNCTION__, au8AimVar);
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }

    //logTraceCIM(LOG_LEV_INFO, "%s()- Set AccessInfo-> ret(%i).", __FUNCTION__, iRet);

    // Send event out to alert tm use new config
    bRet = aim_event_occurred("event_tm_ntp_config", 0, NULL);
    if (!bRet)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to call aim_event_occurred(event_tm_ntp_config)", __FUNCTION__);
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }
     
    // Send software event 
    memset(&timeSync_cfg, 0, sizeof(timeSync_cfg));
    CMPIGetUserNameFromContext(ctx, timeSync_cfg.c_UserID);
    
    bRet = aim_config_get_int(TM_NTP_MODE, &iValue);
    if (!bRet)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to call aim_config_get_int(TM_NTP_MODE).", __FUNCTION__);
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }
    else
    {
        timeSync_cfg.u8IsSyncWithNTPServer = (UINT8) iValue;
    }
            
    iRet = sw_msg_dispatcher(SW_MSGID_TIME_SYNC_CONFIGURED, (void *) &timeSync_cfg);
    if (iRet != CEM_RC_OK)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call sw_msg_dispatcher(SW_MSGID_TIME_SYNC_CONFIGURED), rc is %d.", __FUNCTION__, iRet);
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }

    rc.rc = CMPI_RC_OK;

ERR_EXIT:

    IBM_NTPRemoteAccess_InstAgent_Destroy(pAgentDataPtr);

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

/* IBM_NTPRemoteAccess Class Service Function */
CMPIStatus Lenovo_NTPRemoteAccessService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_NTPRemoteAccess,
                                     CIM_RemotePortService);
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
            rc = IBM_NTPRemoteAccess_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_NTPRemoteAccess_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_NTPRemoteAccess_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_NTPREMOTEACCESS_INIT_SUPPORT
            rc.msg = (void*) &IBM_NTPRemoteAccess_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_NTPREMOTEACCESS_INIT_SUPPORT
            rc.msg = (void*) &IBM_NTPRemoteAccess_InstAgent_Destroy;
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
            rc = IBM_NTPRemoteAccess_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_NTPRemoteAccess_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_NTPRemoteAccess_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_NTPRemoteAccess_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_NTPRemoteAccess_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_NTPRemoteAccess_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_NTPRemoteAccess_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_NTPRemoteAccess_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
             /* involk method service */
        case CLASS_SERVICE_GETMETHODNAMES:
             /* get method name service */
        case CLASS_SERVICE_GETPARAMETERS:
             /* get method param name service */
        case CLASS_SERVICE_CREATEINSTANCE:
            /* create instance service */
        case CLASS_SERVICE_DELETEINSTANCE:
            /* delete instance service */
        case CLASS_SERVICE_GETPROPERTY:
            /* get property service */
        case CLASS_SERVICE_SETPROPERTY:   
            /* set property service */
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
GenNotSupportInstanceMICreateInstance(IBM_NTPRemoteAccess);
// GenNotSupportInstanceMIModifyInstance(IBM_NTPRemoteAccess);
GenNotSupportInstanceMIDeleteInstance(IBM_NTPRemoteAccess);
GenNotSupportInstanceMIExecQuery(IBM_NTPRemoteAccess);
GenNotSupportInstanceMICleanup(IBM_NTPRemoteAccess);

/* MI factory function */
CMInstanceMIStub( IBM_NTPRemoteAccess_,
                  Lenovo_NTPRemoteAccess_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_NTPREMOTEACCESS_INIT_SUPPORT /* You can turn on this flag in IBM_NTPRemoteAccessAgent.h */
#define PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg) \
    Arg.AgentGetProperty = IBM_NTPRemoteAccess_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_NTPRemoteAccess;\
    Arg.GetNextInstIndex = IBM_NTPRemoteAccess_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_NTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_NTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_NTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_NTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_NTPRemoteAccess_InstAgent_Init;\
    Arg.AgentDestroy = IBM_NTPRemoteAccess_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG(Arg) \
    Arg.AgentGetProperty = IBM_NTPRemoteAccess_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_NTPRemoteAccess;\
    Arg.GetNextInstIndex = IBM_NTPRemoteAccess_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_NTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_NTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_NTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_NTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_NTPRemoteAccess Class Service Function */
CMPIStatus Lenovo_NTPRemoteAccessService( 
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

/* Gets the Arg of Class IBM_NTPRemoteAccess Function */
sClassUtilArg IBM_NTPRemoteAccess_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_NTPREMOTEACCESS_ARG( Arg );

    return (Arg);
}

#endif
