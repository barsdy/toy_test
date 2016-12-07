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
#include <emerson/imm_sa/sa_core.h>


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_ServiceAdvisorActivityLogEntry class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_ServiceAdvisorActivityLogEntry = (CMPIUint8 *)CLASSNAMETEXT_IBM_ServiceAdvisorActivityLogEntry;

/* Property List */
static const char * const IBM_ServiceAdvisorActivityLogEntryPropertyList[] = 
{
    PROPERTYNAME_AssignedNumber,
    PROPERTYNAME_Corrected,
    PROPERTYNAME_CreationTimeStamp,
    PROPERTYNAME_EventID,
    PROPERTYNAME_EventSource,
    PROPERTYNAME_Message,
    PROPERTYNAME_PerceivedSeverity,
    PROPERTYNAME_ServerSendState,
    PROPERTYNAME_SupportCenterSendState
};

/* Key property List */
static const char * const IBM_ServiceAdvisorActivityLogEntryKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_SERVICEADVISORACTIVITYLOGENTRY_INIT_SUPPORT /* You can turn on this flag in IBM_ServiceAdvisorActivityLogEntryAgent.h */
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorActivityLogEntry;\
    Arg.GetKeyProperty = IBM_ServiceAdvisorActivityLogEntry_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ServiceAdvisorActivityLogEntry_GetProperty;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorActivityLogEntryKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorActivityLogEntryPropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SERVICEADVISORACTIVITYLOGENTRYASSONUM;\
    Arg.AssocArray = G_sLenovo_ServiceAdvisorActivityLogEntryAssociations;\
    Arg.AgentInit = IBM_ServiceAdvisorActivityLogEntry_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ServiceAdvisorActivityLogEntry_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorActivityLogEntry;\
    Arg.GetKeyProperty = IBM_ServiceAdvisorActivityLogEntry_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ServiceAdvisorActivityLogEntry_GetProperty;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorActivityLogEntryKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorActivityLogEntryPropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SERVICEADVISORACTIVITYLOGENTRYASSONUM;\
    Arg.AssocArray = G_sLenovo_ServiceAdvisorActivityLogEntryAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_SERVICEADVISORACTIVITYLOGENTRY_INIT_SUPPORT /* You can turn on this flag in IBM_ServiceAdvisorActivityLogEntryAgent.h */
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorActivityLogEntry;\
    Arg.GetKeyProperty = IBM_ServiceAdvisorActivityLogEntry_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ServiceAdvisorActivityLogEntry_GetProperty;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorActivityLogEntryKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorActivityLogEntryPropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SERVICEADVISORACTIVITYLOGENTRYASSONUM;\
    Arg.AssocArray = G_sLenovo_ServiceAdvisorActivityLogEntryAssociations;\
    Arg.AgentInit = IBM_ServiceAdvisorActivityLogEntry_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ServiceAdvisorActivityLogEntry_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorActivityLogEntry;\
    Arg.GetKeyProperty = IBM_ServiceAdvisorActivityLogEntry_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ServiceAdvisorActivityLogEntry_GetProperty;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorActivityLogEntryKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorActivityLogEntryPropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SERVICEADVISORACTIVITYLOGENTRYASSONUM;\
    Arg.AssocArray = G_sLenovo_ServiceAdvisorActivityLogEntryAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_ServiceAdvisorActivityLogEntry_GetProperty( 
                                                         CMPICount nInstIndex,
                                                         CMPICount nPropIndex,
                                                         void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_ServiceAdvisorActivityLogEntry_GetKeyProperty( 
                                                            CMPICount nInstIndex,
                                                            CMPICount nKeyIndex,
                                                            void *pAgentDataPtr)
{
    CMPIData data = {CMPI_string, CMPI_badValue, {0}};
        data.state = CMPI_badValue;
    data = IBM_ServiceAdvisorActivityLogEntry_GetProperty(nInstIndex, nKeyIndex | IBM_SERVICEADVISORACTIVITYLOGENTRY_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_ServiceAdvisorActivityLogEntry_GenerateObjectPath( 
                                                                       char **properties,
                                                                       CMPICount InstIndex,
                                                                       void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_ServiceAdvisorActivityLogEntry_GetInstance( 
                                                           CMPIInstanceMI *mi,
                                                           const CMPIContext *ctx,
                                                           const CMPIResult *rslt,
                                                           const CMPIObjectPath *op,
                                                           const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ServiceAdvisorActivityLogEntry_EnumInstances( 
#else
CMPIStatus IBM_ServiceAdvisorActivityLogEntry_EnumerateInstances( 
#endif
                                                                  CMPIInstanceMI *mi,
                                                                  const CMPIContext *ctx,
                                                                  const CMPIResult *rslt,
                                                                  const CMPIObjectPath *op,
                                                                  const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ServiceAdvisorActivityLogEntry_EnumInstanceNames( 
#else
CMPIStatus IBM_ServiceAdvisorActivityLogEntry_EnumerateInstanceNames( 
#endif
                                                                      CMPIInstanceMI *mi,
                                                                      const CMPIContext *ctx,
                                                                      const CMPIResult *rslt,
                                                                      const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_ServiceAdvisorActivityLogEntry_Associators( 
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
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_ServiceAdvisorActivityLogEntry_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_ServiceAdvisorActivityLogEntry_References( 
                                                          CMPIAssociationMI *mi,
                                                          const CMPIContext *ctx,
                                                          const CMPIResult *rslt,
                                                          const CMPIObjectPath *op,
                                                          const char *resultClass,
                                                          const char *role,
                                                          const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_ServiceAdvisorActivityLogEntry_ReferenceNames( 
                                                              CMPIAssociationMI *mi,
                                                              const CMPIContext *ctx,
                                                              const CMPIResult *rslt,
                                                              const CMPIObjectPath *op,
                                                              const char *resultClass,
                                                              const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_ServiceAdvisorActivityLogEntry_ModifyInstance(
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
    CMPIStatus tRC =
    {
        CMPI_RC_ERR_FAILED,
        NULL
    };
    BOOLEAN bValue = FALSE;
    CMPICount nIndex = 0;
    CMPIData data;

    sClassUtilArg Arg;
    SA_LIST_OPERATION_TYPE eOperatType;
    SA_Status nSAStatus = 0;
    UINT32 au32UniqueIndex = 0;
    SAActivityLogEntryAgentData *pAgentDataPtr = NULL;
    SAActivityLogEntryDataUnit *pDataUnit = NULL;

    char nameString[MAX_STR_LEN] = {0};
    UINT32 u32Role = 0;
    
    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg);

    /* check privilege */
    CMPIGetUserNameFromContext(ctx, nameString);
    //logTraceCIM(LOG_LEV_INFO, "%s()- nameString is %s.", __FUNCTION__, nameString);
    CMPIGetUserRoleFromContext(ctx, &u32Role);
    
    /* parameter 3 didn't use currently, pass MODIFY_REQUEST (2) */
    if (!sm_imm_authorized(u32Role, SACFG_ACTION , 2))
    {
        rc.rc = 4; /* Access Deny */
        goto CLEAN;
    }


#if IBM_SERVICEADVISORACTIVITYLOGENTRY_INIT_SUPPORT
    pAgentDataPtr = (SAActivityLogEntryAgentData *) IBM_ServiceAdvisorActivityLogEntry_InstAgent_Init(0);
#endif


    if (pAgentDataPtr == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }
    
    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if ((pAgentDataPtr->pActLogEntUnit == NULL) ||
        (nIndex >= pAgentDataPtr->iUnitCount))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }
    pDataUnit = &(pAgentDataPtr->pActLogEntUnit[nIndex]);
    au32UniqueIndex = pDataUnit->au32UniqueIndex;

    
    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_ServiceAdvisorActivityLogEntryPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    data = inst->ft->getProperty(inst, PROPERTYNAME_Corrected,&tRC);
    if ((data.state != CMPI_goodValue) || (tRC.rc != CMPI_RC_OK))
    {              
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    bValue = data.value.boolean;
    CMPIDataRelease(&data);

    if (bValue)
    {
        eOperatType = SA_SERVICE_PROBLEM_OP_CLOSE;
    }
    else
    {
        eOperatType = SA_SERVICE_PROBLEM_OP_OPEN;
    }
    
    nSAStatus = SAcore_ServiceListOperations(eOperatType, &au32UniqueIndex, 1);
    if (nSAStatus != SA_STATUS_OK)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;
    }
    rc.rc = CMPI_RC_OK;

    
CLEAN:
    /* free resource here if neccesary */

#if IBM_SERVICEADVISORACTIVITYLOGENTRY_INIT_SUPPORT
    IBM_ServiceAdvisorActivityLogEntry_InstAgent_Destroy(pAgentDataPtr);
#endif

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

/* IBM_ServiceAdvisorActivityLogEntry Class Service Function */
CMPIStatus Lenovo_ServiceAdvisorActivityLogEntryService( 
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
    //char **properties;
    char *className = NULL;
    //char *asscClass;
    //char *resultClass;
    //char *role;
    //char *resultRole;
    //CMPIInstance *inst = NULL;
    //char *method;
    //CMPIArgs *in;
    //CMPIArgs *out;

    if (actionID == CLASS_SERVICE_ISA_LITE)
    {
        va_start(argptr, op);
        className = va_arg(argptr, char *);
        va_end(argptr);
    }

    rc = CIMClassUtil_CheckClassName(actionID, mi, ctx, rslt, op, 
                                     className,
                                     (char *) CLASSNAME_Lenovo_IBM_ServiceAdvisorActivityLogEntry,
                                     CIM_LogEntryService);
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
            rc = IBM_ServiceAdvisorActivityLogEntry_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_ServiceAdvisorActivityLogEntry_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_ServiceAdvisorActivityLogEntry_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_SERVICEADVISORACTIVITYLOGENTRY_INIT_SUPPORT
            rc.msg = (void*) &IBM_ServiceAdvisorActivityLogEntry_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_SERVICEADVISORACTIVITYLOGENTRY_INIT_SUPPORT
            rc.msg = (void*) &IBM_ServiceAdvisorActivityLogEntry_InstAgent_Destroy;
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
            rc = IBM_ServiceAdvisorActivityLogEntry_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_ServiceAdvisorActivityLogEntry_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ServiceAdvisorActivityLogEntry_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ServiceAdvisorActivityLogEntry_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_ServiceAdvisorActivityLogEntry_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_ServiceAdvisorActivityLogEntry_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_ServiceAdvisorActivityLogEntry);
// GenNotSupportInstanceMIModifyInstance(IBM_ServiceAdvisorActivityLogEntry);
GenNotSupportInstanceMIDeleteInstance(IBM_ServiceAdvisorActivityLogEntry);
GenNotSupportInstanceMIExecQuery(IBM_ServiceAdvisorActivityLogEntry);
GenNotSupportInstanceMICleanup(IBM_ServiceAdvisorActivityLogEntry);

/* MI factory function */
CMInstanceMIStub( IBM_ServiceAdvisorActivityLogEntry_,
                  Lenovo_ServiceAdvisorActivityLogEntry_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_SERVICEADVISORACTIVITYLOGENTRY_INIT_SUPPORT /* You can turn on this flag in IBM_ServiceAdvisorActivityLogEntryAgent.h */
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorActivityLogEntry;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorActivityLogEntryKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorActivityLogEntryPropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_ServiceAdvisorActivityLogEntry_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ServiceAdvisorActivityLogEntry_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorActivityLogEntry;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorActivityLogEntry_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorActivityLogEntryKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorActivityLogEntryPropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorActivityLogEntryKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_ServiceAdvisorActivityLogEntry Class Service Function */
CMPIStatus Lenovo_ServiceAdvisorActivityLogEntryService( 
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

/* Gets the Arg of Class IBM_ServiceAdvisorActivityLogEntry Function */
sClassUtilArg IBM_ServiceAdvisorActivityLogEntry_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_SERVICEADVISORACTIVITYLOGENTRY_ARG( Arg );

    return (Arg);
}

#endif
