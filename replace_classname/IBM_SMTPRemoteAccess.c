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
#include <sys/socket.h>
#include <SmashCommonUtil.h>

#include "LogUtil.h"
#include <emerson/pm/avct_valid.h>

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

bool IsValidAddress(int nFamily, char *szAddress, char *szNetMask);

/* IBM_SMTPRemoteAccess class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_SMTPRemoteAccess = (CMPIUint8 *)CLASSNAMETEXT_IBM_SMTPRemoteAccess;

/* Property List */
static const char * const IBM_SMTPRemoteAccessPropertyList[] = 
{
    PROPERTYNAME_AccessContext,
    PROPERTYNAME_AccessInfo,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_InfoFormat,
    PROPERTYNAME_PortInfo
};

/* Key property List */
static const char * const IBM_SMTPRemoteAccessKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_SMTPREMOTEACCESS_INIT_SUPPORT /* You can turn on this flag in IBM_SMTPRemoteAccessAgent.h */
#define PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPRemoteAccess;\
    Arg.GetKeyProperty = IBM_SMTPRemoteAccess_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SMTPRemoteAccess_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SMTPRemoteAccess_GetProperty;\
    Arg.KeyPropertyList = IBM_SMTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SMTPREMOTEACCESSASSONUM;\
    Arg.AssocArray = G_sLenovo_SMTPRemoteAccessAssociations;\
    Arg.AgentInit = IBM_SMTPRemoteAccess_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SMTPRemoteAccess_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPRemoteAccess;\
    Arg.GetKeyProperty = IBM_SMTPRemoteAccess_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SMTPRemoteAccess_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SMTPRemoteAccess_GetProperty;\
    Arg.KeyPropertyList = IBM_SMTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SMTPREMOTEACCESSASSONUM;\
    Arg.AssocArray = G_sLenovo_SMTPRemoteAccessAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_SMTPREMOTEACCESS_INIT_SUPPORT /* You can turn on this flag in IBM_SMTPRemoteAccessAgent.h */
