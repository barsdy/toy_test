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
#include "LogUtil.h"
#include <emerson/aem/aem_lib.h>
#include <SmashCommonUtil.h>


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_DNSGeneralSettingData class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_DNSGeneralSettingData = (CMPIUint8 *)CLASSNAMETEXT_IBM_DNSGeneralSettingData;

/* Property List */
static const char * const IBM_DNSGeneralSettingDataPropertyList[] = 
{
    PROPERTYNAME_AddressOrigin,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EnableDNSServerAddresses,
    PROPERTYNAME_IPv6Preferred,
    PROPERTYNAME_RequestedHostName
};

/* Key property List */
static const char * const IBM_DNSGeneralSettingDataKeyPropertyList[] = 
{
    PROPERTYNAME_InstanceID
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_DNSGENERALSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_DNSGeneralSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_DNSGeneralSettingData;\
    Arg.GetKeyProperty = IBM_DNSGeneralSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_DNSGeneralSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_DNSGeneralSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_DNSGeneralSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_DNSGeneralSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_DNSGeneralSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_DNSGeneralSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_DNSGENERALSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_DNSGeneralSettingDataAssociations;\
    Arg.AgentInit = IBM_DNSGeneralSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_DNSGeneralSettingData_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_DNSGeneralSettingData;\
    Arg.GetKeyProperty = IBM_DNSGeneralSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_DNSGeneralSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_DNSGeneralSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_DNSGeneralSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_DNSGeneralSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_DNSGeneralSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_DNSGeneralSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_DNSGENERALSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_DNSGeneralSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_DNSGENERALSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_DNSGeneralSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_DNSGeneralSettingData;\
    Arg.GetKeyProperty = IBM_DNSGeneralSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_DNSGeneralSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_DNSGeneralSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_DNSGeneralSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_DNSGeneralSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_DNSGeneralSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_DNSGeneralSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_DNSGENERALSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_DNSGeneralSettingDataAssociations;\
    Arg.AgentInit = IBM_DNSGeneralSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_DNSGeneralSettingData_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_DNSGeneralSettingData;\
    Arg.GetKeyProperty = IBM_DNSGeneralSettingData_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_DNSGeneralSettingData_InstAgent_GetNext;\
    Arg.GetProperty = IBM_DNSGeneralSettingData_GetProperty;\
    Arg.KeyPropertyList = IBM_DNSGeneralSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_DNSGeneralSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_DNSGeneralSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_DNSGeneralSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_DNSGENERALSETTINGDATAASSONUM;\
    Arg.AssocArray = G_sLenovo_DNSGeneralSettingDataAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_DNSGeneralSettingData_GetProperty( 
                                                CMPICount nInstIndex,
                                                CMPICount nPropIndex,
                                                void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_DNSGeneralSettingData_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_DNSGeneralSettingData_GetKeyProperty( 
                                                   CMPICount nInstIndex,
                                                   CMPICount nKeyIndex,
                                                   void *pAgentDataPtr)
{
    CMPIData data;
        data.state = CMPI_badValue;
    data = IBM_DNSGeneralSettingData_GetProperty(nInstIndex, nKeyIndex | IBM_DNSGENERALSETTINGDATA_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_DNSGeneralSettingData_GenerateObjectPath( 
                                                              char **properties,
                                                              CMPICount InstIndex,
                                                              void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_DNSGeneralSettingData_GetInstance( 
                                                  CMPIInstanceMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_DNSGeneralSettingData_EnumInstances( 
#else
CMPIStatus IBM_DNSGeneralSettingData_EnumerateInstances( 
#endif
                                                         CMPIInstanceMI *mi,
                                                         const CMPIContext *ctx,
                                                         const CMPIResult *rslt,
                                                         const CMPIObjectPath *op,
                                                         const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_DNSGeneralSettingData_EnumInstanceNames( 
#else
CMPIStatus IBM_DNSGeneralSettingData_EnumerateInstanceNames( 
#endif
                                                             CMPIInstanceMI *mi,
                                                             const CMPIContext *ctx,
                                                             const CMPIResult *rslt,
                                                             const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_DNSGeneralSettingData_Associators( 
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
    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_DNSGeneralSettingData_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_DNSGeneralSettingData_References( 
                                                 CMPIAssociationMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char *resultClass,
                                                 const char *role,
                                                 const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_DNSGeneralSettingData_ReferenceNames( 
                                                     CMPIAssociationMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op,
                                                     const char *resultClass,
                                                     const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* IBM_DNSGeneralSettingData_ModifyInstance*/
CMPIStatus IBM_DNSGeneralSettingData_ModifyInstance(
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
    void *pAgentDataPtr = NULL;
    OSINET_STATUS status = OSINET_STATUS_UNSPECIFIED_FAILED;
    UINT8 u8ID = 0;
    UINT8 u8ModifiedDNSSrc = 0;
    sGlobal_Conf sModifiedGlobalConf;
    unsigned int uiSize = 0;
  	int iSize = 0;
    BOOLEAN bValue = FALSE;
    char szValue[255] = { 0 };
    UINT8 u8v6dnsPreference = LAN_NOCHANGE;
    BOOLEAN bIsRequestedHostnameModified = FALSE;
    BOOLEAN bIsIPv6PreferredModified = FALSE;

    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg);

#if IBM_DNSGENERALSETTINGDATA_INIT_SUPPORT
    pAgentDataPtr = IBM_DNSGeneralSettingData_InstAgent_Init(0);
#endif

    /* Get index of instance by objectpath */
    instIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == instIndex)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call CIMClassUtil_GetObjectpathIdx().", __FUNCTION__);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_DNSGeneralSettingDataPropertyList))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call CIMClassUtil_CheckAllPropertyExistence().", __FUNCTION__);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }
    
    if (ctx == NULL)
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- ctx is NULL.", __FUNCTION__);
	    rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }


    /* get parameter IPv6Preferred */
    uiSize = sizeof(bValue);
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_IPv6Preferred, CMPI_boolean, &bValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto ERR_EXIT;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        u8v6dnsPreference = bValue ? LAN_TRUE : LAN_FALSE;
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter RequestedHostname */
    uiSize = sizeof(sModifiedGlobalConf.szHostName);
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_RequestedHostName, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto ERR_EXIT;    
    }
    //Ignore the CMPI_RC_OK
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* Have any input properties */
    if ((u8v6dnsPreference != LAN_NOCHANGE) || (CMPI_RC_OK == rc.rc))
    {
        sGlobal_Conf sOriginalGlobalConf;

        status = avct_osinet_glbconfget_static(&sOriginalGlobalConf);
        if (status != OSINET_STATUS_OK)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call avct_osinet_glbconfget_static(), status %x.", __FUNCTION__, status);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto ERR_EXIT;  
        }

        if ((CMPI_RC_OK == rc.rc) && (strcmp(szValue, sOriginalGlobalConf.szHostName) != 0))
        {
            logTraceCIM(LOG_LEV_INFO, "%s()- Property(%s) is modified.", __FUNCTION__, PROPERTYNAME_RequestedHostname);
            bIsRequestedHostnameModified = TRUE;
        }

        if ((u8v6dnsPreference != LAN_NOCHANGE) && (sOriginalGlobalConf.u8v6dnsPreference != u8v6dnsPreference))
        {
            if (IsBladeServer())
            {
                logTraceCIM(LOG_LEV_WARNING, "%s()- The Flex ITE doesn't support to modify the property 'IPv6Preferred'.", __FUNCTION__);
                rc.rc = CMPI_RC_ERR_NOT_ALLOWED;
                goto ERR_EXIT;
            }
            logTraceCIM(LOG_LEV_INFO, "%s()- Property(%s) is modified.", __FUNCTION__, PROPERTYNAME_IPv6Preferred);
            bIsIPv6PreferredModified = TRUE;
        }

        if (bIsRequestedHostnameModified || bIsIPv6PreferredModified)
        {
            iSize = sizeof (sGlobal_Conf);
            status = avct_osinet_glbconfdatainit(&sModifiedGlobalConf, (uint16_t *) &iSize);
            if (status != OSINET_STATUS_OK)
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call avct_osinet_glbconfdatainit(), status %x.", __FUNCTION__, status);
                rc.rc = CMPI_RC_ERR_FAILED;
                goto ERR_EXIT;  
            }

            if (bIsRequestedHostnameModified)
            {
                snprintf(sModifiedGlobalConf.szHostName, sizeof(sModifiedGlobalConf.szHostName), "%s", szValue);
            }
            
            if (bIsIPv6PreferredModified)
            {
                sModifiedGlobalConf.u8v6dnsPreference = u8v6dnsPreference;
            }
        }
    }

    /* get parameter PROPERTYNAME_EnableDNSServerAddresses */
    uiSize = sizeof(bValue);
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_EnableDNSServerAddresses, CMPI_boolean, &bValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        goto ERR_EXIT;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        u8ModifiedDNSSrc = bValue ? DNS_SOURCE_MANUAL : DNS_SOURCE_DHCP;
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    if (u8ModifiedDNSSrc != 0)
    {
        UINT8 u8DNSSrc = 0;
        
        status = avct_osinet_working_interface(&u8ID);
        if (status != OSINET_STATUS_OK)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call avct_osinet_working_interface(), status %x.", __FUNCTION__, status);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto ERR_EXIT;
        }

        status = avct_osinet_getDnsSource(u8ID, &u8DNSSrc);
        if (status != OSINET_STATUS_OK)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call avct_osinet_getDnsSource(), status %x.", __FUNCTION__, status);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto ERR_EXIT;
        }

        if (u8ModifiedDNSSrc != u8DNSSrc)
        {
            sIF_Conf ifConf;
            
            if (IsBladeServer())
            {
                logTraceCIM(LOG_LEV_WARNING, "%s()- The Flex ITE doesn't support to modify the property 'EnableDNSServerAddresses'.", __FUNCTION__);
                rc.rc = CMPI_RC_ERR_NOT_ALLOWED;
                goto ERR_EXIT;
            }
            
            logTraceCIM(LOG_LEV_INFO, "%s()- Property(%s) is modified.", __FUNCTION__, PROPERTYNAME_EnableDNSServerAddresses);

            iSize = sizeof (sIF_Conf);
            status = avct_osinet_ifconfdatainit(&ifConf, (uint16_t *) &iSize);
            if (status != OSINET_STATUS_OK)
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call avct_osinet_ifconfdatainit(), status %x.", __FUNCTION__, status);
                rc.rc = CMPI_RC_ERR_FAILED;
                goto ERR_EXIT;  
            }

            status = avct_osinet_UpdateDnsSource(u8ModifiedDNSSrc, &ifConf);
            if(status != OSINET_STATUS_OK)
            {
                printf("%s()- Failed to call avct_osinet_UpdateDnsSource(), status %x.\n", __FUNCTION__, status);
                rc.rc = CMPI_RC_ERR_FAILED;
                goto ERR_EXIT;
            }

            CMPIGetUserNameFromContext(ctx, ifConf.c_UserID);
            status = avct_osinet_ifconfset(u8ID, &ifConf);
            if (status != OSINET_STATUS_OK)
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call avct_osinet_ifconfset(), status %x.", __FUNCTION__, status);
           	    rc.rc = CMPI_RC_ERR_FAILED;
            	goto ERR_EXIT;
            }
        }
    }

    if (bIsRequestedHostnameModified || bIsIPv6PreferredModified)
    {
        CMPIGetUserNameFromContext(ctx, sModifiedGlobalConf.c_UserID);
        status = avct_osinet_glbconfset(&sModifiedGlobalConf);
        if (status != OSINET_STATUS_OK)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call avct_osinet_glbconfset(), status %x.", __FUNCTION__, status);
        	rc.rc = CMPI_RC_ERR_FAILED;
        	goto ERR_EXIT;
        } 
    }
    
	rc.rc = CMPI_RC_OK;
    
ERR_EXIT:

#if IBM_DNSGENERALSETTINGDATA_INIT_SUPPORT
    IBM_DNSGeneralSettingData_InstAgent_Destroy(pAgentDataPtr);
#endif

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}




