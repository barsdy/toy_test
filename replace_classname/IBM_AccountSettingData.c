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
#include <emerson/pm/pm_lib.h>

#ifndef _BROKER_SFCB
#include "MethodNames.h"
#endif
/* Include class header files */
#include <RegisterClass.h>

/* Include agent header files */
#include <RegisterClassAgent.h>

#include "../AssociationTable.h"

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif


/* sm security setting */
#include <emerson/securitymgr/secsetting.h>
/* IBM_AccountSettingData class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_AccountSettingData = (CMPIUint8 *)CLASSNAMETEXT_IBM_AccountSettingData;

/* Property List */
static const char * const IBM_AccountSettingDataPropertyList[] = 
{
    PROPERTYNAME_ChangeableType,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_InactivityTimeout,
    PROPERTYNAME_MaximumPasswordExpiration,
    PROPERTYNAME_PasswordHistoryDepth,
    PROPERTYNAME_PasswordRequired,
    PROPERTYNAME_SecurityLevel
};

/* Key property List */
static const char * const IBM_AccountSettingDataKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_ACCOUNTSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_AccountSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AccountSettingData;\
    Arg.GetKeyProperty = IBM_AccountSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AccountSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AccountSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_AccountSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_AccountSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_AccountSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AccountSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ACCOUNTSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_AccountSettingDataAssociations;\
    Arg.AgentInit = IBM_AccountSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AccountSettingData_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AccountSettingData;\
    Arg.GetKeyProperty = IBM_AccountSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AccountSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AccountSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_AccountSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_AccountSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_AccountSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AccountSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ACCOUNTSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_AccountSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_ACCOUNTSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_AccountSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AccountSettingData;\
    Arg.GetKeyProperty = IBM_AccountSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AccountSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AccountSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_AccountSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_AccountSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_AccountSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AccountSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ACCOUNTSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_AccountSettingDataAssociations;\
    Arg.AgentInit = IBM_AccountSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AccountSettingData_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AccountSettingData;\
    Arg.GetKeyProperty = IBM_AccountSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_AccountSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_AccountSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_AccountSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_AccountSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_AccountSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AccountSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ACCOUNTSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_AccountSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_AccountSettingData_GetProperty( 
                                             CMPICount nInstIndex,
                                             CMPICount nPropIndex,
                                             void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_AccountSettingData_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_AccountSettingData_GetKeyProperty( 
                                                CMPICount nInstIndex,
                                                CMPICount nKeyIndex,
                                                void *pAgentDataPtr)
{
    CMPIData data;
        data.state = CMPI_badValue;
    data = IBM_AccountSettingData_GetProperty(nInstIndex, nKeyIndex | IBM_ACCOUNTSETTINGDATA_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_AccountSettingData_GenerateObjectPath( 
                                                           char **properties,
                                                           CMPICount InstIndex,
                                                           void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_AccountSettingData_GetInstance( 
                                               CMPIInstanceMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_AccountSettingData_EnumInstances( 
#else
CMPIStatus IBM_AccountSettingData_EnumerateInstances( 
#endif
                                                      CMPIInstanceMI *mi,
                                                      const CMPIContext *ctx,
                                                      const CMPIResult *rslt,
                                                      const CMPIObjectPath *op,
                                                      const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_AccountSettingData_EnumInstanceNames( 
#else
CMPIStatus IBM_AccountSettingData_EnumerateInstanceNames( 
#endif
                                                          CMPIInstanceMI *mi,
                                                          const CMPIContext *ctx,
                                                          const CMPIResult *rslt,
                                                          const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_AccountSettingData_Associators( 
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
    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_AccountSettingData_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_AccountSettingData_References( 
                                              CMPIAssociationMI *mi,
                                              const CMPIContext *ctx,
                                              const CMPIResult *rslt,
                                              const CMPIObjectPath *op,
                                              const char *resultClass,
                                              const char *role,
                                              const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_AccountSettingData_ReferenceNames( 
                                                  CMPIAssociationMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char *resultClass,
                                                  const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_AccountSettingData_CheckSelectorSet( 
                                                   const CMPIObjectPath *op,
                                                   CMPIBoolean bAllKey,
                                                   void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
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


/* PasswordRequired, MaximumPasswordExpiration, PasswordHistoryDepth  */
CMPIStatus IBM_AccountSettingData_ModifyInstance(
                                      CMPIInstanceMI *mi, 
                                      const CMPIContext *ctx, 
                                      const CMPIResult *rslt, 
                                      const CMPIObjectPath *op,
                                      const CMPIInstance * inst,
                                      const char **properties
                                      )
{
    CMPIStatus rc = {CMPI_RC_ERR_INVALID_PARAMETER, NULL};
    CMPICount instIndex=0;
    CMPIData data;
    CMPIString *dataStr = NULL;
    CMPIUint64 intervalTime = 0;
    CMPIBoolean bValue = CMPIFALSE;
    char tmp_string[128]={0};
    int tmp_number=0;
    char* p_tmp = NULL;
    int nResult =0;
    bool  bPasswordRequired =0;   /* true, false */
    short nExpirationDays=0;      /* (days) 0 ~ 356 */
    char  nPasswordReuseCycle =0; /*  0 ~ 5 */
    void* pAgentDataPtr  =NULL;
    SecuritySettings sSecSettings;    
    sClassUtilArg Arg;
    
    if (pm_provisioning_Is_security_provisioning_enabled())
    {
        rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg);
    
#if IBM_ACCOUNTSETTINGDATA_INIT_SUPPORT
    pAgentDataPtr = Arg.AgentInit(0);
#endif
    
    /* Check current instance */
    instIndex = IBM_AccountSettingData_CheckSelectorSet(op, CMPITRUE, pAgentDataPtr);
    if (instIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        return (rc);
    }
    
    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_AccountSettingDataPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        return (rc);
    }
    
    if (ctx == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        return (rc);
    }

    
    /* Get and check ChangeableType  */
    data = inst->ft->getProperty(inst,PROPERTYNAME_ChangeableType, &rc);
    if((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
    {
        dataStr = CMPIData2String(&data);
        CMPIDataRelease(&data);
        if(dataStr == NULL)
        {
           rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; 
           return (rc);
        } 
        p_tmp = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
        snprintf(tmp_string, sizeof(tmp_string), "%s", p_tmp);
        tmp_number = atoi(tmp_string);
        SafeCMRelease(dataStr);
        if(tmp_number != 2 ) /* Persistent */
        {
            rc.rc  = CMPI_RC_ERR_NOT_SUPPORTED; /* not changed */
            goto EXIT;
        }
    }
    
    /* Get PasswordRequired(Boolean) */
    data = inst->ft->getProperty(inst,PROPERTYNAME_PasswordRequired, &rc);
    if ((data.state == CMPI_goodValue) && (rc.rc == CMPI_RC_OK))
    {
        int iPolicyRequiredPW = -1;
        aim_config_get_int(POLICY_REQUIRED_PW, &iPolicyRequiredPW);
            
        bValue = CMPIData2Boolean(&data, &rc);  
        if((data.state != CMPI_goodValue) || (rc.rc != CMPI_RC_OK))
        {
            rc.rc  = CMPI_RC_ERR_FAILED;
            goto EXIT;
        }
        bPasswordRequired = (bValue == CMPITRUE);
        CMPIDataRelease(&data);        

        //check provisioning...
        if ((1 == iPolicyRequiredPW) && (false == bPasswordRequired))
        {
            rc.rc  = CMPI_RC_ERR_NOT_SUPPORTED;
            goto EXIT;
        }
    }


    /* Get MaximumPasswordExpiration (Datetime) */
    data = inst->ft->getProperty(inst,PROPERTYNAME_MaximumPasswordExpiration, &rc);
    if((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
    {
        if(data.type!=CMPI_dateTime)
        {
            rc.rc  = CMPI_RC_ERR_INVALID_PARAMETER; /* Invalid type */
            goto EXIT;

        }
        /* Check interval value =true */
        if((data.value.dateTime->ft->isInterval(data.value.dateTime, &rc)==CMPIFALSE)||(rc.rc != CMPI_RC_OK))
        {
            rc.rc  = CMPI_RC_ERR_INVALID_PARAMETER; /* Invalid type */
            goto EXIT;
        }
        /* Get binary value (micro-sec) */
        intervalTime = data.value.dateTime->ft->getBinaryFormat(data.value.dateTime, &rc);
        if(rc.rc!=CMPI_RC_OK)
        {
            rc.rc  = CMPI_RC_ERR_FAILED;
            goto EXIT;
        }
        nExpirationDays = intervalTime/((UINT64)1000000*60*60*24);
        if((nExpirationDays <0)||(nExpirationDays > 365))
        {
            rc.rc  = CMPI_RC_ERR_INVALID_PARAMETER;
            goto EXIT;
        }
        CMPIDataRelease(&data);        
    }

    /* Get PasswordHistoryDepth (UINT16) */
    data = inst->ft->getProperty(inst,PROPERTYNAME_PasswordHistoryDepth, &rc);
    if((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
    {
        dataStr = CMPIData2String(&data);   
        if(dataStr == NULL)
        {
           rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; 
           goto EXIT;

        } 
        p_tmp = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
        snprintf(tmp_string, sizeof(tmp_string), "%s", p_tmp);
        tmp_number = atoi(tmp_string);
        SafeCMRelease(dataStr);
        if((tmp_number <0)||(tmp_number>5))
        {
           rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; 
           goto EXIT;
        }
        nPasswordReuseCycle = (char)tmp_number;
        CMPIDataRelease(&data);        
    }
    
    /* invoke api */
    /* Get current setting */

    nResult = sm_get_secsettings(SECURITY_LEVEL_CUSTOM, &sSecSettings);
    if(nResult != 0)
    {
        rc.rc  = CMPI_RC_ERR_FAILED;
        goto EXIT;
    }
    
    sSecSettings.bPasswordRequired = bPasswordRequired;
    sSecSettings.nExpirationDays = nExpirationDays; 
    sSecSettings.nPasswordReuseCycle = nPasswordReuseCycle;
    nResult = sm_set_secsettings(SECURITY_LEVEL_CUSTOM, &sSecSettings);
    if(nResult != 0)
    {
        rc.rc  = CMPI_RC_ERR_FAILED;
        goto EXIT;
    }

    rc.rc = CMPI_RC_OK;
    goto EXIT;
     
EXIT:
    
    CMPIDataRelease(&data);
    
#if IBM_ACCOUNTSETTINGDATA_INIT_SUPPORT
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

/* IBM_AccountSettingData Class Service Function */
CMPIStatus Lenovo_AccountSettingDataService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_AccountSettingData,
                                     CIM_AccountSettingDataService);
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
            rc = IBM_AccountSettingData_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_AccountSettingData_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_AccountSettingData_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_ACCOUNTSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_AccountSettingData_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_ACCOUNTSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_AccountSettingData_InstAgent_Destroy;
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
            rc = IBM_AccountSettingData_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_AccountSettingData_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_AccountSettingData_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_AccountSettingData_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_AccountSettingData_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_AccountSettingData_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_AccountSettingData_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE: 
            /* modify instance service */
            va_start( argptr, op ); 																				
            inst = va_arg(argptr, CMPIInstance *);
            properties = va_arg(argptr, char **);
            rc = IBM_AccountSettingData_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_AccountSettingData);
//GenNotSupportInstanceMIModifyInstance(IBM_AccountSettingData);
GenNotSupportInstanceMIDeleteInstance(IBM_AccountSettingData);
GenNotSupportInstanceMIExecQuery(IBM_AccountSettingData);
GenNotSupportInstanceMICleanup(IBM_AccountSettingData);

/* MI factory function */
CMInstanceMIStub( IBM_AccountSettingData_,
                  Lenovo_AccountSettingData_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_ACCOUNTSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_AccountSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_AccountSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AccountSettingData;\
    Arg.GetNextInstIndex = IBM_AccountSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_AccountSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_AccountSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_AccountSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AccountSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_AccountSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_AccountSettingData_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_AccountSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_AccountSettingData;\
    Arg.GetNextInstIndex = IBM_AccountSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_AccountSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_AccountSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_AccountSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_AccountSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_AccountSettingData Class Service Function */
CMPIStatus Lenovo_AccountSettingDataService( 
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

/* Gets the Arg of Class IBM_AccountSettingData Function */
sClassUtilArg IBM_AccountSettingData_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_ACCOUNTSETTINGDATA_ARG( Arg );

    return (Arg);
}

#endif
