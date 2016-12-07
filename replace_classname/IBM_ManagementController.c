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

/* Include base class' header file here */
/* TBD */

/* ADAM and AIM function usage */
#include <emerson/ab/avct_dm_ADAMLib.h>
#include <emerson/ab/avct_dm_VarList.h>
#include <emerson/aim/libaim.h>
#include <emerson/cemgr/swe_function_table.h>

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

#include "SmashCommonUtil.h"

const UINT16 SaHostPowerOffDelay[14] = {0, 30, 60, 120, 180, 240, 300, 450, 600, 900, 1200, 1800, 3600, 7200};

/* IBM_ManagementController class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_ManagementController = (CMPIUint8 *)CLASSNAMETEXT_IBM_ManagementController;

/* Property List */
static const char * const IBM_ManagementControllerPropertyList[] = 
{
    PROPERTYNAME_Dedicated,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EnabledState,
    PROPERTYNAME_HealthState,
    PROPERTYNAME_HostPowerOffDelay,
    PROPERTYNAME_IdentifyingDescriptions,
    PROPERTYNAME_IPMIEnablementState,
    PROPERTYNAME_OperationalStatus,
    PROPERTYNAME_OtherIdentifyingInfo,
    PROPERTYNAME_PrimaryOwnerContact,
    PROPERTYNAME_PrimaryOwnerName,
    PROPERTYNAME_RequestedState
};

