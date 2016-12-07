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
#include "../instAgent/incEX/IBM_ProtocolServiceAgent.h"

#include <emerson/cemgr/swe_function_table.h>
#include <emerson/pm/pm_lib.h>
#include <netdb.h>
#include <SmashCommonUtil.h>

#include "LogUtil.h"
#include <emerson/pm/avct_valid.h>


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

#define MAX_STRING_LENGTH 512 

/* IBM_LDAPClientService class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_LDAPClientService = (CMPIUint8 *)CLASSNAMETEXT_IBM_LDAPClientService;

/* Property List */
static const char * const IBM_LDAPClientServicePropertyList[] = 
{
    PROPERTYNAME_Authorization,
    PROPERTYNAME_BindingMethod,
    PROPERTYNAME_DomainSourceMethod,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_ForestName,
    PROPERTYNAME_GroupFilters,
    PROPERTYNAME_GroupSearchAttribute,
    PROPERTYNAME_LDAPServers,
    PROPERTYNAME_LDAPServerSelectionMethod,
    PROPERTYNAME_LoginClientDN,
    PROPERTYNAME_LoginPassword,
    PROPERTYNAME_LoginPermissionAttribute,
    PROPERTYNAME_RoleBasedSecurityEnabled,
    PROPERTYNAME_RootDN,
    PROPERTYNAME_SearchDomain,
    PROPERTYNAME_SearchServiceName,
    PROPERTYNAME_ServerTargetName,
    PROPERTYNAME_SSLEnabled,
    PROPERTYNAME_UIDSearchAttribute,
    PROPERTYNAME_UserSearchBaseDN
};

/* Key property List */
static const char * const IBM_LDAPClientServiceKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

