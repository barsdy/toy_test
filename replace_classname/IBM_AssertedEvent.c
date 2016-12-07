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

/* IBM_AssertedEvent class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_AssertedEvent = (CMPIUint8 *)CLASSNAMETEXT_IBM_AssertedEvent;

/* Property List */
static const char * const IBM_AssertedEventPropertyList[] = 
{
    PROPERTYNAME_AlertingElementFormat,
    PROPERTYNAME_AlertingManagedElement,
    PROPERTYNAME_AlertType,
    PROPERTYNAME_CommonEventID,
    PROPERTYNAME_CorrelatedIndications,
    PROPERTYNAME_EventFlag,
    PROPERTYNAME_EventID,
    PROPERTYNAME_EventType,
    PROPERTYNAME_IsLocalEvent,
    PROPERTYNAME_Message,
    PROPERTYNAME_MessageArguments,
    PROPERTYNAME_MessageID,
    PROPERTYNAME_MessageText,
    PROPERTYNAME_MessageVariables,
    PROPERTYNAME_OtherAlertingElementFormat,
    PROPERTYNAME_OtherAlertType,
    PROPERTYNAME_OtherSeverity,
    PROPERTYNAME_OwningEntity,
    PROPERTYNAME_PerceivedSeverity,
    PROPERTYNAME_RawDebugLogURL,
    PROPERTYNAME_RawLogSize,
    PROPERTYNAME_RelatedEventID,
    PROPERTYNAME_ReportingChain,
    PROPERTYNAME_SystemName,
    PROPERTYNAME_TSLVersion
};

