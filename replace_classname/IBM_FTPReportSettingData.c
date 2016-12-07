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

/* IBM_FTPReportSettingData class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_FTPReportSettingData = (CMPIUint8 *)CLASSNAMETEXT_IBM_FTPReportSettingData;

/* Property List */
static const char * const IBM_FTPReportSettingDataPropertyList[] = 
{
    PROPERTYNAME_Address,
    PROPERTYNAME_AddressFormat,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_FTPPassword,
    PROPERTYNAME_FTPUserID,
    PROPERTYNAME_Port,
    PROPERTYNAME_ProtocolMode
};

/* Key property List */
static const char * const IBM_FTPReportSettingDataKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_FTPREPORTSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_FTPReportSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FTPReportSettingData;\
    Arg.GetKeyProperty = IBM_FTPReportSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_FTPReportSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_FTPReportSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_FTPReportSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_FTPReportSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_FTPReportSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FTPReportSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_FTPREPORTSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_FTPReportSettingDataAssociations;\
    Arg.AgentInit = IBM_FTPReportSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_FTPReportSettingData_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FTPReportSettingData;\
    Arg.GetKeyProperty = IBM_FTPReportSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_FTPReportSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_FTPReportSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_FTPReportSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_FTPReportSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_FTPReportSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FTPReportSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_FTPREPORTSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_FTPReportSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_FTPREPORTSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_FTPReportSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FTPReportSettingData;\
    Arg.GetKeyProperty = IBM_FTPReportSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_FTPReportSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_FTPReportSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_FTPReportSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_FTPReportSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_FTPReportSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FTPReportSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_FTPREPORTSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_FTPReportSettingDataAssociations;\
    Arg.AgentInit = IBM_FTPReportSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_FTPReportSettingData_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FTPReportSettingData;\
    Arg.GetKeyProperty = IBM_FTPReportSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_FTPReportSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_FTPReportSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_FTPReportSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_FTPReportSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_FTPReportSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FTPReportSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_FTPREPORTSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_FTPReportSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_FTPReportSettingData_GetProperty( 
                                               CMPICount nInstIndex,
                                               CMPICount nPropIndex,
                                               void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_FTPReportSettingData_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_FTPReportSettingData_GetKeyProperty( 
                                                  CMPICount nInstIndex,
                                                  CMPICount nKeyIndex,
                                                  void *pAgentDataPtr)
{
    CMPIData data = {CMPI_string, CMPI_badValue, {0}};
        data.state = CMPI_badValue;
    data = IBM_FTPReportSettingData_GetProperty(nInstIndex, nKeyIndex | IBM_FTPREPORTSETTINGDATA_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_FTPReportSettingData_GenerateObjectPath( 
                                                             char **properties,
                                                             CMPICount InstIndex,
                                                             void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_FTPReportSettingData_GetInstance( 
                                                 CMPIInstanceMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_FTPReportSettingData_EnumInstances( 
#else
CMPIStatus IBM_FTPReportSettingData_EnumerateInstances( 
#endif
                                                        CMPIInstanceMI *mi,
                                                        const CMPIContext *ctx,
                                                        const CMPIResult *rslt,
                                                        const CMPIObjectPath *op,
                                                        const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_FTPReportSettingData_EnumInstanceNames( 
#else
CMPIStatus IBM_FTPReportSettingData_EnumerateInstanceNames( 
#endif
                                                            CMPIInstanceMI *mi,
                                                            const CMPIContext *ctx,
                                                            const CMPIResult *rslt,
                                                            const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_FTPReportSettingData_Associators( 
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
    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_FTPReportSettingData_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_FTPReportSettingData_References( 
                                                CMPIAssociationMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char *resultClass,
                                                const char *role,
                                                const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_FTPReportSettingData_ReferenceNames( 
                                                    CMPIAssociationMI *mi,
                                                    const CMPIContext *ctx,
                                                    const CMPIResult *rslt,
                                                    const CMPIObjectPath *op,
                                                    const char *resultClass,
                                                    const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_FTPReportSettingData_ModifyInstance(
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
    pSACfgFileTransfer psOriginalData = NULL;
    UINT16 u16Value = 0;
    char szValue[255] = { 0 };
    unsigned int uiSize = 0;
    sSACfgFileTransfer sModifiedData;
    int iResult = 0;
    unsigned int uiReportingMethods = 0;
    char nameString[MAX_STR_LEN] = {0};
    UINT32 u32Role = 0;

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

    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg);
    
#if IBM_FTPREPORTSETTINGDATA_INIT_SUPPORT
    pAgentDataPtr = IBM_FTPReportSettingData_InstAgent_Init(0);
#endif

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_FTPReportSettingDataPropertyList))
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
        psOriginalData = (pSACfgFileTransfer) pAgentDataPtr;
    }

    if (SAcfg_get_uint(SA_CFG_UINT_REPORT_METHOD, &uiReportingMethods) != SA_CFG_STATUS_OK)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call SAcfg_get_uint(SA_CFG_UINT_REPORT_METHOD).", __FUNCTION__);
        goto CLEAN;
    }

    if (!(uiReportingMethods & 0x00000002))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Report to FTP is disabled.", __FUNCTION__);
        goto CLEAN;
    }
    
    if (SAcfg_IniConfigFileTransfer(&sModifiedData) != SA_CFG_STATUS_OK)
    {
        goto CLEAN;
    }

    /* get parameter ProtocolMode */
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_ProtocolMode, CMPI_uint16, &u16Value, NULL, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if ((u16Value > 4) || (1 == u16Value))
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto CLEAN;
        }
        else if (((u16Value != 0) && ((u16Value - 1) != psOriginalData->u32FileTransferProtocol)) ||
                ((0 == u16Value) && (psOriginalData->u32FileTransferProtocol != 0)))
        {
            if (0 == u16Value)
            {
                sModifiedData.u32FileTransferProtocol = 0;
            }
            else
            {
                sModifiedData.u32FileTransferProtocol = u16Value - 1;
            }
        }
            
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY
    
    /* get parameter Address */
    uiSize = 64;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_Address, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szFileTransferAddress) != 0)
        {
            snprintf(sModifiedData.szFileTransferAddress, sizeof(sModifiedData.szFileTransferAddress), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter AddressFormat */
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_AddressFormat, CMPI_uint16, &u16Value, NULL, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if ((u16Value > 4) || (1 == u16Value))
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto CLEAN;
        }
        else if (u16Value != psOriginalData->u32FileTransferFormat)
        {
            if (0 == u16Value)
            {
                sModifiedData.u32FileTransferFormat = 0;
            }
            else
            {
                sModifiedData.u32FileTransferFormat = u16Value;
            }
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter Port */
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_Port, CMPI_uint16, &u16Value, NULL, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (u16Value != psOriginalData->u32FileTransferPort)
        {
           sModifiedData.u32FileTransferPort = u16Value;
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter FTPUserID */
    uiSize = 64;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_FTPUserID, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strcmp(szValue, psOriginalData->szFileTransferUsername) != 0)
        {
            snprintf(sModifiedData.szFileTransferUsername, sizeof(sModifiedData.szFileTransferUsername), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter FTPPassword */
    uiSize = 64;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_FTPPassword, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if ((strcmp(szValue, PASSWORD_DISPALY_STR) != 0) &&
            (strcmp(szValue, psOriginalData->szFileTransferPassword) != 0))
        {
            snprintf(sModifiedData.szFileTransferPassword, sizeof(sModifiedData.szFileTransferPassword), "%s", szValue);
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    iResult = SAcfg_SetConfigFileTransfer(&sModifiedData);
    if (SA_CFG_STATUS_OK == iResult)
    {
        rc.rc = CMPI_RC_OK;    
    }
    else if ((iResult > SA_CFG_STATUS_OK) && (iResult < SA_CFG_STATUS_INVALID_PARAM))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        logTraceCIM(LOG_LEV_INFO, "%s()- Failed to call SAcfg_SetConfigFileTransfer(), return code is %d.", __FUNCTION__, iResult);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        logTraceCIM(LOG_LEV_INFO, "%s()- Failed to call SAcfg_SetConfigFileTransfer(), return code is %d.", __FUNCTION__, iResult);
    }

CLEAN:

#if IBM_FTPREPORTSETTINGDATA_INIT_SUPPORT
        IBM_FTPReportSettingData_InstAgent_Destroy(pAgentDataPtr);
#endif

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

/* IBM_FTPReportSettingData Class Service Function */
CMPIStatus Lenovo_FTPReportSettingDataService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_FTPReportSettingData,
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
            rc = IBM_FTPReportSettingData_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_FTPReportSettingData_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_FTPReportSettingData_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_FTPREPORTSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_FTPReportSettingData_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_FTPREPORTSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_FTPReportSettingData_InstAgent_Destroy;
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
            rc = IBM_FTPReportSettingData_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_FTPReportSettingData_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_FTPReportSettingData_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_FTPReportSettingData_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_FTPReportSettingData_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_FTPReportSettingData_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_FTPReportSettingData_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_FTPReportSettingData_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_FTPReportSettingData);
// GenNotSupportInstanceMIModifyInstance(IBM_FTPReportSettingData);
GenNotSupportInstanceMIDeleteInstance(IBM_FTPReportSettingData);
GenNotSupportInstanceMIExecQuery(IBM_FTPReportSettingData);
GenNotSupportInstanceMICleanup(IBM_FTPReportSettingData);

/* MI factory function */
CMInstanceMIStub( IBM_FTPReportSettingData_,
                  Lenovo_FTPReportSettingData_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_FTPREPORTSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_FTPReportSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_FTPReportSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FTPReportSettingData;\
    Arg.GetNextInstIndex = IBM_FTPReportSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_FTPReportSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_FTPReportSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_FTPReportSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FTPReportSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_FTPReportSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_FTPReportSettingData_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_FTPReportSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FTPReportSettingData;\
    Arg.GetNextInstIndex = IBM_FTPReportSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_FTPReportSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_FTPReportSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_FTPReportSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FTPReportSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_FTPReportSettingData Class Service Function */
CMPIStatus Lenovo_FTPReportSettingDataService( 
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

/* Gets the Arg of Class IBM_FTPReportSettingData Function */
sClassUtilArg IBM_FTPReportSettingData_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_FTPREPORTSETTINGDATA_ARG( Arg );

    return (Arg);
}

#endif
