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
#include "../instAgent/incEX/NetworkPort.h"
#include "../instAgent/incEX/MezzanineCard.h"
#include <ctype.h>


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_EthernetPort class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_EthernetPort = (CMPIUint8 *)CLASSNAMETEXT_IBM_EthernetPort;

/* Property List */
static const char * const IBM_EthernetPortPropertyList[] = 
{
    PROPERTYNAME_ActiveMaximumTransmissionUnit,
    PROPERTYNAME_AutoSense,
    PROPERTYNAME_BurnedInMAC,
    PROPERTYNAME_Capabilities,
    PROPERTYNAME_ConfiguredLAMAC,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EnabledCapabilities,
    PROPERTYNAME_EnabledState,
    PROPERTYNAME_FullDuplex,
    PROPERTYNAME_IdentifyingDescriptions,
    PROPERTYNAME_LinkTechnology,
    PROPERTYNAME_MaxSpeed,
    PROPERTYNAME_Name,
    PROPERTYNAME_NetworkAddresses,
    PROPERTYNAME_OtherIdentifyingInfo,
    PROPERTYNAME_OtherLinkTechnology,
    PROPERTYNAME_PermanentAddress,
    PROPERTYNAME_PortNumber,
    PROPERTYNAME_PortType,
    PROPERTYNAME_RequestedState,
    PROPERTYNAME_Speed
};