/* IBM_DNSGeneralSettingData Class Service Function */
CMPIStatus Lenovo_DNSGeneralSettingDataService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_DNSGeneralSettingData,
                                     CIM_DNSGeneralSettingDataService);
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
            rc = IBM_DNSGeneralSettingData_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_DNSGeneralSettingData_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_DNSGeneralSettingData_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_DNSGENERALSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_DNSGeneralSettingData_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_DNSGENERALSETTINGDATA_INIT_SUPPORT
            rc.msg = (void*) &IBM_DNSGeneralSettingData_InstAgent_Destroy;
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
            rc = IBM_DNSGeneralSettingData_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_DNSGeneralSettingData_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_DNSGeneralSettingData_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_DNSGeneralSettingData_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_DNSGeneralSettingData_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_DNSGeneralSettingData_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_DNSGeneralSettingData_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
		case CLASS_SERVICE_MODIFYINSTANCE: 
			/* modify instance service */
			va_start( argptr, op ); 																				
            inst = va_arg(argptr, CMPIInstance *); 
            properties = va_arg(argptr, char **);
            rc = IBM_DNSGeneralSettingData_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_DNSGeneralSettingData);
//GenNotSupportInstanceMIModifyInstance(IBM_DNSGeneralSettingData);
GenNotSupportInstanceMIDeleteInstance(IBM_DNSGeneralSettingData);
GenNotSupportInstanceMIExecQuery(IBM_DNSGeneralSettingData);
GenNotSupportInstanceMICleanup(IBM_DNSGeneralSettingData);

