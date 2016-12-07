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
#include "RoleNames.h"

/* Include class header files */
#include <RegisterClass.h>

/* Include agent header files */
#include <RegisterClassAgent.h>

/* Association classes */


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
#include "../AssociationTable.h"

CMPIBroker *TheBroker;
#endif

/* IBM_AssociatedCertificate class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_AssociatedCertificate = (CMPIUint8 *)CLASSNAMETEXT_IBM_AssociatedCertificate;

/* Property List */
static const char * const IBM_AssociatedCertificatePropertyList[] = 
{
    PROPERTYNAME_Index,
    PROPERTYNAME_IsValid,
    PROPERTYNAME_Type
};

/* Key property List */
static const char * const IBM_AssociatedCertificateKeyPropertyList[] = 
{
    (char *)ROLENAME_Antecedent,
    (char *)ROLENAME_Dependent
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_ASSOCIATEDCERTIFICATE_INIT_SUPPORT /* You can turn on this flag in IBM_AssociatedCertificateAgent.h */
#define PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssociatedCertificate;\
    Arg.GetKeyProperty = IBM_AssociatedCertificate_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AssociatedCertificate_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AssociatedCertificate_GetProperty;\
    Arg.KeyPropertyList = IBM_AssociatedCertificateKeyPropertyList;\
    Arg.PropertyList = IBM_AssociatedCertificatePropertyList;\
    Arg.propertyNo = sizeof(IBM_AssociatedCertificatePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssociatedCertificateKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_AssociatedCertificate_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AssociatedCertificate_InstAgent_Destroy;\
    Arg.AssocTable = (sAssoClassTable *)(&(G_sLenovo_AssociatedCertificateAssoTable[0]));\
    Arg.AssocTableSize = G_u32Lenovo_AssociatedCertificateAssoTableSize;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssociatedCertificate;\
    Arg.GetKeyProperty = IBM_AssociatedCertificate_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AssociatedCertificate_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AssociatedCertificate_GetProperty;\
    Arg.KeyPropertyList = IBM_AssociatedCertificateKeyPropertyList;\
    Arg.PropertyList = IBM_AssociatedCertificatePropertyList;\
    Arg.propertyNo = sizeof(IBM_AssociatedCertificatePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssociatedCertificateKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = (sAssoClassTable *)(&(G_sLenovo_AssociatedCertificateAssoTable[0]));\
    Arg.AssocTableSize = G_u32Lenovo_AssociatedCertificateAssoTableSize;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_ASSOCIATEDCERTIFICATE_INIT_SUPPORT /* You can turn on this flag in IBM_AssociatedCertificateAgent.h */
#define PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssociatedCertificate;\
    Arg.GetKeyProperty = IBM_AssociatedCertificate_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AssociatedCertificate_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AssociatedCertificate_GetProperty;\
    Arg.KeyPropertyList = IBM_AssociatedCertificateKeyPropertyList;\
    Arg.PropertyList = IBM_AssociatedCertificatePropertyList;\
    Arg.propertyNo = sizeof(IBM_AssociatedCertificatePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssociatedCertificateKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_AssociatedCertificate_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AssociatedCertificate_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssociatedCertificate;\
    Arg.GetKeyProperty = IBM_AssociatedCertificate_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AssociatedCertificate_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AssociatedCertificate_GetProperty;\
    Arg.KeyPropertyList = IBM_AssociatedCertificateKeyPropertyList;\
    Arg.PropertyList = IBM_AssociatedCertificatePropertyList;\
    Arg.propertyNo = sizeof(IBM_AssociatedCertificatePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssociatedCertificateKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_AssociatedCertificate_GetProperty( 
                                                CMPICount nInstIndex,
                                                CMPICount nPropIndex,
                                                void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_AssociatedCertificate_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_AssociatedCertificate_GetKeyProperty( 
                                                   CMPICount nInstIndex,
                                                   CMPICount nKeyIndex,
                                                   void *pAgentDataPtr)
{
    CMPIData data = {CMPI_string};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    switch (nKeyIndex)
    {
        case 0: /* Antecedent */
            pValue = IBM_AssociatedCertificate_InstAgent_GetProperty(nInstIndex, nKeyIndex | IBM_ASSOCIATEDCERTIFICATE_KEYPROPERTY, &u32Type, pAgentDataPtr);

            if (pValue)
            {
                if (AGENT_CMPI_OBJECTPATH == u32Type)
                {
                    data.value.ref = (CMPIObjectPath *) pValue;
                    data.type = CMPI_ref;
                    data.state = CMPI_goodValue;
                }
                else
                {
                    data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
                    CIMClassUtil_FreePtr(pValue, u32Type);
                }
            }
            break;

        case 1: /* Dependent */
            pValue = IBM_AssociatedCertificate_InstAgent_GetProperty(nInstIndex, nKeyIndex | IBM_ASSOCIATEDCERTIFICATE_KEYPROPERTY, &u32Type, pAgentDataPtr);

            if (pValue)
            {
                if (AGENT_CMPI_OBJECTPATH == u32Type)
                {
                    data.value.ref = (CMPIObjectPath *) pValue;
                    data.type = CMPI_ref;
                    data.state = CMPI_goodValue;
                }
                else
                {
                    data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
                    CIMClassUtil_FreePtr(pValue, u32Type);
                }
            }
            break;
        default:
            break;
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_AssociatedCertificate_GenerateObjectPath( 
                                                              char **properties,
                                                              CMPICount InstIndex,
                                                              void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_AssociatedCertificate_GetInstance( 
                                                  CMPIInstanceMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_AssociatedCertificate_EnumInstances( 
#else
CMPIStatus IBM_AssociatedCertificate_EnumerateInstances( 
#endif
                                                         CMPIInstanceMI *mi,
                                                         const CMPIContext *ctx,
                                                         const CMPIResult *rslt,
                                                         const CMPIObjectPath *op,
                                                         const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_AssociatedCertificate_EnumInstanceNames( 
#else
CMPIStatus IBM_AssociatedCertificate_EnumerateInstanceNames( 
#endif
                                                             CMPIInstanceMI *mi,
                                                             const CMPIContext *ctx,
                                                             const CMPIResult *rslt,
                                                             const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifdef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_AssociatedCertificate_Associators( 
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
    PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_AssociatedCertificate_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_AssociatedCertificate_References( 
                                                 CMPIAssociationMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char *resultClass,
                                                 const char *role,
                                                 const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_AssociatedCertificate_ReferenceNames( 
                                                     CMPIAssociationMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op,
                                                     const char *resultClass,
                                                     const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* IBM_AssociatedCertificate Class Service Function */
CMPIStatus Lenovo_AssociatedCertificateService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_AssociatedCertificate,
                                     CIM_DependencyService);
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
            rc = IBM_AssociatedCertificate_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_AssociatedCertificate_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_AssociatedCertificate_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_ASSOCIATEDCERTIFICATE_INIT_SUPPORT
            rc.msg = (void*) &IBM_AssociatedCertificate_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_ASSOCIATEDCERTIFICATE_INIT_SUPPORT
            rc.msg = (void*) &IBM_AssociatedCertificate_InstAgent_Destroy;
        #else
            rc.msg = NULL;
        #endif
            break;

        default:
            rc = CIMClassUtil_DefaultFunction(mi, ctx, rslt, op);
            break;
    }

    return (rc);
}

#ifdef _BROKER_SFCB
/* Not Support function */
GenNotSupportInstanceMICreateInstance(IBM_AssociatedCertificate);
GenNotSupportInstanceMIModifyInstance(IBM_AssociatedCertificate);
GenNotSupportInstanceMIDeleteInstance(IBM_AssociatedCertificate);
GenNotSupportInstanceMIExecQuery(IBM_AssociatedCertificate);
GenNotSupportInstanceMICleanup(IBM_AssociatedCertificate);

GenNotSupportAssociationMICleanup(IBM_AssociatedCertificate);

/* MI factory function */
CMInstanceMIStub( IBM_AssociatedCertificate_,
                  Lenovo_AssociatedCertificate_,
                  TheBroker,
                  CMNoHook);

CMAssociationMIStub( IBM_AssociatedCertificate_,
                     Lenovo_AssociatedCertificate_,
                     TheBroker,
                     CMNoHook);

#endif

#else
#if IBM_ASSOCIATEDCERTIFICATE_INIT_SUPPORT /* You can turn on this flag in IBM_AssociatedCertificateAgent.h */
#define PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_AssociatedCertificate_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssociatedCertificate;\
    Arg.GetNextInstIndex = IBM_AssociatedCertificate_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_AssociatedCertificateKeyPropertyList;\
    Arg.PropertyList = IBM_AssociatedCertificatePropertyList;\
    Arg.propertyNo = sizeof(IBM_AssociatedCertificatePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssociatedCertificateKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_AssociatedCertificate_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AssociatedCertificate_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_AssociatedCertificate_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AssociatedCertificate;\
    Arg.GetNextInstIndex = IBM_AssociatedCertificate_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_AssociatedCertificateKeyPropertyList;\
    Arg.PropertyList = IBM_AssociatedCertificatePropertyList;\
    Arg.propertyNo = sizeof(IBM_AssociatedCertificatePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AssociatedCertificateKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_AssociatedCertificate Class Service Function */
CMPIStatus Lenovo_AssociatedCertificateService( 
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

/* Gets the Arg of Class IBM_AssociatedCertificate Function */
sClassUtilArg IBM_AssociatedCertificate_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_ASSOCIATEDCERTIFICATE_ARG( Arg );

    return (Arg);
}

#endif
