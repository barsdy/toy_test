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
#include <emerson/imm_sa/sa_cfg.h>
#include "LogUtil.h"
#include <SmashCommonUtil.h>

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_SupportCenterSettingData class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_SupportCenterSettingData = (CMPIUint8 *)CLASSNAMETEXT_IBM_SupportCenterSettingData;

/* Property List */
static const char * const IBM_SupportCenterSettingDataPropertyList[] = 
{
    PROPERTYNAME_Address,
    PROPERTYNAME_AlternateContactName,
    PROPERTYNAME_AlternateEmail,
    PROPERTYNAME_AlternatePhone,
    PROPERTYNAME_AlternatePhoneExtension,
    PROPERTYNAME_City,
    PROPERTYNAME_CompanyName,
    PROPERTYNAME_ContactName,
    PROPERTYNAME_Country,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_Email,
    PROPERTYNAME_HTTPProxyAddress,
    PROPERTYNAME_HTTPProxyAddressFormat,
    PROPERTYNAME_HTTPProxyEnabled,
    PROPERTYNAME_HTTPProxyPassword,
    PROPERTYNAME_HTTPProxyPort,
    PROPERTYNAME_HTTPProxyUserID,
    PROPERTYNAME_MachineLocationPhone,
    PROPERTYNAME_Phone,
    PROPERTYNAME_PhoneExtension,
    PROPERTYNAME_PostalCode,
    PROPERTYNAME_StateOrProvince
};