/* AIM variable List*/
static const char * const IBM_LDAPClientServiceAIMVariableList[] = 
{
    "pam_ldap_int_authentication_mode",             //  PROPERTYNAME_Authorization
    "pam_ldap_int_binding_method",                  //  PROPERTYNAME_BindingMethod
    "pam_ldap_int_dns_domain_source",               //  PROPERTYNAME_DomainSourceMethod,
    0,                                              //  PROPERTYNAME_ElementName,
    "pam_ldap_str_dns_search_forest",               //  PROPERTYNAME_ForestName
    "pam_ldap_str_group_filter",                    //  PROPERTYNAME_GroupFilters,
    "pam_ldap_str_group_search_attr",               //  PROPERTYNAME_GroupSearchAttribute,
    "pam_ldap_str_dc_",                             //  PROPERTYNAME_LDAPServers,
    "pam_ldap_bool_use_dns_to_find_servers",        //  PROPERTYNAME_LDAPServerSelectionMethod,
    "pam_ldap_str_client_id",                       //  PROPERTYNAME_LoginClientDN,
    "pam_ldap_str_client_password",                 //  PROPERTYNAME_LoginPassword,
    "pam_ldap_str_login_permission_attr",           //  PROPERTYNAME_LoginPermissionAttribute,
    "pam_ldap_bool_enhanced_role_based_security",   // PROPERTYNAME_RoleBasedSecurityEnabled,
    "pam_ldap_str_base_dn",                         //  PROPERTYNAME_RootDN,
    "pam_ldap_str_dns_search_domain",               //  PROPERTYNAME_SearchDomain,
    "pam_ldap_str_dns_service_name",                //  PROPERTYNAME_SearchServiceName,
    "pam_ldap_str_erbs_target_server",              //  PROPERTYNAME_ServerTargetName,
    "pam_ldap_bool_encryption_enabled",             // PROPERTYNAME_SSLEnabled,
    "pam_ldap_str_uid_search_attr",                 //  PROPERTYNAME_UIDSearchAttribute,
    "pam_ldap_str_user_search_base_dn"              // PROPERTYNAME_UserSearchBaseDN
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_LDAPCLIENTSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_LDAPClientServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LDAPClientService;\
    Arg.GetKeyProperty = IBM_LDAPClientService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_LDAPClientService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_LDAPClientService_GetProperty;\
    Arg.KeyPropertyList = IBM_LDAPClientServiceKeyPropertyList;\
    Arg.PropertyList = IBM_LDAPClientServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_LDAPClientServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LDAPClientServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LDAPCLIENTSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_LDAPClientServiceAssociations;\
    Arg.AgentInit = IBM_LDAPClientService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_LDAPClientService_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LDAPClientService;\
    Arg.GetKeyProperty = IBM_LDAPClientService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_LDAPClientService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_LDAPClientService_GetProperty;\
    Arg.KeyPropertyList = IBM_LDAPClientServiceKeyPropertyList;\
    Arg.PropertyList = IBM_LDAPClientServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_LDAPClientServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LDAPClientServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LDAPCLIENTSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_LDAPClientServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_LDAPCLIENTSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_LDAPClientServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LDAPClientService;\
    Arg.GetKeyProperty = IBM_LDAPClientService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_LDAPClientService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_LDAPClientService_GetProperty;\
    Arg.KeyPropertyList = IBM_LDAPClientServiceKeyPropertyList;\
    Arg.PropertyList = IBM_LDAPClientServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_LDAPClientServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LDAPClientServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LDAPCLIENTSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_LDAPClientServiceAssociations;\
    Arg.AgentInit = IBM_LDAPClientService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_LDAPClientService_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LDAPClientService;\
    Arg.GetKeyProperty = IBM_LDAPClientService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_LDAPClientService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_LDAPClientService_GetProperty;\
    Arg.KeyPropertyList = IBM_LDAPClientServiceKeyPropertyList;\
    Arg.PropertyList = IBM_LDAPClientServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_LDAPClientServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LDAPClientServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LDAPCLIENTSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_LDAPClientServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_LDAPClientService_GetProperty( 
                                            CMPICount nInstIndex,
                                            CMPICount nPropIndex,
                                            void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_LDAPClientService_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_LDAPClientService_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_LDAPClientService, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_LDAPClientService, &rc);
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
        data = IBM_LDAPClientService_GetProperty(nInstIndex, nKeyIndex | IBM_LDAPCLIENTSERVICE_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_LDAPClientService_GenerateObjectPath( 
                                                          char **properties,
                                                          CMPICount InstIndex,
                                                          void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_LDAPClientService_GetInstance( 
                                              CMPIInstanceMI *mi,
                                              const CMPIContext *ctx,
                                              const CMPIResult *rslt,
                                              const CMPIObjectPath *op,
                                              const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_LDAPClientService_EnumInstances( 
#else
CMPIStatus IBM_LDAPClientService_EnumerateInstances( 
#endif
                                                     CMPIInstanceMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op,
                                                     const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_LDAPClientService_EnumInstanceNames( 
#else
CMPIStatus IBM_LDAPClientService_EnumerateInstanceNames( 
#endif
                                                         CMPIInstanceMI *mi,
                                                         const CMPIContext *ctx,
                                                         const CMPIResult *rslt,
                                                         const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_LDAPClientService_Associators( 
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
    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_LDAPClientService_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_LDAPClientService_References( 
                                             CMPIAssociationMI *mi,
                                             const CMPIContext *ctx,
                                             const CMPIResult *rslt,
                                             const CMPIObjectPath *op,
                                             const char *resultClass,
                                             const char *role,
                                             const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_LDAPClientService_ReferenceNames( 
                                                 CMPIAssociationMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char *resultClass,
                                                 const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

BOOLEAN CheckLengthForLDAPConfig(int nIndex, const char *pValue)
{
    int ret = TRUE;
    int nLen = 0;
    if (!pValue)
    {
        return FALSE;
    }

    nLen = strlen(pValue);
    switch(nIndex)
    {
        case 5:    
        case 7:
        case 9:            
        case 13:                        
            ret = (nLen < 128) ? TRUE : FALSE;
            break;
        case 14:
            ret = (nLen < 64) ? TRUE : FALSE;
            break;
        case 15:
        case 16:
            ret = (nLen < 16) ? TRUE : FALSE;
            break;
        case 18:            
            ret = (nLen < 64) ? TRUE : FALSE;
            break;
        default:
            break;
    }

    return ret ;
}

CMPIBoolean IBM_LDAPClientService_HasAddressPort(char *szAddress)
{
    if(strchr(szAddress, ':') == NULL)
    {
        return CMPIFALSE;
    }
    else if((strstr(szAddress, "]:") == NULL) && IsValidAddress(AF_INET6, szAddress, NULL))
    {
        return CMPIFALSE;
    }
    return CMPITRUE;
}


CMPIBoolean IBM_LDAPClientService_ValidDigit(char *pData)
{
    char *pTmp = pData;
    while (*pTmp != 0)
    {
        if ((*pTmp < '0') || (*pTmp > '9'))
        {
            return CMPIFALSE;
        }
        pTmp++;
    }
    return CMPITRUE;
}


/* Cheryl 2010/11/02 begin */
CMPIStatus IBM_LDAPClientService_ModifyInstance(
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
    CMPIStatus rc_temp =
    {
        CMPI_RC_ERR_FAILED,
        NULL
    };
    CMPICount instIndex = 0;
    void *pAgentDataPtr = NULL;
    sClassUtilArg Arg; 
    CMPIData data, data2;
    CMPIString *dataStr = NULL;
    CMPIArray *arr = NULL;
    int i, j;
    char *szName = NULL;
    UINT16 u16Value = 0;
    UINT16 u16Value_src = 0;
    UINT32 u32ArrSize = 0;
    BOOLEAN bValue = FALSE;
    BOOLEAN bValue_src = FALSE;
    UINT8 au8GroupFilter[MAX_STRING_LENGTH] = {};
    UINT16 u16Event = 0;
    BOOLEAN bRBSEnabled = FALSE;
    sSwMsg_UserCfg sw_userCfg = {"\0"};
    sSwMsg_LDAPMiscCfg sw_ldapMiscCfg = {"\0", "\0", 0};
    char local_UserID[MAX_ATTR_STR_LEN];
    int iPolicyLDAPSSO = -1;

    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);

    if (Arg.AgentInit)
    {
        pAgentDataPtr = Arg.AgentInit(0);
    }

    /* Get index of instance by objectpath */
    instIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == instIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_LDAPClientServicePropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }
    
    CMPIGetUserNameFromContext(ctx, local_UserID);
    
    aim_config_get_int(POLICY_LDAP_SINGLE_SIGN_ON, &iPolicyLDAPSSO);
    if(iPolicyLDAPSSO == 1)
    {
        rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
        goto ERR_EXIT;
    }

    for(i = 0; i < Arg.propertyNo; i++)
    {
        data = inst->ft->getProperty(inst, IBM_LDAPClientServicePropertyList[i],&rc_temp);
        if ((data.state != CMPI_goodValue) || (rc_temp.rc != CMPI_RC_OK))
        {        
            //printf("%s,data.state=%d\n",IBM_LDAPClientServicePropertyList[i], data.state);
            continue; /* continue to read remaining prperties if one found with a NULL value */
        }
        switch(data.type)
        {
            case CMPI_boolean:
                bValue = data.value.boolean;
                if (!aim_config_set_bool((char *)IBM_LDAPClientServiceAIMVariableList[i], bValue, TRUE))
                {
                    rc.rc = CMPI_RC_ERR_FAILED;
                    goto ERR_EXIT_RELEASE;                            
                }
                CMPIDataRelease(&data);
                break;
                            
            case CMPI_uint16:
                u16Value = (UINT16) data.value.uint16;
                if (0 == strcmp(PROPERTYNAME_LDAPServerSelectionMethod, IBM_LDAPClientServicePropertyList[i]))
                {
                    /* 2 (DNS): TRUE 
                       3 (Preconfigured): FALSE */
                    switch (u16Value)
                    {
                        case 2:
                            bValue = TRUE;
                            break;
                        case 3:
                            bValue = FALSE;
                            break;
                        default:
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE; 
                    }

                    aim_config_get_bool((char *)IBM_LDAPClientServiceAIMVariableList[i],(bool *) &bValue_src);
                    if (!aim_config_set_bool((char *)IBM_LDAPClientServiceAIMVariableList[i], bValue, TRUE))
                    {
                        rc.rc = CMPI_RC_ERR_FAILED;
                        goto ERR_EXIT_RELEASE;                        
                    }
                    CMPIDataRelease(&data);

                    if (bValue != bValue_src)
                    {
                         u16Event |= 0x01;
                        snprintf(sw_userCfg.c_UserID, sizeof(sw_userCfg.c_UserID), "%s", local_UserID);
                        //CMPIGetUserNameFromContext(ctx, sw_userCfg.c_UserID);                                                    
                    }
                    break;
                }
                if (0 == strcmp("DomainSourceMethod", IBM_LDAPClientServicePropertyList[i]))
                {
                    int u16PamValue = 0;
                    
                    /* 2 (Extract from login id)       : 0, 
                       3 (Use preconfigured)           : 1,
                       4 (Login id, then preconfigured): 2 */
                    switch (u16Value)
                    {
                        case 2:
                            u16PamValue = 0;
                            break;
                        case 3:
                            u16PamValue = 1;
                            break;
                        case 4:
                            u16PamValue = 2;
                            break;
                        default:
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE;  
                    }
                    if (!aim_config_set_int((char *)IBM_LDAPClientServiceAIMVariableList[i], u16PamValue, TRUE))
                    {
                        rc.rc = CMPI_RC_ERR_FAILED;
                        goto ERR_EXIT_RELEASE;                          
                    }
                    CMPIDataRelease(&data);
                    break;
                }
                if (0 == strcmp(PROPERTYNAME_BindingMethod, IBM_LDAPClientServicePropertyList[i]))
                {
                    UINT16 u16PamValue = 0;
                    aim_config_get_int((char *)IBM_LDAPClientServiceAIMVariableList[i],(int *) &u16Value_src);
                        
                    /* 2 ("Configured Credentials"): 1,
                       3 ("Login Credentials")     : 2,
                       4 ("Anonymous")             : 0 */
                    switch (u16Value)
                    {
                        case 2:
                            u16PamValue = 1;
                            break;
                        case 3:
                            u16PamValue = 2;
                            break;
                        case 4:
                            u16PamValue = 0;
                            break;
                        default:
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE;  
                    }
                    if (!aim_config_set_int((char *)IBM_LDAPClientServiceAIMVariableList[i], u16PamValue, TRUE))
                    {
                        rc.rc = CMPI_RC_ERR_FAILED;
                        goto ERR_EXIT_RELEASE;                            
                    }
                    CMPIDataRelease(&data);
                    
                    if (u16Value_src != u16PamValue)
                    {
                        u16Event |= 0x02;
                        snprintf(sw_ldapMiscCfg.c_UserID, sizeof(sw_ldapMiscCfg.c_UserID), "%s", local_UserID);
                        //CMPIGetUserNameFromContext(ctx, sw_ldapMiscCfg.c_UserID);                            
                        aim_config_get_bool("pam_ldap_bool_enhanced_role_based_security",(bool *) &bRBSEnabled);
                        sw_ldapMiscCfg.b_EnhancedRBS = bRBSEnabled;
                        aim_config_get_str("pam_ldap_str_erbs_target_server", sw_ldapMiscCfg.c_TargetName);
                    }
                    
                    break;
                }
                if(0 == strcmp("SSLEnabled", IBM_LDAPClientServicePropertyList[i]))
                {
                    int iPolicyLDAPSOnly = -1;

                    /* 2 (Enabled): TRUE,
                                       3 (Disabled):FALSE */
                    switch (u16Value)
                    {
                        case 2:
                            bValue = TRUE;
                            break;
                        case 3:
                            bValue = FALSE;
                            break;
                        default:
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE; 
                    }
                    aim_config_get_int(POLICY_LDAPS_ONLY, &iPolicyLDAPSOnly);
                    if((iPolicyLDAPSOnly == 1) && (FALSE == bValue))
                    {
                        rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
                        goto ERR_EXIT_RELEASE;
                    }
                        
                    aim_config_get_bool((char *)IBM_LDAPClientServiceAIMVariableList[i],(bool *) &bValue_src);
                    if (bValue_src != bValue)
                    {
                        int iResult = sfcb_switch_cert(bValue, SFCB_CERT_TYPE_CLIENT, (CMPIContext *) ctx);
                        if (iResult)
                        {
                            logTraceCIM(LOG_LEV_ERROR, "%s()- Fail to call sfcb_switch_cert(), error code is %d.", __FUNCTION__, iResult);
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE;  
                        }
                    }
                    CMPIDataRelease(&data);
                    break;
                }
                if(0 == strcmp(PROPERTYNAME_Authorization, IBM_LDAPClientServicePropertyList[i]))
                {

                    UINT16 u16PamValue = 0;
                    /* 2 (LDAP Server) : 0 */
                    /* 3 (Local (AOM)) : 1 */
                    switch (u16Value)
                    {
                        case 2:
                            u16PamValue = 0;
                            break;
                        case 3:
                            u16PamValue = 1;
                            break;
                        default:
                            /* TODO: change return error code */
                            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                            goto ERR_EXIT_RELEASE; 
                    }
                
                    if (!aim_config_get_int((char *)IBM_LDAPClientServiceAIMVariableList[i],(int *) &u16Value_src))
                    {
                        rc.rc = CMPI_RC_ERR_FAILED;
                        goto ERR_EXIT_RELEASE;
                    }

                    if (u16Value_src != u16PamValue)
                    {
                        if (!aim_config_set_int((char *)IBM_LDAPClientServiceAIMVariableList[i], u16PamValue, TRUE))
                        {
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE;                            
                        }
                    }

                    CMPIDataRelease(&data);
                    break;
                }
            case CMPI_string:
                dataStr = CMPIData2String(&data);
                if (dataStr == NULL)
                {
                    rc.rc = CMPI_RC_ERR_FAILED;
                    goto ERR_EXIT_RELEASE;  
                }
                szName = (char *)dataStr->ft->getCharPtr(dataStr, &rc_temp);
                if (IBM_LDAPClientServiceAIMVariableList[i]) /* Some have no AIM variable to store value */
                {
                    if (!CheckLengthForLDAPConfig(i, szName))
                    {
                        SafeCMRelease(dataStr);
                        rc.rc = CMPI_RC_ERR_FAILED;
                        goto ERR_EXIT_RELEASE;                              
                    }
                    if (strcmp((char *)IBM_LDAPClientServiceAIMVariableList[i], "pam_ldap_str_client_password") == 0)
                    {
                        if (szName)
                        {
                            if (strcmp(szName, PASSWORD_DISPALY_STR) != 0)
                            {
                                TrimString((void *) szName);
                                sm_encrypt_ldap_client_pw(szName);
                            }
                        }
                    }
                    else
                    {
                        aim_config_get_str((char *)IBM_LDAPClientServiceAIMVariableList[i],(char *) au8GroupFilter);                        
                        TrimString((void *)szName);
                        if(!aim_config_set_str((char *)IBM_LDAPClientServiceAIMVariableList[i], szName, TRUE)) /* for RootDN and UserSearchBaseDN that are sharing the same AIM var, the latter one will override the value saved by the former one */
                        {
                            SafeCMRelease(dataStr);
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE;  
                        }
                    }
                }
                
                if (strcmp(PROPERTYNAME_SearchDomain, IBM_LDAPClientServicePropertyList[i]) == 0 &&
                    strcmp(szName,(char *) au8GroupFilter) != 0)
                {
                    u16Event |= 0x01;
                    snprintf(sw_userCfg.c_UserID, sizeof(sw_userCfg.c_UserID), "%s", local_UserID);
                    //CMPIGetUserNameFromContext(ctx, &sw_userCfg.c_UserID);
                }
                else if ((strcmp(PROPERTYNAME_RootDN, IBM_LDAPClientServicePropertyList[i]) == 0 ||
                          strcmp(PROPERTYNAME_ServerTargetName, IBM_LDAPClientServicePropertyList[i]) == 0 ||
                          strcmp(PROPERTYNAME_UIDSearchAttribute, IBM_LDAPClientServicePropertyList[i]) == 0 || 
                          strcmp(PROPERTYNAME_GroupSearchAttribute, IBM_LDAPClientServicePropertyList[i]) == 0 ||
                          strcmp(PROPERTYNAME_LoginPermissionAttribute, IBM_LDAPClientServicePropertyList[i]) == 0 ) &&
                          strcmp(szName,(char *) au8GroupFilter) != 0)
                {
                    u16Event |= 0x02;
                    snprintf(sw_ldapMiscCfg.c_UserID, sizeof(sw_ldapMiscCfg.c_UserID), "%s", local_UserID);
                    //CMPIGetUserNameFromContext(ctx, &sw_ldapMiscCfg.c_UserID);                            
                    aim_config_get_bool("pam_ldap_bool_enhanced_role_based_security",(bool *) &bRBSEnabled);
                    sw_ldapMiscCfg.b_EnhancedRBS = bRBSEnabled;
                    aim_config_get_str("pam_ldap_str_erbs_target_server", sw_ldapMiscCfg.c_TargetName);
                }
                
                SafeCMRelease(dataStr);
                CMPIDataRelease(&data);
                break;
                        
            case CMPI_stringA:
                if((arr = data.value.array) == NULL)
                {
                    break;
                }
                if((u32ArrSize = arr->ft->getSize(arr, &rc_temp)) == 0)
                {
                    rc.rc = CMPI_RC_ERR_FAILED;
                    goto ERR_EXIT_RELEASE;
                }
                if(0 == strcmp("LDAPServers", IBM_LDAPClientServicePropertyList[i]))
                {
                    for (j = 0; j < u32ArrSize; j++) /* Maximum 4 elements allowed */
                    {
                        char szIPName[32] = {0};
                        char szPortName[32] = {0};
                        char szCurrentIP[MAX_STRING_LENGTH] = {0};
                        char szCurrentPort[MAX_STRING_LENGTH] = {0};
                        char szNewIPPort[MAX_STRING_LENGTH * 2] = {0};

                        memset(szNewIPPort, 0, sizeof(szNewIPPort));

                        data2 = arr->ft->getElementAt(arr, j, &rc_temp);
                        if (rc_temp.rc != CMPI_RC_OK)
                        {
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE;  
                        }
                        if (data2.state != CMPI_goodValue)
                        {
                            continue;
                        }
                        if (data2.type != CMPI_string)
                        {
                            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                            CMPIDataRelease(&data2);
                            goto ERR_EXIT_RELEASE;  
                        }
                        snprintf(szIPName, 31, "pam_ldap_str_dc_%d", j + 1);
                        snprintf(szPortName, 31, "pam_ldap_str_port_%d", j + 1);
                        aim_config_get_str(szIPName, szCurrentIP);
                        aim_config_get_str(szPortName, szCurrentPort);

                        if(data2.value.string)
                        {
                            strncpy(szNewIPPort, data2.value.string->ft->getCharPtr(data2.value.string, &rc), sizeof(szNewIPPort) - 1);
                            data2.value.string->ft->release(data2.value.string);                            
                        }

                        if((data2.state == CMPI_goodValue) && (szNewIPPort != NULL) && (strlen(szNewIPPort) > 0))
                        {
                            char *pPortPoint = NULL;
                            char szNewPort[MAX_STRING_LENGTH] = {0};
                            char szNewIP[MAX_STRING_LENGTH] = {0};
                            int iAddressType = -1;

                            memset(szNewPort, 0 ,sizeof(szNewPort));
                            memset(szNewIP, 0, sizeof(szNewIP));

                            if(IBM_LDAPClientService_HasAddressPort(szNewIPPort) == CMPITRUE)
                            {
                                if((pPortPoint = strstr(szNewIPPort, "]:")) != NULL)
                                {
                                    iAddressType = AF_INET6;
                                }
                                else
                                {
                                    pPortPoint = strchr(szNewIPPort, ':');
                                }
                                if(iAddressType == AF_INET6)
                                {
                                    if(szNewIPPort[0] != '[')
                                    {
                                        logTraceCIM(LOG_LEV_ERROR, "%s()- Invalid IP format.", __FUNCTION__);
                                        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                                        goto ERR_EXIT_RELEASE;
                                    }

                                    if (strlen(&pPortPoint[2]) >= sizeof(szNewPort))
                                    {
                                        strncpy(szNewPort, &pPortPoint[2], sizeof(szNewPort) - 1);
                                    }
                                    else
                                    {
                                        strncpy(szNewPort, &pPortPoint[2], strlen(&pPortPoint[2]));
                                    }

                                    if ((pPortPoint - szNewIPPort - 1) >= sizeof(szNewIP))
                                    {
                                        strncpy(szNewIP, &szNewIPPort[1], sizeof(szNewIP) - 1);
                                    }
                                    else
                                    {
                                        strncpy(szNewIP, &szNewIPPort[1], pPortPoint - szNewIPPort - 1);
                                    }
                                }
                                else
                                {
                                    if (strlen(&pPortPoint[1]) >= sizeof(szNewPort))
                                    {
                                        strncpy(szNewPort, &pPortPoint[1], sizeof(szNewPort) - 1);
                                    }
                                    else
                                    {
                                        strncpy(szNewPort, &pPortPoint[1], strlen(&pPortPoint[1]));
                                    }

                                    if ((pPortPoint - szNewIPPort) >= sizeof(szNewIP))
                                    {
                                        strncpy(szNewIP, szNewIPPort, sizeof(szNewIP) - 1);
                                    }
                                    else
                                    {
                                        strncpy(szNewIP, szNewIPPort, (pPortPoint - szNewIPPort));
                                    }
                                    
                                }
                                //printf("%s %s\n", szNewIP, szNewPort);
                                
                                //Valid Port
                                if((strlen(szNewPort) == 0) || (IBM_LDAPClientService_ValidDigit(szNewPort) == CMPIFALSE) ||
                                   (atoi(szNewPort) < 1) || (atoi(szNewPort) > 65535))
                                {
                                    logTraceCIM(LOG_LEV_ERROR, "%s()- Invalid Port(%s).", __FUNCTION__, szNewPort);
                                    rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                                    goto ERR_EXIT_RELEASE; 
                                }
                            }
                            else
                            {
                                strncpy(szNewIP, szNewIPPort, sizeof(szNewIP) - 1);
                                //printf("%s\n", szNewIP);
                            }

                            /* Valid IP */
                            if(!IsValidServerName(szNewIP))
                            {
                                logTraceCIM(LOG_LEV_ERROR, "%s()- Invalid IP.", __FUNCTION__);
                                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                                goto ERR_EXIT_RELEASE;
                            }
                            
                            if((strcmp(szCurrentIP, szNewIP) == 0) && (strcmp(szCurrentPort, szNewPort) == 0))
                            {
                                continue;
                            }
                                                        
                            if(!aim_config_set_str(szIPName, szNewIP, TRUE) ||
                               !aim_config_set_str(szPortName, szNewPort, TRUE))
                            {
                                rc.rc = CMPI_RC_ERR_FAILED;
                                goto ERR_EXIT_RELEASE;  
                            }
                            u16Event |= 0x01;
                        }
                        else /* Clear the remaining entries if the input is less than 4 elements */
                        {
                            if((strlen(szCurrentIP) > 0) || (strlen(szCurrentPort) > 0))
                            {
                                if((aim_config_set_str(szIPName, "", TRUE) == FALSE) || (aim_config_set_str(szPortName, "", TRUE) == FALSE))
                                {
                                    rc.rc = CMPI_RC_ERR_FAILED;
                                    goto ERR_EXIT_RELEASE;  
                                }
                                u16Event |= 0x01;
                            }
                        }
                    }
                    if((u16Event & 0x01) > 0)
                    {
                        snprintf(sw_userCfg.c_UserID, sizeof(sw_userCfg.c_UserID), "%s", local_UserID);
                    }
                    CMPIDataRelease(&data);
                    break;
                } 
                if(0 == strcmp("GroupFilters", IBM_LDAPClientServicePropertyList[i]))
                {
                    char szCurrentGroupFilterStr[MAX_STRING_LENGTH] = {0};
                    for(j = 0; j < u32ArrSize; j++)
                    {                  
                        data2 = arr->ft->getElementAt(arr, j, &rc_temp);
                        if ((data2.state != CMPI_goodValue) || (rc_temp.rc != CMPI_RC_OK))
                        {
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE;  
                        }
                        szName = (char *)(data2.value.string->ft->getCharPtr(data2.value.string, &rc));
                                   
                        /* Only allow to store full filter names if exceed (MAX_STRING_LENGTH - 1) */
                        if( ( strlen((char *)au8GroupFilter) + strlen((char *)szName) ) >= MAX_STRING_LENGTH ) 
                        {
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto ERR_EXIT_RELEASE;  
                        }                            
                        strncat((char *)au8GroupFilter, szName, sizeof(au8GroupFilter) - 1);
                        strncat((char *)au8GroupFilter, ",", sizeof(au8GroupFilter) - 1);  
                        
                    }
                    
                    aim_config_get_str((char *)IBM_LDAPClientServiceAIMVariableList[i], szCurrentGroupFilterStr);
                    au8GroupFilter[strlen((char *)au8GroupFilter)-1] = '\0';
                    if(!aim_config_set_str((char *)IBM_LDAPClientServiceAIMVariableList[i],(char *) au8GroupFilter, TRUE))
                    {
                        rc.rc = CMPI_RC_ERR_FAILED;
                        goto ERR_EXIT_RELEASE;  
                    }                     

                    
                    if (strcmp((char *)au8GroupFilter, szCurrentGroupFilterStr) != 0)
                    {
                        u16Event |= 0x02;
                        snprintf(sw_ldapMiscCfg.c_UserID, sizeof(sw_ldapMiscCfg.c_UserID), "%s", local_UserID);
                        //CMPIGetUserNameFromContext(ctx, &sw_ldapMiscCfg.c_UserID);                            
                        aim_config_get_bool("pam_ldap_bool_enhanced_role_based_security",(bool *) &bRBSEnabled);
                        sw_ldapMiscCfg.b_EnhancedRBS = bRBSEnabled;
                        aim_config_get_str("pam_ldap_str_erbs_target_server", sw_ldapMiscCfg.c_TargetName);
                    }
                }
                CMPIDataRelease(&data);
                break;
            default:
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                CMPIDataRelease(&data);
                break;
        }                   
    }        

    if (u16Event & 0x01)
    {   
        //printf("Send an event %d, user: %s\n", SW_MSGID_LDAP_SERVER_CONFIGURED, sw_userCfg.c_UserID);
        if (sw_msg_dispatcher(SW_MSGID_LDAP_SERVER_CONFIGURED, (void*)&sw_userCfg) != CEM_RC_OK)
        {
            logTraceCIM(LOG_LEV_WARNING, "%s()- Fail to send software event %d.", __FUNCTION__, SW_MSGID_LDAP_SERVER_CONFIGURED);
        } 
    }

    if (u16Event & 0x02)
    {
        //printf("Send an event %d, user: %s, rbs: %d\n", SW_MSGID_LDAP_MISC_SETTINGS_CONFIGURED, sw_ldapMiscCfg.c_UserID, sw_ldapMiscCfg.b_EnhancedRBS);
        if (sw_msg_dispatcher(SW_MSGID_LDAP_MISC_SETTINGS_CONFIGURED, (void*)&sw_ldapMiscCfg) != CEM_RC_OK)
        {
            logTraceCIM(LOG_LEV_WARNING, "%s()- Fail to send software event %d.", __FUNCTION__, SW_MSGID_LDAP_MISC_SETTINGS_CONFIGURED);
        }             
    }

    //printf("Send an event ends\n");
    rc.rc = CMPI_RC_OK;
    goto ERR_EXIT;

ERR_EXIT_RELEASE:
    CMPIDataRelease(&data);
    
ERR_EXIT:
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
/* Cheryl 2010/11/02 end*/

CMPIStatus IBM_LDAPClientService_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg);

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
    if (0 == strcmp(method, "AssignRoles"))
    {
        value.uint32 = IBM_LDAPClientService_InstAgent_AssignRoles((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "CreateGroup"))
    {
        value.uint32 = IBM_LDAPClientService_InstAgent_CreateGroup((UINT32) nIndex, in, out);
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
CMPIData *IBM_LDAPClientService_GetMethodName()
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
    value.chars = (char *) METHODNAME_AssignRoles;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_CreateGroup;
    nameArray->ft->setElementAt(nameArray, 1, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

CMPIData *IBM_LDAPClientService_GetMethodParameters(const char * MethodName)
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

    if (0 == strcmp(MethodName, METHODNAME_AssignRoles))
    {
        iMethID = 0;
    }
    else if (0 == strcmp(MethodName, METHODNAME_CreateGroup))
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
            value.chars = "ref CIM_Group";
            pArgs->ft->addArg(pArgs, PARAMNAME_Group,&value,CMPI_chars);
            value.chars = "Aref CIM_Role";
            pArgs->ft->addArg(pArgs, PARAMNAME_Roles,&value,CMPI_chars);
            break;

        case 1:
            value.chars = "ref CIM_ComputerSystem";
            pArgs->ft->addArg(pArgs, PARAMNAME_System,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_GroupTemplate,&value,CMPI_chars);
            value.chars = "ref CIM_Group";
            pArgs->ft->addArg(pArgs, PARAMNAME_Group,&value,CMPI_chars);
            break;

    }

    data->value.args = pArgs;
    data->type = CMPI_args;
    data->state = CMPI_goodValue;
    return (data);
}
#endif

/* IBM_LDAPClientService Class Service Function */
CMPIStatus Lenovo_LDAPClientServiceService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_LDAPClientService,
                                     CIM_SecurityServiceService);
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
            rc = IBM_LDAPClientService_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_LDAPClientService_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_LDAPClientService_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_LDAPCLIENTSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_LDAPClientService_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_LDAPCLIENTSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_LDAPClientService_InstAgent_Destroy;
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
            rc = IBM_LDAPClientService_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_LDAPClientService_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_LDAPClientService_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_LDAPClientService_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_LDAPClientService_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_LDAPClientService_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_LDAPClientService_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_LDAPClientService_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_LDAPClientService_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_LDAPClientService_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_LDAPClientService_GetMethodParameters(method);
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
GenNotSupportInstanceMICreateInstance(IBM_LDAPClientService);
//GenNotSupportInstanceMIModifyInstance(IBM_LDAPClientService);
GenNotSupportInstanceMIDeleteInstance(IBM_LDAPClientService);
GenNotSupportInstanceMIExecQuery(IBM_LDAPClientService);
GenNotSupportInstanceMICleanup(IBM_LDAPClientService);

/* MI factory function */
CMInstanceMIStub( IBM_LDAPClientService_,
                  Lenovo_LDAPClientService_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_LDAPClientService);

CMMethodMIStub( IBM_LDAPClientService_,
                Lenovo_LDAPClientService_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_LDAPCLIENTSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_LDAPClientServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_LDAPClientService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LDAPClientService;\
    Arg.GetNextInstIndex = IBM_LDAPClientService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_LDAPClientServiceKeyPropertyList;\
    Arg.PropertyList = IBM_LDAPClientServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_LDAPClientServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LDAPClientServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_LDAPClientService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_LDAPClientService_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_LDAPClientService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LDAPClientService;\
    Arg.GetNextInstIndex = IBM_LDAPClientService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_LDAPClientServiceKeyPropertyList;\
    Arg.PropertyList = IBM_LDAPClientServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_LDAPClientServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LDAPClientServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_LDAPClientService Class Service Function */
CMPIStatus Lenovo_LDAPClientServiceService( 
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

/* Gets the Arg of Class IBM_LDAPClientService Function */
sClassUtilArg IBM_LDAPClientService_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_LDAPCLIENTSERVICE_ARG( Arg );

    return (Arg);
}

#endif
