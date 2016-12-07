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

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
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


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_SLPProtocolEndpoint class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint = (CMPIUint8 *)CLASSNAMETEXT_IBM_SLPProtocolEndpoint;

/* Property List */
static const char * const IBM_SLPProtocolEndpointPropertyList[] = 
{
    PROPERTYNAME_AddressType,
    PROPERTYNAME_Description,
    PROPERTYNAME_EnabledState,
    PROPERTYNAME_MulticastAddress,
    PROPERTYNAME_OtherTypeDescription,
    PROPERTYNAME_ProtocolIFType
};

/* Key property List */
static const char * const IBM_SLPProtocolEndpointKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_SLPPROTOCOLENDPOINT_INIT_SUPPORT /* You can turn on this flag in IBM_SLPProtocolEndpointAgent.h */
#define PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint;\
    Arg.GetKeyProperty = IBM_SLPProtocolEndpoint_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SLPProtocolEndpoint_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SLPProtocolEndpoint_GetProperty;\
    Arg.KeyPropertyList = IBM_SLPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SLPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SLPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SLPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SLPPROTOCOLENDPOINTASSONUM;\
    Arg.AssocArray = G_sLenovo_SLPProtocolEndpointAssociations;\
    Arg.AgentInit = IBM_SLPProtocolEndpoint_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SLPProtocolEndpoint_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint;\
    Arg.GetKeyProperty = IBM_SLPProtocolEndpoint_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SLPProtocolEndpoint_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SLPProtocolEndpoint_GetProperty;\
    Arg.KeyPropertyList = IBM_SLPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SLPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SLPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SLPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SLPPROTOCOLENDPOINTASSONUM;\
    Arg.AssocArray = G_sLenovo_SLPProtocolEndpointAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_SLPPROTOCOLENDPOINT_INIT_SUPPORT /* You can turn on this flag in IBM_SLPProtocolEndpointAgent.h */
#define PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint;\
    Arg.GetKeyProperty = IBM_SLPProtocolEndpoint_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SLPProtocolEndpoint_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SLPProtocolEndpoint_GetProperty;\
    Arg.KeyPropertyList = IBM_SLPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SLPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SLPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SLPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SLPPROTOCOLENDPOINTASSONUM;\
    Arg.AssocArray = G_sLenovo_SLPProtocolEndpointAssociations;\
    Arg.AgentInit = IBM_SLPProtocolEndpoint_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SLPProtocolEndpoint_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint;\
    Arg.GetKeyProperty = IBM_SLPProtocolEndpoint_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SLPProtocolEndpoint_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SLPProtocolEndpoint_GetProperty;\
    Arg.KeyPropertyList = IBM_SLPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SLPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SLPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SLPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SLPPROTOCOLENDPOINTASSONUM;\
    Arg.AssocArray = G_sLenovo_SLPProtocolEndpointAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

#define RETURN_ERR(src, err)\
    src.rc = err; \
    return (src)
    
#define SLP_ADDRESS_TYPE_MULTICAST  2
#define SLP_ADDRESS_TYPE_BROADCAST  3