/* Key property List */
static const char * const IBM_SupportCenterSettingDataKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_SUPPORTCENTERSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_SupportCenterSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SupportCenterSettingData;\
    Arg.GetKeyProperty = IBM_SupportCenterSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SupportCenterSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SupportCenterSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_SupportCenterSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_SupportCenterSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_SupportCenterSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SupportCenterSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SUPPORTCENTERSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_SupportCenterSettingDataAssociations;\
    Arg.AgentInit = IBM_SupportCenterSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SupportCenterSettingData_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SupportCenterSettingData;\
    Arg.GetKeyProperty = IBM_SupportCenterSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SupportCenterSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SupportCenterSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_SupportCenterSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_SupportCenterSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_SupportCenterSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SupportCenterSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SUPPORTCENTERSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_SupportCenterSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_SUPPORTCENTERSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_SupportCenterSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SupportCenterSettingData;\
    Arg.GetKeyProperty = IBM_SupportCenterSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SupportCenterSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SupportCenterSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_SupportCenterSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_SupportCenterSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_SupportCenterSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SupportCenterSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SUPPORTCENTERSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_SupportCenterSettingDataAssociations;\
    Arg.AgentInit = IBM_SupportCenterSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SupportCenterSettingData_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SupportCenterSettingData;\
    Arg.GetKeyProperty = IBM_SupportCenterSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SupportCenterSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SupportCenterSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_SupportCenterSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_SupportCenterSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_SupportCenterSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SupportCenterSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SUPPORTCENTERSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_SupportCenterSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_SupportCenterSettingData_GetProperty( 
                                                   CMPICount nInstIndex,
                                                   CMPICount nPropIndex,
                                                   void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_SupportCenterSettingData_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_SupportCenterSettingData_GetKeyProperty( 
                                                      CMPICount nInstIndex,
                                                      CMPICount nKeyIndex,
                                                      void *pAgentDataPtr)
{
    CMPIData data = {CMPI_string, CMPI_badValue, {0}};
        data.state = CMPI_badValue;
    data = IBM_SupportCenterSettingData_GetProperty(nInstIndex, nKeyIndex | IBM_SUPPORTCENTERSETTINGDATA_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_SupportCenterSettingData_GenerateObjectPath( 
                                                                 char **properties,
                                                                 CMPICount InstIndex,
                                                                 void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_SupportCenterSettingData_GetInstance( 
                                                     CMPIInstanceMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op,
                                                     const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SupportCenterSettingData_EnumInstances( 
#else
CMPIStatus IBM_SupportCenterSettingData_EnumerateInstances( 
#endif
                                                            CMPIInstanceMI *mi,
                                                            const CMPIContext *ctx,
                                                            const CMPIResult *rslt,
                                                            const CMPIObjectPath *op,
                                                            const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SupportCenterSettingData_EnumInstanceNames( 
#else
CMPIStatus IBM_SupportCenterSettingData_EnumerateInstanceNames( 
#endif
                                                                CMPIInstanceMI *mi,
                                                                const CMPIContext *ctx,
                                                                const CMPIResult *rslt,
                                                                const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_SupportCenterSettingData_Associators( 
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
    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_SupportCenterSettingData_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_SupportCenterSettingData_References( 
                                                    CMPIAssociationMI *mi,
                                                    const CMPIContext *ctx,
                                                    const CMPIResult *rslt,
                                                    const CMPIObjectPath *op,
                                                    const char *resultClass,
                                                    const char *role,
                                                    const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_SupportCenterSettingData_ReferenceNames( 
                                                        CMPIAssociationMI *mi,
                                                        const CMPIContext *ctx,
                                                        const CMPIResult *rslt,
                                                        const CMPIObjectPath *op,
                                                        const char *resultClass,
                                                        const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_SupportCenterSettingData_ModifyInstance(
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
    pSACfgSupportCenter psOriginalData = NULL;
    UINT16 u16Value = 0;
    char szValue[321] = { 0 };
    unsigned int uiSize = 0;
    BOOLEAN bValue = FALSE;
    BOOLEAN bIsHttpProxyEnable = FALSE;
    sSACfgSupportCenter sModifiedData;
    int iResult = 0;
    char nameString[MAX_STR_LEN] = {0};
    UINT32 u32Role = 0;
    sSACfgServiceData sServiceCfg;
    
    logTraceCIM(LOG_LEV_INFO, "%s()- Function entry.", __FUNCTION__);
    if (inst == NULL)
    {
        return (rc);
    }

    /* check privilege */
    CMPIGetUserNameFromContext(ctx, nameString);
    //logTraceCIM(LOG_LEV_INFO, "%s()- nameString is %s.", __FUNCTION__, nameString);
    CMPIGetUserRoleFromContext(ctx, &u32Role);
    
    /* parameter 3 didn't use currently, pass MODIFY_REQUEST (2) */
    if (!sm_imm_authorized(u32Role, SACFG_ACTION , 2))
    {
        logTraceCIM(LOG_LEV_INFO, "%s()- User(%s) does not have modify privilege.", __FUNCTION__, nameString);
        rc.rc = CMPI_RC_ERR_ACCESS_DENIED;
        goto CLEAN;
    }

    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg);

#if IBM_SUPPORTCENTERSETTINGDATA_INIT_SUPPORT
    pAgentDataPtr = IBM_SupportCenterSettingData_InstAgent_Init(0);
#endif

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_SupportCenterSettingDataPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (pAgentDataPtr == NULL)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- The agent data is null.", __FUNCTION__);
        goto CLEAN;
    }
    else
    {
        psOriginalData = (pSACfgSupportCenter) pAgentDataPtr;
    }

    iResult = SAcfg_GetConfigServiceData(&sServiceCfg);    
    if (iResult != SA_CFG_STATUS_OK)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SAcfg_GetConfigServiceData(), return code is %d.", __FUNCTION__, iResult);
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;
    }

    iResult = SAcfg_IniConfigSupportCenter(&sModifiedData);
    if (iResult != SA_CFG_STATUS_OK)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SAcfg_IniConfigSupportCenter(), return code is %d.", __FUNCTION__, iResult);
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;
    }

    /* get parameter CompanyName */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_CompanyName, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szCompanyName) != 0)
        {
            snprintf(sModifiedData.szCompanyName, sizeof(sModifiedData.szCompanyName), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter ContactName */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_ContactName, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szContactName) != 0)
        {
            snprintf(sModifiedData.szContactName, sizeof(sModifiedData.szContactName), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY


    /* get parameter Phone */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_Phone, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szPhone) != 0)
        {
            if (((uiSize != 0) && (uiSize < 5)) || ((sServiceCfg.u32ReportMethod & 1) && (0 == uiSize)))
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Length(%d) of Property(%s) is incorrect.", __FUNCTION__, uiSize, PROPERTYNAME_Phone);
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                goto CLEAN;
            }
            else
            {
               snprintf(sModifiedData.szPhone, sizeof(sModifiedData.szPhone), "%s", szValue);
            }
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter PhoneExtension */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_PhoneExtension, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szPhoneExt) != 0)
        {
            snprintf(sModifiedData.szPhoneExt, sizeof(sModifiedData.szPhoneExt), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter Email */
    uiSize = 321;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_Email, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szEmail) != 0)
        {
            snprintf(sModifiedData.szEmail, sizeof(sModifiedData.szEmail), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter Address */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_Address, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szAddress) != 0)
        {
            snprintf(sModifiedData.szAddress, sizeof(sModifiedData.szAddress), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter City */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_City, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szCity) != 0)
        {
            snprintf(sModifiedData.szCity, sizeof(sModifiedData.szCity), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter StateOrProvince */
    uiSize = 4;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_StateOrProvince, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szState) != 0)
        {
            if (1 == uiSize)
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Length(%d) of Property(%s) is incorrect.", __FUNCTION__, uiSize, PROPERTYNAME_StateOrProvince);
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                goto CLEAN;
            }
            else
            {
                snprintf(sModifiedData.szState, sizeof(sModifiedData.szState), "%s", szValue);
            }
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter PostalCode */
    uiSize = 10;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_PostalCode, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szPostalCode) != 0)
        {
            snprintf(sModifiedData.szPostalCode, sizeof(sModifiedData.szPostalCode), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter Country */
    uiSize = 3;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_Country, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szCountryCode) != 0)
        {
            snprintf(sModifiedData.szCountryCode, sizeof(sModifiedData.szCountryCode), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter AlternateContactName */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_AlternateContactName, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szAltContactName) != 0)
        {
            snprintf(sModifiedData.szAltContactName, sizeof(sModifiedData.szAltContactName), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY


    /* get parameter AlternatePhone */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_AlternatePhone, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szAltPhone) != 0)
        {
            if ((uiSize != 0) && (uiSize < 5))
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Length(%d) of Property(%s) is incorrect.", __FUNCTION__, uiSize, PROPERTYNAME_AlternatePhone);
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                goto CLEAN;
            }
            else
            {
                snprintf(sModifiedData.szAltPhone, sizeof(sModifiedData.szAltPhone), "%s", szValue);
            }
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter AlternatePhoneExtension */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_AlternatePhoneExtension, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szAltPhoneExt) != 0)
        {
            snprintf(sModifiedData.szAltPhoneExt, sizeof(sModifiedData.szAltPhoneExt), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter AlternateEmail */
    uiSize = 321;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_AlternateEmail, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szAltEmail) != 0)
        {
            snprintf(sModifiedData.szAltEmail, sizeof(sModifiedData.szAltEmail), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter MachineLocationPhone */
    uiSize = 31;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_MachineLocationPhone, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szAltMachineLocationPhone) != 0)
        {
            if ((uiSize != 0) && (uiSize < 5))
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Length(%d) of Property(%s) is incorrect.", __FUNCTION__, uiSize, PROPERTYNAME_MachineLocationPhone);
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                goto CLEAN;
            }
            else
            {
                snprintf(sModifiedData.szAltMachineLocationPhone, sizeof(sModifiedData.szAltMachineLocationPhone), "%s", szValue);
            }
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter HTTPProxyEnabled */
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_HTTPProxyEnabled, CMPI_boolean, &bValue, NULL, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (bValue != psOriginalData->u32HttpProxyEnable)
        {
            sModifiedData.u32HttpProxyEnable = bValue;
            logTraceCIM(LOG_LEV_INFO, "%s()- bValue(%d) != psOriginalData->u32HttpProxyEnable(%d).", __FUNCTION__, bValue, psOriginalData->u32HttpProxyEnable);
        }
        bIsHttpProxyEnable = bValue;
    }
    else //CMPI_RC_ERR_NO_SUCH_PROPERTY
    {
        bIsHttpProxyEnable = psOriginalData->u32HttpProxyEnable;
    }

    if (bIsHttpProxyEnable)
    {
        /* get parameter HTTPProxyAddress */
        uiSize = 64;
        rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_HTTPProxyAddress, CMPI_string, szValue, &uiSize, __FUNCTION__);
        if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
        {
            goto CLEAN;    
        }
        else if (CMPI_RC_OK == rc.rc)
        {
            if (strcmp(szValue, psOriginalData->szHttpProxyAddress) != 0)
            {
                snprintf(sModifiedData.szHttpProxyAddress, sizeof(sModifiedData.szHttpProxyAddress), "%s", szValue);
            }
        }
        //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

        /* get parameter HTTPProxyAddressFormat */
        rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_HTTPProxyAddressFormat, CMPI_uint16, &u16Value, NULL, __FUNCTION__);
        if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
        {
            goto CLEAN;    
        }
        else if (CMPI_RC_OK == rc.rc)
        {
            if ((1 == u16Value) || (u16Value > 4))
            {
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                goto CLEAN;
            }
            else if (u16Value != psOriginalData->u32HttpProxyFormat)
            {
                sModifiedData.u32HttpProxyFormat = u16Value;
            }
                
        }
        //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

        /* get parameter HTTPProxyPort */
        rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_HTTPProxyPort, CMPI_uint16, &u16Value, NULL, __FUNCTION__);
        if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
        {
            goto CLEAN;    
        }
        else if (CMPI_RC_OK == rc.rc)
        {
            if (u16Value != psOriginalData->u32HttpProxyPort)
            {
                sModifiedData.u32HttpProxyPort = u16Value;
            }
                
        }
        //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY
        
        /* get parameter HTTPProxyUserID */
        uiSize = 31;
        rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_HTTPProxyUserID, CMPI_string, szValue, &uiSize, __FUNCTION__);
        if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
        {
            goto CLEAN;    
        }
        else if (CMPI_RC_OK == rc.rc)
        {
            if (strcmp(szValue, psOriginalData->szHttpProxyUsername) != 0)
            {
                snprintf(sModifiedData.szHttpProxyUsername, sizeof(sModifiedData.szHttpProxyUsername), "%s", szValue);
            }
        }
        //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

        /* get parameter HTTPProxyPassword */
        uiSize = 16;
        rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_HTTPProxyPassword, CMPI_string, szValue, &uiSize, __FUNCTION__);
        if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
        {
            goto CLEAN;    
        }
        else if (CMPI_RC_OK == rc.rc)
        {
            if ((strcmp(szValue, PASSWORD_DISPALY_STR) != 0) &&
                (strcmp(szValue, psOriginalData->szHttpProxyPassword) != 0))
            {
                snprintf(sModifiedData.szHttpProxyPassword, sizeof(sModifiedData.szHttpProxyPassword), "%s", szValue);
            }
        }
        //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    }

    iResult = SAcfg_SetConfigSupportCenter(&sModifiedData);
    if (SA_CFG_STATUS_OK == iResult)
    {
        rc.rc = CMPI_RC_OK;    
    }
    else if ((iResult > SA_CFG_STATUS_OK) && (iResult < SA_CFG_STATUS_INVALID_PARAM))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        logTraceCIM(LOG_LEV_INFO, "%s()- Failed to call SAcfg_SetConfigSupportCenter(), return code is %d.", __FUNCTION__, iResult);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        logTraceCIM(LOG_LEV_INFO, "%s()- Failed to call SAcfg_SetConfigSupportCenter(), return code is %d.", __FUNCTION__, iResult);
    }

