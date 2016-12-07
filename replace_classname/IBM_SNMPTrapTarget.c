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
#include <emerson/cemgr/swe_function_table.h>

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

/* Retreive ADAM var */
#include <emerson/ab/avct_dm_ADAMLib.h>
#include <emerson/ab/avct_dm_VarList.h>
#include <emerson/ab/avct_SharedMem.h>
#include <emerson/ab/avct_SharedList.h>
#include <ctype.h>
#include "LogUtil.h"


/* IBM_SNMPTrapTarget class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_SNMPTrapTarget = (CMPIUint8 *)CLASSNAMETEXT_IBM_SNMPTrapTarget;

/* Property List */
static const char * const IBM_SNMPTrapTargetPropertyList[] = 
{
    PROPERTYNAME_NotificationMessage,
    PROPERTYNAME_PortInfo,
    PROPERTYNAME_PortProtocol,
    PROPERTYNAME_SNMPVersion
};

/* Key property List */
static const char * const IBM_SNMPTrapTargetKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_SNMPTRAPTARGET_INIT_SUPPORT /* You can turn on this flag in IBM_SNMPTrapTargetAgent.h */
#define PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPTrapTarget;\
    Arg.GetKeyProperty = IBM_SNMPTrapTarget_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPTrapTarget_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPTrapTarget_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPTrapTargetKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPTrapTargetPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPTrapTargetPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPTrapTargetKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPTRAPTARGETASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPTrapTargetAssociations;\
    Arg.AgentInit = IBM_SNMPTrapTarget_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SNMPTrapTarget_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPTrapTarget;\
    Arg.GetKeyProperty = IBM_SNMPTrapTarget_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPTrapTarget_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPTrapTarget_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPTrapTargetKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPTrapTargetPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPTrapTargetPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPTrapTargetKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPTRAPTARGETASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPTrapTargetAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_SNMPTRAPTARGET_INIT_SUPPORT /* You can turn on this flag in IBM_SNMPTrapTargetAgent.h */