#define PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPRemoteAccess;\
    Arg.GetKeyProperty = IBM_SMTPRemoteAccess_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SMTPRemoteAccess_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SMTPRemoteAccess_GetProperty;\
    Arg.KeyPropertyList = IBM_SMTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SMTPREMOTEACCESSASSONUM;\
    Arg.AssocArray = G_sLenovo_SMTPRemoteAccessAssociations;\
    Arg.AgentInit = IBM_SMTPRemoteAccess_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SMTPRemoteAccess_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPRemoteAccess;\
    Arg.GetKeyProperty = IBM_SMTPRemoteAccess_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SMTPRemoteAccess_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SMTPRemoteAccess_GetProperty;\
    Arg.KeyPropertyList = IBM_SMTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SMTPREMOTEACCESSASSONUM;\
    Arg.AssocArray = G_sLenovo_SMTPRemoteAccessAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_SMTPRemoteAccess_GetProperty( 
                                           CMPICount nInstIndex,
                                           CMPICount nPropIndex,
                                           void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_SMTPRemoteAccess_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_SMTPRemoteAccess_GetKeyProperty( 
                                              CMPICount nInstIndex,
                                              CMPICount nKeyIndex,
                                              void *pAgentDataPtr)
{
    CMPIData data = {CMPI_string, CMPI_badValue, {0}};
    CMPIStatus rc;

    data.state = CMPI_badValue;

    if (nKeyIndex == 0) /* CreationClassName */
    {
        #ifdef _BROKER_SFCB
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_SMTPRemoteAccess, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_SMTPRemoteAccess, &rc);
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
        data = IBM_SMTPRemoteAccess_GetProperty(nInstIndex, nKeyIndex | IBM_SMTPREMOTEACCESS_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_SMTPRemoteAccess_GenerateObjectPath( 
                                                         char **properties,
                                                         CMPICount InstIndex,
                                                         void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_SMTPRemoteAccess_GetInstance( 
                                             CMPIInstanceMI *mi,
                                             const CMPIContext *ctx,
                                             const CMPIResult *rslt,
                                             const CMPIObjectPath *op,
                                             const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SMTPRemoteAccess_EnumInstances( 
#else
CMPIStatus IBM_SMTPRemoteAccess_EnumerateInstances( 
#endif
                                                    CMPIInstanceMI *mi,
                                                    const CMPIContext *ctx,
                                                    const CMPIResult *rslt,
                                                    const CMPIObjectPath *op,
                                                    const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SMTPRemoteAccess_EnumInstanceNames( 
#else
CMPIStatus IBM_SMTPRemoteAccess_EnumerateInstanceNames( 
#endif
                                                        CMPIInstanceMI *mi,
                                                        const CMPIContext *ctx,
                                                        const CMPIResult *rslt,
                                                        const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_SMTPRemoteAccess_Associators( 
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
    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_SMTPRemoteAccess_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_SMTPRemoteAccess_References( 
                                            CMPIAssociationMI *mi,
                                            const CMPIContext *ctx,
                                            const CMPIResult *rslt,
                                            const CMPIObjectPath *op,
                                            const char *resultClass,
                                            const char *role,
                                            const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_SMTPRemoteAccess_ReferenceNames( 
                                                CMPIAssociationMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char *resultClass,
                                                const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_SMTPRemoteAccess_CheckSelectorSet( 
                                                         const CMPIObjectPath *op,
                                                         CMPIBoolean bAllKey,
                                                         void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);
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

CMPIStatus IBM_SMTPRemoteAccess_ModifyInstance(
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
    UINT8 au8AccessInfo[MAX_ACCESSINFO_LEN];
    char *szAccessInfo = NULL;
    int iLenAccessInfo = 0;
    int iRet;

    UINT8 * pu8PortInfo = NULL;
    UINT8 * pu8Stop = NULL;
    UINT8 au8PortInfo[MAX_PORTINFO_LEN] = {0};
    INT32 i32PortInfo = 0;

    memset((void *)&data, 0 , sizeof(data));
    data.state = CMPI_nullValue;

    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg);

    /* Check SelectorSet */
    instIndex = IBM_SMTPRemoteAccess_CheckSelectorSet(op, CMPITRUE, NULL);
    if (instIndex == INSTANCE_INDEX_INVALID)
    {
        goto ERR_EXIT;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_SMTPRemoteAccessPropertyList))
    {
        goto ERR_EXIT;
    }

    if (ctx == NULL)
    {
        goto ERR_EXIT;
    }

    /* Read AccessInfo from input property */
    data = inst->ft->getProperty(inst, IBM_SMTPRemoteAccessPropertyList[1], &rc);
    if ((CMPI_RC_OK != rc.rc) || (data.state != CMPI_goodValue))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to get parameter AccessInfo.", __FUNCTION__);
        goto ERR_EXIT;
    }   

    dataStr = CMPIData2String(&data);   
    if(dataStr == NULL)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to convert AccessInfo to string.", __FUNCTION__);
        goto ERR_EXIT;
    }       
    
    memset(au8AccessInfo, 0, sizeof (au8AccessInfo));
    szAccessInfo = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
    iLenAccessInfo = strlen(szAccessInfo);
    memcpy(au8AccessInfo, szAccessInfo, (MAX_ACCESSINFO_LEN >= iLenAccessInfo) ? iLenAccessInfo : MAX_ACCESSINFO_LEN);

    //logTraceCIM(LOG_LEV_INFO, "%s()- AccessInfo data type:[%X] Value:[%s].", __FUNCTION__, data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc));

    TrimString((void *)au8AccessInfo);

    /* validate server address or host name */
    if ((!IsValidServerName((void *)au8AccessInfo)))
    {
        /* invalid SMTP server address or host name */
        logTraceCIM(LOG_LEV_ERROR, "%s()- Invalid SMTP server address or host name", __FUNCTION__);
        goto ERR_EXIT;
    }
    
    //Set AccessInfo
    iRet = aim_config_set_str(AIM_VAR_SMTP_SERVER,(char *) au8AccessInfo, TRUE);
    if (!iRet)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to set aim_config_set_str(%s)", __FUNCTION__, AIM_VAR_SMTP_SERVER);
        goto ERR_EXIT;
    }

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);
       
    /* Read PortInfo from input property */
    data = inst->ft->getProperty(inst, IBM_SMTPRemoteAccessPropertyList[4], &rc);
    if ((CMPI_RC_OK != rc.rc) || (data.state != CMPI_goodValue))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to get parameter PortInfo.", __FUNCTION__);
        goto ERR_EXIT;
    }   

    /* PortInfo is string type, acutally it's numeric port number for SMTP */
    dataStr = CMPIData2String(&data);   
    if (NULL == dataStr)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to convert PortInfo to string.", __FUNCTION__);
        goto ERR_EXIT;
    }       
    
    pu8PortInfo = (UINT8 *) dataStr->ft->getCharPtr(dataStr, &rc);

    memset(au8PortInfo, 0, sizeof(au8PortInfo));
    strncpy((void *)au8PortInfo, (void *)pu8PortInfo, sizeof(au8PortInfo) - 1);

    i32PortInfo = strtol((void *)au8PortInfo, (void *)&pu8Stop, 10);

    if ((i32PortInfo > 65535) || (i32PortInfo < 1))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- PortInfo out of range.", __FUNCTION__);
        goto ERR_EXIT;
    }

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);
    
    //Set PortInfo
    iRet = aim_config_set_int(AIM_VAR_SMTP_PORT, i32PortInfo, TRUE);
    if (!iRet)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to set aim_config_set_int(%s).", __FUNCTION__, AIM_VAR_SMTP_PORT);
        goto ERR_EXIT;
    }
    
    rc.rc = CMPI_RC_OK;
    return (rc);
       
ERR_EXIT:

    rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  

    SafeCMRelease(dataStr);

    if (data.state != CMPI_nullValue)
    {
        CMPIDataRelease(&data);
    }
    
    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);

}