CLEAN:
    /* free resource here if neccesary */
#if IBM_SUPPORTCENTERSETTINGDATA_INIT_SUPPORT
    IBM_SupportCenterSettingData_InstAgent_Destroy(pAgentDataPtr);
#endif
    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

/* IBM_SupportCenterSettingData Class Service Function */
CMPIStatus Lenovo_SupportCenterSettingDataService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_SupportCenterSettingData,
                                     CIM_SettingDataService);
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
            rc = IBM_SupportCenterSettingData_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_SupportCenterSettingData_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_SupportCenterSettingData_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_SUPPORTCENTERSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_SupportCenterSettingData_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_SUPPORTCENTERSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_SupportCenterSettingData_InstAgent_Destroy;
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
            rc = IBM_SupportCenterSettingData_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_SupportCenterSettingData_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SupportCenterSettingData_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SupportCenterSettingData_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_SupportCenterSettingData_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_SupportCenterSettingData_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_SupportCenterSettingData_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_SupportCenterSettingData_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_SupportCenterSettingData);
// GenNotSupportInstanceMIModifyInstance(IBM_SupportCenterSettingData);
GenNotSupportInstanceMIDeleteInstance(IBM_SupportCenterSettingData);
GenNotSupportInstanceMIExecQuery(IBM_SupportCenterSettingData);
GenNotSupportInstanceMICleanup(IBM_SupportCenterSettingData);

/* MI factory function */
CMInstanceMIStub( IBM_SupportCenterSettingData_,
                  Lenovo_SupportCenterSettingData_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_SUPPORTCENTERSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_SupportCenterSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SupportCenterSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SupportCenterSettingData;\
    Arg.GetNextInstIndex = IBM_SupportCenterSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SupportCenterSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_SupportCenterSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_SupportCenterSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SupportCenterSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_SupportCenterSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SupportCenterSettingData_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SupportCenterSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SupportCenterSettingData;\
    Arg.GetNextInstIndex = IBM_SupportCenterSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SupportCenterSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_SupportCenterSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_SupportCenterSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SupportCenterSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_SupportCenterSettingData Class Service Function */
CMPIStatus Lenovo_SupportCenterSettingDataService( 
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

/* Gets the Arg of Class IBM_SupportCenterSettingData Function */
sClassUtilArg IBM_SupportCenterSettingData_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_SUPPORTCENTERSETTINGDATA_ARG( Arg );

    return (Arg);
}

#endif