/* Get Properties value */
CMPIData IBM_SLPProtocolEndpoint_GetProperty( 
                                              CMPICount nInstIndex,
                                              CMPICount nPropIndex,
                                              void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_SLPProtocolEndpoint_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_SLPProtocolEndpoint_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint, &rc);
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
        data = IBM_SLPProtocolEndpoint_GetProperty(nInstIndex, nKeyIndex | IBM_SLPPROTOCOLENDPOINT_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_SLPProtocolEndpoint_GenerateObjectPath( 
                                                            char **properties,
                                                            CMPICount InstIndex,
                                                            void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_SLPProtocolEndpoint_GetInstance( 
                                                CMPIInstanceMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SLPProtocolEndpoint_EnumInstances( 
#else
CMPIStatus IBM_SLPProtocolEndpoint_EnumerateInstances( 
#endif
                                                       CMPIInstanceMI *mi,
                                                       const CMPIContext *ctx,
                                                       const CMPIResult *rslt,
                                                       const CMPIObjectPath *op,
                                                       const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SLPProtocolEndpoint_EnumInstanceNames( 
#else
CMPIStatus IBM_SLPProtocolEndpoint_EnumerateInstanceNames( 
#endif
                                                           CMPIInstanceMI *mi,
                                                           const CMPIContext *ctx,
                                                           const CMPIResult *rslt,
                                                           const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_SLPProtocolEndpoint_Associators( 
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
    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_SLPProtocolEndpoint_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_SLPProtocolEndpoint_References( 
                                               CMPIAssociationMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char *resultClass,
                                               const char *role,
                                               const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_SLPProtocolEndpoint_ReferenceNames( 
                                                   CMPIAssociationMI *mi,
                                                   const CMPIContext *ctx,
                                                   const CMPIResult *rslt,
                                                   const CMPIObjectPath *op,
                                                   const char *resultClass,
                                                   const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_SLPProtocolEndpoint_CheckSelectorSet( 
                                                    const CMPIObjectPath *op,
                                                    CMPIBoolean bAllKey,
                                                    void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);
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

CMPIStatus IBM_SLPProtocolEndpoint_ModifyInstance(CMPIInstanceMI *mi, 
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
    char *szMulticastAddress;
    UINT8 u8AddressType = 0;
    struct sockaddr_in sMulticastAddr_in;

    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg);

    /* Check SelectorSet */
    instIndex = IBM_SLPProtocolEndpoint_CheckSelectorSet(op, CMPITRUE, NULL);
    if (instIndex == INSTANCE_INDEX_INVALID)
    {
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_PARAMETER);
    }
    
    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_SLPProtocolEndpointPropertyList))
    {
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_PARAMETER);// CMPI_RC_ERR_NO_SUCH_PROPERTY 
    }
    if (ctx == NULL)
    {
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_HANDLE);
    }
    /* Read BaudRate from input property */
    data = inst->ft->getProperty(inst, PROPERTYNAME_AddressType, &rc);
    if (data.state != CMPI_goodValue)
    {
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_PARAMETER);  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
    }

    dataStr = CMPIData2String(&data);
    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_PARAMETER);  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
    }
    u8AddressType = atoi(dataStr->ft->getCharPtr(dataStr, &rc));

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

    if(u8AddressType != SLP_ADDRESS_TYPE_MULTICAST && u8AddressType != SLP_ADDRESS_TYPE_BROADCAST)
    {
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_PARAMETER);
    }
    if(aim_config_set_int(AIM_SLP_ADDRESS_TYPE, u8AddressType, TRUE))
    {
        rc.rc = CMPI_RC_OK;
    }
    else
    {
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_HANDLE);
    }

    data = inst->ft->getProperty(inst, PROPERTYNAME_MulticastAddress, &rc);
    if (data.state != CMPI_goodValue)
    {
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_PARAMETER);  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
    }
    dataStr = CMPIData2String(&data);
    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_PARAMETER);  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
    }
    szMulticastAddress = (char *)dataStr->ft->getCharPtr(dataStr, &rc);
    
    if(inet_pton(AF_INET, szMulticastAddress, &(sMulticastAddr_in.sin_addr)) < 0)
    {
        printf("The format of MulticastAddress is not valid.\n");
        SafeCMRelease(dataStr);
        CMPIDataRelease(&data);
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_PARAMETER);
    }
    if(!IN_MULTICAST(ntohl(sMulticastAddr_in.sin_addr.s_addr)))
    {
        printf("The input address is not MulticastAddress.\n");
        SafeCMRelease(dataStr);
        CMPIDataRelease(&data);
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_PARAMETER);
    }
    if(aim_config_set_str(AIM_SLP_MULTICAST_ADDRESS, szMulticastAddress, TRUE))
    {
        rc.rc = CMPI_RC_OK;
    }
    else
    {
        RETURN_ERR(rc, CMPI_RC_ERR_INVALID_HANDLE);
    }
    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}