/* IBM_SMTPRemoteAccess Class Service Function */
CMPIStatus Lenovo_SMTPRemoteAccessService( 
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
    /* char **properties; */
    char *className = NULL;
    /* char *asscClass;
    char *resultClass;
    char *role;
    char *resultRole; */
    if (actionID == CLASS_SERVICE_ISA_LITE)
    {
        va_start(argptr, op);
        className = va_arg(argptr, char *);
        va_end(argptr);
    }

    rc = CIMClassUtil_CheckClassName(actionID, mi, ctx, rslt, op, 
                                     className,
                                     (char *) CLASSNAME_Lenovo_IBM_SMTPRemoteAccess,
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
            rc = IBM_SMTPRemoteAccess_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_SMTPRemoteAccess_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_SMTPRemoteAccess_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_SMTPREMOTEACCESS_INIT_SUPPORT
            rc.msg = (void*) &IBM_SMTPRemoteAccess_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_SMTPREMOTEACCESS_INIT_SUPPORT
            rc.msg = (void*) &IBM_SMTPRemoteAccess_InstAgent_Destroy;
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
            rc = IBM_SMTPRemoteAccess_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_SMTPRemoteAccess_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SMTPRemoteAccess_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SMTPRemoteAccess_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_SMTPRemoteAccess_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_SMTPRemoteAccess_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_SMTPRemoteAccess_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_INVOKEMETHOD: 
             /* involk method service */
        case CLASS_SERVICE_GETMETHODNAMES:
             /* get method name service */
        case CLASS_SERVICE_GETPARAMETERS:
             /* get method param name service */
        case CLASS_SERVICE_MODIFYINSTANCE:
            va_start( argptr, op ); 																				
            inst = va_arg(argptr, CMPIInstance *);
            properties = (char **)  va_arg(argptr,  char **);
            rc = IBM_SMTPRemoteAccess_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end( argptr );
            break;
            /* modify instance service */
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
GenNotSupportInstanceMICreateInstance(IBM_SMTPRemoteAccess);
//GenNotSupportInstanceMIModifyInstance(IBM_SMTPRemoteAccess);
GenNotSupportInstanceMIDeleteInstance(IBM_SMTPRemoteAccess);
GenNotSupportInstanceMIExecQuery(IBM_SMTPRemoteAccess);
GenNotSupportInstanceMICleanup(IBM_SMTPRemoteAccess);

/* MI factory function */
CMInstanceMIStub( IBM_SMTPRemoteAccess_,
                  Lenovo_SMTPRemoteAccess_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_SMTPREMOTEACCESS_INIT_SUPPORT /* You can turn on this flag in IBM_SMTPRemoteAccessAgent.h */
#define PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SMTPRemoteAccess_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPRemoteAccess;\
    Arg.GetNextInstIndex = IBM_SMTPRemoteAccess_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SMTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_SMTPRemoteAccess_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SMTPRemoteAccess_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SMTPRemoteAccess_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPRemoteAccess;\
    Arg.GetNextInstIndex = IBM_SMTPRemoteAccess_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SMTPRemoteAccessKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPRemoteAccessPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPRemoteAccessPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPRemoteAccessKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_SMTPRemoteAccess Class Service Function */
CMPIStatus Lenovo_SMTPRemoteAccessService( 
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

/* Gets the Arg of Class IBM_SMTPRemoteAccess Function */
sClassUtilArg IBM_SMTPRemoteAccess_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_SMTPREMOTEACCESS_ARG( Arg );

    return (Arg);
}

#endif