/* Key property List */
static const char * const IBM_EthernetPortKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_DeviceID,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_ETHERNETPORT_INIT_SUPPORT /* You can turn on this flag in IBM_EthernetPortAgent.h */
#define PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_EthernetPort;\
    Arg.GetKeyProperty = IBM_EthernetPort_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_EthernetPort_InstAgent_GetNext;\
    Arg.GetProperty = IBM_EthernetPort_GetProperty;\
    Arg.KeyPropertyList = IBM_EthernetPortKeyPropertyList;\
    Arg.PropertyList = IBM_EthernetPortPropertyList;\
    Arg.propertyNo = sizeof(IBM_EthernetPortPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_EthernetPortKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ETHERNETPORTASSONUM;\
    Arg.AssocArray = G_sLenovo_EthernetPortAssociations;\
    Arg.AgentInit = IBM_EthernetPort_InstAgent_Init;\
    Arg.AgentDestroy = IBM_EthernetPort_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_EthernetPort;\
    Arg.GetKeyProperty = IBM_EthernetPort_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_EthernetPort_InstAgent_GetNext;\
    Arg.GetProperty = IBM_EthernetPort_GetProperty;\
    Arg.KeyPropertyList = IBM_EthernetPortKeyPropertyList;\
    Arg.PropertyList = IBM_EthernetPortPropertyList;\
    Arg.propertyNo = sizeof(IBM_EthernetPortPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_EthernetPortKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ETHERNETPORTASSONUM;\
    Arg.AssocArray = G_sLenovo_EthernetPortAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_ETHERNETPORT_INIT_SUPPORT /* You can turn on this flag in IBM_EthernetPortAgent.h */
#define PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_EthernetPort;\
    Arg.GetKeyProperty = IBM_EthernetPort_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_EthernetPort_InstAgent_GetNext;\
    Arg.GetProperty = IBM_EthernetPort_GetProperty;\
    Arg.KeyPropertyList = IBM_EthernetPortKeyPropertyList;\
    Arg.PropertyList = IBM_EthernetPortPropertyList;\
    Arg.propertyNo = sizeof(IBM_EthernetPortPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_EthernetPortKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ETHERNETPORTASSONUM;\
    Arg.AssocArray = G_sLenovo_EthernetPortAssociations;\
    Arg.AgentInit = IBM_EthernetPort_InstAgent_Init;\
    Arg.AgentDestroy = IBM_EthernetPort_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_EthernetPort;\
    Arg.GetKeyProperty = IBM_EthernetPort_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_EthernetPort_InstAgent_GetNext;\
    Arg.GetProperty = IBM_EthernetPort_GetProperty;\
    Arg.KeyPropertyList = IBM_EthernetPortKeyPropertyList;\
    Arg.PropertyList = IBM_EthernetPortPropertyList;\
    Arg.propertyNo = sizeof(IBM_EthernetPortPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_EthernetPortKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_ETHERNETPORTASSONUM;\
    Arg.AssocArray = G_sLenovo_EthernetPortAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_EthernetPort_GetProperty( 
                                       CMPICount nInstIndex,
                                       CMPICount nPropIndex,
                                       void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_EthernetPort_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_EthernetPort_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_EthernetPort, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_EthernetPort, &rc);
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
        data = IBM_EthernetPort_GetProperty(nInstIndex, nKeyIndex | IBM_ETHERNETPORT_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_EthernetPort_GenerateObjectPath( 
                                                     char **properties,
                                                     CMPICount InstIndex,
                                                     void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_EthernetPort_GetInstance( 
                                         CMPIInstanceMI *mi,
                                         const CMPIContext *ctx,
                                         const CMPIResult *rslt,
                                         const CMPIObjectPath *op,
                                         const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_EthernetPort_EnumInstances( 
#else
CMPIStatus IBM_EthernetPort_EnumerateInstances( 
#endif
                                                CMPIInstanceMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_EthernetPort_EnumInstanceNames( 
#else
CMPIStatus IBM_EthernetPort_EnumerateInstanceNames( 
#endif
                                                    CMPIInstanceMI *mi,
                                                    const CMPIContext *ctx,
                                                    const CMPIResult *rslt,
                                                    const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_EthernetPort_Associators( 
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
    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_EthernetPort_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_EthernetPort_References( 
                                        CMPIAssociationMI *mi,
                                        const CMPIContext *ctx,
                                        const CMPIResult *rslt,
                                        const CMPIObjectPath *op,
                                        const char *resultClass,
                                        const char *role,
                                        const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_EthernetPort_ReferenceNames( 
                                            CMPIAssociationMI *mi,
                                            const CMPIContext *ctx,
                                            const CMPIResult *rslt,
                                            const CMPIObjectPath *op,
                                            const char *resultClass,
                                            const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Cheryl 2010/11/10 begin */
CMPIStatus IBM_EthernetPort_ModifyInstance(
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
    CMPIString *pDataStr = NULL;
    sNetworkPortAgentData *pDataPtr;
    sNetworkPortData *pPortData;
    OSINET_STATUS status;
    sIF_Conf ifConf;

    char *pName = NULL;
    UINT8 u8tmpBuf[3];
    int i = 0;
    int len;
    UINT16 u16size;
    UINT8 u8ID;
    UINT8 u8ZeroCount = 0;
    char szParameter[64];

    if (inst == NULL) 
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);

#if IBM_ETHERNETPORT_INIT_SUPPORT
    pAgentDataPtr = IBM_EthernetPort_InstAgent_Init(0);
#endif
    
    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }
	
    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_EthernetPortPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    if (pAgentDataPtr)
    {
        pDataPtr = (sNetworkPortAgentData *) pAgentDataPtr;

        if ((nIndex < pDataPtr->PortCount) && (pDataPtr->PortData))
        {
            pPortData = pDataPtr->PortData + nIndex;
        }
        else
        {
            printf("[%s] Error: Port data is out of range or is NULL.\n", __FUNCTION__);
            
            rc.rc = CMPI_RC_ERR_FAILED;
            goto ERR_EXIT;
        }
    }
    else
    {
        printf("[%s] Error: Agent data is NULL.\n", __FUNCTION__);
        
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }

    if (0 == strncmp((char *)pPortData->szDevName, (char *) "host", 4))
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }

    if (pPortData->PortType != MEZZ_TYPE_ETHERNET)
    {
        u16size = sizeof(sIF_Conf);
        status = avct_osinet_ifconfdatainit(&ifConf, &u16size);
        if (status != OSINET_STATUS_OK)
        {
            rc.rc = CMPI_RC_ERR_FAILED;
            goto ERR_EXIT;
        }

        if (strncmp((char *)pPortData->szDevName, (char *)"usb", 3) != 0)
        {
            /* CQ XB145259 */
            /* get parameter ActiveMaximumTransmissionUnit */
            snprintf(szParameter, sizeof(szParameter), "%s", PROPERTYNAME_ActiveMaximumTransmissionUnit);
            data = inst->ft->getProperty(inst, szParameter, &rc);
            if ((CMPI_goodValue == data.state) && (CMPI_RC_OK == rc.rc))
            {
                if (CMPI_uint64 == data.type)
                {
                    if (ifConf.ifDev.u16MTU != (uint16_t)data.value.uint64)
                    {
                        ifConf.ifDev.u16MTU = (uint16_t)data.value.uint64;
                    }
                }
                else
                {
                    printf("[%s] Paramater(%s) type error, type is %d.\n", __FUNCTION__, szParameter, data.type);
                    
                    rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                    goto ERR_EXIT_RELEASE_1;
                }
            }
            else
            {
                printf("[%s] Failed to get parameter(%s).\n", __FUNCTION__, szParameter);
                
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                goto ERR_EXIT;
            }
            /* CQ XB145259 */

            /* get parameter AutoSense */
            snprintf(szParameter, sizeof(szParameter), "%s", PROPERTYNAME_AutoSense);
            //printf("Try to get parameter(%s).\n", szParameter);
            
            data = inst->ft->getProperty(inst, szParameter, &rc);
            if ((CMPI_goodValue == data.state) && (CMPI_RC_OK == rc.rc))
            {
                if (CMPI_boolean == data.type)
                {
                    ifConf.ifDev.bAutoNegotiate = data.value.boolean ? DEV_AUTONEG_ON : DEV_AUTONEG_OFF;
           
                    //printf("The AutoSense is %d.\n", ifConf.ifDev.bAutoNegotiate);
                }
                else
                {
                    printf("[%s] Paramater(%s) type error, type is %d.\n", __FUNCTION__, szParameter, data.type);
                    
                    rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                    goto ERR_EXIT_RELEASE_1;
                }
                
                CMPIDataRelease(&data);
            }
            else
            {
                printf("[%s] Failed to get parameter(%s).\n", __FUNCTION__, szParameter);
                
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                goto ERR_EXIT;
            }
            
            if (DEV_AUTONEG_OFF == ifConf.ifDev.bAutoNegotiate)
            {
                /* get parameter FullDuplex */
                snprintf(szParameter, sizeof(szParameter), "%s", PROPERTYNAME_FullDuplex);
                //printf("Try to get parameter(%s).\n", szParameter);
                
                data = inst->ft->getProperty(inst, szParameter, &rc);
                if ((CMPI_goodValue == data.state) && (CMPI_RC_OK == rc.rc))
                {
                    if (CMPI_boolean == data.type)
                    {
                        ifConf.ifDev.u8NetDuplex = data.value.boolean ? DEV_DUPLEX_FULL : DEV_DUPLEX_HALF;
                
                        //printf("The FullDuplex is %d.\n", ifConf.ifDev.u8NetDuplex);
                    }
                    else
                    {
                        printf("[%s] Paramater(%s) type error, type is %d.\n", __FUNCTION__, szParameter, data.type);
                        
                        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                        goto ERR_EXIT_RELEASE_1;
                    }
                    
                    CMPIDataRelease(&data);
                }
                else
                {
                    printf("[%s] Cannot get parameter(%s).\n", __FUNCTION__, szParameter);
                }
                
                /* get parameter Speed */
                snprintf(szParameter, sizeof(szParameter), "%s", PROPERTYNAME_Speed);
                //printf("Try to get parameter(%s).\n", szParameter);
                
                data = inst->ft->getProperty(inst, szParameter, &rc);
                if ((CMPI_goodValue == data.state) && (CMPI_RC_OK == rc.rc))
                {
                    if ((CMPI_uint64 == data.type) && ((10 == data.value.uint64) || (100 == data.value.uint64)))
                    {
                        if (10 == data.value.uint64)
                        {
                            ifConf.ifDev.u8NetSpeed = DEV_SPEED_10;
                        }
                        else
                        {
                            ifConf.ifDev.u8NetSpeed = DEV_SPEED_100;
                        }

                        //printf("The Speed is %d and NetSpeed is %d.\n", data.value.uint64, ifConf.ifDev.u8NetSpeed);
                    }
                    else
                    {
                        printf("[%s] Paramater(%s) type error, type is %d.\n", __FUNCTION__, szParameter, data.type);
                        
                        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                        goto ERR_EXIT_RELEASE_1;
                    }
                    
                    CMPIDataRelease(&data);
                }
                else
                {
                    printf("[%s] Cannot get parameter(%s).\n", __FUNCTION__, szParameter);
                }
            }

            status = avct_osinet_working_interface(&u8ID);
        }
        else
        {
            status = avct_osinet_getifidbytype(ABS_IF_TYPE_USB, &u8ID);
        }

        if (status != OSINET_STATUS_OK)
        {
            rc.rc = CMPI_RC_ERR_FAILED;
            goto ERR_EXIT;
        }
        
        /* get parameter ConfiguredLAMAC */
        snprintf(szParameter, sizeof(szParameter), "%s", PROPERTYNAME_ConfiguredLAMAC);
        //printf("Try to get parameter(%s).\n", szParameter);
        
        /* User customized MAC address configuration */   
        data = inst->ft->getProperty(inst, szParameter, &rc); /* get PROPERTYNAME_ConfiguredLAMAC */
        if (data.state != CMPI_goodValue)
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY; */
            goto ERR_EXIT;
        }  
        pDataStr = CMPIData2String(&data); 
        pName = (char *) pDataStr->ft->getCharPtr(pDataStr, &rc);
        
        /* Verify the input MAC address matches the format of 12 unseparated uppercase hex digits */
        len = strlen(pName);
        if (len != 12)
        {
            rc.rc = CMPI_RC_ERR_FAILED;
            goto ERR_EXIT_RELEASE;
        }

        for (i = 0; i < len; i++)
        {
           if (!isxdigit(pName[i]))
           {
               rc.rc = CMPI_RC_ERR_FAILED;
               goto ERR_EXIT_RELEASE;
           }
           
           if (pName[i] == '0')
           {
               u8ZeroCount++;
           }
        }

        memset(u8tmpBuf, 0, 2);
        memset(ifConf.ifDev.au8MAC, 0, 6);
        
        /* Reset to Burned In MAC address */
        if (u8ZeroCount == 12)
        {
            for(i = 0; i < 6; i++)
            {
                ifConf.ifDev.au8MAC[i] = 255;
            }
        }
        else
        {
            for(i = 0; i < 6; i++)
            {
                snprintf((char *)u8tmpBuf, sizeof(u8tmpBuf), "%c%c", pName[i*2], pName[i*2+1]);
                ifConf.ifDev.au8MAC[i] = (uint8_t) strtol((char *)u8tmpBuf, NULL, 16); // Convert to hex format
            }
        }

        CMPIGetUserNameFromContext(ctx, ifConf.c_UserID);
        status = avct_osinet_ifconfset(u8ID, &ifConf); // abstract interface index start from 1
        if (status != OSINET_STATUS_OK)
        {
            rc.rc = CMPI_RC_ERR_FAILED;
            goto ERR_EXIT_RELEASE;
        }

    }
    else
    {
        printf("[%s] Error: Mezz card is not supported.\n", __FUNCTION__);
        
        rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
        goto ERR_EXIT;    
    }    
    
ERR_EXIT_RELEASE:
    
    SafeCMRelease(pDataStr);

ERR_EXIT_RELEASE_1:
    
    CMPIDataRelease(&data);
    
ERR_EXIT:
    
#if IBM_ETHERNETPORT_INIT_SUPPORT
    IBM_EthernetPort_InstAgent_Destroy(pAgentDataPtr);
#endif

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc); 
}
/* Cheryl 2010/11/10 end */

CMPIStatus IBM_EthernetPort_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg);

#if IBM_ETHERNETPORT_INIT_SUPPORT
    pAgentDataPtr = IBM_EthernetPort_InstAgent_Init(0);
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
        value.uint32 = IBM_EthernetPort_InstAgent_RequestStateChange((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_METHOD_NOT_FOUND;
    }

CLEAN:

#if IBM_ETHERNETPORT_INIT_SUPPORT
    IBM_EthernetPort_InstAgent_Destroy(pAgentDataPtr);
#endif

    return (rc);
}

#ifndef _BROKER_SFCB
CMPIData *IBM_EthernetPort_GetMethodName()
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

CMPIData *IBM_EthernetPort_GetMethodParameters(const char * MethodName)
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

/* IBM_EthernetPort Class Service Function */
CMPIStatus Lenovo_EthernetPortService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_EthernetPort,
                                     CIM_EthernetPortService);
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
            rc = IBM_EthernetPort_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_EthernetPort_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_EthernetPort_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_ETHERNETPORT_INIT_SUPPORT
            rc.msg = (void*) &IBM_EthernetPort_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_ETHERNETPORT_INIT_SUPPORT
            rc.msg = (void*) &IBM_EthernetPort_InstAgent_Destroy;
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
            rc = IBM_EthernetPort_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_EthernetPort_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_EthernetPort_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_EthernetPort_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_EthernetPort_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_EthernetPort_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_EthernetPort_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_EthernetPort_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_EthernetPort_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_EthernetPort_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_EthernetPort_GetMethodParameters(method);
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
GenNotSupportInstanceMICreateInstance(IBM_EthernetPort);
//GenNotSupportInstanceMIModifyInstance(IBM_EthernetPort);
GenNotSupportInstanceMIDeleteInstance(IBM_EthernetPort);
GenNotSupportInstanceMIExecQuery(IBM_EthernetPort);
GenNotSupportInstanceMICleanup(IBM_EthernetPort);

/* MI factory function */
CMInstanceMIStub( IBM_EthernetPort_,
                  Lenovo_EthernetPort_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_EthernetPort);

CMMethodMIStub( IBM_EthernetPort_,
                Lenovo_EthernetPort_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_ETHERNETPORT_INIT_SUPPORT /* You can turn on this flag in IBM_EthernetPortAgent.h */
#define PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_EthernetPort_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_EthernetPort;\
    Arg.GetNextInstIndex = IBM_EthernetPort_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_EthernetPortKeyPropertyList;\
    Arg.PropertyList = IBM_EthernetPortPropertyList;\
    Arg.propertyNo = sizeof(IBM_EthernetPortPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_EthernetPortKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_EthernetPort_InstAgent_Init;\
    Arg.AgentDestroy = IBM_EthernetPort_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG(Arg) \
    Arg.AgentGetProperty = IBM_EthernetPort_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_EthernetPort;\
    Arg.GetNextInstIndex = IBM_EthernetPort_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_EthernetPortKeyPropertyList;\
    Arg.PropertyList = IBM_EthernetPortPropertyList;\
    Arg.propertyNo = sizeof(IBM_EthernetPortPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_EthernetPortKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_EthernetPort Class Service Function */
CMPIStatus Lenovo_EthernetPortService( 
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

/* Gets the Arg of Class IBM_EthernetPort Function */
sClassUtilArg IBM_EthernetPort_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_ETHERNETPORT_ARG( Arg );

    return (Arg);
}

#endif
