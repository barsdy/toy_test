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


/* Include base class' header file here */
#include <emerson/aim/libaim.h>
#include <emerson/securitymgr/sm.h>
#include <emerson/securitymgr/secsetting.h>

#include <emerson/ab/avct_dm_ADAMLib.h>
#include <emerson/ab/avct_dm_VarList.h>
#include <emerson/ab/avct_SharedMem.h>
#include <emerson/ab/avct_SharedList.h>

#include <emerson/cemgr/swe_function_table.h>
#include <emerson/pm/pm_lib.h>

/* Include debug header file here */
#include "LogUtil.h"


#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

const char *AIM_Var_SessionTimeoutMethod = "session_timeout_method";

/* IBM_LoginSettingData class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_LoginSettingData = (CMPIUint8 *)CLASSNAMETEXT_IBM_LoginSettingData;

/* Property List */
static const char * const IBM_LoginSettingDataPropertyList[] = 
{
    PROPERTYNAME_ChangeableType,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_InactivitySessionTimeout,
    PROPERTYNAME_LockoutPeriod,
    PROPERTYNAME_LoginFailureLockout,
    PROPERTYNAME_MaximumLockoutPeriod,
    PROPERTYNAME_MaximumPasswordExpirationLimit,
    PROPERTYNAME_MaximumPasswordHistoryDepth,
    PROPERTYNAME_SessionTimeoutMethod,
    PROPERTYNAME_UserAuthenticationMethod
};

/* Key property List */
static const char * const IBM_LoginSettingDataKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};


static const char * const IBM_LoginSettingDataPropertyListChangeable[] = 
{
  
    PROPERTYNAME_SessionTimeoutMethod, //move to first

//    PROPERTYNAME_ChangeableType,
//    PROPERTYNAME_ElementName,
    PROPERTYNAME_InactivitySessionTimeout,
//    PROPERTYNAME_LockoutPeriod,
    PROPERTYNAME_LoginFailureLockout,
//    PROPERTYNAME_MaximumLockoutPeriod,
//    PROPERTYNAME_MaximumPasswordExpirationLimit,
//    PROPERTYNAME_MaximumPasswordHistoryDepth,

    PROPERTYNAME_UserAuthenticationMethod
};


void GetSessionTimeoutData(int *piSessionTimeout, int *piMethod)
{
    AVCT_DM_VarListStatus varStatus;
    AVCT_DM_VarListError varError;

    varStatus = GETVARVALUE(UINT, AVCT_DM_DEFVARLIST, 0, 0, false, "s/WebGui/config/timeout", &varError, (void *) piSessionTimeout);

    if (AVCT_DM_VarListStatus_OK != varStatus)
    {
        printf("[%s] GET VARVALUE failed.\n", __FUNCTION__);
        *piSessionTimeout = 6;
    }

    if (!aim_config_get_int((char *) AIM_Var_SessionTimeoutMethod, piMethod))
    {
        printf("[%s] Failed to call aim_config_get_int(%s).\n", __FUNCTION__, AIM_Var_SessionTimeoutMethod);
        switch (*piSessionTimeout)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                *piMethod = 2;
                break;
            case 6:
                *piMethod = 3;
                break;
            case 7:
            default:
                *piMethod = 4;
                break;
        }
        
        if (!aim_config_set_int((char *) AIM_Var_SessionTimeoutMethod, *piMethod, true))
        {
            printf("[%s] Failed to call aim_config_set_int(%s, %d).\n", __FUNCTION__, AIM_Var_SessionTimeoutMethod, *piMethod);
        }
    }

}


