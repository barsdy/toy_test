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
#include <system-core/ipmiraw/IPMIRaw.h>
#include <emerson/ipmi/IPMICmd.h>

#define IPMI_CMD_IPMI_PROPERTY 0xc4

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_OOBInventoryService class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_OOBInventoryService = (CMPIUint8 *)CLASSNAMETEXT_IBM_OOBInventoryService;

/* Property List */
static const char * const IBM_OOBInventoryServicePropertyList[] = 
{
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EnabledState,
    PROPERTYNAME_ForcedInventory,
    PROPERTYNAME_InventorySequences,
    PROPERTYNAME_InventorySequencesDescriptions,
    PROPERTYNAME_InventoryStatus,
    PROPERTYNAME_InventoryStatusDescriptions,
    PROPERTYNAME_InventoryTypes,
    PROPERTYNAME_InventoryTypesDescriptions,
    PROPERTYNAME_RequestedState
};

/* Key property List */
static const char * const IBM_OOBInventoryServiceKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_OOBINVENTORYSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_OOBInventoryServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBInventoryService;\
    Arg.GetKeyProperty = IBM_OOBInventoryService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_OOBInventoryService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_OOBInventoryService_GetProperty;\
    Arg.KeyPropertyList = IBM_OOBInventoryServiceKeyPropertyList;\
    Arg.PropertyList = IBM_OOBInventoryServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBInventoryServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBInventoryServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_OOBINVENTORYSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_OOBInventoryServiceAssociations;\
    Arg.AgentInit = IBM_OOBInventoryService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_OOBInventoryService_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBInventoryService;\
    Arg.GetKeyProperty = IBM_OOBInventoryService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_OOBInventoryService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_OOBInventoryService_GetProperty;\
    Arg.KeyPropertyList = IBM_OOBInventoryServiceKeyPropertyList;\
    Arg.PropertyList = IBM_OOBInventoryServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBInventoryServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBInventoryServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_OOBINVENTORYSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_OOBInventoryServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_OOBINVENTORYSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_OOBInventoryServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBInventoryService;\
    Arg.GetKeyProperty = IBM_OOBInventoryService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_OOBInventoryService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_OOBInventoryService_GetProperty;\
    Arg.KeyPropertyList = IBM_OOBInventoryServiceKeyPropertyList;\
    Arg.PropertyList = IBM_OOBInventoryServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBInventoryServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBInventoryServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_OOBINVENTORYSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_OOBInventoryServiceAssociations;\
    Arg.AgentInit = IBM_OOBInventoryService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_OOBInventoryService_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBInventoryService;\
    Arg.GetKeyProperty = IBM_OOBInventoryService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_OOBInventoryService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_OOBInventoryService_GetProperty;\
    Arg.KeyPropertyList = IBM_OOBInventoryServiceKeyPropertyList;\
    Arg.PropertyList = IBM_OOBInventoryServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBInventoryServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBInventoryServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_OOBINVENTORYSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_OOBInventoryServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

static const char* sPROP_ForcedInventory = "/v2/ibmc/uefi/force-inventory";

UINT8 SetForcedInventory(UINT8 value);