/* MI factory function */
CMInstanceMIStub( IBM_DNSGeneralSettingData_,
                  Lenovo_DNSGeneralSettingData_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_DNSGENERALSETTINGDATA_INIT_SUPPORT /* You can turn on this flag in IBM_DNSGeneralSettingDataAgent.h */
#define PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_DNSGeneralSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_DNSGeneralSettingData;\
    Arg.GetNextInstIndex = IBM_DNSGeneralSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_DNSGeneralSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_DNSGeneralSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_DNSGeneralSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_DNSGeneralSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_DNSGeneralSettingData_InstAgent_Init;\
    Arg.AgentDestroy = IBM_DNSGeneralSettingData_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG(Arg) \
    Arg.AgentGetProperty = IBM_DNSGeneralSettingData_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_DNSGeneralSettingData;\
    Arg.GetNextInstIndex = IBM_DNSGeneralSettingData_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_DNSGeneralSettingDataKeyPropertyList;\
    Arg.PropertyList = IBM_DNSGeneralSettingDataPropertyList;\
    Arg.propertyNo = sizeof(IBM_DNSGeneralSettingDataPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_DNSGeneralSettingDataKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_DNSGeneralSettingData Class Service Function */
CMPIStatus Lenovo_DNSGeneralSettingDataService( 
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

/* Gets the Arg of Class IBM_DNSGeneralSettingData Function */
sClassUtilArg IBM_DNSGeneralSettingData_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_DNSGENERALSETTINGDATA_ARG( Arg );

    return (Arg);
}

#endif
