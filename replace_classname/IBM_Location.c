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
#include <emerson/ab/avct_dm_ADAMLib.h>
#include <emerson/ab/avct_dm_VarList.h>
#include <emerson/aim/libaim.h>
#include "LogUtil.h"

#define MAX_LENGTH 48

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_Location class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_Location = (CMPIUint8 *)CLASSNAMETEXT_IBM_Location;

/* Property List */
static const char * const IBM_LocationPropertyList[] = 
{
    PROPERTYNAME_Address,
    PROPERTYNAME_FullPostalAddr,
    PROPERTYNAME_Location,
    PROPERTYNAME_Rack,
    PROPERTYNAME_Room,
    PROPERTYNAME_Slot,
    PROPERTYNAME_UHeight,
    PROPERTYNAME_UPosition
};

/* Key property List */
static const char * const IBM_LocationKeyPropertyList[] = 
{
    PROPERTYNAME_Name,
    PROPERTYNAME_PhysicalPosition
};

/* ADAM variable List*/
static const char * const IBM_LocationAdamVariableList[] = 
{
    "s/Server_Info/config/service_and_support/system_location/postal_address",
    "s/Server_Info/config/server_properties/general_setting/full_postal_addr",
    "s/Server_Info/config/server_properties/general_setting/location",
    "s/Server_Info/config/server_properties/general_setting/rack_id",
    "s/Server_Info/config/server_properties/general_setting/room_id",
    "s/Server_Info/status/blade_bay",
    "s/Server_Info/status/height_u",
    "s/Server_Info/config/server_properties/general_setting/lowest_u"
};

#define ADAM_VarsToUpdateNamespaces         "s/Server_Info"
#define ADAM_VAR_INFO_SWE_USERNAME          "s/Server_Info/data/swe_username"


