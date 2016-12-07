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

#ifndef _BROKER_SFCB
#include "MethodNames.h"
#endif
/* Include class header files */
#include <RegisterClass.h>

/* Include agent header files */
#include <RegisterClassAgent.h>

#include "../AssociationTable.h"
#include "../instAgent/incEX/IBM_ActivationKeyManagementServiceAgent.h"


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_ActivationKey class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_ActivationKey = (CMPIUint8 *)CLASSNAMETEXT_IBM_ActivationKey;

/* Property List */
static const char * const IBM_ActivationKeyPropertyList[] = 
{
    PROPERTYNAME_ActivationKeyDescription,
    PROPERTYNAME_ActivationKeyIdentifier,
    PROPERTYNAME_ActivationKeyIdentifierType,
    PROPERTYNAME_ActivationKeyStatus,
    PROPERTYNAME_ActivationKeyUseCount,
    PROPERTYNAME_ActivationKeyUseLimit,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_Expires,
    PROPERTYNAME_FeatureDescriptionType
};

/* Key property List */
static const char * const IBM_ActivationKeyKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_ACTIVATIONKEY_INIT_SUPPORT /* You can turn on this flag in IBM_ActivationKeyAgent.h */
#define PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ActivationKey;\
    Arg.GetKeyProperty = IBM_ActivationKey_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ActivationKey_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ActivationKey_GetProperty;\
    Arg.KeyPropertyList = IBM_ActivationKeyKeyPropertyList;\
    Arg.PropertyList = IBM_ActivationKeyPropertyList;\
    Arg.propertyNo = sizeof(IBM_ActivationKeyPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ActivationKeyKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ACTIVATIONKEYASSONUM;\
    Arg.AssocArray = G_sLenovo_ActivationKeyAssociations;\
    Arg.AgentInit = IBM_ActivationKey_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ActivationKey_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ActivationKey;\
    Arg.GetKeyProperty = IBM_ActivationKey_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ActivationKey_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ActivationKey_GetProperty;\
    Arg.KeyPropertyList = IBM_ActivationKeyKeyPropertyList;\
    Arg.PropertyList = IBM_ActivationKeyPropertyList;\
    Arg.propertyNo = sizeof(IBM_ActivationKeyPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ActivationKeyKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ACTIVATIONKEYASSONUM;\
    Arg.AssocArray = G_sLenovo_ActivationKeyAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_ACTIVATIONKEY_INIT_SUPPORT /* You can turn on this flag in IBM_ActivationKeyAgent.h */
#define PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ActivationKey;\
    Arg.GetKeyProperty = IBM_ActivationKey_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ActivationKey_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ActivationKey_GetProperty;\
    Arg.KeyPropertyList = IBM_ActivationKeyKeyPropertyList;\
    Arg.PropertyList = IBM_ActivationKeyPropertyList;\
    Arg.propertyNo = sizeof(IBM_ActivationKeyPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ActivationKeyKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ACTIVATIONKEYASSONUM;\
    Arg.AssocArray = G_sLenovo_ActivationKeyAssociations;\
    Arg.AgentInit = IBM_ActivationKey_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ActivationKey_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ActivationKey;\
    Arg.GetKeyProperty = IBM_ActivationKey_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ActivationKey_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ActivationKey_GetProperty;\
    Arg.KeyPropertyList = IBM_ActivationKeyKeyPropertyList;\
    Arg.PropertyList = IBM_ActivationKeyPropertyList;\
    Arg.propertyNo = sizeof(IBM_ActivationKeyPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ActivationKeyKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ACTIVATIONKEYASSONUM;\
    Arg.AssocArray = G_sLenovo_ActivationKeyAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_ActivationKey_GetProperty( 
                                        CMPICount nInstIndex,
                                        CMPICount nPropIndex,
                                        void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_ActivationKey_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_ActivationKey_GetKeyProperty( 
                                           CMPICount nInstIndex,
                                           CMPICount nKeyIndex,
                                           void *pAgentDataPtr)
{
    CMPIData data;
        data.state = CMPI_badValue;
    data = IBM_ActivationKey_GetProperty(nInstIndex, nKeyIndex | IBM_ACTIVATIONKEY_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_ActivationKey_GenerateObjectPath( 
                                                      char **properties,
                                                      CMPICount InstIndex,
                                                      void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_ActivationKey_GetInstance( 
                                          CMPIInstanceMI *mi,
                                          const CMPIContext *ctx,
                                          const CMPIResult *rslt,
                                          const CMPIObjectPath *op,
                                          const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ActivationKey_EnumInstances( 
#else
CMPIStatus IBM_ActivationKey_EnumerateInstances( 
#endif
                                                 CMPIInstanceMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ActivationKey_EnumInstanceNames( 
#else
CMPIStatus IBM_ActivationKey_EnumerateInstanceNames( 
#endif
                                                     CMPIInstanceMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_ActivationKey_Associators( 
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
    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_ActivationKey_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_ActivationKey_References( 
                                         CMPIAssociationMI *mi,
                                         const CMPIContext *ctx,
                                         const CMPIResult *rslt,
                                         const CMPIObjectPath *op,
                                         const char *resultClass,
                                         const char *role,
                                         const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_ActivationKey_ReferenceNames( 
                                             CMPIAssociationMI *mi,
                                             const CMPIContext *ctx,
                                             const CMPIResult *rslt,
                                             const CMPIObjectPath *op,
                                             const char *resultClass,
                                             const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_ActivationKey_ModifyInstance(
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
    CMPIData dataReq;
    CMPIArray *arr = NULL;
    UINT32 u32FDType = 0;
    UINT32 u32UseCount = 0;
    UINT8 au8TmpBuf[17] = {0};

    UINT8 au8ActivationKeyID[8] = {0};
    int i = 0;

    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);

#if IBM_ACTIVATIONKEY_INIT_SUPPORT
    pAgentDataPtr = Arg.AgentInit(0);
#endif

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_ActivationKeyPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }
    
    /* get Activation Key Identifier */
    dataReq = inst->ft->getProperty(inst, PROPERTYNAME_ActivationKeyIdentifier,&rc);
    if (dataReq.state != CMPI_goodValue || dataReq.type != CMPI_stringA)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }
    arr = dataReq.value.array;
    dataReq = arr->ft->getElementAt(arr, 0, &rc);
    memset(au8TmpBuf, 0, sizeof(au8TmpBuf));
    strncpy((char *)au8TmpBuf, dataReq.value.string->ft->getCharPtr(dataReq.value.string, &rc), sizeof(au8TmpBuf) - 1);
    if (rc.rc != CMPI_RC_OK)
    {
        goto CLEAN;
    }
    for (i = 0; i < 8; i++)
    {
        UINT8 au8tmpBuf2[3] = {0};
        snprintf((char *)au8tmpBuf2, sizeof(au8tmpBuf2), "%c%c", (char)au8TmpBuf[i*2], (char)au8TmpBuf[i*2+1]);
        au8ActivationKeyID[i] = strtol((char *)au8tmpBuf2, NULL, 16);
    }
    dataReq.value.string->ft->release(dataReq.value.string);
    arr->ft->release(arr);
    
    /* get Feature Descriptor type */
    dataReq = inst->ft->getProperty(inst, PROPERTYNAME_FeatureDescriptionType,&rc);
    if (dataReq.state != CMPI_goodValue || dataReq.type != CMPI_uint32)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; 
        goto CLEAN;
    }
    u32FDType = dataReq.value.uint32;

    /* get new Use Count */
    dataReq = inst->ft->getProperty(inst, PROPERTYNAME_ActivationKeyUseCount,&rc);
    if (dataReq.state != CMPI_goodValue || dataReq.type != CMPI_uint32 || rc.rc != CMPI_RC_OK)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; 
        goto CLEAN;
    }
    u32UseCount = dataReq.value.uint32;

    /* If the input is 0, increment by 1 */
    /*if (u32UseCount == 0)
    {
        u32UseCount = 1; // If the use count = 0, the count kept by the IMM is incremented by 1
    }*/
    
    /* Set Activation Use Count */
    if (IBM_ActivationKeyManagementService_InstAgent_SetActivationKeyCount(u32FDType, au8ActivationKeyID, u32UseCount) != FOD_OK)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;
    }
    /*if (IBM_ActivationKeyManagementService_InstAgent_GetActivationKeyConstraints(u32FDType, au8ActivationKeyID, &sKeyInfo) != FOD_OK)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;
    }
    u32UseCount = sKeyInfo.u32ActivationKeyUseCount;*/

CLEAN:
    /* free resource here if neccesary */

#if IBM_ACTIVATIONKEY_INIT_SUPPORT
    Arg.AgentDestroy(pAgentDataPtr);
#endif

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

CMPIStatus IBM_ActivationKey_DeleteInstance(
                                            CMPIInstanceMI *mi,
                                            const CMPIContext *ctx,
                                            const CMPIResult *rslt,
                                            const CMPIObjectPath *op
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
    CMPIData dataReq;
    CMPIString *dataStr;
    char *szName;
    UINT8 au8TmpBuf[16] = {};
    UINT8 au8ActivationKeyID[8] = {};
    int i;
    char au8UserName[MAX_STR_LEN] = {0};

    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg);

#if IBM_ACTIVATIONKEY_INIT_SUPPORT
    pAgentDataPtr = Arg.AgentInit(0);
#endif

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    dataReq = op->ft->getKey(op, PROPERTYNAME_InstanceID, &rc);
    if (dataReq.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY; */
        goto CLEAN;
    }   
    
    dataStr = CMPIData2String(&dataReq);   
    if(dataStr == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto CLEAN;
    }       
    
    /* Get Instance ID, which is the Activation Key ID */
    szName = (char *) dataStr->ft->getCharPtr(dataStr, &rc);

    for (i = 0; i < 8; i++)
    {
        snprintf((char *)au8TmpBuf, sizeof(au8TmpBuf), "%c%c", szName[i*2], szName[i*2+1]);
        au8ActivationKeyID[i] = strtol((char *)au8TmpBuf, NULL, 16);
    }    
    
    CMPIGetUserNameFromContext(ctx, au8UserName);
    if (IBM_ActivationKeyManagementService_InstAgent_DeleteActivationKey(au8ActivationKeyID, au8UserName) != FOD_OK)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;
    }

CLEAN:
    /* free resource here if neccesary */
    
#if IBM_ACTIVATIONKEY_INIT_SUPPORT
    Arg.AgentDestroy(pAgentDataPtr);
#endif

    return (rc);
}


/* IBM_ActivationKey Class Service Function */
CMPIStatus Lenovo_ActivationKeyService( 
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
    char **properties;
    char *asscClass;
    char *resultClass;
    char *role;
    char *resultRole;
    CMPIInstance *inst = NULL;
#endif

    if (actionID == CLASS_SERVICE_ISA_LITE)
    {
        va_start(argptr, op);
        className = va_arg(argptr, char *);
        va_end(argptr);
    }

    rc = CIMClassUtil_CheckClassName(actionID, mi, ctx, rslt, op, 
                                     className,
                                     (char *) CLASSNAME_Lenovo_IBM_ActivationKey,
                                     CIM_CredentialService);
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
            rc = IBM_ActivationKey_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_ActivationKey_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_ActivationKey_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_ACTIVATIONKEY_INIT_SUPPORT
            rc.msg = (void*) &IBM_ActivationKey_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_ACTIVATIONKEY_INIT_SUPPORT
            rc.msg = (void*) &IBM_ActivationKey_InstAgent_Destroy;
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
            rc = IBM_ActivationKey_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_ActivationKey_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ActivationKey_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ActivationKey_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_ActivationKey_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_ActivationKey_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_ActivationKey_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_ActivationKey_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_DELETEINSTANCE: 
            /* delete instance service */
            rc = IBM_ActivationKey_DeleteInstance((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
             /* involk method service */
        case CLASS_SERVICE_GETMETHODNAMES:
             /* get method name service */
        case CLASS_SERVICE_GETPARAMETERS:
             /* get method param name service */
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
GenNotSupportInstanceMICreateInstance(IBM_ActivationKey);
// GenNotSupportInstanceMIModifyInstance(IBM_ActivationKey);
// GenNotSupportInstanceMIDeleteInstance(IBM_ActivationKey);
GenNotSupportInstanceMIExecQuery(IBM_ActivationKey);
GenNotSupportInstanceMICleanup(IBM_ActivationKey);

/* MI factory function */
CMInstanceMIStub( IBM_ActivationKey_,
                  Lenovo_ActivationKey_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_ACTIVATIONKEY_INIT_SUPPORT /* You can turn on this flag in IBM_ActivationKeyAgent.h */
#define PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ActivationKey_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ActivationKey;\
    Arg.GetNextInstIndex = IBM_ActivationKey_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ActivationKeyKeyPropertyList;\
    Arg.PropertyList = IBM_ActivationKeyPropertyList;\
    Arg.propertyNo = sizeof(IBM_ActivationKeyPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ActivationKeyKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_ActivationKey_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ActivationKey_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ActivationKey_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ActivationKey;\
    Arg.GetNextInstIndex = IBM_ActivationKey_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ActivationKeyKeyPropertyList;\
    Arg.PropertyList = IBM_ActivationKeyPropertyList;\
    Arg.propertyNo = sizeof(IBM_ActivationKeyPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ActivationKeyKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_ActivationKey Class Service Function */
CMPIStatus Lenovo_ActivationKeyService( 
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

/* Gets the Arg of Class IBM_ActivationKey Function */
sClassUtilArg IBM_ActivationKey_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_ACTIVATIONKEY_ARG( Arg );

    return (Arg);
}

#endif
