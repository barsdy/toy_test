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

#include "LogUtil.h"
#include <emerson/imm_alertmgr/alertmgr_lib.h>

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_SMTPProtocolEndpoint class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint = (CMPIUint8 *)CLASSNAMETEXT_IBM_SMTPProtocolEndpoint;

/* Property List */
static const char * const IBM_SMTPProtocolEndpointPropertyList[] = 
{
    PROPERTYNAME_Authentication,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EnabledState,
    PROPERTYNAME_NameFormat,
    PROPERTYNAME_ProtocolIFType,
    PROPERTYNAME_RequestedState,
    PROPERTYNAME_ReversePath
};

/* Key property List */
static const char * const IBM_SMTPProtocolEndpointKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_SMTPPROTOCOLENDPOINT_INIT_SUPPORT /* You can turn on this flag in IBM_SMTPProtocolEndpointAgent.h */
#define PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint;\
    Arg.GetKeyProperty = IBM_SMTPProtocolEndpoint_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SMTPProtocolEndpoint_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SMTPProtocolEndpoint_GetProperty;\
    Arg.KeyPropertyList = IBM_SMTPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SMTPPROTOCOLENDPOINTASSONUM;\
    Arg.AssocArray = G_sLenovo_SMTPProtocolEndpointAssociations;\
    Arg.AgentInit = IBM_SMTPProtocolEndpoint_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SMTPProtocolEndpoint_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint;\
    Arg.GetKeyProperty = IBM_SMTPProtocolEndpoint_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SMTPProtocolEndpoint_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SMTPProtocolEndpoint_GetProperty;\
    Arg.KeyPropertyList = IBM_SMTPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SMTPPROTOCOLENDPOINTASSONUM;\
    Arg.AssocArray = G_sLenovo_SMTPProtocolEndpointAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_SMTPPROTOCOLENDPOINT_INIT_SUPPORT /* You can turn on this flag in IBM_SMTPProtocolEndpointAgent.h */