#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_LOCATION_INIT_SUPPORT /* You can turn on this flag in IBM_LocationAgent.h */
#define PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_Location;\
    Arg.GetKeyProperty = IBM_Location_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_Location_InstAgent_GetNext;\
    Arg.GetProperty = IBM_Location_GetProperty;\
    Arg.KeyPropertyList = IBM_LocationKeyPropertyList;\
    Arg.PropertyList = IBM_LocationPropertyList;\
    Arg.propertyNo = sizeof(IBM_LocationPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LocationKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LOCATIONASSONUM;\
    Arg.AssocArray = G_sLenovo_LocationAssociations;\
    Arg.AgentInit = IBM_Location_InstAgent_Init;\
    Arg.AgentDestroy = IBM_Location_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_Location;\
    Arg.GetKeyProperty = IBM_Location_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_Location_InstAgent_GetNext;\
    Arg.GetProperty = IBM_Location_GetProperty;\
    Arg.KeyPropertyList = IBM_LocationKeyPropertyList;\
    Arg.PropertyList = IBM_LocationPropertyList;\
    Arg.propertyNo = sizeof(IBM_LocationPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LocationKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LOCATIONASSONUM;\
    Arg.AssocArray = G_sLenovo_LocationAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_LOCATION_INIT_SUPPORT /* You can turn on this flag in IBM_LocationAgent.h */
#define PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_Location;\
    Arg.GetKeyProperty = IBM_Location_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_Location_InstAgent_GetNext;\
    Arg.GetProperty = IBM_Location_GetProperty;\
    Arg.KeyPropertyList = IBM_LocationKeyPropertyList;\
    Arg.PropertyList = IBM_LocationPropertyList;\
    Arg.propertyNo = sizeof(IBM_LocationPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LocationKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LOCATIONASSONUM;\
    Arg.AssocArray = G_sLenovo_LocationAssociations;\
    Arg.AgentInit = IBM_Location_InstAgent_Init;\
    Arg.AgentDestroy = IBM_Location_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_Location;\
    Arg.GetKeyProperty = IBM_Location_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_Location_InstAgent_GetNext;\
    Arg.GetProperty = IBM_Location_GetProperty;\
    Arg.KeyPropertyList = IBM_LocationKeyPropertyList;\
    Arg.PropertyList = IBM_LocationPropertyList;\
    Arg.propertyNo = sizeof(IBM_LocationPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LocationKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_LOCATIONASSONUM;\
    Arg.AssocArray = G_sLenovo_LocationAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_Location_GetProperty( 
                                   CMPICount nInstIndex,
                                   CMPICount nPropIndex,
                                   void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_Location_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_Location_GetKeyProperty( 
                                      CMPICount nInstIndex,
                                      CMPICount nKeyIndex,
                                      void *pAgentDataPtr)
{
    CMPIData data = {CMPI_string, CMPI_badValue, {0}};
        data.state = CMPI_badValue;
    data = IBM_Location_GetProperty(nInstIndex, nKeyIndex | IBM_LOCATION_KEYPROPERTY, pAgentDataPtr);
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_Location_GenerateObjectPath( 
                                                 char **properties,
                                                 CMPICount InstIndex,
                                                 void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_Location_GetInstance( 
                                     CMPIInstanceMI *mi,
                                     const CMPIContext *ctx,
                                     const CMPIResult *rslt,
                                     const CMPIObjectPath *op,
                                     const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_Location_EnumInstances( 
#else
CMPIStatus IBM_Location_EnumerateInstances( 
#endif
                                            CMPIInstanceMI *mi,
                                            const CMPIContext *ctx,
                                            const CMPIResult *rslt,
                                            const CMPIObjectPath *op,
                                            const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_Location_EnumInstanceNames( 
#else
CMPIStatus IBM_Location_EnumerateInstanceNames( 
#endif
                                                CMPIInstanceMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_Location_Associators( 
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
    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_Location_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_Location_References( 
                                    CMPIAssociationMI *mi,
                                    const CMPIContext *ctx,
                                    const CMPIResult *rslt,
                                    const CMPIObjectPath *op,
                                    const char *resultClass,
                                    const char *role,
                                    const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_Location_ReferenceNames( 
                                        CMPIAssociationMI *mi,
                                        const CMPIContext *ctx,
                                        const CMPIResult *rslt,
                                        const CMPIObjectPath *op,
                                        const char *resultClass,
                                        const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_Location_CheckSelectorSet( 
                                         const CMPIObjectPath *op,
                                         CMPIBoolean bAllKey,
                                         void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);
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

CMPIStatus IBM_Location_ModifyInstance(
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
    AVCT_DM_VarListStatus    varStatus;
    AVCT_DM_VarListError     varError;
    int i = 0;
    UINT16 u16Value = 0;
    char szValue[MAX_LENGTH] = {0};
    unsigned int uiSize = 0;
    unsigned long ulValue = 0;
    BOOLEAN bIsSet = FALSE;
    INT8 ai8Value[MAX_LENGTH] = {0};
    PAVCT_DM_VARLIST        infoVars;
    const char*             as_InfoVarsToUpdate[] = { ADAM_VarsToUpdateNamespaces, NULL };
    char pUserName[MAX_STR_LEN];
    CMPIGetUserNameFromContext(ctx, pUserName);
    
    PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg);

    if (inst == NULL) 
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }
    
    if (Arg.AgentInit)
    {
        pAgentDataPtr = Arg.AgentInit(0);
    }
    instIndex = IBM_Location_CheckSelectorSet(op, CMPITRUE, pAgentDataPtr);
    if (INSTANCE_INDEX_INVALID == instIndex)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }
    
    /* Before setting values, get a copy of all namespace variables in var list */
    varStatus = avct_dm_GetUpdatableVars(
                    "cliinfoVars",            // just a name, doesn't matter
                    0, 0, false,            // just use these
                    as_InfoVarsToUpdate,    // a collection of all related namespace
                    &infoVars,              // the name of var list
                    &varError);             // error message
    //logTraceCIM(LOG_LEV_INFO, "%s() ADAM(%d) status value : %d", __FUNCTION__, __LINE__, varStatus); 
    if (AVCT_DM_VarListError_OK != varStatus)
    {
        rc.rc = CMPI_RC_ERR_FAILED; /* Error Occurred */
        goto ERR_EXIT;
    }
    
    for (i = 0; i < Arg.propertyNo; i++)
    {
         /* Slot and uheight are read-only */
         if (IBM_LOCATION_SLOT == i || IBM_LOCATION_UHEIGHT == i)
            continue;

         memset(szValue, 0 , sizeof(szValue));
         memset(ai8Value, 0 , sizeof(ai8Value));
         bIsSet = FALSE;

         logTraceCIM(LOG_LEV_INFO, "%s()- property name : %s %i", __FUNCTION__, IBM_LocationPropertyList[i], i); 

         if (IBM_LOCATION_UPOSITION == i)
         {
             rc.rc = CIMClassUtil_GetPropertyValue(inst, IBM_LocationPropertyList[i], CMPI_uint16, &u16Value, NULL, __FUNCTION__); 
             if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
             {
                 logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s), error code is %d.", __FUNCTION__, IBM_LocationPropertyList[i], rc.rc);
                 goto ERR_EXIT;
             }
             else
             {
                 /* Get value */
                 varStatus = GETVARVALUE(UINT,
                                     AVCT_DM_DEFVARLIST,
                                     0,
                                     0,
                                     true,
                                     IBM_LocationAdamVariableList[i],
                                     &varError,
                                     &ulValue);
                 //logTraceCIM(LOG_LEV_INFO, "%s() ADAM(%d) status value : %d", __FUNCTION__, __LINE__, varStatus); 
                 if (AVCT_DM_VarListStatus_OK == varStatus)
                 {
                     if (ulValue != u16Value)
                     {
                         bIsSet = TRUE; 
                         logTraceCIM(LOG_LEV_INFO, "%s()- property(%s) value from user input and backend is difference.", __FUNCTION__, IBM_LocationPropertyList[i]); 
                     }
                     else
                     {
                         logTraceCIM(LOG_LEV_INFO, "%s()- property(%s) value from user input and backend is the smae.", __FUNCTION__, IBM_LocationPropertyList[i]); 
                         continue;
                     }
                 }
                 else
                 {
                     logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s) by method GETVARVALUE.", __FUNCTION__, IBM_LocationPropertyList[i]);
                     rc.rc = CMPI_RC_ERR_FAILED;
                     goto ERR_EXIT;
                 }

                 if (bIsSet)
                 {
                     /* Set value */
                     varStatus = SETVARVALUE(UINT, 
                                        infoVars, 
                                        0, 
                                        0, 
                                        true,
                                        IBM_LocationAdamVariableList[i],
                                        &varError,
                                        u16Value);
                     //logTraceCIM(LOG_LEV_INFO, "%s() ADAM(%d) status value : %d", __FUNCTION__, __LINE__, varStatus); 
                     if (AVCT_DM_VarListStatus_OK != varStatus)
                     {
                         logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to set property(%s) by method SETVARVALUE.", __FUNCTION__, IBM_LocationPropertyList[i]);
                         rc.rc = CMPI_RC_ERR_FAILED;
                         goto ERR_EXIT;
                     }
                 }
             }
         }
	  else if(IBM_LOCATION_FULLPOSTALADDR == i)  // if modify full post address
	  {
             unsigned int uiSize1 = 301;
		char szValue1[301] = {0};
             INT8 ai8Value1[301] = {0};
				
             rc.rc = CIMClassUtil_GetPropertyValue(inst, IBM_LocationPropertyList[i], CMPI_string, szValue1, &uiSize1, __FUNCTION__);
             if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
             {
                 logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s), error code is %d.", __FUNCTION__, IBM_LocationPropertyList[i], rc.rc);
                 goto ERR_EXIT;
             }
             else
             {
                 /* Get value */
                 varStatus = GETVARVALUE(STRING,
                                    AVCT_DM_DEFVARLIST,
                                    0,
                                    0,                 
                                    true,
                                    IBM_LocationAdamVariableList[i],
                                    &varError,
                                    ai8Value1,
                                    sizeof (ai8Value1));
                 //logTraceCIM(LOG_LEV_INFO, "%s() ADAM(%d) status value : %d", __FUNCTION__, __LINE__, varStatus); 
                 if (AVCT_DM_VarListStatus_OK == varStatus)
                 {
                     if (0 != strcmp(szValue1, ai8Value1))
                     {
                         bIsSet = TRUE; 
                         logTraceCIM(LOG_LEV_INFO, "%s()- property(%s) value from user input and backend is different.", __FUNCTION__, IBM_LocationPropertyList[i]); 
                     }
                     else
                     {
                         logTraceCIM(LOG_LEV_INFO, "%s()- property(%s) value from user input and backend is the same.", __FUNCTION__, IBM_LocationPropertyList[i]); 
                         continue;
                     }
                 }
                 else
                 {
                     logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s) by method GETVARVALUE.", __FUNCTION__, IBM_LocationPropertyList[i]);
                     rc.rc = CMPI_RC_ERR_FAILED;
                     goto ERR_EXIT;
                 }

                 if (bIsSet)
                 {
                     /* Set value */
                     varStatus = SETVARVALUE(STRING, 
                                        infoVars, 
                                        0, 
                                        0, 
                                        true,
                                        IBM_LocationAdamVariableList[i],
                                        &varError,
                                        szValue1);
                     //logTraceCIM(LOG_LEV_INFO, "%s() ADAM(%d) status value : %d", __FUNCTION__, __LINE__, varStatus); 
                     if (AVCT_DM_VarListStatus_OK != varStatus)
                     {
                         logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to set property(%s) by method SETVARVALUE.", __FUNCTION__, IBM_LocationPropertyList[i]);
                         rc.rc = CMPI_RC_ERR_FAILED;
                         goto ERR_EXIT;
                     }
                 }
             }
	   }
         else
         {
             uiSize = MAX_LENGTH;
             rc.rc = CIMClassUtil_GetPropertyValue(inst, IBM_LocationPropertyList[i], CMPI_string, szValue, &uiSize, __FUNCTION__);
             if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
             {
                 logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s), error code is %d.", __FUNCTION__, IBM_LocationPropertyList[i], rc.rc);
                 goto ERR_EXIT;
             }
             else
             {
                 /* Get value */
                 varStatus = GETVARVALUE(STRING,
                                    AVCT_DM_DEFVARLIST,
                                    0,
                                    0,                 
                                    true,
                                    IBM_LocationAdamVariableList[i],
                                    &varError,
                                    ai8Value,
                                    sizeof (ai8Value));
                 //logTraceCIM(LOG_LEV_INFO, "%s() ADAM(%d) status value : %d", __FUNCTION__, __LINE__, varStatus); 
                 if (AVCT_DM_VarListStatus_OK == varStatus)
                 {
                     if (0 != strcmp(szValue, ai8Value))
                     {
                         bIsSet = TRUE; 
                         logTraceCIM(LOG_LEV_INFO, "%s()- property(%s) value from user input and backend is different.", __FUNCTION__, IBM_LocationPropertyList[i]); 
                     }
                     else
                     {
                         logTraceCIM(LOG_LEV_INFO, "%s()- property(%s) value from user input and backend is the same.", __FUNCTION__, IBM_LocationPropertyList[i]); 
                         continue;
                     }
                 }
                 else
                 {
                     logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s) by method GETVARVALUE.", __FUNCTION__, IBM_LocationPropertyList[i]);
                     rc.rc = CMPI_RC_ERR_FAILED;
                     goto ERR_EXIT;
                 }

                 if (bIsSet)
                 {
                     /* Set value */
                     varStatus = SETVARVALUE(STRING, 
                                        infoVars, 
                                        0, 
                                        0, 
                                        true,
                                        IBM_LocationAdamVariableList[i],
                                        &varError,
                                        szValue);
                     //logTraceCIM(LOG_LEV_INFO, "%s() ADAM(%d) status value : %d", __FUNCTION__, __LINE__, varStatus); 
                     if (AVCT_DM_VarListStatus_OK != varStatus)
                     {
                         logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to set property(%s) by method SETVARVALUE.", __FUNCTION__, IBM_LocationPropertyList[i]);
                         rc.rc = CMPI_RC_ERR_FAILED;
                         goto ERR_EXIT;
                     }
                 }
             }
         }
    }

    /* Set username for SWE in namespace */
    varStatus = SETVARVALUE(STRING,                     // adam value type
                            infoVars,                   // the name of var list
                            0, 0, false, 
                            ADAM_VAR_INFO_SWE_USERNAME, // the adam var name
                            &varError, 
                            pUserName);             // value for setting
    //logTraceCIM(LOG_LEV_INFO, "%s() ADAM(%d) status value : %d", __FUNCTION__, __LINE__, varStatus); 
    if (varStatus != AVCT_DM_VarListStatus_OK)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    } 
    
    /* Update values in var list into ADAM */
    varStatus = avct_dm_UpdateVars(infoVars, 0, 0, false, &varError);
    //logTraceCIM(LOG_LEV_INFO, "%s() ADAM(%d) status value : %d", __FUNCTION__, __LINE__, varStatus); 
    if (varStatus != AVCT_DM_VarListStatus_OK)
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto ERR_EXIT;
    }
    /* Trigger aim event to notify slpmgr to register again */
    //aim_event_occurred("event_location_info_changed", 0, NULL);

    rc.rc = CMPI_RC_OK;
    if (Arg.AgentDestroy)
    {
        Arg.AgentDestroy(pAgentDataPtr);
    }
    return (rc);

ERR_EXIT:
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

/* IBM_Location Class Service Function */
CMPIStatus Lenovo_LocationService( 
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
    if (actionID == CLASS_SERVICE_ISA_LITE)
    {
        va_start(argptr, op);
        className = va_arg(argptr, char *);
        va_end(argptr);
    }

    rc = CIMClassUtil_CheckClassName(actionID, mi, ctx, rslt, op, 
                                     className,
                                     (char *) CLASSNAME_Lenovo_IBM_Location,
                                     CIM_LocationService);
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
            rc = IBM_Location_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_Location_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_Location_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_LOCATION_INIT_SUPPORT
            rc.msg = (void*) &IBM_Location_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_LOCATION_INIT_SUPPORT
            rc.msg = (void*) &IBM_Location_InstAgent_Destroy;
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
            rc = IBM_Location_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_Location_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_Location_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_Location_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_Location_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_Location_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_Location_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_INVOKEMETHOD: 
             /* involk method service */
        case CLASS_SERVICE_GETMETHODNAMES:
             /* get method name service */
        case CLASS_SERVICE_GETPARAMETERS:
             /* get method param name service */
        case CLASS_SERVICE_MODIFYINSTANCE: 
            /* modify instance service */
            va_start( argptr, op ); 																				
            role = va_arg(argptr, CMPIInstance *);
            properties = va_arg(argptr, char **);
            rc = IBM_Location_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, role, (const char **)properties);
            va_end( argptr );	
            break;
            
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
GenNotSupportInstanceMICreateInstance(IBM_Location);
//GenNotSupportInstanceMIModifyInstance(IBM_Location);
GenNotSupportInstanceMIDeleteInstance(IBM_Location);
GenNotSupportInstanceMIExecQuery(IBM_Location);
GenNotSupportInstanceMICleanup(IBM_Location);

/* MI factory function */
CMInstanceMIStub( IBM_Location_,
                  Lenovo_Location_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_LOCATION_INIT_SUPPORT /* You can turn on this flag in IBM_LocationAgent.h */
#define PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg) \
    Arg.AgentGetProperty = IBM_Location_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_Location;\
    Arg.GetNextInstIndex = IBM_Location_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_LocationKeyPropertyList;\
    Arg.PropertyList = IBM_LocationPropertyList;\
    Arg.propertyNo = sizeof(IBM_LocationPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LocationKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_Location_InstAgent_Init;\
    Arg.AgentDestroy = IBM_Location_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_LOCATION_ARG(Arg) \
    Arg.AgentGetProperty = IBM_Location_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_Location;\
    Arg.GetNextInstIndex = IBM_Location_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_LocationKeyPropertyList;\
    Arg.PropertyList = IBM_LocationPropertyList;\
    Arg.propertyNo = sizeof(IBM_LocationPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_LocationKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_Location Class Service Function */
CMPIStatus Lenovo_LocationService( 
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

/* Gets the Arg of Class IBM_Location Function */
sClassUtilArg IBM_Location_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_LOCATION_ARG( Arg );

    return (Arg);
}

#endif
