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
//For get user privilege
#include <emerson/securitymgr/sm.h>

#include <emerson/imm_sa/sa_cfg.h>
#include "LogUtil.h"

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_ServiceAdvisorService class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_ServiceAdvisorService = (CMPIUint8 *)CLASSNAMETEXT_IBM_ServiceAdvisorService;

/* Property List */
static const char * const IBM_ServiceAdvisorServicePropertyList[] =
{
    PROPERTYNAME_AgreementAccepted,
    PROPERTYNAME_AvailableNumberOfExclusionEvents,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EnabledReportingMethods,
    PROPERTYNAME_ExclusionEventList,
    PROPERTYNAME_ExternalServers,
    PROPERTYNAME_ThisSystemCallsHome
};

/* Key property List */
static const char * const IBM_ServiceAdvisorServiceKeyPropertyList[] =
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_SERVICEADVISORSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_ServiceAdvisorServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorService;\
    Arg.GetKeyProperty = IBM_ServiceAdvisorService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ServiceAdvisorService_GetProperty;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SERVICEADVISORSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_ServiceAdvisorServiceAssociations;\
    Arg.AgentInit = IBM_ServiceAdvisorService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ServiceAdvisorService_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorService;\
    Arg.GetKeyProperty = IBM_ServiceAdvisorService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ServiceAdvisorService_GetProperty;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SERVICEADVISORSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_ServiceAdvisorServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_SERVICEADVISORSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_ServiceAdvisorServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorService;\
    Arg.GetKeyProperty = IBM_ServiceAdvisorService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ServiceAdvisorService_GetProperty;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SERVICEADVISORSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_ServiceAdvisorServiceAssociations;\
    Arg.AgentInit = IBM_ServiceAdvisorService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ServiceAdvisorService_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorService;\
    Arg.GetKeyProperty = IBM_ServiceAdvisorService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ServiceAdvisorService_GetProperty;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SERVICEADVISORSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_ServiceAdvisorServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_ServiceAdvisorService_GetProperty(
                                                CMPICount nInstIndex,
                                                CMPICount nPropIndex,
                                                void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_ServiceAdvisorService_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_ServiceAdvisorService_GetKeyProperty(
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_ServiceAdvisorService, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_ServiceAdvisorService, &rc);
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
        data = IBM_ServiceAdvisorService_GetProperty(nInstIndex, nKeyIndex | IBM_SERVICEADVISORSERVICE_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_ServiceAdvisorService_GenerateObjectPath(
                                                              char **properties,
                                                              CMPICount InstIndex,
                                                              void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_ServiceAdvisorService_GetInstance(
                                                  CMPIInstanceMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ServiceAdvisorService_EnumInstances(
#else
CMPIStatus IBM_ServiceAdvisorService_EnumerateInstances(
#endif
                                                         CMPIInstanceMI *mi,
                                                         const CMPIContext *ctx,
                                                         const CMPIResult *rslt,
                                                         const CMPIObjectPath *op,
                                                         const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ServiceAdvisorService_EnumInstanceNames(
#else
CMPIStatus IBM_ServiceAdvisorService_EnumerateInstanceNames(
#endif
                                                             CMPIInstanceMI *mi,
                                                             const CMPIContext *ctx,
                                                             const CMPIResult *rslt,
                                                             const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_ServiceAdvisorService_Associators(
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
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_ServiceAdvisorService_AssociatorNames(
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
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_ServiceAdvisorService_References(
                                                 CMPIAssociationMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char *resultClass,
                                                 const char *role,
                                                 const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_ServiceAdvisorService_ReferenceNames(
                                                     CMPIAssociationMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op,
                                                     const char *resultClass,
                                                     const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_ServiceAdvisorService_ModifyInstance(
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
    SAServiceData *pSAServiceData = NULL;
    unsigned int uiSize = 0;
    UINT16 **apu16Value = NULL;
    char nameString[MAX_STR_LEN] = {0};
    UINT32 u32Role = 0;

    logTraceCIM(LOG_LEV_INFO, "%s()- Function entry.", __FUNCTION__);
    if ((inst == NULL) || (ctx == NULL))
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

    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);

    pAgentDataPtr = IBM_ServiceAdvisorService_InstAgent_Init(0);
    if (pAgentDataPtr == NULL)
    {
        return (rc);
    }

    pSAServiceData = (SAServiceData *) pAgentDataPtr;
    rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        goto CLEAN;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_ServiceAdvisorServicePropertyList))
    {
        goto CLEAN;
    }

    if ((!pSAServiceData->sServiceCfg.u32AcceptLicenseAgreement) || (!pSAServiceData->sServiceCfg.u32Enable))
    {
        logTraceCIM(LOG_LEV_INFO, "%s()- The license agreement is not accepted.", __FUNCTION__);
        rc.rc = CMPI_RC_ERR_FAILED;
        goto CLEAN;
    }

    /* get parameter EnabledReportingMethods */
    uiSize = 2;
    apu16Value = (UINT16 **) CIMClassUtil_GeneratePopertyValueArray(sizeof(UINT16), uiSize, __FUNCTION__);
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_EnabledReportingMethods, CMPI_uint16A, apu16Value, &uiSize, __FUNCTION__);
    if (CMPI_RC_OK == rc.rc)
    {
        int iSAResult = SA_CFG_STATUS_FAIL;
        sSACfgServiceData sCfg;

        iSAResult = SAcfg_IniConfigServiceData(&sCfg);
        if (iSAResult != SA_CFG_STATUS_OK)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SAcfg_IniConfigServiceData().", __FUNCTION__);
            rc.rc = CMPI_RC_ERR_FAILED;
        }
        else if ((uiSize > 2) || (uiSize < 1))
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        }
        else if ((1 == uiSize) && (0 == *(apu16Value[0])))
        {
            logTraceCIM(LOG_LEV_INFO, "%s()- It will disable all reporting methods.", __FUNCTION__);
            sCfg.u32EnableSupportCenter = 0;
            sCfg.u32EnableFileTransfer = 0;
        }
        else
        {
            int i = 0;
            
            sCfg.u32EnableSupportCenter = 0;
            sCfg.u32EnableFileTransfer = 0;

            while (i < uiSize)
            {
                if (2 == *(apu16Value[i]))  //Support Center
                {
                    if (SAcfg_CheckConfig(SA_CFG_RPT_SUPPORT_CENTER) & SA_CFG_RPT_SUPPORT_CENTER)
                    {
                        sCfg.u32EnableSupportCenter = 1;
                    }
                    else
                    {
                        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SAcfg_CheckConfig(SA_CFG_RPT_SUPPORT_CENTER).", __FUNCTION__);
                        rc.rc = CMPI_RC_ERR_FAILED;
                        break;
                    }
                }
                else if (3 == *(apu16Value[i]))  //FTP
                {
                    /* FTP do not need to check configurations. */
                    sCfg.u32EnableFileTransfer = 1;
                    
                    /*
                                                      if (SAcfg_CheckConfig(SA_CFG_RPT_FILE_TRANSFER) & SA_CFG_RPT_FILE_TRANSFER)
                                                      {
                                                          uiReportingMethods |= SA_CFG_RPT_FILE_TRANSFER;
                                                      }
                                                      else
                                                      {
                                                          logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SAcfg_CheckConfig(SA_CFG_RPT_FILE_TRANSFER).", __FUNCTION__);
                                                          rc.rc = CMPI_RC_ERR_FAILED;
                                                          break;
                                                      }
                                                      */
                }
                else
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- The value(%d) is not supported .", __FUNCTION__, *(apu16Value[i]));
                    rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
                    break;
                }
                i++;
            }
        }
        
        if (CMPI_RC_OK == rc.rc)
        {
            snprintf(sCfg.szUserID, sizeof(sCfg.szUserID), "%s", nameString);
            logTraceCIM(LOG_LEV_INFO, "%s()- Try to call SAcfg_SetConfigServiceData() by UserID(%s).", __FUNCTION__, sCfg.szUserID);

            iSAResult = SAcfg_SetConfigServiceData(&sCfg);
            if (iSAResult != SA_CFG_STATUS_OK)
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SAcfg_SetConfigServiceData(), error code is %d.", __FUNCTION__, iSAResult);
                rc.rc = CMPI_RC_ERR_FAILED;
            }
        }
    }
    else
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
    }
    CIMClassUtil_FreePopertyValueArray((void **) apu16Value, uiSize);

CLEAN:
    
    IBM_ServiceAdvisorService_InstAgent_Destroy(pAgentDataPtr);

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

CMPIStatus IBM_ServiceAdvisorService_InvokeMethod(
                                                   CMPIMethodMI *mi,
                                                   const CMPIContext *ctx,
                                                   const CMPIResult *rslt,
                                                   const CMPIObjectPath *op,
                                                   const char *method,
                                                   const CMPIArgs *in,
                                                   CMPIArgs *out)
{
    CMPIValue value;
    CMPIValue cUserIDValue;
    CMPIStatus rc =
    {
        CMPI_RC_OK,
        NULL
    };
    
    char nameString[MAX_STR_LEN] = {0};
    UINT32 u32Role = 0;
        
    CMPICount nIndex = 0;
    void *pAgentDataPtr = NULL;

    sClassUtilArg Arg;
    char szNameString[64] = {0};

    cUserIDValue.string = NULL;
    
    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg);
    
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
    
    pAgentDataPtr = IBM_ServiceAdvisorService_InstAgent_Init(0);

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (nIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    memset(&value, 0, sizeof(CMPIValue));
    CMPIGetUserNameFromContext(ctx, szNameString);
#ifdef _BROKER_SFCB
    cUserIDValue.string = CMNewString(GET_BROKER_PTR, szNameString, &rc);
#else
    cUserIDValue.string = CMPIStringAllocate(szNameString, &rc);
#endif
    if((rc.rc != CMPI_RC_OK) || (cUserIDValue.string == NULL))
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        printf("Can't new a string for userID\n");
        goto CLEAN;
    }

    rc = in->ft->addArg(in, SYS_USER_ID, &cUserIDValue, CMPI_string);
    if(rc.rc != CMPI_RC_OK)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        printf("Can't add userID in Arg\n");
        goto CLEAN;
    }

    /* invoke method */
    if (0 == strcmp(method, "AcceptAgreement"))
    {
        value.uint32 = IBM_ServiceAdvisorService_InstAgent_AcceptAgreement((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "AddExclusionEvents"))
    {
        value.uint32 = IBM_ServiceAdvisorService_InstAgent_AddExclusionEvents((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "CallHomeStateChange"))
    {
        value.uint32 = IBM_ServiceAdvisorService_InstAgent_CallHomeStateChange((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "ManualCallHome"))
    {
        value.uint32 = IBM_ServiceAdvisorService_InstAgent_ManualCallHome((UINT32) nIndex, ctx, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "RemoveExclusionEvents"))
    {
        value.uint32 = IBM_ServiceAdvisorService_InstAgent_RemoveExclusionEvents((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "TestCallHome"))
    {
        value.uint32 = IBM_ServiceAdvisorService_InstAgent_TestCallHome((UINT32) nIndex, ctx, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_METHOD_NOT_FOUND;
    }

CLEAN:
    
    SafeCMRelease(cUserIDValue.string);

	IBM_ServiceAdvisorService_InstAgent_Destroy(pAgentDataPtr);

    return (rc);
}

#ifndef _BROKER_SFCB
CMPIData *IBM_ServiceAdvisorService_GetMethodName()
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
    value.chars = (char *) METHODNAME_AcceptAgreement;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_AddExclusionEvents;
    nameArray->ft->setElementAt(nameArray, 1, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_CallHomeStateChange;
    nameArray->ft->setElementAt(nameArray, 2, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_ManualCallHome;
    nameArray->ft->setElementAt(nameArray, 3, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_RemoveExclusionEvents;
    nameArray->ft->setElementAt(nameArray, 4, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_TestCallHome;
    nameArray->ft->setElementAt(nameArray, 5, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

CMPIData *IBM_ServiceAdvisorService_GetMethodParameters(const char * MethodName)
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

    if (0 == strcmp(MethodName, METHODNAME_AcceptAgreement))
    {
        iMethID = 0;
    }
    else if (0 == strcmp(MethodName, METHODNAME_AddExclusionEvents))
    {
        iMethID = 1;
    }
    else if (0 == strcmp(MethodName, METHODNAME_CallHomeStateChange))
    {
        iMethID = 2;
    }
    else if (0 == strcmp(MethodName, METHODNAME_ManualCallHome))
    {
        iMethID = 3;
    }
    else if (0 == strcmp(MethodName, METHODNAME_RemoveExclusionEvents))
    {
        iMethID = 4;
    }
    else if (0 == strcmp(MethodName, METHODNAME_TestCallHome))
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
            break;

        case 1:
            value.chars = "A string";
            pArgs->ft->addArg(pArgs, PARAMNAME_EventIDs,&value,CMPI_chars);
            break;

        case 2:
            value.chars = (char *) TYPENAME_uint16;
            pArgs->ft->addArg(pArgs, PARAMNAME_RequestedState,&value,CMPI_chars);
            value.chars = "A uint8";
            pArgs->ft->addArg(pArgs, PARAMNAME_ExternalServers,&value,CMPI_chars);
            break;

        case 3:
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ProblemDescription,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ProblemArea,&value,CMPI_chars);
            break;

        case 4:
            value.chars = "A string";
            pArgs->ft->addArg(pArgs, PARAMNAME_EventIDs,&value,CMPI_chars);
            break;

        case 5:
            break;

    }

    data->value.args = pArgs;
    data->type = CMPI_args;
    data->state = CMPI_goodValue;
    return (data);
}
#endif

/* IBM_ServiceAdvisorService Class Service Function */
CMPIStatus Lenovo_ServiceAdvisorServiceService(
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
                                     (char *) CLASSNAME_Lenovo_IBM_ServiceAdvisorService,
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
            rc = IBM_ServiceAdvisorService_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_ServiceAdvisorService_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_ServiceAdvisorService_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_SERVICEADVISORSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_ServiceAdvisorService_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_SERVICEADVISORSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_ServiceAdvisorService_InstAgent_Destroy;
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
            rc = IBM_ServiceAdvisorService_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_ServiceAdvisorService_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ServiceAdvisorService_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ServiceAdvisorService_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH:
            rc.msg = (void*) &IBM_ServiceAdvisorService_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX:
            rc.msg = (void*) &IBM_ServiceAdvisorService_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX:
            rc.msg = (void*) &IBM_ServiceAdvisorService_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_ServiceAdvisorService_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_ServiceAdvisorService_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_ServiceAdvisorService_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_ServiceAdvisorService_GetMethodParameters(method);
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
GenNotSupportInstanceMICreateInstance(IBM_ServiceAdvisorService);
// GenNotSupportInstanceMIModifyInstance(IBM_ServiceAdvisorService);
GenNotSupportInstanceMIDeleteInstance(IBM_ServiceAdvisorService);
GenNotSupportInstanceMIExecQuery(IBM_ServiceAdvisorService);
GenNotSupportInstanceMICleanup(IBM_ServiceAdvisorService);

/* MI factory function */
CMInstanceMIStub( IBM_ServiceAdvisorService_,
                  Lenovo_ServiceAdvisorService_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_ServiceAdvisorService);

CMMethodMIStub( IBM_ServiceAdvisorService_,
                Lenovo_ServiceAdvisorService_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_SERVICEADVISORSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_ServiceAdvisorServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ServiceAdvisorService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorService;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_ServiceAdvisorService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ServiceAdvisorService_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ServiceAdvisorService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ServiceAdvisorService;\
    Arg.GetNextInstIndex = IBM_ServiceAdvisorService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ServiceAdvisorServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ServiceAdvisorServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ServiceAdvisorServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ServiceAdvisorServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_ServiceAdvisorService Class Service Function */
CMPIStatus Lenovo_ServiceAdvisorServiceService( 
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

/* Gets the Arg of Class IBM_ServiceAdvisorService Function */
sClassUtilArg IBM_ServiceAdvisorService_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_SERVICEADVISORSERVICE_ARG( Arg );

    return (Arg);
}

#endif