#define PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint;\
    Arg.GetKeyProperty = IBM_SMTPProtocolEndpoint_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SMTPProtocolEndpoint_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SMTPProtocolEndpoint_GetProperty;\
    Arg.KeyPropertyList = IBM_SMTPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SMTPPROTOCOLENDPOINTASSONUM;\
    Arg.AssocArray = G_sLenovo_SMTPProtocolEndpointAssociations;\
    Arg.AgentInit = IBM_SMTPProtocolEndpoint_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SMTPProtocolEndpoint_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint;\
    Arg.GetKeyProperty = IBM_SMTPProtocolEndpoint_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SMTPProtocolEndpoint_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SMTPProtocolEndpoint_GetProperty;\
    Arg.KeyPropertyList = IBM_SMTPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SMTPPROTOCOLENDPOINTASSONUM;\
    Arg.AssocArray = G_sLenovo_SMTPProtocolEndpointAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_SMTPProtocolEndpoint_GetProperty( 
                                               CMPICount nInstIndex,
                                               CMPICount nPropIndex,
                                               void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_SMTPProtocolEndpoint_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_SMTPProtocolEndpoint_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint, &rc);
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
        data = IBM_SMTPProtocolEndpoint_GetProperty(nInstIndex, nKeyIndex | IBM_SMTPPROTOCOLENDPOINT_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_SMTPProtocolEndpoint_GenerateObjectPath( 
                                                             char **properties,
                                                             CMPICount InstIndex,
                                                             void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_SMTPProtocolEndpoint_GetInstance( 
                                                 CMPIInstanceMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SMTPProtocolEndpoint_EnumInstances( 
#else
CMPIStatus IBM_SMTPProtocolEndpoint_EnumerateInstances( 
#endif
                                                        CMPIInstanceMI *mi,
                                                        const CMPIContext *ctx,
                                                        const CMPIResult *rslt,
                                                        const CMPIObjectPath *op,
                                                        const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SMTPProtocolEndpoint_EnumInstanceNames( 
#else
CMPIStatus IBM_SMTPProtocolEndpoint_EnumerateInstanceNames( 
#endif
                                                            CMPIInstanceMI *mi,
                                                            const CMPIContext *ctx,
                                                            const CMPIResult *rslt,
                                                            const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_SMTPProtocolEndpoint_Associators( 
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
    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_SMTPProtocolEndpoint_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_SMTPProtocolEndpoint_References( 
                                                CMPIAssociationMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char *resultClass,
                                                const char *role,
                                                const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_SMTPProtocolEndpoint_ReferenceNames( 
                                                    CMPIAssociationMI *mi,
                                                    const CMPIContext *ctx,
                                                    const CMPIResult *rslt,
                                                    const CMPIObjectPath *op,
                                                    const char *resultClass,
                                                    const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_SMTPProtocolEndpoint_ModifyInstance(
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
	sSMTPAuthData sAuthData;
    sSMTPAuthData sOriginData;
    UINT16 u16Value = 0;
    unsigned int uiValueSize = 0;
    char szSmtpReversePath[MAX_SMTP_RP_INPUT_LEN + 1] = { 0 };
    
    logTraceCIM(LOG_LEV_INFO, "%s()- Function entry.", __FUNCTION__);

    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);

    pAgentDataPtr = IBM_SMTPProtocolEndpoint_InstAgent_Init(0);

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_SMTPProtocolEndpointPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    /* get property ReversePath */
    uiValueSize = sizeof(szSmtpReversePath);
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_ReversePath, CMPI_string, szSmtpReversePath, &uiValueSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get the property %s.", __FUNCTION__, PROPERTYNAME_ReversePath);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        sAlertRpData sRpCfg;
        ALERTMGR_STATUS eResult = ALERTMGR_UNKNOW_ERROR;

        eResult = alertmgr_rpcfg_get(&sRpCfg);
        if (ALERTMGR_OK == eResult)
        {
            if (strcmp(sRpCfg.szSmtpReversePath, szSmtpReversePath) != 0)
            {
                eResult = alertmgr_rpcfg_init(&sRpCfg);
                if (ALERTMGR_OK == eResult)
                {
                    CMPIGetUserNameFromContext(ctx, sRpCfg.szUserID);
                    //logTraceCIM(LOG_LEV_INFO, "%s()- szUserID is %s.", __FUNCTION__, sRpCfg.szUserID);
                
                    snprintf(sRpCfg.szSmtpReversePath, sizeof(sRpCfg.szSmtpReversePath), "%s", szSmtpReversePath);
                    eResult = alertmgr_rpcfg_set(&sRpCfg);
                    if (eResult != ALERTMGR_OK)
                    {
                        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call alertmgr_rpcfg_set(%s), error code is %d.", __FUNCTION__, sRpCfg.szSmtpReversePath, eResult);
                    
                        if (ALERTMGR_REVERSE_PATH_FORMAT_ERROR == eResult)
                        {
                            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                        }
                        else
                        {
                            rc.rc = CMPI_RC_ERR_FAILED;
                        }
                        goto CLEAN;
                    }
                }
                else
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call alertmgr_rpcfg_init(), error code is %d.", __FUNCTION__, eResult);
                    rc.rc = CMPI_RC_ERR_FAILED;
                    goto CLEAN;
                }
            
            }

        }
        else
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call alertmgr_rpcfg_get(), error code is %d.", __FUNCTION__, eResult);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }

    }
    //else is CMPI_RC_ERR_NO_SUCH_PROPERTY

    
    /* get property Authentication */
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_Authentication, CMPI_uint16, &u16Value, NULL, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get the property %s.", __FUNCTION__, PROPERTYNAME_Authentication);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if ((u16Value != 2) && (u16Value != 3))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- The value (%d) of %s is invalid value.", __FUNCTION__, u16Value, PROPERTYNAME_Authentication);
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto CLEAN;
        }
        else
        {
            ALERTMGR_STATUS status = ALERTMGR_UNKNOW_ERROR;
            
            status = alertmgr_smtp_auth_cfg_get(&sOriginData);
            if (ALERTMGR_OK == status)
            {
                if ((((0 == sOriginData.mode) || (1 == sOriginData.mode)) && 
                     (strlen(sOriginData.uname) > 0) && 
                     (strlen(sOriginData.pwd) > 0) && 
                     (2 == u16Value)) || 
                    (3 == u16Value))
                {
                    status = alertmgr_smtp_auth_cfg_init(&sAuthData);
                    if (ALERTMGR_OK == status)
                    {
                        sAuthData.enable = (2 == u16Value);
                        if (sAuthData.enable != sOriginData.enable)
                        {
                            status = alertmgr_smtp_auth_cfg_set(&sAuthData);
                            if (status != ALERTMGR_OK)
                            {
                                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call alertmgr_smtp_auth_cfg_set(), return code is %d.", __FUNCTION__, status);
                                rc.rc = CMPI_RC_ERR_FAILED;
                                goto CLEAN;
                            }
                        }
                    }
                    else
                    {
                        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call alertmgr_smtp_auth_cfg_init(), return code is %d.", __FUNCTION__, status);
                        rc.rc = CMPI_RC_ERR_FAILED;
                        goto CLEAN;
                    }
                }
                else
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- All authentication data (Algorithm, RemoteID and Secret of SMTP) must be set.", __FUNCTION__);
                    rc.rc = CMPI_RC_ERR_FAILED;
                    goto CLEAN;
                }
            }
            else
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call alertmgr_smtp_auth_cfg_get(), return code is %d.", __FUNCTION__, status);
                rc.rc = CMPI_RC_ERR_FAILED;
                goto CLEAN;
            }

        }

    }
    //else is CMPI_RC_ERR_NO_SUCH_PROPERTY


    CLEAN:
        
    IBM_SMTPProtocolEndpoint_InstAgent_Destroy(pAgentDataPtr);

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

CMPIStatus IBM_SMTPProtocolEndpoint_InvokeMethod( 
                                                  CMPIMethodMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char *method,
                                                  const CMPIArgs *in,
                                                  CMPIArgs *out)
{
    CMPIValue value;
    CMPIStatus rc = 
    {
        CMPI_RC_OK,
        NULL
    };

    CMPICount nIndex = 0;
    void *pAgentDataPtr = NULL;

    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg);

#if IBM_SMTPPROTOCOLENDPOINT_INIT_SUPPORT
    pAgentDataPtr = IBM_SMTPProtocolEndpoint_InstAgent_Init(0);
#endif

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (nIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    /* invoke method */
    if (0 == strcmp(method, "RequestStateChange"))
    {
        value.uint32 = IBM_SMTPProtocolEndpoint_InstAgent_RequestStateChange((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_METHOD_NOT_FOUND;
    }

CLEAN:
    
#if IBM_SMTPPROTOCOLENDPOINT_INIT_SUPPORT
    IBM_SMTPProtocolEndpoint_InstAgent_Destroy(pAgentDataPtr);
#endif

    return (rc);
}

#ifndef _BROKER_SFCB
CMPIData *IBM_SMTPProtocolEndpoint_GetMethodName()
{
    CMPIArray *nameArray;
    CMPIStatus status;
    CMPIData *data;
    CMPIValue value;

    data = Malloc(sizeof(CMPIData));

    if(!data)
    {
        return (NULL);
    }

    data->state = CMPI_badValue;

    /* new CMPIArray */
    nameArray = (void*) TheBroker.eft->newArray(&TheBroker, 1, CMPI_chars, &status);

    if(!nameArray)
    {
        return (NULL);
    }

    /* add method name */
    value.chars = (char *) METHODNAME_RequestStateChange;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

CMPIData *IBM_SMTPProtocolEndpoint_GetMethodParameters(const char * MethodName)
{
    CMPIArgs *pArgs;
    CMPIStatus status;
    CMPIData *data;
    CMPIValue value;
    UINT8 iMethID = 0xFF;

    data = Malloc(sizeof(CMPIData));

    if(!data)
    {
        return (NULL);
    }

    if (0 == strcmp(MethodName, METHODNAME_RequestStateChange))
    {
        iMethID = 0;
    }
    else
    {
        return (data);
    }

    pArgs = (void*) TheBroker.eft->newArgs(&TheBroker,&status);

    if(!pArgs)
    {
        return (NULL);
    }

    /* add method Parameter */
    switch(iMethID)
    {
        case 0:
            value.chars = (char *) TYPENAME_uint16;
            pArgs->ft->addArg(pArgs, PARAMNAME_RequestedState,&value,CMPI_chars);
            value.chars = "ref CIM_ConcreteJob";
            pArgs->ft->addArg(pArgs, PARAMNAME_Job,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_datetime;
            pArgs->ft->addArg(pArgs, PARAMNAME_TimeoutPeriod,&value,CMPI_chars);
            break;

    }

    data->value.args = pArgs;
    data->type = CMPI_args;
    data->state = CMPI_goodValue;
    return (data);
}
#endif

/* IBM_SMTPProtocolEndpoint Class Service Function */
CMPIStatus Lenovo_SMTPProtocolEndpointService( 
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
    /* CMPIInstance *inst = NULL;
    char *method;
    CMPIArgs *in;
    CMPIArgs *out; */

    if (actionID == CLASS_SERVICE_ISA_LITE)
    {
        va_start(argptr, op);
        className = va_arg(argptr, char *);
        va_end(argptr);
    }

    rc = CIMClassUtil_CheckClassName(actionID, mi, ctx, rslt, op, 
                                     className,
                                     (char *) CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint,
                                     CIM_ProtocolEndpointService);
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
            rc = IBM_SMTPProtocolEndpoint_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_SMTPProtocolEndpoint_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_SMTPProtocolEndpoint_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_SMTPPROTOCOLENDPOINT_INIT_SUPPORT
            rc.msg = (void*) &IBM_SMTPProtocolEndpoint_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_SMTPPROTOCOLENDPOINT_INIT_SUPPORT
            rc.msg = (void*) &IBM_SMTPProtocolEndpoint_InstAgent_Destroy;
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
            rc = IBM_SMTPProtocolEndpoint_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_SMTPProtocolEndpoint_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SMTPProtocolEndpoint_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SMTPProtocolEndpoint_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_SMTPProtocolEndpoint_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_SMTPProtocolEndpoint_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_SMTPProtocolEndpoint_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_SMTPProtocolEndpoint_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_SMTPProtocolEndpoint_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_SMTPProtocolEndpoint_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_SMTPProtocolEndpoint_GetMethodParameters(method);
            va_end(argptr);
            rc.rc = CMPI_RC_OK;
            break;

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
GenNotSupportInstanceMICreateInstance(IBM_SMTPProtocolEndpoint);
// GenNotSupportInstanceMIModifyInstance(IBM_SMTPProtocolEndpoint);
GenNotSupportInstanceMIDeleteInstance(IBM_SMTPProtocolEndpoint);
GenNotSupportInstanceMIExecQuery(IBM_SMTPProtocolEndpoint);
GenNotSupportInstanceMICleanup(IBM_SMTPProtocolEndpoint);

/* MI factory function */
CMInstanceMIStub( IBM_SMTPProtocolEndpoint_,
                  Lenovo_SMTPProtocolEndpoint_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_SMTPProtocolEndpoint);

CMMethodMIStub( IBM_SMTPProtocolEndpoint_,
                Lenovo_SMTPProtocolEndpoint_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_SMTPPROTOCOLENDPOINT_INIT_SUPPORT /* You can turn on this flag in IBM_SMTPProtocolEndpointAgent.h */
#define PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SMTPProtocolEndpoint_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint;\
    Arg.GetNextInstIndex = IBM_SMTPProtocolEndpoint_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SMTPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_SMTPProtocolEndpoint_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SMTPProtocolEndpoint_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SMTPProtocolEndpoint_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SMTPProtocolEndpoint;\
    Arg.GetNextInstIndex = IBM_SMTPProtocolEndpoint_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SMTPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SMTPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SMTPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SMTPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_SMTPProtocolEndpoint Class Service Function */
CMPIStatus Lenovo_SMTPProtocolEndpointService( 
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

/* Gets the Arg of Class IBM_SMTPProtocolEndpoint Function */
sClassUtilArg IBM_SMTPProtocolEndpoint_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_SMTPPROTOCOLENDPOINT_ARG( Arg );

    return (Arg);
}

#endif