/* IBM_SLPProtocolEndpoint Class Service Function */
CMPIStatus Lenovo_SLPProtocolEndpointService( 
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
    char *asscClass;
    char *resultClass;
    char *role;
    char *resultRole;
#endif
    char **properties;
    CMPIInstance *inst = NULL;
    
    if (actionID == CLASS_SERVICE_ISA_LITE)
    {
        va_start(argptr, op);
        className = va_arg(argptr, char *);
        va_end(argptr);
    }

    rc = CIMClassUtil_CheckClassName(actionID, mi, ctx, rslt, op, 
                                     className,
                                     (char *) CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint,
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
            rc = IBM_SLPProtocolEndpoint_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_SLPProtocolEndpoint_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_SLPProtocolEndpoint_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_SLPPROTOCOLENDPOINT_INIT_SUPPORT
            rc.msg = (void*) &IBM_SLPProtocolEndpoint_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_SLPPROTOCOLENDPOINT_INIT_SUPPORT
            rc.msg = (void*) &IBM_SLPProtocolEndpoint_InstAgent_Destroy;
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
            rc = IBM_SLPProtocolEndpoint_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_SLPProtocolEndpoint_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SLPProtocolEndpoint_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SLPProtocolEndpoint_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_SLPProtocolEndpoint_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_SLPProtocolEndpoint_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_SLPProtocolEndpoint_InstAgent_GetMaxIndex;
            break;
        case CLASS_SERVICE_MODIFYINSTANCE: 
            /* modify instance service */
            va_start( argptr, op ); 																				
            inst = va_arg(argptr, CMPIInstance *); 
            properties = va_arg(argptr, char **);
            rc = IBM_SLPProtocolEndpoint_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end( argptr );
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_INVOKEMETHOD: 
             /* involk method service */
        case CLASS_SERVICE_GETMETHODNAMES:
             /* get method name service */
        case CLASS_SERVICE_GETPARAMETERS:
             /* get method param name service */
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
GenNotSupportInstanceMICreateInstance(IBM_SLPProtocolEndpoint);
//GenNotSupportInstanceMIModifyInstance(IBM_SLPProtocolEndpoint);
GenNotSupportInstanceMIDeleteInstance(IBM_SLPProtocolEndpoint);
GenNotSupportInstanceMIExecQuery(IBM_SLPProtocolEndpoint);
GenNotSupportInstanceMICleanup(IBM_SLPProtocolEndpoint);

/* MI factory function */
CMInstanceMIStub( IBM_SLPProtocolEndpoint_,
                  Lenovo_SLPProtocolEndpoint_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_SLPPROTOCOLENDPOINT_INIT_SUPPORT /* You can turn on this flag in IBM_SLPProtocolEndpointAgent.h */
#define PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SLPProtocolEndpoint_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint;\
    Arg.GetNextInstIndex = IBM_SLPProtocolEndpoint_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SLPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SLPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SLPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SLPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_SLPProtocolEndpoint_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SLPProtocolEndpoint_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SLPProtocolEndpoint_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SLPProtocolEndpoint;\
    Arg.GetNextInstIndex = IBM_SLPProtocolEndpoint_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SLPProtocolEndpointKeyPropertyList;\
    Arg.PropertyList = IBM_SLPProtocolEndpointPropertyList;\
    Arg.propertyNo = sizeof(IBM_SLPProtocolEndpointPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SLPProtocolEndpointKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_SLPProtocolEndpoint Class Service Function */
CMPIStatus Lenovo_SLPProtocolEndpointService( 
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

/* Gets the Arg of Class IBM_SLPProtocolEndpoint Function */
sClassUtilArg IBM_SLPProtocolEndpoint_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_SLPPROTOCOLENDPOINT_ARG( Arg );

    return (Arg);
}

#endif