/* Key property List */
static const char * const IBM_AssertedEventKeyPropertyList[] = 
{
    PROPERTYNAME_IndicationIdentifier,
    PROPERTYNAME_IndicationTime
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_ASSERTEDEVENT_INIT_SUPPORT /* You can turn on this flag in IBM_AssertedEventAgent.h */
#define PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssertedEvent;\
    Arg.GetKeyProperty = IBM_AssertedEvent_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AssertedEvent_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AssertedEvent_GetProperty;\
    Arg.KeyPropertyList = IBM_AssertedEventKeyPropertyList;\
    Arg.PropertyList = IBM_AssertedEventPropertyList;\
    Arg.propertyNo = sizeof(IBM_AssertedEventPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssertedEventKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ASSERTEDEVENTASSONUM;\
    Arg.AssocArray = G_sLenovo_AssertedEventAssociations;\
    Arg.AgentInit = IBM_AssertedEvent_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AssertedEvent_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssertedEvent;\
    Arg.GetKeyProperty = IBM_AssertedEvent_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AssertedEvent_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AssertedEvent_GetProperty;\
    Arg.KeyPropertyList = IBM_AssertedEventKeyPropertyList;\
    Arg.PropertyList = IBM_AssertedEventPropertyList;\
    Arg.propertyNo = sizeof(IBM_AssertedEventPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssertedEventKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ASSERTEDEVENTASSONUM;\
    Arg.AssocArray = G_sLenovo_AssertedEventAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_ASSERTEDEVENT_INIT_SUPPORT /* You can turn on this flag in IBM_AssertedEventAgent.h */
#define PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssertedEvent;\
    Arg.GetKeyProperty = IBM_AssertedEvent_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AssertedEvent_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AssertedEvent_GetProperty;\
    Arg.KeyPropertyList = IBM_AssertedEventKeyPropertyList;\
    Arg.PropertyList = IBM_AssertedEventPropertyList;\
    Arg.propertyNo = sizeof(IBM_AssertedEventPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssertedEventKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ASSERTEDEVENTASSONUM;\
    Arg.AssocArray = G_sLenovo_AssertedEventAssociations;\
    Arg.AgentInit = IBM_AssertedEvent_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AssertedEvent_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssertedEvent;\
    Arg.GetKeyProperty = IBM_AssertedEvent_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AssertedEvent_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AssertedEvent_GetProperty;\
    Arg.KeyPropertyList = IBM_AssertedEventKeyPropertyList;\
    Arg.PropertyList = IBM_AssertedEventPropertyList;\
    Arg.propertyNo = sizeof(IBM_AssertedEventPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssertedEventKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ASSERTEDEVENTASSONUM;\
    Arg.AssocArray = G_sLenovo_AssertedEventAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_AssertedEvent_GetProperty( 
                                        CMPICount nInstIndex,
                                        CMPICount nPropIndex,
                                        void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_AssertedEvent_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_AssertedEvent_GetKeyProperty( 
                                           CMPICount nInstIndex,
                                           CMPICount nKeyIndex,
                                           void *pAgentDataPtr)
{
    CMPIData data = {CMPI_string, CMPI_badValue, {0}};
        data.state = CMPI_badValue;
    data = IBM_AssertedEvent_GetProperty(nInstIndex, nKeyIndex | IBM_ASSERTEDEVENT_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Get Argument */
void IBM_AssertedEvent_GetArgument(sClassUtilArg *pArg)
{
    sClassUtilArg Arg;

    if (pArg)
    {
        PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg);
        memcpy(pArg, &Arg, sizeof (sClassUtilArg));
    }
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_AssertedEvent_GenerateObjectPath( 
                                                      char **properties,
                                                      CMPICount InstIndex,
                                                      void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_AssertedEvent_GetInstance( 
                                          CMPIInstanceMI *mi,
                                          const CMPIContext *ctx,
                                          const CMPIResult *rslt,
                                          const CMPIObjectPath *op,
                                          const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_AssertedEvent_EnumInstances( 
#else
CMPIStatus IBM_AssertedEvent_EnumerateInstances( 
#endif
                                                 CMPIInstanceMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_AssertedEvent_EnumInstanceNames( 
#else
CMPIStatus IBM_AssertedEvent_EnumerateInstanceNames( 
#endif
                                                     CMPIInstanceMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_AssertedEvent_Associators( 
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
    PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_AssertedEvent_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_AssertedEvent_References( 
                                         CMPIAssociationMI *mi,
                                         const CMPIContext *ctx,
                                         const CMPIResult *rslt,
                                         const CMPIObjectPath *op,
                                         const char *resultClass,
                                         const char *role,
                                         const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_AssertedEvent_ReferenceNames( 
                                             CMPIAssociationMI *mi,
                                             const CMPIContext *ctx,
                                             const CMPIResult *rslt,
                                             const CMPIObjectPath *op,
                                             const char *resultClass,
                                             const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* IBM_AssertedEvent Class Service Function */
CMPIStatus Lenovo_AssertedEventService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_AssertedEvent,
                                     CIM_AlertIndicationService);
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
            rc = IBM_AssertedEvent_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_AssertedEvent_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_AssertedEvent_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_ASSERTEDEVENT_INIT_SUPPORT
            rc.msg = (void*) &IBM_AssertedEvent_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_ASSERTEDEVENT_INIT_SUPPORT
            rc.msg = (void*) &IBM_AssertedEvent_InstAgent_Destroy;
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
            rc = IBM_AssertedEvent_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_AssertedEvent_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_AssertedEvent_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_AssertedEvent_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_AssertedEvent_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_AssertedEvent_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_AssertedEvent_InstAgent_GetMaxIndex;
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
GenNotSupportInstanceMICreateInstance(IBM_AssertedEvent);
GenNotSupportInstanceMIModifyInstance(IBM_AssertedEvent);
GenNotSupportInstanceMIDeleteInstance(IBM_AssertedEvent);
GenNotSupportInstanceMIExecQuery(IBM_AssertedEvent);
GenNotSupportInstanceMICleanup(IBM_AssertedEvent);

/* MI factory function */
CMInstanceMIStub( IBM_AssertedEvent_,
                  Lenovo_AssertedEvent_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_ASSERTEDEVENT_INIT_SUPPORT /* You can turn on this flag in IBM_AssertedEventAgent.h */
#define PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_AssertedEvent_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssertedEvent;\
    Arg.GetNextInstIndex = IBM_AssertedEvent_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_AssertedEventKeyPropertyList;\
    Arg.PropertyList = IBM_AssertedEventPropertyList;\
    Arg.propertyNo = sizeof(IBM_AssertedEventPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssertedEventKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_AssertedEvent_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AssertedEvent_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_AssertedEvent_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssertedEvent;\
    Arg.GetNextInstIndex = IBM_AssertedEvent_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_AssertedEventKeyPropertyList;\
    Arg.PropertyList = IBM_AssertedEventPropertyList;\
    Arg.propertyNo = sizeof(IBM_AssertedEventPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssertedEventKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_AssertedEvent Class Service Function */
CMPIStatus Lenovo_AssertedEventService( 
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

/* Gets the Arg of Class IBM_AssertedEvent Function */
sClassUtilArg IBM_AssertedEvent_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_ASSERTEDEVENT_ARG( Arg );

    return (Arg);
}

#endif