#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_LOGINSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_LoginSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LoginSettingData;\
    Arg.GetKeyProperty = IBM_LoginSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_LoginSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_LoginSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_LoginSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_LoginSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_LoginSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LoginSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LOGINSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_LoginSettingDataAssociations;\
    Arg.AgentInit = IBM_LoginSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_LoginSettingData_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LoginSettingData;\
    Arg.GetKeyProperty = IBM_LoginSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_LoginSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_LoginSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_LoginSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_LoginSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_LoginSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LoginSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LOGINSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_LoginSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_LOGINSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_LoginSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LoginSettingData;\
    Arg.GetKeyProperty = IBM_LoginSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_LoginSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_LoginSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_LoginSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_LoginSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_LoginSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LoginSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LOGINSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_LoginSettingDataAssociations;\
    Arg.AgentInit = IBM_LoginSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_LoginSettingData_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LoginSettingData;\
    Arg.GetKeyProperty = IBM_LoginSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_LoginSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_LoginSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_LoginSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_LoginSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_LoginSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LoginSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LOGINSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_LoginSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_LoginSettingData_GetProperty( 
                                           CMPICount nInstIndex,
                                           CMPICount nPropIndex,
                                           void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_LoginSettingData_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_LoginSettingData_GetKeyProperty( 
                                              CMPICount nInstIndex,
                                              CMPICount nKeyIndex,
                                              void *pAgentDataPtr)
{
    CMPIData data;
        data.state = CMPI_badValue;
    data = IBM_LoginSettingData_GetProperty(nInstIndex, nKeyIndex | IBM_LOGINSETTINGDATA_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_LoginSettingData_GenerateObjectPath( 
                                                         char **properties,
                                                         CMPICount InstIndex,
                                                         void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_LoginSettingData_GetInstance( 
                                             CMPIInstanceMI *mi,
                                             const CMPIContext *ctx,
                                             const CMPIResult *rslt,
                                             const CMPIObjectPath *op,
                                             const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_LoginSettingData_EnumInstances( 
#else
CMPIStatus IBM_LoginSettingData_EnumerateInstances( 
#endif
                                                    CMPIInstanceMI *mi,
                                                    const CMPIContext *ctx,
                                                    const CMPIResult *rslt,
                                                    const CMPIObjectPath *op,
                                                    const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_LoginSettingData_EnumInstanceNames( 
#else
CMPIStatus IBM_LoginSettingData_EnumerateInstanceNames( 
#endif
                                                        CMPIInstanceMI *mi,
                                                        const CMPIContext *ctx,
                                                        const CMPIResult *rslt,
                                                        const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_LoginSettingData_Associators( 
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
    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_LoginSettingData_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_LoginSettingData_References( 
                                            CMPIAssociationMI *mi,
                                            const CMPIContext *ctx,
                                            const CMPIResult *rslt,
                                            const CMPIObjectPath *op,
                                            const char *resultClass,
                                            const char *role,
                                            const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_LoginSettingData_ReferenceNames( 
                                                CMPIAssociationMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char *resultClass,
                                                const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_LoginSettingData_CheckSelectorSet( 
                                                 const CMPIObjectPath *op,
                                                 CMPIBoolean bAllKey,
                                                 void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    nIndex = CIMClassUtil_CheckSelectorSet(op, bAllKey, INSTANCE_INDEX_INVALID, &Arg, pAgentDataPtr);

    if (nIndex != INSTANCE_INDEX_INVALID)
    {
        nNextIndex = CIMClassUtil_CheckSelectorSet(op, bAllKey, nIndex, &Arg, pAgentDataPtr);

        if (nNextIndex == INSTANCE_INDEX_INVALID)
        {
            return (nIndex);
        }
        else
        {
            return (INSTANCE_INDEX_INVALID);
        }
    }
    return (INSTANCE_INDEX_INVALID);
}
#if 0
void GetSessionTimeoutData(int *piSessionTimeout, int *piMethod)
{
    AVCT_DM_VarListStatus varStatus;
    AVCT_DM_VarListError varError;

    varStatus = GETVARVALUE(UINT, AVCT_DM_DEFVARLIST, 0, 0, false, "s/WebGui/config/timeout", &varError, (void *) piSessionTimeout);

    if (AVCT_DM_VarListStatus_OK != varStatus)
    {
        printf("[%s] GET VARVALUE failed.\n", __FUNCTION__);
        *piSessionTimeout = 6;
    }

    if (!aim_config_get_int((char *) AIM_Var_SessionTimeoutMethod, piMethod))
    {
        printf("[%s] Failed to call aim_config_get_int(%s).\n", __FUNCTION__, AIM_Var_SessionTimeoutMethod);
        switch (*piSessionTimeout)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                *piMethod = 2;
                break;
            case 6:
                *piMethod = 3;
                break;
            case 7:
            default:
                *piMethod = 4;
                break;
        }
        
        if (!aim_config_set_int((char *) AIM_Var_SessionTimeoutMethod, *piMethod, true))
        {
            printf("[%s] Failed to call aim_config_set_int(%s, %d).\n", __FUNCTION__, AIM_Var_SessionTimeoutMethod, *piMethod);
        }
    }

}
#endif
/* UserAuthenticationMethod, SessionTimeoutMethod, InactivitySessionTimeout,  LoginFailureLockout, LockoutPeriod,  */
CMPIStatus IBM_LoginSettingData_ModifyInstance(
                                      CMPIInstanceMI *mi, 
                                      const CMPIContext *ctx, 
                                      const CMPIResult *rslt, 
                                      const CMPIObjectPath *op,
                                      const CMPIInstance * inst,
                                      const char **properties
                                      )
{
    CMPIStatus rc = {CMPI_RC_ERR_INVALID_PARAMETER, NULL};
    CMPICount instIndex = 0;
    CMPIData data;
    CMPIString *dataStr = NULL;
    char tmp_string[128] = {0};
    int tmp_number = 0;
    int nOrgAuth_Mode = 0;
    char *p_tmp = NULL;
    int bResult = 0;
    AVCT_DM_VarListStatus varStatus;
    AVCT_DM_VarListError varError;
    int nSessionTimeout = 0;
    int nOrgSessionTimeout = 0;
    void *pAgentDataPtr = NULL;
    sSwMsg_AccSecCfg sw_accseccfg = {};
    BOOLEAN bAuthenticationMethodChange = FALSE;
    BOOLEAN bLockoutPeriodChange = FALSE;
    BOOLEAN bSessionTimeoutChange = FALSE;  
    int sw_tmp_number = 0;
    int nOrgFailCount = 0;
    sClassUtilArg Arg;
    int iTimeoutMethod = 0;
    int iPolicyLDAPOnly = -1;   //Policy # 615
    
    //printf("IBM_LoginSettingData_ModifyInstance.\n");
    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg);
    
#if IBM_LOGINSETTINGDATA_INIT_SUPPORT
    pAgentDataPtr = Arg.AgentInit(0);
#endif

    /* Check current instance */    
    instIndex = IBM_LoginSettingData_CheckSelectorSet(op, CMPITRUE, pAgentDataPtr);
    if (instIndex == INSTANCE_INDEX_INVALID)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- IBM_LoginSettingData_CheckSelectorSet failed.", __FUNCTION__);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        return (rc);
    }

    /* Get and check ChangeableType  */
    data = inst->ft->getProperty(inst,PROPERTYNAME_ChangeableType, &rc);
    if((data.state != CMPI_goodValue) || (rc.rc != CMPI_RC_OK))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- PROPERTYNAME_ChangeableType get failed.", __FUNCTION__);
        rc.rc  = CMPI_RC_ERR_FAILED;
        goto EXIT;
    }

    dataStr = CMPIData2String(&data);

    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        return (rc);
    }

    p_tmp = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
    memset(tmp_string, 0, sizeof(tmp_string));
    strncpy(tmp_string, p_tmp, sizeof(tmp_string) - 1);
    tmp_number = atoi(tmp_string);

    if(tmp_number == 3 ) /* Persistent */
    {
        SafeCMRelease(dataStr);
        CMPIDataRelease(&data);
        rc.rc  = CMPI_RC_ERR_NOT_SUPPORTED; /* not changed */
        goto EXIT;
    }

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

    aim_config_get_int(POLICY_LDAP_ONLY, &iPolicyLDAPOnly);
    if (iPolicyLDAPOnly != 1)
    {
        /* 1. UserAuthenticationMethod */
        data = inst->ft->getProperty(inst, PROPERTYNAME_UserAuthenticationMethod, &rc);
        if((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
        {
            dataStr = CMPIData2String(&data); 

            if(dataStr == NULL)
            {
                CMPIDataRelease(&data);
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                return (rc);
            }

            p_tmp = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
            if (p_tmp==NULL)
            {
                SafeCMRelease(dataStr);
                CMPIDataRelease(&data);
                rc.rc  = CMPI_RC_ERR_FAILED;
                goto EXIT;
            }
            tmp_number = atoi(p_tmp);

            SafeCMRelease(dataStr);
            CMPIDataRelease(&data);

            if ((tmp_number < 2) || (tmp_number > 5)) /* 2,3,4,5 */
            {
                rc.rc  = CMPI_RC_ERR_FAILED;
                goto EXIT;
            }
                    
            aim_config_get_int("pam_arbd_auth_mode", &sw_tmp_number);
            switch(sw_tmp_number)
            {
                case 0: /* Local only */
                case 4:
                    nOrgAuth_Mode = 2;
                    break;
                case 1: /* LDAP only */
                case 5:
                    nOrgAuth_Mode = 3;
                    break;
                case 2: /* Local first, then LDAP */
                case 6:
                    nOrgAuth_Mode = 4;
                    break;
                case 3: /* LDAP first, then Local */
                case 7:
                    nOrgAuth_Mode = 5;
                    break;
               default:
                    nOrgAuth_Mode = 0;
            }


            if (nOrgAuth_Mode != tmp_number)
            {
            	tmp_number = tmp_number -2;
                bResult = aim_config_set_int("pam_arbd_auth_mode", tmp_number, TRUE);
                if(bResult==FALSE)
                {
                    rc.rc  = CMPI_RC_ERR_FAILED;
                    goto EXIT;
                }
                
                bAuthenticationMethodChange = TRUE;
                if (tmp_number == 0)
                {
                    strncpy(sw_accseccfg.c_AuthenticationMethod, "local only", sizeof(sw_accseccfg.c_AuthenticationMethod));                
                }
                else if(tmp_number == 1)
                {
                    strncpy(sw_accseccfg.c_AuthenticationMethod, "ldap only", sizeof(sw_accseccfg.c_AuthenticationMethod));                
                }
                else if(tmp_number == 2)    
                {
                    strncpy(sw_accseccfg.c_AuthenticationMethod, "local first then ldap", sizeof(sw_accseccfg.c_AuthenticationMethod));                    
                }
                else if(tmp_number == 3)
                {
                    strncpy(sw_accseccfg.c_AuthenticationMethod, "ldap first then local", sizeof(sw_accseccfg.c_AuthenticationMethod));                    
                }
            }
            
        }/* End of UserAutheticationMethod */
    }
    /* 2. SessionTimeoutMethod and InactivitySessionTimeout */
    /* Get input value */
    data = inst->ft->getProperty(inst, PROPERTYNAME_SessionTimeoutMethod, &rc);
    if ((CMPI_goodValue == data.state) && (CMPI_RC_OK == rc.rc))
    {
        dataStr = CMPIData2String(&data); 

        if(dataStr == NULL)
        {
           rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
           CMPIDataRelease(&data);
           return (rc);
        }
        p_tmp = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
        if (p_tmp==NULL)
        {
            SafeCMRelease(dataStr);
            CMPIDataRelease(&data);
            rc.rc  = CMPI_RC_ERR_FAILED;
            goto EXIT;
        }
        tmp_number = atoi(p_tmp);
        SafeCMRelease(dataStr);
        CMPIDataRelease(&data);

        /* Get new Session time out method */
        if (tmp_number == 2) /* is global time-out */
        {
            data = inst->ft->getProperty(inst, PROPERTYNAME_InactivitySessionTimeout, &rc);
            if((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
            {
                dataStr = CMPIData2String(&data);
                //CMPIDataRelease(&data); /* release CMPI Data after clone the value */
                if (dataStr == NULL)
                {
                    CMPIDataRelease(&data);
                    rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                    return (rc);
                }
                p_tmp = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
                if (p_tmp==NULL)
                {
                    SafeCMRelease(dataStr);
                    CMPIDataRelease(&data);
                    rc.rc  = CMPI_RC_ERR_FAILED;
                    goto EXIT;
                }
                nSessionTimeout = atoi(p_tmp);
                SafeCMRelease(dataStr);
                CMPIDataRelease(&data);
                //dataStr= NULL;

                /* Check input number is valid or not  */
                /* if config as global time-out inactivity time-out sohuld be a valid value */
                switch(nSessionTimeout)
                {
                    case 0:
                        nSessionTimeout = 6;
                        break;
                    case 1:
                        nSessionTimeout = 1;
                        break;
                    case 5:
                        nSessionTimeout = 2;
                        break;
                    case 10:
                        nSessionTimeout = 3;
                        break;
                    case 15:
                        nSessionTimeout = 4;
                        break;
                    case 20:
                        nSessionTimeout = 5;
                        break;
                    default:
                        rc.rc  = CMPI_RC_ERR_INVALID_PARAMETER;
                        goto EXIT;
                }
            }
            else
            {
                nSessionTimeout = 5;
                //rc.rc  = CMPI_RC_ERR_FAILED;
                //goto EXIT;
            }
        }
        else if (tmp_number == 3) /* no-timeout */
        {
            nSessionTimeout = 6;
        }
        else if (tmp_number == 4) /* user specified at login */
        {
            nSessionTimeout = 7;
        }
        else
        {
            rc.rc  = CMPI_RC_ERR_INVALID_PARAMETER;
            goto EXIT;
        }

        /* Get current value */
        GetSessionTimeoutData(&nOrgSessionTimeout, &iTimeoutMethod);

        if (tmp_number != iTimeoutMethod)
        {
            if (!aim_config_set_int((char *) AIM_Var_SessionTimeoutMethod, tmp_number, true))
            {
                printf("[%s] Failed to call aim_config_set_int(%s, %d).\n", __FUNCTION__, AIM_Var_SessionTimeoutMethod, tmp_number);
            }
        }

        if (nSessionTimeout != nOrgSessionTimeout)
        {
            varStatus = SETVARVALUE(UINT,
                                    AVCT_DM_DEFVARLIST,
                                    0,
                                    0,
                                    true,
                                    "s/WebGui/config/timeout",
                                    &varError,
                                    nSessionTimeout);
            if (AVCT_DM_VarListStatus_OK != varStatus)
            {
                rc.rc  = CMPI_RC_ERR_FAILED;
                goto EXIT;
            }


            bSessionTimeoutChange = TRUE;
            if (nSessionTimeout == 1)
                strncpy(sw_accseccfg.c_SessionTimeout, "1", sizeof(sw_accseccfg.c_SessionTimeout));
            else if (nSessionTimeout == 2)
                strncpy(sw_accseccfg.c_SessionTimeout, "5", sizeof(sw_accseccfg.c_SessionTimeout));
            else if (nSessionTimeout == 3)
                strncpy(sw_accseccfg.c_SessionTimeout, "10", sizeof(sw_accseccfg.c_SessionTimeout));
            else if (nSessionTimeout == 4)
                strncpy(sw_accseccfg.c_SessionTimeout, "15", sizeof(sw_accseccfg.c_SessionTimeout));
            else if (nSessionTimeout == 5)
                strncpy(sw_accseccfg.c_SessionTimeout, "20", sizeof(sw_accseccfg.c_SessionTimeout));
            else if (nSessionTimeout == 6)
                strncpy(sw_accseccfg.c_SessionTimeout, "none", sizeof(sw_accseccfg.c_SessionTimeout));
            else if (nSessionTimeout == 7)
                strncpy(sw_accseccfg.c_SessionTimeout, "user", sizeof(sw_accseccfg.c_SessionTimeout));
        }
    }/* End of InactivityTimeout and timeout method */

    if (!pm_provisioning_Is_security_provisioning_enabled())
    {
        /* 3. LoginFailureLockout */
        data = inst->ft->getProperty(inst, PROPERTYNAME_LoginFailureLockout, &rc);
        if((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
        {
            dataStr = CMPIData2String(&data); 
            if(dataStr == NULL)
            {
                CMPIDataRelease(&data);
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                return (rc);
            }
            p_tmp = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
            if (p_tmp==NULL)
            {
                SafeCMRelease(dataStr);
                CMPIDataRelease(&data);
                rc.rc  = CMPI_RC_ERR_FAILED;
                goto EXIT;
            }
            tmp_number = atoi(p_tmp);
            SafeCMRelease(dataStr);
            CMPIDataRelease(&data);
            //dataStr= NULL;
            if (tmp_number <0)
            {
                rc.rc  = CMPI_RC_ERR_INVALID_PARAMETER;
                goto EXIT;
            }

            aim_config_get_int("firewall_int_ip_block_fail_count", &nOrgFailCount);
            if (nOrgFailCount != tmp_number)
            {
                bResult = aim_config_set_int("firewall_int_ip_block_fail_count", tmp_number, TRUE);
                if(bResult==FALSE)
                {
                    rc.rc  = CMPI_RC_ERR_FAILED;
                    goto EXIT;
                }
            }
        }/* End of LoginFailureLockout */
        /* 4. LockoutPeriod */
        data = inst->ft->getProperty(inst, PROPERTYNAME_LockoutPeriod, &rc);
        if((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
        {
            dataStr = CMPIData2String(&data); 
            if(dataStr == NULL)
            {
                CMPIDataRelease(&data);
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                return (rc);
            }
            p_tmp = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
            if (p_tmp==NULL)
            {
                SafeCMRelease(dataStr);
                CMPIDataRelease(&data);
                rc.rc  = CMPI_RC_ERR_FAILED;
                goto EXIT;
            }
            tmp_number = atoi(p_tmp);
            SafeCMRelease(dataStr);
            CMPIDataRelease(&data);
            if ( tmp_number <0)
            {
                rc.rc  = CMPI_RC_ERR_INVALID_PARAMETER;
                goto EXIT;
            }
            
            aim_config_get_int("avct_int_lockout_time_period", &sw_tmp_number);
            if (tmp_number != sw_tmp_number)
            {
                sm_set_seclevel(SECURITY_LEVEL_CUSTOM);
                if(aim_config_set_int("avct_int_lockout_time_period", tmp_number, TRUE) == FALSE)
                {
                    rc.rc  = CMPI_RC_ERR_FAILED;
                    goto EXIT;
                }
                
                bLockoutPeriodChange = TRUE;
                sw_accseccfg.u32LockoutPeriod = tmp_number;            
            }
        }/* End of LoginFailureLockout */
    }
    
    rc.rc = CMPI_RC_OK;

    if (bAuthenticationMethodChange || bLockoutPeriodChange || bSessionTimeoutChange)
    {
        //printf("send a software event 98.\n");
        CMPIGetUserNameFromContext(ctx, sw_accseccfg.c_UserID);
        if (sw_msg_dispatcher(SW_MSGID_LOGIN_SETTINGS_CHANGED, (void *)&sw_accseccfg) != CEM_RC_OK)
        {
            printf("Fail to send a software event 98.\n");
        }
        //printf("send the event ends\n");
    }
    
EXIT:
    
#if IBM_LOGINSETTINGDATA_INIT_SUPPORT
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


/* IBM_LoginSettingData Class Service Function */
CMPIStatus Lenovo_LoginSettingDataService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_LoginSettingData,
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
            rc = IBM_LoginSettingData_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_LoginSettingData_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_LoginSettingData_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_LOGINSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_LoginSettingData_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_LOGINSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_LoginSettingData_InstAgent_Destroy;
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
            rc = IBM_LoginSettingData_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_LoginSettingData_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_LoginSettingData_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_LoginSettingData_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_LoginSettingData_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_LoginSettingData_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_LoginSettingData_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE: 
            va_start( argptr, op ); 																				
            inst = va_arg(argptr, CMPIInstance *);
            properties = va_arg(argptr, char **);
            rc = IBM_LoginSettingData_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end( argptr );
            break;
        case CLASS_SERVICE_INVOKEMETHOD: 
             /* involk method service */
        case CLASS_SERVICE_GETMETHODNAMES:
             /* get method name service */
        case CLASS_SERVICE_GETPARAMETERS:
             /* get method param name service */
        case CLASS_SERVICE_GETPROPERTY:   
            /* get property service */
        case CLASS_SERVICE_SETPROPERTY:   
            /* set property service */
        case CLASS_SERVICE_CREATEINSTANCE:
            /* create instance service */
        case CLASS_SERVICE_DELETEINSTANCE: 
            /* delete instance service */
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
GenNotSupportInstanceMICreateInstance(IBM_LoginSettingData);
//GenNotSupportInstanceMIModifyInstance(IBM_LoginSettingData);
GenNotSupportInstanceMIDeleteInstance(IBM_LoginSettingData);
GenNotSupportInstanceMIExecQuery(IBM_LoginSettingData);
GenNotSupportInstanceMICleanup(IBM_LoginSettingData);

/* MI factory function */
CMInstanceMIStub( IBM_LoginSettingData_,
                  Lenovo_LoginSettingData_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_LOGINSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_LoginSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_LoginSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LoginSettingData;\
    Arg.GetNextInstIndex = IBM_LoginSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_LoginSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_LoginSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_LoginSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LoginSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_LoginSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_LoginSettingData_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_LoginSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_LoginSettingData;\
    Arg.GetNextInstIndex = IBM_LoginSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_LoginSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_LoginSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_LoginSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LoginSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_LoginSettingData Class Service Function */
CMPIStatus Lenovo_LoginSettingDataService( 
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

/* Gets the Arg of Class IBM_LoginSettingData Function */
sClassUtilArg IBM_LoginSettingData_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_LOGINSETTINGDATA_ARG( Arg );

    return (Arg);
}

#endif
