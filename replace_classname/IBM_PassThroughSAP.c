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

#include <emerson/osinet/osinet_lib.h>
#include <emerson/osinet/osinet_pfw.h>
#include "LogUtil.h"

/* Include base class' header file here */
/* TBD */

#define BMU_PFW_ENTRY_INDEX     23
#define ETH0                    1

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_PassThroughSAP class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_PassThroughSAP = (CMPIUint8 *)CLASSNAMETEXT_IBM_PassThroughSAP;

/* Property List */
static const char * const IBM_PassThroughSAPPropertyList[] = 
{
    PROPERTYNAME_AddressMode,
    PROPERTYNAME_DefaultIPEnabled,
    PROPERTYNAME_ExternalPort,
    PROPERTYNAME_Initialized,
    PROPERTYNAME_IPAddress,
    PROPERTYNAME_RequestedState,
    PROPERTYNAME_USBPort
};

/* Key property List */
static const char * const IBM_PassThroughSAPKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_PASSTHROUGHSAP_INIT_SUPPORT /* You can turn on this flag in IBM_PassThroughSAPAgent.h */
#define PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PassThroughSAP;\
    Arg.GetKeyProperty = IBM_PassThroughSAP_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PassThroughSAP_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PassThroughSAP_GetProperty;\
    Arg.KeyPropertyList = IBM_PassThroughSAPKeyPropertyList;\
    Arg.PropertyList = IBM_PassThroughSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_PassThroughSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PassThroughSAPKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_PASSTHROUGHSAPASSONUM;\
    Arg.AssocArray = G_sLenovo_PassThroughSAPAssociations;\
    Arg.AgentInit = IBM_PassThroughSAP_InstAgent_Init;\
    Arg.AgentDestroy = IBM_PassThroughSAP_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PassThroughSAP;\
    Arg.GetKeyProperty = IBM_PassThroughSAP_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PassThroughSAP_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PassThroughSAP_GetProperty;\
    Arg.KeyPropertyList = IBM_PassThroughSAPKeyPropertyList;\
    Arg.PropertyList = IBM_PassThroughSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_PassThroughSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PassThroughSAPKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_PASSTHROUGHSAPASSONUM;\
    Arg.AssocArray = G_sLenovo_PassThroughSAPAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_PASSTHROUGHSAP_INIT_SUPPORT /* You can turn on this flag in IBM_PassThroughSAPAgent.h */
