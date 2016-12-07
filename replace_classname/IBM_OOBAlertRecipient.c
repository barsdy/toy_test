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

#include <emerson/imm_alertmgr/alertmgr_lib.h>

#include <SmashCommonUtil.h>
/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

#include "incEX/IBM_OOBAlertRecipient.h"

/* IBM_OOBAlertRecipient class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_OOBAlertRecipient = (CMPIUint8 *)CLASSNAMETEXT_IBM_OOBAlertRecipient;

/* Property List */
static const char * const IBM_OOBAlertRecipientPropertyList[] = 
{
    PROPERTYNAME_AlertType,
    PROPERTYNAME_Caption,
    PROPERTYNAME_DestinationAddress,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EmailAddress,
    PROPERTYNAME_EnabledState,
    PROPERTYNAME_IncludeEventLog
};

/* Key property List */
static const char * const IBM_OOBAlertRecipientKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_OOBALERTRECIPIENT_INIT_SUPPORT /* You can turn on this flag in IBM_OOBAlertRecipientAgent.h */
#define PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBAlertRecipient;\
    Arg.GetKeyProperty = IBM_OOBAlertRecipient_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_OOBAlertRecipient_InstAgent_GetNext;\
    Arg.GetProperty = IBM_OOBAlertRecipient_GetProperty;\
    Arg.KeyPropertyList = IBM_OOBAlertRecipientKeyPropertyList;\
    Arg.PropertyList = IBM_OOBAlertRecipientPropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBAlertRecipientPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBAlertRecipientKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_OOBALERTRECIPIENTASSONUM;\
    Arg.AssocArray = G_sLenovo_OOBAlertRecipientAssociations;\
    Arg.AgentInit = IBM_OOBAlertRecipient_InstAgent_Init;\
    Arg.AgentDestroy = IBM_OOBAlertRecipient_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBAlertRecipient;\
    Arg.GetKeyProperty = IBM_OOBAlertRecipient_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_OOBAlertRecipient_InstAgent_GetNext;\
    Arg.GetProperty = IBM_OOBAlertRecipient_GetProperty;\
    Arg.KeyPropertyList = IBM_OOBAlertRecipientKeyPropertyList;\
    Arg.PropertyList = IBM_OOBAlertRecipientPropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBAlertRecipientPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBAlertRecipientKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_OOBALERTRECIPIENTASSONUM;\
    Arg.AssocArray = G_sLenovo_OOBAlertRecipientAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_OOBALERTRECIPIENT_INIT_SUPPORT /* You can turn on this flag in IBM_OOBAlertRecipientAgent.h */
