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
#include "LogUtil.h"
#include "SmashCommonUtil.h"

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_PowerUtilizationManagementService class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService = (CMPIUint8 *)CLASSNAMETEXT_IBM_PowerUtilizationManagementService;

/* Property List */
static const char * const IBM_PowerUtilizationManagementServicePropertyList[] = 
{
    PROPERTYNAME_EnabledState,
    PROPERTYNAME_PowerCappingMode,
    PROPERTYNAME_PowerRedundancyMode,
    PROPERTYNAME_PowerUtilizationMode,
    PROPERTYNAME_RequestedState
};

/* Key property List */
static const char * const IBM_PowerUtilizationManagementServiceKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_POWERUTILIZATIONMANAGEMENTSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_PowerUtilizationManagementServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService;\
    Arg.GetKeyProperty = IBM_PowerUtilizationManagementService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PowerUtilizationManagementService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PowerUtilizationManagementService_GetProperty;\
    Arg.KeyPropertyList = IBM_PowerUtilizationManagementServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PowerUtilizationManagementServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PowerUtilizationManagementServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PowerUtilizationManagementServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_POWERUTILIZATIONMANAGEMENTSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_PowerUtilizationManagementServiceAssociations;\
    Arg.AgentInit = IBM_PowerUtilizationManagementService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_PowerUtilizationManagementService_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService;\
    Arg.GetKeyProperty = IBM_PowerUtilizationManagementService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PowerUtilizationManagementService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PowerUtilizationManagementService_GetProperty;\
    Arg.KeyPropertyList = IBM_PowerUtilizationManagementServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PowerUtilizationManagementServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PowerUtilizationManagementServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PowerUtilizationManagementServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_POWERUTILIZATIONMANAGEMENTSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_PowerUtilizationManagementServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_POWERUTILIZATIONMANAGEMENTSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_PowerUtilizationManagementServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService;\
    Arg.GetKeyProperty = IBM_PowerUtilizationManagementService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PowerUtilizationManagementService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PowerUtilizationManagementService_GetProperty;\
    Arg.KeyPropertyList = IBM_PowerUtilizationManagementServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PowerUtilizationManagementServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PowerUtilizationManagementServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PowerUtilizationManagementServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_POWERUTILIZATIONMANAGEMENTSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_PowerUtilizationManagementServiceAssociations;\
    Arg.AgentInit = IBM_PowerUtilizationManagementService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_PowerUtilizationManagementService_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService;\
    Arg.GetKeyProperty = IBM_PowerUtilizationManagementService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_PowerUtilizationManagementService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_PowerUtilizationManagementService_GetProperty;\
    Arg.KeyPropertyList = IBM_PowerUtilizationManagementServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PowerUtilizationManagementServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PowerUtilizationManagementServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PowerUtilizationManagementServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_POWERUTILIZATIONMANAGEMENTSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_PowerUtilizationManagementServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_PowerUtilizationManagementService_GetProperty( 
                                                            CMPICount nInstIndex,
                                                            CMPICount nPropIndex,
                                                            void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_PowerUtilizationManagementService_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_PowerUtilizationManagementService_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService, &rc);
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
        data = IBM_PowerUtilizationManagementService_GetProperty(nInstIndex, nKeyIndex | IBM_POWERUTILIZATIONMANAGEMENTSERVICE_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_PowerUtilizationManagementService_GenerateObjectPath( 
                                                                          char **properties,
                                                                          CMPICount InstIndex,
                                                                          void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_PowerUtilizationManagementService_GetInstance( 
                                                              CMPIInstanceMI *mi,
                                                              const CMPIContext *ctx,
                                                              const CMPIResult *rslt,
                                                              const CMPIObjectPath *op,
                                                              const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_PowerUtilizationManagementService_EnumInstances( 
#else
CMPIStatus IBM_PowerUtilizationManagementService_EnumerateInstances( 
#endif
                                                                     CMPIInstanceMI *mi,
                                                                     const CMPIContext *ctx,
                                                                     const CMPIResult *rslt,
                                                                     const CMPIObjectPath *op,
                                                                     const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_PowerUtilizationManagementService_EnumInstanceNames( 
#else
CMPIStatus IBM_PowerUtilizationManagementService_EnumerateInstanceNames( 
#endif
                                                                         CMPIInstanceMI *mi,
                                                                         const CMPIContext *ctx,
                                                                         const CMPIResult *rslt,
                                                                         const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_PowerUtilizationManagementService_Associators( 
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
    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_PowerUtilizationManagementService_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_PowerUtilizationManagementService_References( 
                                                             CMPIAssociationMI *mi,
                                                             const CMPIContext *ctx,
                                                             const CMPIResult *rslt,
                                                             const CMPIObjectPath *op,
                                                             const char *resultClass,
                                                             const char *role,
                                                             const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_PowerUtilizationManagementService_ReferenceNames( 
                                                                 CMPIAssociationMI *mi,
                                                                 const CMPIContext *ctx,
                                                                 const CMPIResult *rslt,
                                                                 const CMPIObjectPath *op,
                                                                 const char *resultClass,
                                                                 const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

UINT8 WritePowercapMode(UINT8 u8PcapMode)
{
    uint8_t u8ModuleHandle;
    uint8_t u8Result = 1;

    if (AEM_IsSupported(AEM_DEFAULT_INSTANCE) && (!IsBladeServer()))
    {
        u8ModuleHandle = AEM_GetModuleHandle(AEM_DEFAULT_INSTANCE); 

        if (0x00 == u8ModuleHandle)
        {
            printf("[%s]Failed to call AEM_GetModuleHandle().\n",__FUNCTION__);
        }
        else
        {
            u8Result = AEM_WritePcapModeRegister(u8ModuleHandle,u8PcapMode);

            printf("[%s]AEM_ReadPcapModeRegister() returns [%d].\n",__FUNCTION__,u8Result);

            if(0x00 != u8Result)
            {
                 logTraceCIM(LOG_LEV_WARNING,"%s: WritePowercapMode failed with result [%d]\n",__FUNCTION__,u8Result);
            }
        }
    }

    return u8Result;
}

CMPIStatus IBM_PowerUtilizationManagementService_ModifyInstance(
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
    UINT8 u8PowerCapMode = 255;
    UINT8 u8PowerUtilizationMode = 255;
    UINT16 u16PowerRedundancyMode = 255;
    UINT8 u8ModuleHandle = 0;    
    UINT8 u8Result = 0;
    bool bIgnorePowerSavingSetting = 0;
    
    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);

    if (Arg.AgentInit)
    {
        pAgentDataPtr = Arg.AgentInit(0);
    }

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_PowerUtilizationManagementServicePropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (ctx == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto CLEAN;
    }

    /* Read power capping mode from input property */
    data = inst->ft->getProperty(inst, IBM_PowerUtilizationManagementServicePropertyList[1], &rc);
    if( (data.state != CMPI_goodValue)||(data.type != CMPI_uint16))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;    
    }

    dataStr = CMPIData2String(&data);

    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    printf("power capping mode type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc));
    u8PowerCapMode = atoi(dataStr->ft->getCharPtr(dataStr, &rc));

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

    if((u8PowerCapMode ==0)||(u8PowerCapMode == 1))
    {
        if(0x00 != WritePowercapMode(u8PowerCapMode))
        {
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }
    }
    else
    {
         logTraceCIM(LOG_LEV_WARNING,"%s: Passed in value %d is invalid power cap mode value\n",__FUNCTION__,u8PowerCapMode);
         rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
         goto CLEAN;
    }


    //read PowerUtilizationMode property value from input 
    data = inst->ft->getProperty(inst, IBM_PowerUtilizationManagementServicePropertyList[3], &rc);
    if((data.state != CMPI_goodValue) || (data.type != CMPI_uint16))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    dataStr = CMPIData2String(&data);

    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    u8PowerUtilizationMode = atoi(dataStr->ft->getCharPtr(dataStr, &rc));
    
    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

    if((u8PowerUtilizationMode == 2) ||(u8PowerUtilizationMode == 4))
    {
        if(AEM_IsStaticPowerSavingsModeSupported())
        {
            UINT8 u8Policy;
            UINT8 u8L3bSPCPReg;
            UINT8 u8TargetPolicy;
            UINT16 u16MsgID = 0;
            char psUserName[MAX_STR_LEN] = {0};
            void *pParameter = NULL;

            u8ModuleHandle = AEM_GetModuleHandle(AEM_DEFAULT_INSTANCE);
            if (0x00 == u8ModuleHandle)
            {
                logTraceCIM(LOG_LEV_WARNING,"[%s] Failed to call AEM_GetModuleHandle().\n", __FUNCTION__);
                 rc.rc = CMPI_RC_ERR_FAILED;
                goto CLEAN;
            }
            
            u8Result = AEM_ReadSMSPowerControlPolicyRegister(u8ModuleHandle, &u8Policy);
            if(0x00 !=  u8Result)
            {
                logTraceCIM(LOG_LEV_WARNING,"%s: fails to read SMS Power Control Policy Register.\n",__FUNCTION__);
                rc.rc = CMPI_RC_ERR_FAILED;
                goto CLEAN;
            }
            else
            {
                u8L3bSPCPReg = u8Policy&0x07;
            }

            switch(u8L3bSPCPReg)
            {
                case X_SPSR_BIT02_PMD_PCD_SPSD://0
                case X_SPSR_BIT02_PME_PCD_SPSD://1
                case X_SPSR_BIT02_PME_PCE_SPSD://2
                {
                    if(u8PowerUtilizationMode ==4)
                    {
                        u8L3bSPCPReg = u8L3bSPCPReg + 3;
                    }
                    else
                    {
                        logTraceCIM(LOG_LEV_INFO,"%s: static power savings mode is already disabled, shall not disable it actually again.\n",__FUNCTION__);
                        rc.rc = CMPI_RC_OK;
                        bIgnorePowerSavingSetting = true;
                    }
                }
                break;

                case X_SPSR_BIT02_PMD_PCD_SPSE://3
                case X_SPSR_BIT02_PME_PCD_SPSE://4
                case X_SPSR_BIT02_PME_PCE_SPSE://5
                {
                    if(u8PowerUtilizationMode ==2)
                    {
                        u8L3bSPCPReg = u8L3bSPCPReg -3;
                    }
                    else
                    {
                        logTraceCIM(LOG_LEV_INFO,"%s: static power savings mode is already enabled shall not enable it actually again.\n",__FUNCTION__);
                        rc.rc = CMPI_RC_OK;
                        bIgnorePowerSavingSetting = true;
                    }
                }
                break;

                default:
                {
                    logTraceCIM(LOG_LEV_WARNING,"%s: unexpected existing value: [%d] .\n",__FUNCTION__,u8L3bSPCPReg);
                    rc.rc = CMPI_RC_ERR_FAILED;
                    goto CLEAN;
                }
                break;                
            }

            if(!bIgnorePowerSavingSetting)
            {
                //go further to call AEM_WriteSMSPowerControlPolicyRegister()
                u8TargetPolicy = (u8Policy&0xF8) |u8L3bSPCPReg;
                //printf("%s - target policy is: %d\n",__FUNCTION__,u8TargetPolicy);
                u8Result = AEM_WriteSMSPowerControlPolicyRegister(u8ModuleHandle,u8TargetPolicy);

                if(0x00 != u8Result)
                {
                    logTraceCIM(LOG_LEV_ERROR,"%s: fails to write sms power control policy register to policy:[%d] with ret_value: [%d] .\n",__FUNCTION__,u8TargetPolicy,u8Result);
                    rc.rc = CMPI_RC_ERR_FAILED;
                    goto CLEAN;
                }

                rc.rc = CMPI_RC_OK;

                //trigger the related SW event out
                CMPIGetUserNameFromContext(ctx, psUserName);
                pParameter = psUserName;
                
                if(u8PowerUtilizationMode == 2)
                {
                    u16MsgID = SW_MSGID_STATIC_POWER_SAVINGS_TURNED_OFF;
                }
                else  if(u8PowerUtilizationMode == 4)
                {
                    u16MsgID = SW_MSGID_STATIC_POWER_SAVINGS_TURNED_ON;
                }

                if ((pParameter != NULL) && (sw_msg_dispatcher(u16MsgID, pParameter) != CEM_RC_OK))
                {
                    logTraceCIM(LOG_LEV_INFO,"%s: Generate sw message [%d] failed!!\n", __FUNCTION__,u16MsgID);
                }
            }
        }
        else
        {
            logTraceCIM(LOG_LEV_INFO,"%s: Static Power savings mode is not supported on this platform\n",__FUNCTION__);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }
    }
    else
    {
         logTraceCIM(LOG_LEV_WARNING,"%s: Passed in value %d is invalid power utilization mode value\n",__FUNCTION__,u8PowerUtilizationMode);
         rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
         goto CLEAN;
    }

    //get PowerRedundancyMode from input
    data = inst->ft->getProperty(inst, IBM_PowerUtilizationManagementServicePropertyList[2], &rc);
    if((data.state != CMPI_goodValue) || (data.type != CMPI_uint16))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }
    
    dataStr = CMPIData2String(&data);

    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    printf("power redundancy mode type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc));
    u16PowerRedundancyMode = atoi(dataStr->ft->getCharPtr(dataStr, &rc));

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

    if((u16PowerRedundancyMode >=2)&&(u16PowerRedundancyMode <= 5))
    {
        u8ModuleHandle = AEM_GetModuleHandle(AEM_DEFAULT_INSTANCE);
        if (0x00 == u8ModuleHandle)
        {
            logTraceCIM(LOG_LEV_WARNING,"[%s] Failed to call AEM_GetModuleHandle().\n", __FUNCTION__);
             rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }

        u8Result = AEM_WriteCFFPowerControlPolicyRegister(u8ModuleHandle,(u16PowerRedundancyMode-2));
        if(0x00 !=  u8Result)
        {
            logTraceCIM(LOG_LEV_WARNING,"%s: fails to write PSU Oversubscription Mode Register.\n",__FUNCTION__);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }
    }
    else
    {
        logTraceCIM(LOG_LEV_ERROR,"%s - parameter passed in <%d> is invalid\n",__FUNCTION__,u16PowerRedundancyMode);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

CLEAN:
    /* free resource here if neccesary */

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
CMPIStatus IBM_PowerUtilizationManagementService_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg);

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
    if (0 == strcmp(method, "ApplyPowerAllocationSettings"))
    {
        char psUserName[MAX_STR_LEN] = {0};
        CMPIGetUserNameFromContext(ctx, psUserName);
        value.uint32 = IBM_PowerUtilizationManagementService_InstAgent_ApplyPowerAllocationSettings((UINT32) nIndex, in, out, psUserName);
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
CMPIData *IBM_PowerUtilizationManagementService_GetMethodName()
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
    value.chars = (char *) METHODNAME_ApplyPowerAllocationSettings;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

CMPIData *IBM_PowerUtilizationManagementService_GetMethodParameters(const char * MethodName)
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

    if (0 == strcmp(MethodName, METHODNAME_ApplyPowerAllocationSettings))
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
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_PowerAllocationSettings,&value,CMPI_chars);
            value.chars = "ref CIM_ConcreteJob";
            pArgs->ft->addArg(pArgs, PARAMNAME_Job,&value,CMPI_chars);
            break;

    }

    data->value.args = pArgs;
    data->type = CMPI_args;
    data->state = CMPI_goodValue;
    return (data);
}
#endif

/* IBM_PowerUtilizationManagementService Class Service Function */
CMPIStatus Lenovo_PowerUtilizationManagementServiceService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService,
                                     CIM_PowerUtilizationManagementServiceService);
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
            rc = IBM_PowerUtilizationManagementService_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_PowerUtilizationManagementService_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_PowerUtilizationManagementService_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_POWERUTILIZATIONMANAGEMENTSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_PowerUtilizationManagementService_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_POWERUTILIZATIONMANAGEMENTSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_PowerUtilizationManagementService_InstAgent_Destroy;
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
            rc = IBM_PowerUtilizationManagementService_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_PowerUtilizationManagementService_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_PowerUtilizationManagementService_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_PowerUtilizationManagementService_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_PowerUtilizationManagementService_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_PowerUtilizationManagementService_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_PowerUtilizationManagementService_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_PowerUtilizationManagementService_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;
        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_PowerUtilizationManagementService_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_PowerUtilizationManagementService_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_PowerUtilizationManagementService_GetMethodParameters(method);
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
GenNotSupportInstanceMICreateInstance(IBM_PowerUtilizationManagementService);
// GenNotSupportInstanceMIModifyInstance(IBM_PowerUtilizationManagementService);
GenNotSupportInstanceMIDeleteInstance(IBM_PowerUtilizationManagementService);
GenNotSupportInstanceMIExecQuery(IBM_PowerUtilizationManagementService);
GenNotSupportInstanceMICleanup(IBM_PowerUtilizationManagementService);

/* MI factory function */
CMInstanceMIStub( IBM_PowerUtilizationManagementService_,
                  Lenovo_PowerUtilizationManagementService_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_PowerUtilizationManagementService);

CMMethodMIStub( IBM_PowerUtilizationManagementService_,
                Lenovo_PowerUtilizationManagementService_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_POWERUTILIZATIONMANAGEMENTSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_PowerUtilizationManagementServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_PowerUtilizationManagementService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService;\
    Arg.GetNextInstIndex = IBM_PowerUtilizationManagementService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_PowerUtilizationManagementServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PowerUtilizationManagementServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PowerUtilizationManagementServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PowerUtilizationManagementServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_PowerUtilizationManagementService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_PowerUtilizationManagementService_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_PowerUtilizationManagementService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_PowerUtilizationManagementService;\
    Arg.GetNextInstIndex = IBM_PowerUtilizationManagementService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_PowerUtilizationManagementServiceKeyPropertyList;\
    Arg.PropertyList = IBM_PowerUtilizationManagementServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_PowerUtilizationManagementServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_PowerUtilizationManagementServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_PowerUtilizationManagementService Class Service Function */
CMPIStatus Lenovo_PowerUtilizationManagementServiceService( 
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

/* Gets the Arg of Class IBM_PowerUtilizationManagementService Function */
sClassUtilArg IBM_PowerUtilizationManagementService_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_POWERUTILIZATIONMANAGEMENTSERVICE_ARG( Arg );

    return (Arg);
}

#endif