/* Get Properties value */
CMPIData IBM_OOBInventoryService_GetProperty( 
                                              CMPICount nInstIndex,
                                              CMPICount nPropIndex,
                                              void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_OOBInventoryService_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_OOBInventoryService_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_OOBInventoryService, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_OOBInventoryService, &rc);
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
        data = IBM_OOBInventoryService_GetProperty(nInstIndex, nKeyIndex | IBM_OOBINVENTORYSERVICE_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_OOBInventoryService_GenerateObjectPath( 
                                                            char **properties,
                                                            CMPICount InstIndex,
                                                            void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_OOBInventoryService_GetInstance( 
                                                CMPIInstanceMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_OOBInventoryService_EnumInstances( 
#else
CMPIStatus IBM_OOBInventoryService_EnumerateInstances( 
#endif
                                                       CMPIInstanceMI *mi,
                                                       const CMPIContext *ctx,
                                                       const CMPIResult *rslt,
                                                       const CMPIObjectPath *op,
                                                       const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_OOBInventoryService_EnumInstanceNames( 
#else
CMPIStatus IBM_OOBInventoryService_EnumerateInstanceNames( 
#endif
                                                           CMPIInstanceMI *mi,
                                                           const CMPIContext *ctx,
                                                           const CMPIResult *rslt,
                                                           const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_OOBInventoryService_Associators( 
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
    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_OOBInventoryService_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_OOBInventoryService_References( 
                                               CMPIAssociationMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char *resultClass,
                                               const char *role,
                                               const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_OOBInventoryService_ReferenceNames( 
                                                   CMPIAssociationMI *mi,
                                                   const CMPIContext *ctx,
                                                   const CMPIResult *rslt,
                                                   const CMPIObjectPath *op,
                                                   const char *resultClass,
                                                   const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_OOBInventoryService_ModifyInstance(
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
    BOOLEAN bValue = false;
    unsigned int uiSize = 0;
	UINT8 u8Forced = 0;
	UINT8 ret = 0;
	
    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg);

    if (Arg.AgentInit)
    {
        pAgentDataPtr = Arg.AgentInit(0);
    }

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_OOBInventoryServicePropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    /* check static property values if neccessary */
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_ForcedInventory, CMPI_boolean, &bValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;
    }

    /* call modify API here */
	if (bValue == true)
		u8Forced = 1;

    rc.rc = CMPI_RC_ERR_FAILED;
	ret = SetForcedInventory(u8Forced);
    if (ret == 0)
    {
        rc.rc = CMPI_RC_OK;
    }
CLEAN:
    /* free resource here if neccesary */

    if (Arg.AgentDestroy)
    {
        Arg.AgentDestroy(pAgentDataPtr);
    }
    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

/* IBM_OOBInventoryService Class Service Function */
CMPIStatus Lenovo_OOBInventoryServiceService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_OOBInventoryService,
                                     CIM_ServiceService);
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
            rc = IBM_OOBInventoryService_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_OOBInventoryService_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_OOBInventoryService_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_OOBINVENTORYSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_OOBInventoryService_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_OOBINVENTORYSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_OOBInventoryService_InstAgent_Destroy;
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
            rc = IBM_OOBInventoryService_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_OOBInventoryService_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_OOBInventoryService_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_OOBInventoryService_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_OOBInventoryService_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_OOBInventoryService_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_OOBInventoryService_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_OOBInventoryService_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_OOBInventoryService);
// GenNotSupportInstanceMIModifyInstance(IBM_OOBInventoryService);
GenNotSupportInstanceMIDeleteInstance(IBM_OOBInventoryService);
GenNotSupportInstanceMIExecQuery(IBM_OOBInventoryService);
GenNotSupportInstanceMICleanup(IBM_OOBInventoryService);

/* MI factory function */
CMInstanceMIStub( IBM_OOBInventoryService_,
                  Lenovo_OOBInventoryService_,
                  TheBroker,
                  CMNoHook);

#endif

/*
  0: success
  1: ipmi error
  2: error setting property or property not exist
*/
UINT8 SetForcedInventory(UINT8 value)
{
    UINT8 u8ret = 0;
    int len= strlen(sPROP_ForcedInventory);
    // ipmi command related info
    unsigned char au8reqBuf[256] = {0};
    int reqBufSize = 0;
    int respBufSize = 0;
    unsigned char au8respBuf [256] = {0};

    au8reqBuf[0] = 0x03;
    au8reqBuf[1] = len+1;
	/* Byte 4: Flags = 1 create */
	au8reqBuf[3] = 0x01;
	/* Byte 5: TLV type */
    au8reqBuf[4] = 0x80|(len); 
    strncpy((char *)au8reqBuf+5, sPROP_ForcedInventory, len);
	au8reqBuf[5+len] = 0x11;
	au8reqBuf[5+len+1] = value;
    reqBufSize = 5+len+2;

    u8ret = IPMI_DoIPMICmd(NETFN_IBM, IPMI_CMD_IPMI_PROPERTY, au8reqBuf, reqBufSize, au8respBuf, &respBufSize); 
    if (STATUS_OK != u8ret)
    {
        logTraceCIM(LOG_LEV_ERROR, "[%s]Calling IPMI_DoIPMICmd() to set IPMI Property[%s] failed",  __FUNCTION__, au8reqBuf+4);
        return 1;
    }
    logTraceCIM(LOG_LEV_DEBUG, "[%s]Set IPMI Property by IPMI Cmd for [%s]:result len[%d] %02x %02x %02x %02x.",  __FUNCTION__, 
		au8reqBuf+5, respBufSize, au8respBuf[0], au8respBuf[1], au8respBuf[2], au8respBuf[3]);

    if (0 != au8respBuf[0])
    {
        logTraceCIM(LOG_LEV_ERROR, "[%s]IPMI response Error[0x%02x] for [%s]",  __FUNCTION__, au8respBuf[0], au8reqBuf+5);
        return 2;
    }

/*
    if (0x03 == au8respBuf[1])
    {
        logTraceCIM(LOG_LEV_INFO, "[%s]IPMI response Property not exist for [%s]",  __FUNCTION__, au8reqBuf+5);
        return 2;
    }
*/
    return 0;

}


#else
#if IBM_OOBINVENTORYSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_OOBInventoryServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_OOBInventoryService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBInventoryService;\
    Arg.GetNextInstIndex = IBM_OOBInventoryService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_OOBInventoryServiceKeyPropertyList;\
    Arg.PropertyList = IBM_OOBInventoryServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBInventoryServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBInventoryServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_OOBInventoryService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_OOBInventoryService_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_OOBInventoryService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBInventoryService;\
    Arg.GetNextInstIndex = IBM_OOBInventoryService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_OOBInventoryServiceKeyPropertyList;\
    Arg.PropertyList = IBM_OOBInventoryServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBInventoryServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBInventoryServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_OOBInventoryService Class Service Function */
CMPIStatus Lenovo_OOBInventoryServiceService( 
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

/* Gets the Arg of Class IBM_OOBInventoryService Function */
sClassUtilArg IBM_OOBInventoryService_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_OOBINVENTORYSERVICE_ARG( Arg );

    return (Arg);
}

#endif