#define PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBAlertRecipient;\
    Arg.GetKeyProperty = IBM_OOBAlertRecipient_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_OOBAlertRecipient_InstAgent_GetNext;\
    Arg.GetProperty = IBM_OOBAlertRecipient_GetProperty;\
    Arg.KeyPropertyList = IBM_OOBAlertRecipientKeyPropertyList;\
    Arg.PropertyList = IBM_OOBAlertRecipientPropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBAlertRecipientPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBAlertRecipientKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_OOBALERTRECIPIENTASSONUM;\
    Arg.AssocArray = G_sLenovo_OOBAlertRecipientAssociations;\
    Arg.AgentInit = IBM_OOBAlertRecipient_InstAgent_Init;\
    Arg.AgentDestroy = IBM_OOBAlertRecipient_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBAlertRecipient;\
    Arg.GetKeyProperty = IBM_OOBAlertRecipient_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_OOBAlertRecipient_InstAgent_GetNext;\
    Arg.GetProperty = IBM_OOBAlertRecipient_GetProperty;\
    Arg.KeyPropertyList = IBM_OOBAlertRecipientKeyPropertyList;\
    Arg.PropertyList = IBM_OOBAlertRecipientPropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBAlertRecipientPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBAlertRecipientKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_OOBALERTRECIPIENTASSONUM;\
    Arg.AssocArray = G_sLenovo_OOBAlertRecipientAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_OOBAlertRecipient_GetProperty( 
                                            CMPICount nInstIndex,
                                            CMPICount nPropIndex,
                                            void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_OOBAlertRecipient_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_OOBAlertRecipient_GetKeyProperty( 
                                               CMPICount nInstIndex,
                                               CMPICount nKeyIndex,
                                               void *pAgentDataPtr)
{
    CMPIData data = {CMPI_string, CMPI_badValue, {0}};
        data.state = CMPI_badValue;
    data = IBM_OOBAlertRecipient_GetProperty(nInstIndex, nKeyIndex | IBM_OOBALERTRECIPIENT_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_OOBAlertRecipient_GenerateObjectPath( 
                                                          char **properties,
                                                          CMPICount InstIndex,
                                                          void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_OOBAlertRecipient_GetInstance( 
                                              CMPIInstanceMI *mi,
                                              const CMPIContext *ctx,
                                              const CMPIResult *rslt,
                                              const CMPIObjectPath *op,
                                              const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_OOBAlertRecipient_EnumInstances( 
#else
CMPIStatus IBM_OOBAlertRecipient_EnumerateInstances( 
#endif
                                                     CMPIInstanceMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op,
                                                     const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_OOBAlertRecipient_EnumInstanceNames( 
#else
CMPIStatus IBM_OOBAlertRecipient_EnumerateInstanceNames( 
#endif
                                                         CMPIInstanceMI *mi,
                                                         const CMPIContext *ctx,
                                                         const CMPIResult *rslt,
                                                         const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_OOBAlertRecipient_Associators( 
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
    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_OOBAlertRecipient_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_OOBAlertRecipient_References( 
                                             CMPIAssociationMI *mi,
                                             const CMPIContext *ctx,
                                             const CMPIResult *rslt,
                                             const CMPIObjectPath *op,
                                             const char *resultClass,
                                             const char *role,
                                             const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_OOBAlertRecipient_ReferenceNames( 
                                                 CMPIAssociationMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char *resultClass,
                                                 const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_OOBAlertRecipient_ModifyInstance(
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

    CMPIData data;
    CMPIString *dataStr = NULL;
    char *szBuf = NULL;
    int iLen = 0;
    BOOLEAN bIncludeEventLog;
    sAlertMgrData sTempAlertData; 
    ALERTMGR_STATUS eStatus;
    unsigned short u16AlertType = 0;
    char * pszPort = NULL;
    int s32port = 0;
    unsigned int uiSize = 0;
    
    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);

#if IBM_OOBALERTRECIPIENT_INIT_SUPPORT
    pAgentDataPtr = Arg.AgentInit(0);
#endif

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_OOBAlertRecipientPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    if (ctx == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }

    //memset(&sTempAlertData, 0, sizeof (sAlertMgrData));
    //alertmgr_setting_init(&sTempAlertData);

    eStatus = alertmgr_setting_get(nIndex+1, &sTempAlertData);
    if ((eStatus != ALERTMGR_OK) && (eStatus != ALERTMGR_CONFIG_EMPTY))
    {
       logTraceCIM(LOG_LEV_ERROR, "[%s] Failed to call alertmgr_setting_get(), result code is %d.\n", __FUNCTION__,  eStatus);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }
    logTraceCIM(LOG_LEV_DEBUG, "[%s]existing instance = %d, type = %d, Caption = %s, EmailAddress = %s, DestinationAddress = %s:%d, and operator = %d(0:mod, 1:del).\n", __FUNCTION__, 
        (nIndex + 1),  sTempAlertData.u16AlertType, sTempAlertData.szName, sTempAlertData.szEMailAddr,  sTempAlertData.szAddress, sTempAlertData.nPort, sTempAlertData.eOperator);

    sTempAlertData.eOperator = ALERTMGR_OPERATE_TYPE_MODIFY;

    /* Read Caption from input property */
    uiSize = sizeof(sTempAlertData.szName);
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_Caption, CMPI_string, sTempAlertData.szName, &uiSize, __FUNCTION__);
    if (rc.rc != CMPI_RC_OK)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get the property %s.", __FUNCTION__, PROPERTYNAME_Caption);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    /* Read AlertType from input property */
    data = inst->ft->getProperty(inst, PROPERTYNAME_AlertType, &rc);
    if (CMPI_goodValue == data.state)
    {
        u16AlertType = data.value.uint16;
        //check alert type input valid 
        if ((u16AlertType==0) || (u16AlertType>CIM_ALERT_TYPE_UNKNOWN)
            || (sTempAlertData.u16AlertType == ALERTMGR_TYPE_EMAIL && u16AlertType != CIM_ALERT_TYPE_EMAIL && u16AlertType != CIM_ALERT_TYPE_UNKNOWN) 
            || (sTempAlertData.u16AlertType == ALERTMGR_TYPE_SYSLOG && u16AlertType != CIM_ALERT_TYPE_SYSLOG && u16AlertType != CIM_ALERT_TYPE_UNKNOWN) 
            || (sTempAlertData.u16AlertType == ALERTMGR_TYPE_SNMPTRAP && u16AlertType != CIM_ALERT_TYPE_UNKNOWN))
        {
            logTraceCIM(LOG_LEV_ERROR, "[%s] Invalid alert type %d, existing type is %d.\n", __FUNCTION__,  u16AlertType, sTempAlertData.u16AlertType);
            rc.rc = CMPI_RC_ERR_NOT_ALLOWED;
            goto ERR_EXIT;

        }
        if( u16AlertType == CIM_ALERT_TYPE_EMAIL)
            sTempAlertData.u16AlertType = ALERTMGR_TYPE_EMAIL;
        else if( u16AlertType == CIM_ALERT_TYPE_SYSLOG)
            sTempAlertData.u16AlertType = ALERTMGR_TYPE_SYSLOG;
        else if( u16AlertType == CIM_ALERT_TYPE_UNKNOWN)
            sTempAlertData.u16AlertType = 0;
        logTraceCIM(LOG_LEV_DEBUG, "[%s]modify alert type:instance = %d, type = %d, Caption = %s, EmailAddress = %s, DestinationAddress = %s:%d, and operator = %d(0:mod, 1:del).\n", __FUNCTION__, 
            (nIndex + 1),  sTempAlertData.u16AlertType, sTempAlertData.szName, sTempAlertData.szEMailAddr,  sTempAlertData.szAddress, sTempAlertData.nPort, sTempAlertData.eOperator);
      
    }



    /* Read EmailAddress from input property */
    data = inst->ft->getProperty(inst, PROPERTYNAME_EmailAddress, &rc);
    if (CMPI_goodValue == data.state )
    {
        if((sTempAlertData.u16AlertType==ALERTMGR_TYPE_SYSLOG) || (sTempAlertData.u16AlertType==ALERTMGR_TYPE_SNMPTRAP))
        {
            logTraceCIM(LOG_LEV_ERROR, "[%s] Invalid operation to NON email recipient , existing type is %d.\n", __FUNCTION__,  sTempAlertData.u16AlertType);
             rc.rc = CMPI_RC_ERR_NOT_ALLOWED;
            goto ERR_EXIT;
       }
        dataStr = CMPIData2String(&data);   
        if(dataStr == NULL)
        {
            CMPIDataRelease(&data);
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
            goto ERR_EXIT;
        }
        
        //printf("EmailAddress data type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc));        
        szBuf = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
        iLen = strlen(szBuf);
        if(iLen)
        {
            sTempAlertData.u16AlertType = ALERTMGR_TYPE_EMAIL;
            if( u16AlertType == CIM_ALERT_TYPE_UNKNOWN)
                u16AlertType = 0;
             iLen = (MAX_STR_LEN >= iLen) ? iLen : MAX_STR_LEN;
            memcpy(sTempAlertData.szEMailAddr, szBuf,  iLen);
            sTempAlertData.szEMailAddr[iLen] = 0;
        }
        else
        {
            snprintf(sTempAlertData.szEMailAddr, sizeof(sTempAlertData.szEMailAddr), "%s", szBuf);
        }
        
        SafeCMRelease(dataStr);
        CMPIDataRelease(&data);

    }

    /* Read syslog address from input property */
    data = inst->ft->getProperty(inst, PROPERTYNAME_DestinationAddress, &rc);
    if (CMPI_goodValue == data.state)
    {
        if((sTempAlertData.u16AlertType==ALERTMGR_TYPE_EMAIL) || (sTempAlertData.u16AlertType==ALERTMGR_TYPE_SNMPTRAP))
        {
            logTraceCIM(LOG_LEV_ERROR, "[%s] Invalid operation to NON syslog recipient , existing type is %d.\n", __FUNCTION__,  sTempAlertData.u16AlertType);
             rc.rc = CMPI_RC_ERR_NOT_ALLOWED;
            goto ERR_EXIT;
       }

        dataStr = CMPIData2String(&data);   
        if(dataStr == NULL)
        {
            CMPIDataRelease(&data);
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
            goto ERR_EXIT;
        }
        
        //printf("EmailAddress data type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc));        
      
        szBuf = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
        iLen = strlen(szBuf);
        if(iLen)
        {
            if( (pszPort= strchr(szBuf, ':')))
            s32port = atoi(pszPort+1);
            if((!pszPort) || s32port<=0 || s32port>MAX_SYSLOG_PORT)
            {
                SafeCMRelease(dataStr);
                CMPIDataRelease(&data);
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
                goto ERR_EXIT;
            }
            sTempAlertData.u16AlertType = ALERTMGR_TYPE_SYSLOG;
             if( u16AlertType == CIM_ALERT_TYPE_UNKNOWN)
                u16AlertType = 0;
           sTempAlertData.nPort = s32port;
            iLen = (MAX_STR_LEN >= (pszPort - szBuf)) ? (pszPort - szBuf) : MAX_STR_LEN;
            memcpy(sTempAlertData.szAddress, szBuf, iLen);
            sTempAlertData.szAddress[iLen] = 0;
        }
        else
        {
            snprintf(sTempAlertData.szAddress, sizeof(sTempAlertData.szAddress), "%s", szBuf);
            sTempAlertData.nPort = 0;

        }
       
        SafeCMRelease(dataStr);
        CMPIDataRelease(&data);
    }

    /* Read IncludeEventLog from input property */
    data = inst->ft->getProperty(inst, PROPERTYNAME_IncludeEventLog, &rc);
    if (CMPI_goodValue == data.state)
    {
        bIncludeEventLog = CMPIData2Boolean(&data, &rc);
        if (rc.rc != CMPI_RC_OK)
        {
            CMPIDataRelease(&data);
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
            goto ERR_EXIT;
        }    

        if((sTempAlertData.u16AlertType == ALERTMGR_TYPE_SYSLOG) && (bIncludeEventLog == TRUE))
        {
            CMPIDataRelease(&data);
            logTraceCIM(LOG_LEV_ERROR, "[%s] NOT allowed to set includeEventLog property for syslog recipient.\n", __FUNCTION__,  sTempAlertData.u16AlertType);
            rc.rc = CMPI_RC_ERR_NOT_ALLOWED;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
            goto ERR_EXIT;

        }
        //printf("IncludeEventLog data type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc));     
        sTempAlertData.u16IncludeLog = bIncludeEventLog;
        CMPIDataRelease(&data);
    }

     if( u16AlertType == CIM_ALERT_TYPE_UNKNOWN)
     {
        logTraceCIM(LOG_LEV_DEBUG, "[%s] Modify instance %d clear alert type \n", __FUNCTION__, (nIndex + 1));
        sTempAlertData.szAddress[0] = sTempAlertData.szEMailAddr[0] = 0;
        sTempAlertData.nPort = 0;
     }

    if(  (!strlen(sTempAlertData.szAddress)) && (!strlen(sTempAlertData.szEMailAddr)))
    {
        sTempAlertData.u16Status = ALERTMGR_DISABLE;
        if(!strlen(sTempAlertData.szName))
        {
           logTraceCIM(LOG_LEV_DEBUG, "[%s] Modify instance %d set operation to DELETE \n", __FUNCTION__, (nIndex + 1));
           sTempAlertData.eOperator = ALERTMGR_OPERATE_TYPE_DELETE;
        }
    }
     
     logTraceCIM(LOG_LEV_DEBUG, "[%s]instance = %d, type = %d, Caption = %s, EmailAddress = %s, DestinationAddress = %s:%d, and operator = %d(0:mod, 1:del).\n", __FUNCTION__, 
        (nIndex + 1),  sTempAlertData.u16AlertType, sTempAlertData.szName, sTempAlertData.szEMailAddr,  sTempAlertData.szAddress, sTempAlertData.nPort, sTempAlertData.eOperator);

    CMPIGetUserNameFromContext(ctx, sTempAlertData.szUserID);
    eStatus = alertmgr_setting_set((UINT8) (nIndex + 1), &sTempAlertData);
    if (eStatus != ALERTMGR_OK)
    {
        logTraceCIM(LOG_LEV_ERROR, "[%s] Failed to call alertmgr_setting_set(), result code is %d.\n", __FUNCTION__,  eStatus);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;
    }

    rc.rc = 0;

ERR_EXIT:

#if IBM_OOBALERTRECIPIENT_INIT_SUPPORT
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

CMPIStatus IBM_OOBAlertRecipient_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg);

#if IBM_OOBALERTRECIPIENT_INIT_SUPPORT
    pAgentDataPtr = Arg.AgentInit(0);
#endif

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (nIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    /* invoke method */
    if (0 == strcmp(method, "RequestStateChange"))
    {
        value.uint32 = IBM_OOBAlertRecipient_InstAgent_RequestStateChange((UINT32) nIndex, ctx, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_METHOD_NOT_FOUND;
    }

CLEAN:

#if IBM_OOBALERTRECIPIENT_INIT_SUPPORT
    Arg.AgentDestroy(pAgentDataPtr);
#endif

    return (rc);
}

#ifndef _BROKER_SFCB
CMPIData *IBM_OOBAlertRecipient_GetMethodName()
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
    nameArray = (void*) TheBroker.eft->newArray(&TheBroker, 1, CMPI_chars, &status);

    if(!nameArray)
    {
        return (NULL);
    }

    /* add method name */
    value.chars = (char *) METHODNAME_RequestStateChange;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

CMPIData *IBM_OOBAlertRecipient_GetMethodParameters(const char * MethodName)
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

    if (0 == strcmp(MethodName, METHODNAME_RequestStateChange))
    {
        iMethID = 0;
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
            value.chars = (char *) TYPENAME_uint16;
            pArgs->ft->addArg(pArgs, PARAMNAME_RequestedState,&value,CMPI_chars);
            value.chars = "ref CIM_ConcreteJob";
            pArgs->ft->addArg(pArgs, PARAMNAME_Job,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_datetime;
            pArgs->ft->addArg(pArgs, PARAMNAME_TimeoutPeriod,&value,CMPI_chars);
            break;

    }

    data->value.args = pArgs;
    data->type = CMPI_args;
    data->state = CMPI_goodValue;
    return (data);
}
#endif

/* IBM_OOBAlertRecipient Class Service Function */
CMPIStatus Lenovo_OOBAlertRecipientService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_OOBAlertRecipient,
                                     CIM_EnabledLogicalElementService);
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
            rc = IBM_OOBAlertRecipient_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_OOBAlertRecipient_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_OOBAlertRecipient_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_OOBALERTRECIPIENT_INIT_SUPPORT
            rc.msg = (void*) &IBM_OOBAlertRecipient_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_OOBALERTRECIPIENT_INIT_SUPPORT
            rc.msg = (void*) &IBM_OOBAlertRecipient_InstAgent_Destroy;
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
            rc = IBM_OOBAlertRecipient_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_OOBAlertRecipient_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_OOBAlertRecipient_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_OOBAlertRecipient_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_OOBAlertRecipient_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_OOBAlertRecipient_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_OOBAlertRecipient_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_OOBAlertRecipient_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_OOBAlertRecipient_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_OOBAlertRecipient_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_OOBAlertRecipient_GetMethodParameters(method);
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
GenNotSupportInstanceMICreateInstance(IBM_OOBAlertRecipient);
// GenNotSupportInstanceMIModifyInstance(IBM_OOBAlertRecipient);
GenNotSupportInstanceMIDeleteInstance(IBM_OOBAlertRecipient);
GenNotSupportInstanceMIExecQuery(IBM_OOBAlertRecipient);
GenNotSupportInstanceMICleanup(IBM_OOBAlertRecipient);

/* MI factory function */
CMInstanceMIStub( IBM_OOBAlertRecipient_,
                  Lenovo_OOBAlertRecipient_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_OOBAlertRecipient);

CMMethodMIStub( IBM_OOBAlertRecipient_,
                Lenovo_OOBAlertRecipient_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_OOBALERTRECIPIENT_INIT_SUPPORT /* You can turn on this flag in IBM_OOBAlertRecipientAgent.h */
#define PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_OOBAlertRecipient_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBAlertRecipient;\
    Arg.GetNextInstIndex = IBM_OOBAlertRecipient_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_OOBAlertRecipientKeyPropertyList;\
    Arg.PropertyList = IBM_OOBAlertRecipientPropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBAlertRecipientPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBAlertRecipientKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_OOBAlertRecipient_InstAgent_Init;\
    Arg.AgentDestroy = IBM_OOBAlertRecipient_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_OOBAlertRecipient_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_OOBAlertRecipient;\
    Arg.GetNextInstIndex = IBM_OOBAlertRecipient_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_OOBAlertRecipientKeyPropertyList;\
    Arg.PropertyList = IBM_OOBAlertRecipientPropertyList;\
    Arg.propertyNo = sizeof(IBM_OOBAlertRecipientPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_OOBAlertRecipientKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_OOBAlertRecipient Class Service Function */
CMPIStatus Lenovo_OOBAlertRecipientService( 
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

/* Gets the Arg of Class IBM_OOBAlertRecipient Function */
sClassUtilArg IBM_OOBAlertRecipient_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_OOBALERTRECIPIENT_ARG( Arg );

    return (Arg);
}

#endif
