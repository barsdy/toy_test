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


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_PropertyService class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_PropertyService = (CMPIUint8 *)CLASSNAMETEXT_IBM_PropertyService;

/* Property List */
static const char * const IBM_PropertyServicePropertyList[] = 
{
    PROPERTYNAME_USBHypervisorPresence
};

/* Key property List */
static const char * const IBM_PropertyServiceKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_PROPERTYSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_PropertyServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PropertyService;\
    Arg.GetKeyProperty = IBM_PropertyService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PropertyService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PropertyService_GetProperty;\
    Arg.KeyPropertyList = IBM_PropertyServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PropertyServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PropertyServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PropertyServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_PROPERTYSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_PropertyServiceAssociations;\
    Arg.AgentInit = IBM_PropertyService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_PropertyService_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PropertyService;\
    Arg.GetKeyProperty = IBM_PropertyService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PropertyService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PropertyService_GetProperty;\
    Arg.KeyPropertyList = IBM_PropertyServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PropertyServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PropertyServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PropertyServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_PROPERTYSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_PropertyServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_PROPERTYSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_PropertyServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PropertyService;\
    Arg.GetKeyProperty = IBM_PropertyService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PropertyService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PropertyService_GetProperty;\
    Arg.KeyPropertyList = IBM_PropertyServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PropertyServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PropertyServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PropertyServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_PROPERTYSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_PropertyServiceAssociations;\
    Arg.AgentInit = IBM_PropertyService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_PropertyService_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PropertyService;\
    Arg.GetKeyProperty = IBM_PropertyService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PropertyService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PropertyService_GetProperty;\
    Arg.KeyPropertyList = IBM_PropertyServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PropertyServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PropertyServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PropertyServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_PROPERTYSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_PropertyServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_PropertyService_GetProperty( 
                                          CMPICount nInstIndex,
                                          CMPICount nPropIndex,
                                          void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_PropertyService_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_PropertyService_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_PropertyService, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_PropertyService, &rc);
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
        data = IBM_PropertyService_GetProperty(nInstIndex, nKeyIndex | IBM_PROPERTYSERVICE_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_PropertyService_GenerateObjectPath( 
                                                        char **properties,
                                                        CMPICount InstIndex,
                                                        void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_PropertyService_GetInstance( 
                                            CMPIInstanceMI *mi,
                                            const CMPIContext *ctx,
                                            const CMPIResult *rslt,
                                            const CMPIObjectPath *op,
                                            const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_PropertyService_EnumInstances( 
#else
CMPIStatus IBM_PropertyService_EnumerateInstances( 
#endif
                                                   CMPIInstanceMI *mi,
                                                   const CMPIContext *ctx,
                                                   const CMPIResult *rslt,
                                                   const CMPIObjectPath *op,
                                                   const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_PropertyService_EnumInstanceNames( 
#else
CMPIStatus IBM_PropertyService_EnumerateInstanceNames( 
#endif
                                                       CMPIInstanceMI *mi,
                                                       const CMPIContext *ctx,
                                                       const CMPIResult *rslt,
                                                       const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_PropertyService_Associators( 
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
    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_PropertyService_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_PropertyService_References( 
                                           CMPIAssociationMI *mi,
                                           const CMPIContext *ctx,
                                           const CMPIResult *rslt,
                                           const CMPIObjectPath *op,
                                           const char *resultClass,
                                           const char *role,
                                           const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_PropertyService_ReferenceNames( 
                                               CMPIAssociationMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char *resultClass,
                                               const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_PropertyService_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg);

    if (Arg.AgentInit)
    {
        pAgentDataPtr = Arg.AgentInit(0);
    }

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (nIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    /* invoke method */
    if (0 == strcmp(method, "GetConfigurationURL"))
    {
        value.uint32 = IBM_PropertyService_InstAgent_GetConfigurationURL((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "GetIPMIPropertyValue"))
    {
        value.uint32 = IBM_PropertyService_InstAgent_GetIPMIPropertyValue((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_METHOD_NOT_FOUND;
    }

CLEAN:
    if (Arg.AgentDestroy)
    {
        Arg.AgentDestroy(pAgentDataPtr);
    }

    return (rc);
}

#ifndef _BROKER_SFCB
CMPIData *IBM_PropertyService_GetMethodName()
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
    nameArray = (void*) TheBroker.eft->newArray(&TheBroker, 2, CMPI_chars, &status);

    if(!nameArray)
    {
        return (NULL);
    }

    /* add method name */
    value.chars = (char *) METHODNAME_GetConfigurationURL;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_GetIPMIPropertyValue;
    nameArray->ft->setElementAt(nameArray, 1, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

CMPIData *IBM_PropertyService_GetMethodParameters(const char * MethodName)
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

    if (0 == strcmp(MethodName, METHODNAME_GetConfigurationURL))
    {
        iMethID = 0;
    }
    else if (0 == strcmp(MethodName, METHODNAME_GetIPMIPropertyValue))
    {
        iMethID = 1;
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
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Protocol,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_uint16;
            pArgs->ft->addArg(pArgs, PARAMNAME_Port,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_URL,&value,CMPI_chars);
            break;

        case 1:
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Name,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_uint8;
            pArgs->ft->addArg(pArgs, PARAMNAME_PropertyType,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Value,&value,CMPI_chars);
            value.chars = "A uint8";
            pArgs->ft->addArg(pArgs, PARAMNAME_ByteValue,&value,CMPI_chars);
            value.chars = "A uint16";
            pArgs->ft->addArg(pArgs, PARAMNAME_WordValue,&value,CMPI_chars);
            value.chars = "A uint32";
            pArgs->ft->addArg(pArgs, PARAMNAME_DWordValue,&value,CMPI_chars);
            break;

    }

    data->value.args = pArgs;
    data->type = CMPI_args;
    data->state = CMPI_goodValue;
    return (data);
}
#endif

/* IBM_PropertyService Class Service Function */
CMPIStatus Lenovo_PropertyServiceService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_PropertyService,
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
            rc = IBM_PropertyService_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_PropertyService_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_PropertyService_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_PROPERTYSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_PropertyService_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_PROPERTYSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_PropertyService_InstAgent_Destroy;
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
            rc = IBM_PropertyService_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_PropertyService_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_PropertyService_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_PropertyService_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_PropertyService_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_PropertyService_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_PropertyService_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_PropertyService_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_PropertyService_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_PropertyService_GetMethodParameters(method);
            va_end(argptr);
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_MODIFYINSTANCE:
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
GenNotSupportInstanceMICreateInstance(IBM_PropertyService);
GenNotSupportInstanceMIModifyInstance(IBM_PropertyService);
GenNotSupportInstanceMIDeleteInstance(IBM_PropertyService);
GenNotSupportInstanceMIExecQuery(IBM_PropertyService);
GenNotSupportInstanceMICleanup(IBM_PropertyService);

/* MI factory function */
CMInstanceMIStub( IBM_PropertyService_,
                  Lenovo_PropertyService_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_PropertyService);

CMMethodMIStub( IBM_PropertyService_,
                Lenovo_PropertyService_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_PROPERTYSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_PropertyServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_PropertyService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PropertyService;\
    Arg.GetNextInstIndex = IBM_PropertyService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_PropertyServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PropertyServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PropertyServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PropertyServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_PropertyService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_PropertyService_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_PropertyService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PropertyService;\
    Arg.GetNextInstIndex = IBM_PropertyService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_PropertyServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PropertyServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PropertyServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PropertyServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_PropertyService Class Service Function */
CMPIStatus Lenovo_PropertyServiceService( 
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

/* Gets the Arg of Class IBM_PropertyService Function */
sClassUtilArg IBM_PropertyService_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_PROPERTYSERVICE_ARG( Arg );

    return (Arg);
}

#endif
