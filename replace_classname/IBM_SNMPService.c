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
#include <emerson/aim/libaim.h>
#include <emerson/pm/pm_lib.h>

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

#include <emerson/ab/avct_dm_ADAMLib.h>
#include <emerson/ab/avct_dm_VarList.h>

#include <emerson/ab/avct_SharedMem.h>
#include <emerson/ab/avct_SharedList.h>

/* IBM_SNMPService class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_SNMPService = (CMPIUint8 *)CLASSNAMETEXT_IBM_SNMPService;

/* Property List */
static const char * const IBM_SNMPServicePropertyList[] = 
{
    PROPERTYNAME_Contact,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EnabledSNMPVersions,
    PROPERTYNAME_Location,
    PROPERTYNAME_TrapsEnabled
};

/* Key property List */
static const char * const IBM_SNMPServiceKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_SNMPSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_SNMPServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPService;\
    Arg.GetKeyProperty = IBM_SNMPService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPService_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPServiceKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPServiceAssociations;\
    Arg.AgentInit = IBM_SNMPService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SNMPService_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPService;\
    Arg.GetKeyProperty = IBM_SNMPService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPService_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPServiceKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_SNMPSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_SNMPServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPService;\
    Arg.GetKeyProperty = IBM_SNMPService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPService_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPServiceKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPServiceAssociations;\
    Arg.AgentInit = IBM_SNMPService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SNMPService_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPService;\
    Arg.GetKeyProperty = IBM_SNMPService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPService_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPServiceKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_SNMPService_GetProperty( 
                                      CMPICount nInstIndex,
                                      CMPICount nPropIndex,
                                      void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_SNMPService_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_SNMPService_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_SNMPService, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_SNMPService, &rc);
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
        data = IBM_SNMPService_GetProperty(nInstIndex, nKeyIndex | IBM_SNMPSERVICE_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_SNMPService_GenerateObjectPath( 
                                                    char **properties,
                                                    CMPICount InstIndex,
                                                    void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_SNMPService_GetInstance( 
                                        CMPIInstanceMI *mi,
                                        const CMPIContext *ctx,
                                        const CMPIResult *rslt,
                                        const CMPIObjectPath *op,
                                        const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SNMPService_EnumInstances( 
#else
CMPIStatus IBM_SNMPService_EnumerateInstances( 
#endif
                                               CMPIInstanceMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SNMPService_EnumInstanceNames( 
#else
CMPIStatus IBM_SNMPService_EnumerateInstanceNames( 
#endif
                                                   CMPIInstanceMI *mi,
                                                   const CMPIContext *ctx,
                                                   const CMPIResult *rslt,
                                                   const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_SNMPService_Associators( 
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
    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_SNMPService_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_SNMPService_References( 
                                       CMPIAssociationMI *mi,
                                       const CMPIContext *ctx,
                                       const CMPIResult *rslt,
                                       const CMPIObjectPath *op,
                                       const char *resultClass,
                                       const char *role,
                                       const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_SNMPService_ReferenceNames( 
                                           CMPIAssociationMI *mi,
                                           const CMPIContext *ctx,
                                           const CMPIResult *rslt,
                                           const CMPIObjectPath *op,
                                           const char *resultClass,
                                           const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_SNMPService_CheckSelectorSet( 
                                            const CMPIObjectPath *op,
                                            CMPIBoolean bAllKey,
                                            void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);
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



/* ModifyInstance shall only modify the following properties: ElementName, EnabledSNMPVersions, TrapsEnabled, Contact, and Location. */
/* Current contact and location use imm's shared info , deny to modify it                                                                                             */
CMPIStatus IBM_SNMPService_ModifyInstance(
                                      CMPIInstanceMI *mi, 
                                      const CMPIContext *ctx, 
                                      const CMPIResult *rslt, 
                                      const CMPIObjectPath *op,
                                      const CMPIInstance * inst,
                                      const char **properties
                                      )
{
    sClassUtilArg Arg;   
    CMPIStatus rc = {CMPI_RC_ERR_INVALID_PARAMETER, NULL};
    CMPICount instIndex = 0;
    CMPICount nCount2 = 0;
    CMPIData data;
    char szTmpStr[64] = {0};
    char szLocation[64] = {0};
    char szContact[64] = {0};
    char *pTmpStr = NULL;
    int iLen = 0;  
    CMPIString *dataStr = NULL;
    UINT16 EnabledSNMPVersions = 0;
    int EnabledSNMPVersion = 0;
    int bTrapEnabled = 0;    
    CMPIArray *arrayEnabledSNMPVersions = NULL;
    int i = 0;
    AVCT_DM_VarListStatus varStatus;
    AVCT_DM_VarListError varError;
    char swe_username[MAX_STR_LEN] = {0};
    void *pAgentDataPtr = NULL;
    PAVCT_DM_VARLIST snmpVars;
    const char* as_SnmpVarsToUpdate[] = {"s/snmp", "s/Server_Info", NULL};
    int iPolicyLDAPOnly = -1;

    if (inst == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        return (rc);
    }

    varStatus = avct_dm_GetUpdatableVars(
                    "myCfgVars",
                    0, 0, false,
                    as_SnmpVarsToUpdate,
                    &snmpVars,
                    &varError);
    
    if (AVCT_DM_VarListError_OK != varStatus)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg);

#if IBM_SNMPSERVICE_INIT_SUPPORT
    pAgentDataPtr = Arg.AgentInit(0);
#endif

    /* Check SelectorSet */
    instIndex = IBM_SNMPService_CheckSelectorSet(op, CMPITRUE, pAgentDataPtr);
    if (instIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        return (rc);
    }


    /* Get input properties : ElementName, EnabledSNMPVersions,TrapsEnabled */    
    /* Contact */
    data = inst->ft->getProperty(inst,"Contact", &rc);
    if ((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
    {
    //printf("get contact -->\n");    
        dataStr = CMPIData2String(&data);
        if(dataStr == NULL)
        {
            CMPIDataRelease(&data);
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto EXIT;
        }
        pTmpStr = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
        iLen = strlen(pTmpStr);
        memset(szContact, 0, sizeof (szContact));
        if(iLen > 48)
        {
            CMPIDataRelease(&data);
             rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* invalid size */
             goto EXIT;
        }
        strncpy(szContact, pTmpStr, iLen);
        /* Before set value,  lock the namespace IMM_Information / snmp */
        /* set the value */
        varStatus = SETVARVALUE(STRING,
                                snmpVars,
                                0,
                                0,
                                false,
                                VAR_SYSTEM_CONTACT,
                                &varError,
                                szContact);
        if( varStatus != AVCT_DM_VarListStatus_OK) /* failed */
        {
            CMPIDataRelease(&data);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto EXIT;
        }
        rc.rc = CMPI_RC_OK;
        /* CMPI Data Release */
        SafeCMRelease(dataStr);
        dataStr = NULL;
        CMPIDataRelease(&data);
    //printf("get contact okay\n");            
     }
    
    /* Location */
    data = inst->ft->getProperty(inst,"Location", &rc);
    if ((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
    {
    //printf("get location -->\n");            
        dataStr = CMPIData2String(&data);
        if(dataStr == NULL)
        {
            CMPIDataRelease(&data);
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto EXIT;
        }
        pTmpStr = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
        iLen = strlen(pTmpStr);
        memset(szLocation, 0, sizeof (szLocation));
        if(iLen > 48)
        {
             CMPIDataRelease(&data);
             rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* invalid size */
             goto EXIT;
        }
        strncpy(szLocation, pTmpStr, iLen);
        /* Before set value,  lock the namespace IMM_Information / snmp */
        /* set the value */
        varStatus = SETVARVALUE(STRING,
                                snmpVars,
                                0,
                                0,
                                false,
                                VAR_SYSTEM_LOCATION,
                                &varError,
                                szLocation);
        if( varStatus != AVCT_DM_VarListStatus_OK) /* failed */
        {
            CMPIDataRelease(&data);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto EXIT;
        }
        rc.rc = CMPI_RC_OK;
        /* CMPI Data Release */
        SafeCMRelease(dataStr);
        dataStr = NULL;
        CMPIDataRelease(&data);
        //printf("get location okay\n");                    
     }

    aim_config_get_int(POLICY_LDAP_ONLY, &iPolicyLDAPOnly);    
    if ((!pm_provisioning_Is_ProvisioningPhase3_enabled()) || (iPolicyLDAPOnly != 1))
    {    
        /* EnabledSNMPVersions */
        data = inst->ft->getProperty(inst,"EnabledSNMPVersions", &rc);
        if ((data.state == CMPI_goodValue) && (rc.rc== CMPI_RC_OK))
        {
            //printf("get enableSNMPVersion -->\n");                    
            arrayEnabledSNMPVersions = (&data)->value.array;
            nCount2= arrayEnabledSNMPVersions->ft->getSize(arrayEnabledSNMPVersions,&rc);

            //printf("count : %d\n", nCount2);
            for(i=0;i < (int)nCount2; i++)
            {
                EnabledSNMPVersion = arrayEnabledSNMPVersions->ft->getElementAt(arrayEnabledSNMPVersions,i,&rc).value.uint16;
                if (EnabledSNMPVersion == 2)
                {
                    int iProvisioning = 0;
                    bool iResult = FALSE;
                    
                    //Check provisioning 210
                    iResult = aim_config_get_int(POLICY_DISABLE_SNMPV1, &iProvisioning);
                    if ((TRUE == iResult) && (1 == iProvisioning))
                    {
                        printf("[%s] Operate the SNMPV1 is blocked by provisioning(%s):%d.\n", __FUNCTION__, POLICY_DISABLE_SNMPV1, iProvisioning);
                        rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
                        CMPIDataRelease(&data);
                        goto EXIT;
                    }
                   
                    EnabledSNMPVersions |= SNMP_V1_SUPPORTED;
                }
                else if (EnabledSNMPVersion == 4)
                {
                    EnabledSNMPVersions |= SNMP_V3_SUPPORTED;
                }
                else if (EnabledSNMPVersion == 0) // disable snmp v1 and snmp v3
                {
                    EnabledSNMPVersion = 0;
                    break;
                }
                else
                {
                    CMPIDataRelease(&data);
                    rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                    goto EXIT;
                }
            }
            
            //printf("version %d\n", EnabledSNMPVersions);
            if (EnabledSNMPVersions > 0)
            {
                if (Stricmp(szContact, "") == 0 || Stricmp(szLocation, "") == 0)
                {
                    CMPIDataRelease(&data);
                    rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                    goto EXIT;                
                }
            }
            
            varStatus = SETVARVALUE(BOOL,
                                    snmpVars,
                                    0, 0, false,
                                    VAR_SNMPV1_ENABLE,
                                    &varError,
                                    (EnabledSNMPVersions & SNMP_V1_SUPPORTED) ? TRUE : FALSE);            
            
            if(varStatus != AVCT_DM_VarListStatus_OK)
            {
                CMPIDataRelease(&data);
                rc.rc = CMPI_RC_ERR_FAILED ;        
                goto EXIT;
            }
            
            varStatus = SETVARVALUE(BOOL,
                                    snmpVars,
                                    0, 0, false,
                                    VAR_SNMPV3_ENABLE,
                                    &varError,
                                    (EnabledSNMPVersions & SNMP_V3_SUPPORTED) ? TRUE : FALSE);

            if(varStatus != AVCT_DM_VarListStatus_OK)
            {
                CMPIDataRelease(&data);
                rc.rc = CMPI_RC_ERR_FAILED ;        
                goto EXIT;
            }
            
            CMPIDataRelease(&data);
            rc.rc = CMPI_RC_OK;

            //printf("get enableSNMPVersion okay\n");                            
       }
   }
    
   /* ElementName */
   data = inst->ft->getProperty(inst,"ElementName", &rc);
   if ((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
   {
       //printf(" get ElementName -->\n");                               
       dataStr = CMPIData2String(&data);   
       if(dataStr == NULL)
       {
           CMPIDataRelease(&data);
           rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; 
           goto EXIT;
       }
       pTmpStr = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
       iLen = strlen(pTmpStr);
       memset(szTmpStr, 0, sizeof (szTmpStr));
       if(iLen > 47)
       {
            CMPIDataRelease(&data);
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* invalid size */
            goto EXIT;
       }
       strncpy(szTmpStr, pTmpStr, iLen);
       /* Before set value,  lock the namespace IMM_Information / snmp */

       /* set the value */
       varStatus = SETVARVALUE(STRING,
                               snmpVars,
                               0,
                               0,
                               false,
                               VAR_SNMP_SERVICE_NAME,
                               &varError,
                               szTmpStr);
       if( varStatus != AVCT_DM_VarListStatus_OK) /* failed */
       {
           CMPIDataRelease(&data);
           rc.rc = CMPI_RC_ERR_FAILED;
           goto EXIT;
       }

       rc.rc = CMPI_RC_OK;
       /* CMPI Data Release */
       SafeCMRelease(dataStr);
       dataStr = NULL;
       CMPIDataRelease(&data);
       //printf("get ElementName okay\n");                                      
    }

   /* 5.TrapsEnabled */
   data = inst->ft->getProperty(inst,"TrapsEnabled", &rc);
   if ((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
   {
       //printf("get TrapEnabled -->\n");                                     

       bTrapEnabled =(int) CMPIData2Boolean(&data,&rc);
       if(rc.rc !=CMPI_RC_OK)
       {
           CMPIDataRelease(&data);
           rc.rc = CMPI_RC_ERR_FAILED;
           goto EXIT;
       }
       varStatus = SETVARVALUE(BOOL,
                               snmpVars,
                               0,
                               0,                     /* CMOHandle of the user */
                               false,
                               VAR_SNMP_TRAP_ENABLED, /* v1 */
                               &varError,
                               bTrapEnabled);
       
       if(varStatus != AVCT_DM_VarListStatus_OK)
       {
           /* failed to set adam var */
           CMPIDataRelease(&data);
           rc.rc = CMPI_RC_ERR_FAILED;
           goto EXIT;
       }
       rc.rc = CMPI_RC_OK;
       CMPIDataRelease(&data);
       //printf("get TrapEnabled okay\n");                                            
   }

   /* Set username for software event 73, 74 */
   CMPIGetUserNameFromContext(ctx, swe_username);
   if (AVCT_DM_VarListError_OK == varError) 
   {
       varStatus = SETVARVALUE(STRING,
                               snmpVars,
                               0, 0, false,
                               VAR_SNMP_SWE_USERNAME,
                               &varError,
                               swe_username);
   }
   /* failed to set adam var */
   if (AVCT_DM_VarListError_OK != varError) 
       rc.rc = CMPI_RC_ERR_FAILED;

   varStatus = avct_dm_UpdateVars(snmpVars, 0, 0, false, &varError);    
   if (varStatus != AVCT_DM_VarListStatus_OK) 
   {
        printf("fail to update value in the var list.\n");
        rc.rc = CMPI_RC_ERR_FAILED;
   }

   EXIT:

    SafeCMRelease(dataStr);

#if IBM_SNMPSERVICE_INIT_SUPPORT
    Arg.AgentDestroy(pAgentDataPtr);
#endif

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}/* End of IBM_SNMPService_ModifyInstance */


/* IBM_SNMPService Class Service Function */
CMPIStatus Lenovo_SNMPServiceService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_SNMPService,
                                     CIM_SNMPServiceService);
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
            rc = IBM_SNMPService_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_SNMPService_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_SNMPService_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_SNMPSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_SNMPService_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_SNMPSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_SNMPService_InstAgent_Destroy;
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
            rc = IBM_SNMPService_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_SNMPService_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SNMPService_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SNMPService_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_SNMPService_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_SNMPService_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_SNMPService_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE: 
            va_start( argptr, op );                                                                                 
            inst = va_arg(argptr, CMPIInstance *);
            properties = (char **)  va_arg(argptr,  char **);
            rc = IBM_SNMPService_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_SNMPService);
//GenNotSupportInstanceMIModifyInstance(IBM_SNMPService);
GenNotSupportInstanceMIDeleteInstance(IBM_SNMPService);
GenNotSupportInstanceMIExecQuery(IBM_SNMPService);
GenNotSupportInstanceMICleanup(IBM_SNMPService);

/* MI factory function */
CMInstanceMIStub( IBM_SNMPService_,
                  Lenovo_SNMPService_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_SNMPSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_SNMPServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SNMPService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPService;\
    Arg.GetNextInstIndex = IBM_SNMPService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SNMPServiceKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_SNMPService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SNMPService_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SNMPService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPService;\
    Arg.GetNextInstIndex = IBM_SNMPService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SNMPServiceKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_SNMPService Class Service Function */
CMPIStatus Lenovo_SNMPServiceService( 
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

/* Gets the Arg of Class IBM_SNMPService Function */
sClassUtilArg IBM_SNMPService_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_SNMPSERVICE_ARG( Arg );

    return (Arg);
}

#endif