/* Key property List */
static const char * const IBM_ManagementControllerKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_MANAGEMENTCONTROLLER_INIT_SUPPORT /* You can turn on this flag in IBM_ManagementControllerAgent.h */
#define PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ManagementController;\
    Arg.GetKeyProperty = IBM_ManagementController_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ManagementController_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ManagementController_GetProperty;\
    Arg.KeyPropertyList = IBM_ManagementControllerKeyPropertyList;\
    Arg.PropertyList = IBM_ManagementControllerPropertyList;\
    Arg.propertyNo = sizeof(IBM_ManagementControllerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ManagementControllerKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_MANAGEMENTCONTROLLERASSONUM;\
    Arg.AssocArray = G_sLenovo_ManagementControllerAssociations;\
    Arg.AgentInit = IBM_ManagementController_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ManagementController_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ManagementController;\
    Arg.GetKeyProperty = IBM_ManagementController_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ManagementController_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ManagementController_GetProperty;\
    Arg.KeyPropertyList = IBM_ManagementControllerKeyPropertyList;\
    Arg.PropertyList = IBM_ManagementControllerPropertyList;\
    Arg.propertyNo = sizeof(IBM_ManagementControllerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ManagementControllerKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_MANAGEMENTCONTROLLERASSONUM;\
    Arg.AssocArray = G_sLenovo_ManagementControllerAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_MANAGEMENTCONTROLLER_INIT_SUPPORT /* You can turn on this flag in IBM_ManagementControllerAgent.h */
#define PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ManagementController;\
    Arg.GetKeyProperty = IBM_ManagementController_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ManagementController_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ManagementController_GetProperty;\
    Arg.KeyPropertyList = IBM_ManagementControllerKeyPropertyList;\
    Arg.PropertyList = IBM_ManagementControllerPropertyList;\
    Arg.propertyNo = sizeof(IBM_ManagementControllerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ManagementControllerKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_MANAGEMENTCONTROLLERASSONUM;\
    Arg.AssocArray = G_sLenovo_ManagementControllerAssociations;\
    Arg.AgentInit = IBM_ManagementController_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ManagementController_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ManagementController;\
    Arg.GetKeyProperty = IBM_ManagementController_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ManagementController_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ManagementController_GetProperty;\
    Arg.KeyPropertyList = IBM_ManagementControllerKeyPropertyList;\
    Arg.PropertyList = IBM_ManagementControllerPropertyList;\
    Arg.propertyNo = sizeof(IBM_ManagementControllerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ManagementControllerKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_MANAGEMENTCONTROLLERASSONUM;\
    Arg.AssocArray = G_sLenovo_ManagementControllerAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_ManagementController_GetProperty( 
                                               CMPICount nInstIndex,
                                               CMPICount nPropIndex,
                                               void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_ManagementController_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_ManagementController_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_ManagementController, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_ManagementController, &rc);
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
        data = IBM_ManagementController_GetProperty(nInstIndex, nKeyIndex | IBM_MANAGEMENTCONTROLLER_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_ManagementController_GenerateObjectPath( 
                                                             char **properties,
                                                             CMPICount InstIndex,
                                                             void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_ManagementController_GetInstance( 
                                                 CMPIInstanceMI *mi,
                                                 const CMPIContext *ctx,
                                                 const CMPIResult *rslt,
                                                 const CMPIObjectPath *op,
                                                 const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ManagementController_EnumInstances( 
#else
CMPIStatus IBM_ManagementController_EnumerateInstances( 
#endif
                                                        CMPIInstanceMI *mi,
                                                        const CMPIContext *ctx,
                                                        const CMPIResult *rslt,
                                                        const CMPIObjectPath *op,
                                                        const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ManagementController_EnumInstanceNames( 
#else
CMPIStatus IBM_ManagementController_EnumerateInstanceNames( 
#endif
                                                            CMPIInstanceMI *mi,
                                                            const CMPIContext *ctx,
                                                            const CMPIResult *rslt,
                                                            const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_ManagementController_Associators( 
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
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_ManagementController_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_ManagementController_References( 
                                                CMPIAssociationMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char *resultClass,
                                                const char *role,
                                                const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_ManagementController_ReferenceNames( 
                                                    CMPIAssociationMI *mi,
                                                    const CMPIContext *ctx,
                                                    const CMPIResult *rslt,
                                                    const CMPIObjectPath *op,
                                                    const char *resultClass,
                                                    const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_ManagementController_CheckSelectorSet( 
                                                     const CMPIObjectPath *op,
                                                     CMPIBoolean bAllKey,
                                                     void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);
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

CMPIStatus IBM_ManagementController_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);

    if (Arg.AgentInit)
    {
        pAgentDataPtr = Arg.AgentInit(0);
    }

    /* Get index of instance by objectpath */
    nIndex = IBM_ManagementController_CheckSelectorSet(op, CMPITRUE, pAgentDataPtr);

    if (nIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    /* invoke method */
    if (0 == strcmp(method, "RequestStateChange"))
    {
        value.uint32 = IBM_ManagementController_InstAgent_RequestStateChange((CMPIContext *)ctx, (UINT32) nIndex, in, out);
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
CMPIData *IBM_ManagementController_GetMethodName()
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

#endif

#ifndef _BROKER_SFCB
CMPIData *IBM_ManagementController_GetMethodParameters(const char * MethodName)
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

CMPIStatus IBM_ManagementController_ModifyInstance(
                                      CMPIInstanceMI *mi, 
                                      const CMPIContext *ctx, 
                                      const CMPIResult *rslt, 
                                      const CMPIObjectPath *op,
                                      const CMPIInstance * inst,
                                      const char **properties
                                      )
{

    CMPIStatus rc = {CMPI_RC_OK, NULL};
    CMPICount instIndex = 0;
    sClassUtilArg Arg;
    void *pAgentDataPtr = NULL;
    CMPIData data;
    CMPIString *dataStr = NULL;  
    UINT8 *szName = NULL;
    AVCT_DM_VarListStatus    varStatus;
    AVCT_DM_VarListError     varError;
    UINT16 u16Value = 0;
    INT32 s32RC = 0;
    int i = 0;
    int tmp_aim_value = 0;
    char pUserName[MAX_STR_LEN];
      
    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg);

    if (inst == NULL) 
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto EXIT;
    }
    
#if IBM_MANAGEMENTCONTROLLER_INIT_SUPPORT
    pAgentDataPtr = Arg.AgentInit(0);
#endif    
    
    instIndex = IBM_ManagementController_CheckSelectorSet(op, CMPITRUE, pAgentDataPtr);
    if(INSTANCE_INDEX_INVALID == instIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto EXIT;
    }
    /* PrimaryOwnerContact */
    data = inst->ft->getProperty(inst, PROPERTYNAME_PrimaryOwnerContact,&rc);
    if ((rc.rc != CMPI_RC_OK))
    {
         goto EXIT_RELEASE;
    }
    if (data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto EXIT_RELEASE;
    }  
    
    dataStr = CMPIData2String(&data);
    szName = (UINT8 *)dataStr->ft->getCharPtr(dataStr, &rc);
    varStatus = SETVARVALUE(STRING, 
                            AVCT_DM_DEFVARLIST, 
                            0, 
                            0, 
                            true,
                            "s/Server_Info/config/service_and_support/service_contact/contact_email",
                            &varError,
                            (char *)szName);
    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);
    
    if (AVCT_DM_VarListStatus_OK != varStatus)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto EXIT_RELEASE;
    }
    
    /* HostPowerOffDelay */
    data = inst->ft->getProperty(inst, PROPERTYNAME_HostPowerOffDelay,&rc);
    if ((rc.rc != CMPI_RC_OK))
    {
         goto EXIT_RELEASE;
    }
    if (data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto EXIT_RELEASE;
    }  
    u16Value = data.value.uint16;

    /* ValueMap { "0", "1", "2", "3", "4", "5", "6", "7", "8",  "9", "10", "11", "12", "13"}, 
     * Values { "Infinite", "0.5 minute", "1 minute", "2 minutes", "3 minutes", "4 minutes","5 minutes", "7.5 minutes", "10 minutes", "15 minutes", "20 minutes", "30 minutes", "60 minutes", "120 minutes"},Write]
     */
    aim_config_get_int("watchdog_power_off_delay", &tmp_aim_value);
    
    for (i=0; i < 14; i++)
    {
        if (u16Value == i)
        {
            s32RC = aim_config_set_int("watchdog_power_off_delay", SaHostPowerOffDelay[i], TRUE);
            break;
        }
    }
   
    if(!s32RC)
    {
        rc.rc = CMPI_RC_ERR_FAILED;                                  
    }

   CMPIGetUserNameFromContext(ctx, pUserName);
    if(tmp_aim_value  != u16Value)
    {
        if(sw_msg_dispatcher(SW_MSGID_SERVER_POWER_OFF_DELAY_CHANGED, (void *) pUserName) != CEM_RC_OK)
        {
            printf("Generate sw message %d failed!!\n", SW_MSGID_SERVER_POWER_OFF_DELAY_CHANGED);
        }        
    }

    /* IPMIEnablementState */
    data = inst->ft->getProperty(inst, PROPERTYNAME_IPMIEnablementState,&rc);
    if ((rc.rc != CMPI_RC_OK))
    {
         goto EXIT_RELEASE;
    }
    if (data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto EXIT_RELEASE;
    }  
    u16Value = data.value.uint16;

    /* ValueMap { "1", "2", "3"}, 
        * Values {"On", "Off", "Undetermined"}
      */
    s32RC = SetIPMIEnablementState(u16Value);

    if(s32RC&&(s32RC!=2))
    {
        rc.rc = CMPI_RC_ERR_FAILED;
    }

EXIT_RELEASE:
    CMPIDataRelease(&data);
    
EXIT:
#if IBM_MANAGEMENTCONTROLLER_INIT_SUPPORT
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

/* IBM_ManagementController Class Service Function */
CMPIStatus Lenovo_ManagementControllerService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_ManagementController,
                                     CIM_ComputerSystemService);
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
            rc = IBM_ManagementController_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_ManagementController_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_ManagementController_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_MANAGEMENTCONTROLLER_INIT_SUPPORT
            rc.msg = (void*) &IBM_ManagementController_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_MANAGEMENTCONTROLLER_INIT_SUPPORT
            rc.msg = (void*) &IBM_ManagementController_InstAgent_Destroy;
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
            rc = IBM_ManagementController_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_ManagementController_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ManagementController_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ManagementController_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_ManagementController_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_ManagementController_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_ManagementController_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            role = va_arg(argptr, CMPIInstance *);
            properties = va_arg(argptr, char **);
            rc = IBM_ManagementController_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, role, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_ManagementController_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_ManagementController_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_ManagementController_GetMethodParameters(method);
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
GenNotSupportInstanceMICreateInstance(IBM_ManagementController);
// GenNotSupportInstanceMIModifyInstance(IBM_ManagementController);
GenNotSupportInstanceMIDeleteInstance(IBM_ManagementController);
GenNotSupportInstanceMIExecQuery(IBM_ManagementController);
GenNotSupportInstanceMICleanup(IBM_ManagementController);

/* MI factory function */
CMInstanceMIStub( IBM_ManagementController_,
                  Lenovo_ManagementController_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_ManagementController);

CMMethodMIStub( IBM_ManagementController_,
                Lenovo_ManagementController_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_MANAGEMENTCONTROLLER_INIT_SUPPORT /* You can turn on this flag in IBM_ManagementControllerAgent.h */
#define PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ManagementController_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ManagementController;\
    Arg.GetNextInstIndex = IBM_ManagementController_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ManagementControllerKeyPropertyList;\
    Arg.PropertyList = IBM_ManagementControllerPropertyList;\
    Arg.propertyNo = sizeof(IBM_ManagementControllerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ManagementControllerKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_ManagementController_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ManagementController_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ManagementController_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ManagementController;\
    Arg.GetNextInstIndex = IBM_ManagementController_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ManagementControllerKeyPropertyList;\
    Arg.PropertyList = IBM_ManagementControllerPropertyList;\
    Arg.propertyNo = sizeof(IBM_ManagementControllerPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ManagementControllerKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_ManagementController Class Service Function */
CMPIStatus Lenovo_ManagementControllerService( 
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

/* Gets the Arg of Class IBM_ManagementController Function */
sClassUtilArg IBM_ManagementController_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_MANAGEMENTCONTROLLER_ARG( Arg );

    return (Arg);
}

#endif