#define PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PassThroughSAP;\
    Arg.GetKeyProperty = IBM_PassThroughSAP_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PassThroughSAP_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PassThroughSAP_GetProperty;\
    Arg.KeyPropertyList = IBM_PassThroughSAPKeyPropertyList;\
    Arg.PropertyList = IBM_PassThroughSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_PassThroughSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PassThroughSAPKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_PASSTHROUGHSAPASSONUM;\
    Arg.AssocArray = G_sLenovo_PassThroughSAPAssociations;\
    Arg.AgentInit = IBM_PassThroughSAP_InstAgent_Init;\
    Arg.AgentDestroy = IBM_PassThroughSAP_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PassThroughSAP;\
    Arg.GetKeyProperty = IBM_PassThroughSAP_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PassThroughSAP_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PassThroughSAP_GetProperty;\
    Arg.KeyPropertyList = IBM_PassThroughSAPKeyPropertyList;\
    Arg.PropertyList = IBM_PassThroughSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_PassThroughSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PassThroughSAPKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_PASSTHROUGHSAPASSONUM;\
    Arg.AssocArray = G_sLenovo_PassThroughSAPAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_PassThroughSAP_GetProperty( 
                                         CMPICount nInstIndex,
                                         CMPICount nPropIndex,
                                         void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_PassThroughSAP_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_PassThroughSAP_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_PassThroughSAP, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_PassThroughSAP, &rc);
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
        data = IBM_PassThroughSAP_GetProperty(nInstIndex, nKeyIndex | IBM_PASSTHROUGHSAP_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_PassThroughSAP_GenerateObjectPath( 
                                                       char **properties,
                                                       CMPICount InstIndex,
                                                       void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_PassThroughSAP_GetInstance( 
                                           CMPIInstanceMI *mi,
                                           const CMPIContext *ctx,
                                           const CMPIResult *rslt,
                                           const CMPIObjectPath *op,
                                           const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_PassThroughSAP_EnumInstances( 
#else
CMPIStatus IBM_PassThroughSAP_EnumerateInstances( 
#endif
                                                  CMPIInstanceMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_PassThroughSAP_EnumInstanceNames( 
#else
CMPIStatus IBM_PassThroughSAP_EnumerateInstanceNames( 
#endif
                                                      CMPIInstanceMI *mi,
                                                      const CMPIContext *ctx,
                                                      const CMPIResult *rslt,
                                                      const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_PassThroughSAP_Associators( 
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
    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_PassThroughSAP_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_PassThroughSAP_References( 
                                          CMPIAssociationMI *mi,
                                          const CMPIContext *ctx,
                                          const CMPIResult *rslt,
                                          const CMPIObjectPath *op,
                                          const char *resultClass,
                                          const char *role,
                                          const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_PassThroughSAP_ReferenceNames( 
                                              CMPIAssociationMI *mi,
                                              const CMPIContext *ctx,
                                              const CMPIResult *rslt,
                                              const CMPIObjectPath *op,
                                              const char *resultClass,
                                              const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_PassThroughSAP_ModifyInstance(
                                             CMPIInstanceMI *mi,
                                             const CMPIContext *ctx,
                                             const CMPIResult *rslt,
                                             const CMPIObjectPath *op,
                                             const CMPIInstance * inst,
                                             const char **properties
                                            )
{
    sClassUtilArg Arg;   
    IBM_PASSTHROUGHSAP_AGENT_DATA * pstSapAgentData = NULL;
    IBM_PASSTHROUGHSAP_DATA * pstSapData = NULL;
    CMPIStatus stCmpiStatus;
    _PortForwardingEntry stEntry;
    CMPIData data;
    CMPICount u32InstIndex = 0;
    UINT16 u16UsbPort = 0;
    UINT16 u16ExternalPort = 0;
    UINT8 u8EntryIndex = 0;
    UINT8 au8ServerIp[512];

    memset((void *)&data, 0, sizeof(data));
    memset((void *)&stCmpiStatus, 0, sizeof(stCmpiStatus));
    memset((void *)&stEntry, 0, sizeof(stEntry));
    memset((void *)au8ServerIp, 0, sizeof(au8ServerIp));

    if (NULL == inst)
    {
        stCmpiStatus.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        return (stCmpiStatus);
    }

    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);

#if IBM_PASSTHROUGHSAP_INIT_SUPPORT
    pstSapAgentData = IBM_PassThroughSAP_InstAgent_Init(0);
#endif

    /* instance index */
    u32InstIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pstSapAgentData, &Arg); 
    
    if (INSTANCE_INDEX_INVALID == u32InstIndex)
    {
        stCmpiStatus.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto EXIT;
    }
    
    pstSapData = pstSapAgentData->pstSaps + u32InstIndex; 
    u8EntryIndex = pstSapData->u8EntryIndex;

    if (PORT_FORWARDING_DSA_INDEX == u8EntryIndex)
    {
        /* DSA port forwarding is not supported to ModifyInstance() in CR XB136064 - CMM FFDC retrieval by DSA through IMM */
        logTraceCIM(LOG_LEV_ERROR, "%s()- DSA port forwarding is not supported to ModifyInstance().", __FUNCTION__);
        stCmpiStatus.rc = CMPI_RC_ERR_NOT_SUPPORTED;
        goto EXIT;
    }

    data = inst->ft->getProperty(inst, "USBPort", &stCmpiStatus);
    if ((CMPI_goodValue != data.state) || (CMPI_RC_OK != stCmpiStatus.rc))
    {
        stCmpiStatus.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto EXIT;
    }

    u16UsbPort = (UINT16)data.value.uint16;

    if (0 == u16UsbPort)
    {
        stCmpiStatus.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto EXIT;
    }

    data = inst->ft->getProperty(inst, "ExternalPort", &stCmpiStatus);
    if ((CMPI_goodValue != data.state) || (CMPI_RC_OK != stCmpiStatus.rc))
    {
        stCmpiStatus.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto EXIT;
    }

    u16ExternalPort = data.value.uint16;

    if ((0 == u16ExternalPort))
    {
        stCmpiStatus.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto EXIT;
    }

    /* external port can not conflict with other existed entry */
    if (OSINET_STATUS_OK != avct_osinet_pfw_ValidityCheckPort(u16ExternalPort, OSINET_PORT_TYPE_PFW_0 + u8EntryIndex, true))
    {
        stCmpiStatus.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto EXIT;
    }

    snprintf((void *)stEntry.szServiceName, sizeof(stEntry.szServiceName), "VSChain%i", u8EntryIndex);

    aim_config_get_str(AIM_STR_WATCHDOG_ARPECHO_FINISH , (void *)au8ServerIp);

    if (strlen((void *)au8ServerIp) 
            && strcmp((void *)au8ServerIp, "255.255.255.255"))
    {
        strncpy((void *)stEntry.au8EgressAddr, (void *)au8ServerIp, INET6_ADDRSTRLEN);
        stEntry.au8EgressAddr[INET6_ADDRSTRLEN - 1] = '\0';
    }
    else
    {
        strncpy(stEntry.au8EgressAddr, SERVER_ADDER, INET6_ADDRSTRLEN);
        stEntry.au8EgressAddr[INET6_ADDRSTRLEN - 1] = '\0';
    }

    stEntry.u8Enable = LAN_TRUE;
    stEntry.u8ProtocolFlag = (PFW_CONF_TCP | PFW_CONF_UDP | PFW_CONF_IPv4 | PFW_CONF_IPv6);
    stEntry.u8IngressInterface = ETH0;
    stEntry.u16IngressPort = (uint16_t) u16ExternalPort;
    stEntry.u16EgressPort =(uint16_t) u16UsbPort;

    if (OSINET_STATUS_OK != avct_osinet_pfw_set_service_entry(u8EntryIndex, stEntry))
    {
        stCmpiStatus.rc = CMPI_RC_ERR_FAILED;
    }
    else
    {
        stCmpiStatus.rc = CMPI_RC_OK;
    }

EXIT:
    
#if CIM_PUBLICKEYCERTIFICATE_INIT_SUPPORT
    IBM_PassThroughSAP_InstAgent_Destroy(pstSapAgentData);
#endif

    CMPIDataRelease(&data);

    {
        CMPIValue value;
        value.uint32 = stCmpiStatus.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (stCmpiStatus);
}

CMPIStatus IBM_PassThroughSAP_DeleteInstance(
                                             CMPIInstanceMI *mi,
                                             const CMPIContext *ctx,
                                             const CMPIResult *rslt,
                                             const CMPIObjectPath *op
                                            )
{
    sClassUtilArg Arg;   
    CMPIStatus stCmpiStatus = {CMPI_RC_ERR_INVALID_PARAMETER, NULL}; 
    CMPICount nInstIndex = 0;
    IBM_PASSTHROUGHSAP_AGENT_DATA *pstSapAgentData = NULL;
    IBM_PASSTHROUGHSAP_DATA *pstSapData = NULL;
    UINT8 u8EntryIndex = 0;

    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);

#if IBM_PASSTHROUGHSAP_INIT_SUPPORT
    pstSapAgentData = IBM_PassThroughSAP_InstAgent_Init(0);
#endif
    
    nInstIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pstSapAgentData, &Arg); 
    if (INSTANCE_INDEX_INVALID == nInstIndex)
    {
        stCmpiStatus.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        return (stCmpiStatus);
    }
    pstSapData = pstSapAgentData->pstSaps + nInstIndex;
    u8EntryIndex = pstSapData->u8EntryIndex;

    /* bare metal pfw entry can not be deleted throgh DI */
    if (BMU_PFW_ENTRY_INDEX == u8EntryIndex)
    {
        stCmpiStatus.rc = CMPI_RC_ERR_FAILED;
        return (stCmpiStatus);
    }

    if (OSINET_STATUS_OK != avct_osinet_pfw_clear_service_entry(u8EntryIndex))
    {
        stCmpiStatus.rc = CMPI_RC_ERR_FAILED;
    }
    else
    {
        stCmpiStatus.rc = CMPI_RC_OK;
    }

#if IBM_PASSTHROUGHSAP_INIT_SUPPORT
    IBM_PassThroughSAP_InstAgent_Destroy(pstSapAgentData);
#endif

    return (stCmpiStatus);
}


CMPIStatus IBM_PassThroughSAP_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg);

#if IBM_PASSTHROUGHSAP_INIT_SUPPORT
    pAgentDataPtr = IBM_PassThroughSAP_InstAgent_Init(0);
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
        value.uint32 = IBM_PassThroughSAP_InstAgent_RequestStateChange((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_METHOD_NOT_FOUND;
    }

CLEAN:
#if IBM_PASSTHROUGHSAP_INIT_SUPPORT
    IBM_PassThroughSAP_InstAgent_Destroy(pAgentDataPtr);
#endif

    return (rc);
}

#ifndef _BROKER_SFCB
CMPIData *IBM_PassThroughSAP_GetMethodName()
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

CMPIData *IBM_PassThroughSAP_GetMethodParameters(const char * MethodName)
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

/* IBM_PassThroughSAP Class Service Function */
CMPIStatus Lenovo_PassThroughSAPService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_PassThroughSAP,
                                     CIM_USBRedirectionSAPService);
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
            rc = IBM_PassThroughSAP_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_PassThroughSAP_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_PassThroughSAP_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_PASSTHROUGHSAP_INIT_SUPPORT
            rc.msg = (void*) &IBM_PassThroughSAP_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_PASSTHROUGHSAP_INIT_SUPPORT
            rc.msg = (void*) &IBM_PassThroughSAP_InstAgent_Destroy;
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
            rc = IBM_PassThroughSAP_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_PassThroughSAP_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_PassThroughSAP_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_PassThroughSAP_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_PassThroughSAP_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_PassThroughSAP_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_PassThroughSAP_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_PassThroughSAP_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_DELETEINSTANCE: 
            /* delete instance service */
            rc = IBM_PassThroughSAP_DeleteInstance((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_PassThroughSAP_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_PassThroughSAP_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_PassThroughSAP_GetMethodParameters(method);
            va_end(argptr);
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_CREATEINSTANCE:
            /* create instance service */
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
GenNotSupportInstanceMICreateInstance(IBM_PassThroughSAP);
/*GenNotSupportInstanceMIModifyInstance(IBM_PassThroughSAP);*/
/*GenNotSupportInstanceMIDeleteInstance(IBM_PassThroughSAP);*/
GenNotSupportInstanceMIExecQuery(IBM_PassThroughSAP);
GenNotSupportInstanceMICleanup(IBM_PassThroughSAP);

/* MI factory function */
CMInstanceMIStub( IBM_PassThroughSAP_,
                  Lenovo_PassThroughSAP_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_PassThroughSAP);

CMMethodMIStub( IBM_PassThroughSAP_,
                Lenovo_PassThroughSAP_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_PASSTHROUGHSAP_INIT_SUPPORT /* You can turn on this flag in IBM_PassThroughSAPAgent.h */
#define PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg) \
    Arg.AgentGetProperty = IBM_PassThroughSAP_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PassThroughSAP;\
    Arg.GetNextInstIndex = IBM_PassThroughSAP_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_PassThroughSAPKeyPropertyList;\
    Arg.PropertyList = IBM_PassThroughSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_PassThroughSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PassThroughSAPKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_PassThroughSAP_InstAgent_Init;\
    Arg.AgentDestroy = IBM_PassThroughSAP_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG(Arg) \
    Arg.AgentGetProperty = IBM_PassThroughSAP_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PassThroughSAP;\
    Arg.GetNextInstIndex = IBM_PassThroughSAP_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_PassThroughSAPKeyPropertyList;\
    Arg.PropertyList = IBM_PassThroughSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_PassThroughSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PassThroughSAPKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_PassThroughSAP Class Service Function */
CMPIStatus Lenovo_PassThroughSAPService( 
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

/* Gets the Arg of Class IBM_PassThroughSAP Function */
sClassUtilArg IBM_PassThroughSAP_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_PASSTHROUGHSAP_ARG( Arg );

    return (Arg);
}

#endif