#define PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPTrapTarget;\
    Arg.GetKeyProperty = IBM_SNMPTrapTarget_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPTrapTarget_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPTrapTarget_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPTrapTargetKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPTrapTargetPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPTrapTargetPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPTrapTargetKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPTRAPTARGETASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPTrapTargetAssociations;\
    Arg.AgentInit = IBM_SNMPTrapTarget_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SNMPTrapTarget_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPTrapTarget;\
    Arg.GetKeyProperty = IBM_SNMPTrapTarget_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPTrapTarget_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPTrapTarget_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPTrapTargetKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPTrapTargetPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPTrapTargetPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPTrapTargetKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPTRAPTARGETASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPTrapTargetAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_SNMPTrapTarget_GetProperty( 
                                         CMPICount nInstIndex,
                                         CMPICount nPropIndex,
                                         void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_SNMPTrapTarget_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_SNMPTrapTarget_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_SNMPTrapTarget, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_SNMPTrapTarget, &rc);
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
        data = IBM_SNMPTrapTarget_GetProperty(nInstIndex, nKeyIndex | IBM_SNMPTRAPTARGET_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_SNMPTrapTarget_GenerateObjectPath( 
                                                       char **properties,
                                                       CMPICount InstIndex,
                                                       void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_SNMPTrapTarget_GetInstance( 
                                           CMPIInstanceMI *mi,
                                           const CMPIContext *ctx,
                                           const CMPIResult *rslt,
                                           const CMPIObjectPath *op,
                                           const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SNMPTrapTarget_EnumInstances( 
#else
CMPIStatus IBM_SNMPTrapTarget_EnumerateInstances( 
#endif
                                                  CMPIInstanceMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SNMPTrapTarget_EnumInstanceNames( 
#else
CMPIStatus IBM_SNMPTrapTarget_EnumerateInstanceNames( 
#endif
                                                      CMPIInstanceMI *mi,
                                                      const CMPIContext *ctx,
                                                      const CMPIResult *rslt,
                                                      const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_SNMPTrapTarget_Associators( 
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
    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_SNMPTrapTarget_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_SNMPTrapTarget_References( 
                                          CMPIAssociationMI *mi,
                                          const CMPIContext *ctx,
                                          const CMPIResult *rslt,
                                          const CMPIObjectPath *op,
                                          const char *resultClass,
                                          const char *role,
                                          const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_SNMPTrapTarget_ReferenceNames( 
                                              CMPIAssociationMI *mi,
                                              const CMPIContext *ctx,
                                              const CMPIResult *rslt,
                                              const CMPIObjectPath *op,
                                              const char *resultClass,
                                              const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_SNMPTrapTarget_ModifyInstance(
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
    AVCT_DM_VarListStatus varStatus;
    AVCT_DM_VarListError varError;
    CMPIData dataReq;
    CMPIString *dataStr = NULL;
    char *szName = NULL;
    int i = 0;
    UINT32 u32CurrentPort = 0;
    UINT32 u32NewPort = 0;

    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg);

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

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_SNMPTrapTargetPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    dataReq = inst->ft->getProperty(inst, PROPERTYNAME_PortInfo, &rc);
    if ((dataReq.state != CMPI_goodValue) || (rc.rc != CMPI_RC_OK) || (dataReq.type != CMPI_string))
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;  
    }
    dataStr = CMPIData2String(&dataReq);
    if (dataStr == NULL)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;  
    }
    szName = (char *)dataStr->ft->getCharPtr(dataStr, &rc);
    
    /* Verify if the input port is a digital number */
    for (i = 0; i < strlen(szName); i++)
    {
        if (!isdigit(szName[i]))
        {
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }
    }

    /* Get current port number from ADAM variable */
    varStatus = GETVARVALUE(UINT, AVCT_DM_DEFVARLIST, 0, 0, true, "s/snmp/config/trapPort", &varError, (unsigned long *)&u32CurrentPort);
    if (varStatus != AVCT_DM_VarListStatus_OK)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;
    }

    u32NewPort = atoi(szName);
    if(u32CurrentPort != u32NewPort)
    {
        char pNameString[MAX_STR_LEN] = {0};

        /* Set software event username */        
        CMPIGetUserNameFromContext(ctx, pNameString);
        varStatus = SETVARVALUE(STRING, 
                                AVCT_DM_DEFVARLIST, 
                                0, 0, false, 
                                "s/snmp/data/swe_username", 
                                &varError, 
                                pNameString);
        if (varStatus != AVCT_DM_VarListStatus_OK)
        {
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }

        /* Set new port number to ADAM variable */        
        varStatus = SETVARVALUE(UINT, 
                                AVCT_DM_DEFVARLIST, 
                                0, 0, false, 
                                "s/snmp/config/trapPort", 
                                &varError, 
                                atoi(szName));
        if (varStatus != AVCT_DM_VarListStatus_OK)
        {
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }
    }

CLEAN:

    SafeCMRelease(dataStr); 

    CMPIDataRelease(&dataReq);

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

/* IBM_SNMPTrapTarget Class Service Function */
CMPIStatus Lenovo_SNMPTrapTargetService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_SNMPTrapTarget,
                                     CIM_SNMPTrapTargetService);
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
            rc = IBM_SNMPTrapTarget_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_SNMPTrapTarget_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_SNMPTrapTarget_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_SNMPTRAPTARGET_INIT_SUPPORT
            rc.msg = (void*) &IBM_SNMPTrapTarget_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_SNMPTRAPTARGET_INIT_SUPPORT
            rc.msg = (void*) &IBM_SNMPTrapTarget_InstAgent_Destroy;
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
            rc = IBM_SNMPTrapTarget_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_SNMPTrapTarget_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SNMPTrapTarget_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SNMPTrapTarget_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_SNMPTrapTarget_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_SNMPTrapTarget_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_SNMPTrapTarget_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_SNMPTrapTarget_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_SNMPTrapTarget);
// GenNotSupportInstanceMIModifyInstance(IBM_SNMPTrapTarget);
GenNotSupportInstanceMIDeleteInstance(IBM_SNMPTrapTarget);
GenNotSupportInstanceMIExecQuery(IBM_SNMPTrapTarget);
GenNotSupportInstanceMICleanup(IBM_SNMPTrapTarget);

/* MI factory function */
CMInstanceMIStub( IBM_SNMPTrapTarget_,
                  Lenovo_SNMPTrapTarget_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_SNMPTRAPTARGET_INIT_SUPPORT /* You can turn on this flag in IBM_SNMPTrapTargetAgent.h */
#define PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SNMPTrapTarget_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPTrapTarget;\
    Arg.GetNextInstIndex = IBM_SNMPTrapTarget_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SNMPTrapTargetKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPTrapTargetPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPTrapTargetPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPTrapTargetKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_SNMPTrapTarget_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SNMPTrapTarget_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SNMPTrapTarget_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPTrapTarget;\
    Arg.GetNextInstIndex = IBM_SNMPTrapTarget_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SNMPTrapTargetKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPTrapTargetPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPTrapTargetPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPTrapTargetKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_SNMPTrapTarget Class Service Function */
CMPIStatus Lenovo_SNMPTrapTargetService( 
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

/* Gets the Arg of Class IBM_SNMPTrapTarget Function */
sClassUtilArg IBM_SNMPTrapTarget_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_SNMPTRAPTARGET_ARG( Arg );

    return (Arg);
}

#endif
