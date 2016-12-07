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
#include <emerson/pm/pm_lib.h>
#include "LogUtil.h"
#include <emerson/pm/security_level_lib.h>

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_CertificateManager class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_CertificateManager = (CMPIUint8 *)CLASSNAMETEXT_IBM_CertificateManager;

/* Property List */
static const char * const IBM_CertificateManagerPropertyList[] = 
{
    PROPERTYNAME_CryptographyMode,
    PROPERTYNAME_CryptographyModesExceptions,
    PROPERTYNAME_ExceptionsEnabled,
    PROPERTYNAME_MinTLSLevel,
    PROPERTYNAME_NoncompliantServices,
    PROPERTYNAME_SupportedCryptographyModes
};

/* Key property List */
static const char * const IBM_CertificateManagerKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_CERTIFICATEMANAGER_INIT_SUPPORT /* You can turn on this flag in IBM_CertificateManagerAgent.h */
#define PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_CertificateManager;\
    Arg.GetKeyProperty = IBM_CertificateManager_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_CertificateManager_InstAgent_GetNext;\
    Arg.GetProperty = IBM_CertificateManager_GetProperty;\
    Arg.KeyPropertyList = IBM_CertificateManagerKeyPropertyList;\
    Arg.PropertyList = IBM_CertificateManagerPropertyList;\
    Arg.propertyNo = sizeof(IBM_CertificateManagerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_CertificateManagerKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_CERTIFICATEMANAGERASSONUM;\
    Arg.AssocArray = G_sLenovo_CertificateManagerAssociations;\
    Arg.AgentInit = IBM_CertificateManager_InstAgent_Init;\
    Arg.AgentDestroy = IBM_CertificateManager_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_CertificateManager;\
    Arg.GetKeyProperty = IBM_CertificateManager_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_CertificateManager_InstAgent_GetNext;\
    Arg.GetProperty = IBM_CertificateManager_GetProperty;\
    Arg.KeyPropertyList = IBM_CertificateManagerKeyPropertyList;\
    Arg.PropertyList = IBM_CertificateManagerPropertyList;\
    Arg.propertyNo = sizeof(IBM_CertificateManagerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_CertificateManagerKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_CERTIFICATEMANAGERASSONUM;\
    Arg.AssocArray = G_sLenovo_CertificateManagerAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_CERTIFICATEMANAGER_INIT_SUPPORT /* You can turn on this flag in IBM_CertificateManagerAgent.h */
#define PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_CertificateManager;\
    Arg.GetKeyProperty = IBM_CertificateManager_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_CertificateManager_InstAgent_GetNext;\
    Arg.GetProperty = IBM_CertificateManager_GetProperty;\
    Arg.KeyPropertyList = IBM_CertificateManagerKeyPropertyList;\
    Arg.PropertyList = IBM_CertificateManagerPropertyList;\
    Arg.propertyNo = sizeof(IBM_CertificateManagerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_CertificateManagerKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_CERTIFICATEMANAGERASSONUM;\
    Arg.AssocArray = G_sLenovo_CertificateManagerAssociations;\
    Arg.AgentInit = IBM_CertificateManager_InstAgent_Init;\
    Arg.AgentDestroy = IBM_CertificateManager_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_CertificateManager;\
    Arg.GetKeyProperty = IBM_CertificateManager_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_CertificateManager_InstAgent_GetNext;\
    Arg.GetProperty = IBM_CertificateManager_GetProperty;\
    Arg.KeyPropertyList = IBM_CertificateManagerKeyPropertyList;\
    Arg.PropertyList = IBM_CertificateManagerPropertyList;\
    Arg.propertyNo = sizeof(IBM_CertificateManagerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_CertificateManagerKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_CERTIFICATEMANAGERASSONUM;\
    Arg.AssocArray = G_sLenovo_CertificateManagerAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_CertificateManager_GetProperty( 
                                             CMPICount nInstIndex,
                                             CMPICount nPropIndex,
                                             void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_CertificateManager_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_CertificateManager_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_CertificateManager, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_CertificateManager, &rc);
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
        data = IBM_CertificateManager_GetProperty(nInstIndex, nKeyIndex | IBM_CERTIFICATEMANAGER_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_CertificateManager_GenerateObjectPath( 
                                                           char **properties,
                                                           CMPICount InstIndex,
                                                           void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_CertificateManager_GetInstance( 
                                               CMPIInstanceMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_CertificateManager_EnumInstances( 
#else
CMPIStatus IBM_CertificateManager_EnumerateInstances( 
#endif
                                                      CMPIInstanceMI *mi,
                                                      const CMPIContext *ctx,
                                                      const CMPIResult *rslt,
                                                      const CMPIObjectPath *op,
                                                      const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_CertificateManager_EnumInstanceNames( 
#else
CMPIStatus IBM_CertificateManager_EnumerateInstanceNames( 
#endif
                                                          CMPIInstanceMI *mi,
                                                          const CMPIContext *ctx,
                                                          const CMPIResult *rslt,
                                                          const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_CertificateManager_Associators( 
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
    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_CertificateManager_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_CertificateManager_References( 
                                              CMPIAssociationMI *mi,
                                              const CMPIContext *ctx,
                                              const CMPIResult *rslt,
                                              const CMPIObjectPath *op,
                                              const char *resultClass,
                                              const char *role,
                                              const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_CertificateManager_ReferenceNames( 
                                                  CMPIAssociationMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char *resultClass,
                                                  const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_CertificateManager_ModifyInstance(
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
    UINT16 mode = 0;
    UINT16 ver = 0;
    unsigned int uiSize = MAXEXCEPTIONS;
    BOOLEAN **bArray = NULL;
    SecurityLevelInfo *psSecurityLevelInfo = NULL;
    SECLV_SERVICE_e service = SECLV_SERVICE_SNMP;
    SECLV_RTCODE_e ReturnNo = SECLV_RTCODE_SUCCESS;
    SECLV_SETLV_DATA_s setData = {0, 0};
    SECLV_SET_TLSVER_DATA_s tls_level;
    BOOLEAN bIsModeChanged = FALSE;
    BOOLEAN bIsExceptionsChanged = FALSE;
    BOOLEAN bIsLevelChanged = FALSE;
    char *szEnv = NULL;

    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);

    pAgentDataPtr = IBM_CertificateManager_InstAgent_Init(0);
    if (!pAgentDataPtr)
    {
        return (rc);
    }
    psSecurityLevelInfo = (SecurityLevelInfo *) pAgentDataPtr;

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_CertificateManagerPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    /* not allowed to run on ITEBLADE */
    szEnv = getenv("IMM_FAMILY");
    if (szEnv)
    {
        if (!strcmp(szEnv, "iteblade"))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- The CryptographyMode and ExceptionsEnabled should be preset by the CMM to comply with security policies on Flex ITE platform.", __FUNCTION__);
            rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
            goto CLEAN;
        }
    }
    else
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to call getenv(IMM_FAMILY).", __FUNCTION__);
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;
    }
     
    /* check static property values if neccessary */
    /* Get Property CryptographyMode (user input)*/
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_CryptographyMode, CMPI_uint16, &mode, NULL, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s), error code is %d.", __FUNCTION__, PROPERTYNAME_CryptographyMode, rc.rc);
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (mode > 1)
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto CLEAN;
        }
        else if (mode != psSecurityLevelInfo->CryptographyMode)
        {
            bIsModeChanged = TRUE;
        }
    }
    else
    {
        mode = psSecurityLevelInfo->CryptographyMode;
    }
    
    /* Get Property ExceptionsEnabled (user input) */
    bArray = (BOOLEAN **) CIMClassUtil_GeneratePopertyValueArray(sizeof(BOOLEAN), uiSize, __FUNCTION__);
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_ExceptionsEnabled, CMPI_booleanA, bArray, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s), error code is %d.", __FUNCTION__, PROPERTYNAME_ExceptionsEnabled, rc.rc);
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (uiSize != 1)
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto CLEAN;
        }
        else if (((49 == psSecurityLevelInfo->ExceptionsEnable[0]) && (0 == *bArray[0])) ||
                 ((48 == psSecurityLevelInfo->ExceptionsEnable[0]) && (1 == *bArray[0])))
        {

            bIsExceptionsChanged = TRUE;
        }

        if ((0 == mode) && ((bIsExceptionsChanged) || (!bIsModeChanged)))
        {
            rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
            goto CLEAN;
        }
    }

    /* Get Property MinTLSLevel (user input) */
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_MinTLSLevel, CMPI_uint16, &ver, NULL, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s), error code is %d.", __FUNCTION__, PROPERTYNAME_MinTLSLevel, rc.rc);
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (ver >= MAX_SECLV_TLS_V) 
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto CLEAN;
        }

        bIsLevelChanged = TRUE;
    }

    
    rc.rc = CMPI_RC_OK;
    if (bIsModeChanged)
    {
        setData.mode = mode; 
        ReturnNo = SecLv_SetLevel(&setData);
        if (ReturnNo && (ReturnNo != 2))
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SecLv_SetLevel(). Return code is %d. Certificater Invalid flag mask : %d.", __FUNCTION__, ReturnNo, setData.resFlagCertInvalid);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }  
    }
    
    if (bIsExceptionsChanged)
    {
        ReturnNo = SecLv_SetException(service, (int32_t) *bArray[0]);
        if (ReturnNo)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SecLv_SetException(). Return code is %d.", __FUNCTION__, ReturnNo);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }
    }
 
    if (bIsLevelChanged)
    {
        tls_level.ver = ver;
        ReturnNo = SecLv_SetTLSVersion(&tls_level);
        if (ReturnNo)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SecLv_SetTLSVersion(). Return code is %d.", __FUNCTION__, ReturnNo);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }  
    }

CLEAN:
    /* free resource here if neccesary */
    IBM_CertificateManager_InstAgent_Destroy(pAgentDataPtr);

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

CMPIStatus IBM_CertificateManager_InvokeMethod( 
                                                CMPIMethodMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char *method,
                                                const CMPIArgs *in,
                                                CMPIArgs *out)
{
#define METHOD_NOT_SUPPORTED        1
    CMPIValue value;
    CMPIStatus rc = 
    {
        CMPI_RC_OK,
        NULL
    };

    CMPICount nIndex = 0;
    void *pAgentDataPtr = NULL;
    sClassUtilArg Arg;
    UINT32 u32Role = 0;
    char au8UserName[MAX_STR_LEN] = {0};
    
    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg);

    pAgentDataPtr = IBM_CertificateManager_InstAgent_Init(0);

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (nIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (ctx)
    {
        CMPIGetUserNameFromContext(ctx, au8UserName);
        CMPIGetUserRoleFromContext(ctx, &u32Role);
        
        /* MTCE_REQUEST: 2 , but backend does not care this input at 2013-05-16. */
        if (!sm_imm_authorized(u32Role, SECURITY_ACTION, 2))
        {
            rc.rc = CMPI_RC_ERR_ACCESS_DENIED;
            logTraceCIM(LOG_LEV_ERROR, "%s- Failed to call sm_imm_authorized(%d, %s, 2) for %s.", __FUNCTION__, u32Role, SECURITY_ACTION, au8UserName);
        }
        else
        {
            /* invoke method */
            if (0 == strcmp(method, "CreateKeyPair"))
            {
                value.uint32 = IBM_CertificateManager_InstAgent_CreateKeyPair((UINT32) nIndex, in, out);
                CMReturnData(rslt, &value, CMPI_uint32);
				CMReturnDone(rslt);
            }
            else if (0 == strcmp(method, "CreateSharedCredential"))
            {
                value.uint32 = IBM_CertificateManager_InstAgent_CreateSharedCredential((UINT32) nIndex, in, out);
                CMReturnData(rslt, &value, CMPI_uint32);
				CMReturnDone(rslt);
            }   
            else if (0 == strcmp(method, "GenerateCertificate"))
            {
                value.uint32 = IBM_CertificateManager_InstAgent_GenerateCertificate((UINT32) nIndex, in, out, au8UserName);
                CMReturnData(rslt, &value, CMPI_uint32);
				CMReturnDone(rslt);
            }
            else if (0 == strcmp(method, "GenerateCSR"))
            {
                value.uint32 = IBM_CertificateManager_InstAgent_GenerateCSR((UINT32) nIndex, in, out, au8UserName);
                CMReturnData(rslt, &value, CMPI_uint32);
				CMReturnDone(rslt);
            }
            else if (0 == strcmp(method, "ImportCertificate"))
            {
                //logTraceCIM(LOG_LEV_DEBUG, "%s()- import cert bypass policy.", __FUNCTION__);
                value.uint32 = IBM_CertificateManager_InstAgent_ImportCertificate((UINT32) nIndex, in, out, au8UserName);
                CMReturnData(rslt, &value, CMPI_uint32);
				CMReturnDone(rslt);
            }
            else if (0 == strcmp(method, "RemoveCertificate"))
            {
                value.uint32 = IBM_CertificateManager_InstAgent_RemoveCertificate((UINT32) nIndex, in, out, au8UserName);
                CMReturnData(rslt, &value, CMPI_uint32);
				CMReturnDone(rslt);
            }
            else
            {
                rc.rc = CMPI_RC_ERR_METHOD_NOT_FOUND;
            }
        }
    }
    else
    {
        logTraceCIM(LOG_LEV_ERROR, "%s- ctx is NULL.", __FUNCTION__);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
    }

CLEAN:

    IBM_CertificateManager_InstAgent_Destroy(pAgentDataPtr);

    return (rc);
#undef  METHOD_NOT_SUPPORTED        
}

#ifndef _BROKER_SFCB
CMPIData *IBM_CertificateManager_GetMethodName()
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
    nameArray = (void*) TheBroker.eft->newArray(&TheBroker, 6, CMPI_chars, &status);

    if(!nameArray)
    {
        return (NULL);
    }

    /* add method name */
    value.chars = (char *) METHODNAME_CreateKeyPair;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_CreateSharedCredential;
    nameArray->ft->setElementAt(nameArray, 1, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_GenerateCertificate;
    nameArray->ft->setElementAt(nameArray, 2, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_GenerateCSR;
    nameArray->ft->setElementAt(nameArray, 3, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_ImportCertificate;
    nameArray->ft->setElementAt(nameArray, 4, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_RemoveCertificate;
    nameArray->ft->setElementAt(nameArray, 5, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

#endif

#ifndef _BROKER_SFCB
CMPIData *IBM_CertificateManager_GetMethodParameters(const char * MethodName)
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

    if (0 == strcmp(MethodName, METHODNAME_CreateKeyPair))
    {
        iMethID = 0;
    }
    else if (0 == strcmp(MethodName, METHODNAME_CreateSharedCredential))
    {
        iMethID = 1;
    }
    else if (0 == strcmp(MethodName, METHODNAME_GenerateCertificate))
    {
        iMethID = 2;
    }
    else if (0 == strcmp(MethodName, METHODNAME_GenerateCSR))
    {
        iMethID = 3;
    }
    else if (0 == strcmp(MethodName, METHODNAME_ImportCertificate))
    {
        iMethID = 4;
    }
    else if (0 == strcmp(MethodName, METHODNAME_RemoveCertificate))
    {
        iMethID = 5;
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
            value.chars = "ref CIM_EnabledLogicalElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_target,&value,CMPI_chars);
            break;

        case 1:
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Algorithm,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Protocol,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_RemoteID,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Secret,&value,CMPI_chars);
            value.chars = "ref CIM_EnabledLogicalElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_target,&value,CMPI_chars);
            break;

        case 2:
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_CountryName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_StateOrProvinceName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_LocalityName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_OrganizationName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_HostName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ContactPerson,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_EmailAddress,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_OrganizationalUnitName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Surname,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_GivenName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Initials,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_DnQualifier,&value,CMPI_chars);
            value.chars = "ref CIM_EnabledLogicalElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Target,&value,CMPI_chars);
            break;

        case 3:
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_CountryName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_StateOrProvinceName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_LocalityName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_OrganizationName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_HostName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ContactPerson,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_EmailAddress,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_OrganizationalUnitName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Surname,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_GivenName,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Initials,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_DnQualifier,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ChallengePassword,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_UnstructuredName,&value,CMPI_chars);
            value.chars = "ref CIM_EnabledLogicalElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Target,&value,CMPI_chars);
            break;

        case 4:
            value.chars = "ref CIM_EnabledLogicalElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_target,&value,CMPI_chars);
            value.chars = "A uint8";
            pArgs->ft->addArg(pArgs, PARAMNAME_signedCertificate,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_uint8;
            pArgs->ft->addArg(pArgs, PARAMNAME_type,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_uint8;
            pArgs->ft->addArg(pArgs, PARAMNAME_index,&value,CMPI_chars);
            break;

        case 5:
            value.chars = "ref CIM_PublicKeyCertificate";
            pArgs->ft->addArg(pArgs, PARAMNAME_Certificate,&value,CMPI_chars);
            break;

    }

    data->value.args = pArgs;
    data->type = CMPI_args;
    data->state = CMPI_goodValue;
    return (data);
}
#endif

/* IBM_CertificateManager Class Service Function */
CMPIStatus Lenovo_CertificateManagerService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_CertificateManager,
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
            rc = IBM_CertificateManager_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_CertificateManager_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_CertificateManager_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_CERTIFICATEMANAGER_INIT_SUPPORT
            rc.msg = (void*) &IBM_CertificateManager_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_CERTIFICATEMANAGER_INIT_SUPPORT
            rc.msg = (void*) &IBM_CertificateManager_InstAgent_Destroy;
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
            rc = IBM_CertificateManager_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_CertificateManager_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_CertificateManager_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_CertificateManager_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_CertificateManager_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_CertificateManager_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_CertificateManager_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_CertificateManager_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_CertificateManager_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_CertificateManager_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_CertificateManager_GetMethodParameters(method);
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
GenNotSupportInstanceMICreateInstance(IBM_CertificateManager);
// GenNotSupportInstanceMIModifyInstance(IBM_CertificateManager);
GenNotSupportInstanceMIDeleteInstance(IBM_CertificateManager);
GenNotSupportInstanceMIExecQuery(IBM_CertificateManager);
GenNotSupportInstanceMICleanup(IBM_CertificateManager);

/* MI factory function */
CMInstanceMIStub( IBM_CertificateManager_,
                  Lenovo_CertificateManager_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_CertificateManager);

CMMethodMIStub( IBM_CertificateManager_,
                Lenovo_CertificateManager_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_CERTIFICATEMANAGER_INIT_SUPPORT /* You can turn on this flag in IBM_CertificateManagerAgent.h */
#define PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg) \
    Arg.AgentGetProperty = IBM_CertificateManager_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_CertificateManager;\
    Arg.GetNextInstIndex = IBM_CertificateManager_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_CertificateManagerKeyPropertyList;\
    Arg.PropertyList = IBM_CertificateManagerPropertyList;\
    Arg.propertyNo = sizeof(IBM_CertificateManagerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_CertificateManagerKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_CertificateManager_InstAgent_Init;\
    Arg.AgentDestroy = IBM_CertificateManager_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG(Arg) \
    Arg.AgentGetProperty = IBM_CertificateManager_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_CertificateManager;\
    Arg.GetNextInstIndex = IBM_CertificateManager_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_CertificateManagerKeyPropertyList;\
    Arg.PropertyList = IBM_CertificateManagerPropertyList;\
    Arg.propertyNo = sizeof(IBM_CertificateManagerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_CertificateManagerKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_CertificateManager Class Service Function */
CMPIStatus Lenovo_CertificateManagerService( 
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

/* Gets the Arg of Class IBM_CertificateManager Function */
sClassUtilArg IBM_CertificateManager_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_CERTIFICATEMANAGER_ARG( Arg );

    return (Arg);
}

#endif
