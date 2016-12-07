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
#include <emerson/cemgr/swe_function_table.h>

#include "ClassUtil.h"
#include "PropertyNames.h"
#include "ClassNames.h"
#include <emerson/aem/aem_lib.h>

#ifndef _BROKER_SFCB
#include "MethodNames.h"
#endif
/* Include class header files */
#include <RegisterClass.h>

/* Include agent header files */
#include <RegisterClassAgent.h>

#include "../AssociationTable.h"
#include "../instAgent/incEX/IBM_TimeServiceAgent.h"
#include "LogUtil.h"
#include <SmashCommonUtil.h>


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_TimeService class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_TimeService = (CMPIUint8 *)CLASSNAMETEXT_IBM_TimeService;

/* Property List */
static const char * const IBM_TimeServicePropertyList[] = 
{
    PROPERTYNAME_AutomaticDSTAdjustment,
    PROPERTYNAME_Region
};

/* Key property List */
static const char * const IBM_TimeServiceKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_TIMESERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_TimeServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TimeService;\
    Arg.GetKeyProperty = IBM_TimeService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_TimeService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_TimeService_GetProperty;\
    Arg.KeyPropertyList = IBM_TimeServiceKeyPropertyList;\
    Arg.PropertyList = IBM_TimeServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_TimeServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TimeServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_TIMESERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_TimeServiceAssociations;\
    Arg.AgentInit = IBM_TimeService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_TimeService_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TimeService;\
    Arg.GetKeyProperty = IBM_TimeService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_TimeService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_TimeService_GetProperty;\
    Arg.KeyPropertyList = IBM_TimeServiceKeyPropertyList;\
    Arg.PropertyList = IBM_TimeServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_TimeServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TimeServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_TIMESERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_TimeServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_TIMESERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_TimeServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TimeService;\
    Arg.GetKeyProperty = IBM_TimeService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_TimeService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_TimeService_GetProperty;\
    Arg.KeyPropertyList = IBM_TimeServiceKeyPropertyList;\
    Arg.PropertyList = IBM_TimeServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_TimeServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TimeServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_TIMESERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_TimeServiceAssociations;\
    Arg.AgentInit = IBM_TimeService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_TimeService_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TimeService;\
    Arg.GetKeyProperty = IBM_TimeService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_TimeService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_TimeService_GetProperty;\
    Arg.KeyPropertyList = IBM_TimeServiceKeyPropertyList;\
    Arg.PropertyList = IBM_TimeServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_TimeServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TimeServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_TIMESERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_TimeServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_TimeService_GetProperty( 
                                      CMPICount nInstIndex,
                                      CMPICount nPropIndex,
                                      void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_TimeService_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_TimeService_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_TimeService, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_TimeService, &rc);
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
        data = IBM_TimeService_GetProperty(nInstIndex, nKeyIndex | IBM_TIMESERVICE_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_TimeService_GenerateObjectPath( 
                                                    char **properties,
                                                    CMPICount InstIndex,
                                                    void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_TimeService_GetInstance( 
                                        CMPIInstanceMI *mi,
                                        const CMPIContext *ctx,
                                        const CMPIResult *rslt,
                                        const CMPIObjectPath *op,
                                        const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_TimeService_EnumInstances( 
#else
CMPIStatus IBM_TimeService_EnumerateInstances( 
#endif
                                               CMPIInstanceMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_TimeService_EnumInstanceNames( 
#else
CMPIStatus IBM_TimeService_EnumerateInstanceNames( 
#endif
                                                   CMPIInstanceMI *mi,
                                                   const CMPIContext *ctx,
                                                   const CMPIResult *rslt,
                                                   const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_TimeService_Associators( 
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
    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_TimeService_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_TimeService_References( 
                                       CMPIAssociationMI *mi,
                                       const CMPIContext *ctx,
                                       const CMPIResult *rslt,
                                       const CMPIObjectPath *op,
                                       const char *resultClass,
                                       const char *role,
                                       const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_TimeService_ReferenceNames( 
                                           CMPIAssociationMI *mi,
                                           const CMPIContext *ctx,
                                           const CMPIResult *rslt,
                                           const CMPIObjectPath *op,
                                           const char *resultClass,
                                           const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_TimeService_ModifyInstance(
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
    TimeZoneNode *psTimeZoneData = NULL;
    char szValue[10] = { 0 };
    unsigned int uiSize = 0;
    BOOLEAN bValue = FALSE;
    UINT8 u8InputMask = 0;
    UINT8 u8ModifyMask = 0;
    int i = 0;
    int iDST = 0;
    UINT32 sIBM_TimeZoneTblSize = 0;
    BOOLEAN bRet = FALSE;

    if (inst == NULL)
    {
        return (rc);
    }

    if (IsITEBlade())
    {
        rc.rc = CMPI_RC_ERR_NOT_SUPPORTED;
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    
#if IBM_TIMESERVICE_INIT_SUPPORT
    pAgentDataPtr = IBM_TimeService_InstAgent_Init(0);
#endif

    if (!pAgentDataPtr)
    {
        return (rc);
    }

    psTimeZoneData = (TimeZoneNode *) pAgentDataPtr;
    
    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (INSTANCE_INDEX_INVALID == nIndex)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_TimeServicePropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    sIBM_TimeZoneTblSize = sizeof(sIBM_TimeZoneTbl) / sizeof(TimeZoneNode);

    /* get parameter AutomaticDSTAdjustment */
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_AutomaticDSTAdjustment, CMPI_boolean, &bValue, NULL, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s), error code is %d.", __FUNCTION__, PROPERTYNAME_AutomaticDSTAdjustment, rc.rc);
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        u8InputMask = u8InputMask | 1;
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    /* get parameter Region */
    uiSize = 10;
    rc.rc = CIMClassUtil_GetPropertyValue(inst, PROPERTYNAME_Region, CMPI_string, szValue, &uiSize, __FUNCTION__);
    if ((rc.rc != CMPI_RC_OK) && (rc.rc != CMPI_RC_ERR_NO_SUCH_PROPERTY))
    {
        logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to get property(%s), error code is %d.", __FUNCTION__, PROPERTYNAME_Region, rc.rc);
        goto CLEAN;    
    }
    else if (CMPI_RC_OK == rc.rc)
    {
        if (strlen(szValue) > 0)
        {
            u8InputMask = u8InputMask | 2;
        }
        else
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- The property(%s) is empty value.", __FUNCTION__, PROPERTYNAME_Region);
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto CLEAN;
        }
    }
    //Ignore the CMPI_RC_ERR_NO_SUCH_PROPERTY

    switch (u8InputMask)
    {
        case 0:
            
            logTraceCIM(LOG_LEV_INFO, "%s()- No input modified properties.", __FUNCTION__);
            rc.rc = CMPI_RC_OK;
            goto CLEAN;

        case 1:
            
            if (((psTimeZoneData->s32DST > DST_OFF) && (!bValue)) || ((DST_OFF == psTimeZoneData->s32DST) && (bValue)))
            {
                if (bValue)
                {
                    /* Check if current gmt supports DST_ON */
                    for (i = 0; i < sIBM_TimeZoneTblSize; i++)
                    {
                        if (strcmp((char *) psTimeZoneData->u8GMT, (char *) sIBM_TimeZoneTbl[i].u8GMT) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            if (DST_ON == sIBM_TimeZoneTbl[i].s32DST)
                            {
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                
                    if (i == sIBM_TimeZoneTblSize)
                    {
                        logTraceCIM(LOG_LEV_ERROR, "%s()- Cannot just modify the property(%s) to true at %s.", __FUNCTION__, PROPERTYNAME_AutomaticDSTAdjustment, (char *) psTimeZoneData->u8GMT);
                        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                        goto CLEAN;
                    }
                
                }
                
                u8ModifyMask = u8ModifyMask | 1;
                iDST = bValue ? DST_ON : DST_OFF;
            }
            
            break;

        case 2:
            
            if (strcmp((char *) szValue, (char *) psTimeZoneData->u8Value) != 0)
            {
                int iPossibleIndex = sIBM_TimeZoneTblSize;
                
                /* Try to find the index of element which has the same region and match current DST */
                for (i = 0; i < sIBM_TimeZoneTblSize; i++)
                {
                    if ((0 == (strcmp((char *) szValue, sIBM_TimeZoneTbl[i].u8Value))))
                    {
                        if ((DST_SPECIAL == sIBM_TimeZoneTbl[i].s32DST) ||
                            ((DST_OFF == psTimeZoneData->s32DST) && (DST_OFF == sIBM_TimeZoneTbl[i].s32DST)) ||
                            ((psTimeZoneData->s32DST > DST_OFF) && (DST_ON == sIBM_TimeZoneTbl[i].s32DST)))
                        {
                            break;
                        }
                        else
                        {
                            /* Find  the element which has the same region but DST does not match current DST */
                            /* It is possible element if no other match */
                            iPossibleIndex = i;
                        }
                    }
                }
                
                if (i == sIBM_TimeZoneTblSize)
                {
                    if (iPossibleIndex == sIBM_TimeZoneTblSize)
                    {
                        logTraceCIM(LOG_LEV_ERROR, "%s()- The property(%s) is incorrect value.", __FUNCTION__, PROPERTYNAME_Region);
                        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                        goto CLEAN;
                    }
                    else
                    {
                        i = iPossibleIndex;
                    }
                }

                u8ModifyMask = u8ModifyMask | 2;
                iDST = sIBM_TimeZoneTbl[i].s32DST;
            }

            break;

        case 3:
            
            if (((psTimeZoneData->s32DST > DST_OFF) && (!bValue)) || ((DST_OFF == psTimeZoneData->s32DST) && (bValue)) || (strcmp((char *) szValue, (char *) psTimeZoneData->u8Value) != 0))
            {
                /* Try to find the index of element which has the same region and  DST */
                for (i = 0; i < sIBM_TimeZoneTblSize; i++)
                {
                    if ((0 == (strcmp((char *) szValue, sIBM_TimeZoneTbl[i].u8Value))) &&
                        (((bValue) && (DST_SPECIAL == sIBM_TimeZoneTbl[i].s32DST)) ||
                         ((!bValue) && (DST_OFF == sIBM_TimeZoneTbl[i].s32DST)) ||
                         ((bValue) && (DST_ON == sIBM_TimeZoneTbl[i].s32DST))))
                    {
                        break;
                    }
                }
                
                if (i == sIBM_TimeZoneTblSize)
                {
                    logTraceCIM(LOG_LEV_ERROR, "%s()- The value of properties %s(%s) and %s(%s) are not matched value.",
                                __FUNCTION__, PROPERTYNAME_AutomaticDSTAdjustment, bValue ? "True" : "False",
                                PROPERTYNAME_Region, szValue);
                    rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                    goto CLEAN;
                }
                
                u8ModifyMask = u8ModifyMask | 3;
                iDST = sIBM_TimeZoneTbl[i].s32DST;
            }
            break;
            
        default:
            logTraceCIM(LOG_LEV_ERROR, "%s()- Unknow mask(%d).", __FUNCTION__, u8InputMask);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
    }

    if (u8ModifyMask)
    {
        logTraceCIM(LOG_LEV_INFO, "%s()- Try to call aim_config_set_int(clock_dst_status, %d).", __FUNCTION__, iDST);

        if (!aim_config_set_int((char *) "clock_dst_status", iDST, TRUE)) /* Set the corresponding DST mode */
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_int(clock_dst_status, %d).", __FUNCTION__, iDST);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }

        if (u8ModifyMask & 2)
        {
            logTraceCIM(LOG_LEV_INFO, "%s()- Try to call aim_config_set_str(clock_gmt, %s).", __FUNCTION__, (char *) sIBM_TimeZoneTbl[i].u8GMT);
            
            if (!aim_config_set_str((char *) "clock_gmt", (char *) sIBM_TimeZoneTbl[i].u8GMT, TRUE))
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(clock_gmt, %s).", __FUNCTION__, (char *) sIBM_TimeZoneTbl[i].u8GMT);
                rc.rc = CMPI_RC_ERR_FAILED;
                goto CLEAN;
            }

            logTraceCIM(LOG_LEV_INFO, "%s()- Try to call aim_config_set_str(clock_dst_special_type, %s).", __FUNCTION__, (char *) sIBM_TimeZoneTbl[i].u8SpecialDST);

            if (!aim_config_set_str((char *) "clock_dst_special_type", (char *) sIBM_TimeZoneTbl[i].u8SpecialDST, TRUE))
            {
                logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_config_set_str(clock_dst_special_type, %s).", __FUNCTION__, (char *) sIBM_TimeZoneTbl[i].u8SpecialDST);
                rc.rc = CMPI_RC_ERR_FAILED;
                goto CLEAN;
            }
        }
        
        bRet = aim_event_occurred("pm_event_clock_config_changed", 0, NULL);
        if (bRet == FALSE)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_event_occurred(pm_event_clock_config_changed).", __FUNCTION__);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }

        /* Sync to hardware clock */
        bRet = aim_event_occurred(EVENT_HWCLOCK_UPDATE, 0, NULL);
        if (bRet == FALSE)
        {
            logTraceCIM(LOG_LEV_ERROR, "%s()- Failed to call aim_event_occurred(%s).", __FUNCTION__, EVENT_HWCLOCK_UPDATE);
            rc.rc = CMPI_RC_ERR_FAILED;
            goto CLEAN;
        }
        
        IBM_TimeService_GenerateSWE((CMPIContext *) ctx);
    }
    else
    {
        logTraceCIM(LOG_LEV_INFO, "%s()- No need to modify any properties.", __FUNCTION__);
    }
    
    rc.rc = CMPI_RC_OK;
    
CLEAN:
    
#if IBM_TIMESERVICE_INIT_SUPPORT
    IBM_TimeService_InstAgent_Destroy(pAgentDataPtr);
#endif

    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

CMPIStatus IBM_TimeService_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg);
    
#if IBM_TIMESERVICE_INIT_SUPPORT
    pAgentDataPtr = IBM_TimeService_InstAgent_Init(0);
#endif

    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (nIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    /* invoke method */
    if (0 == strcmp(method, "ManageTime"))
    {
        value.uint32 = IBM_TimeService_InstAgent_ManageTime((UINT32) nIndex, (CMPIContext *)ctx, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_METHOD_NOT_FOUND;
    }

CLEAN:
    
#if IBM_TIMESERVICE_INIT_SUPPORT
    IBM_TimeService_InstAgent_Destroy(pAgentDataPtr);
#endif

    return (rc);
}

#ifndef _BROKER_SFCB
CMPIData *IBM_TimeService_GetMethodName()
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
    value.chars = (char *) METHODNAME_ManageTime;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

CMPIData *IBM_TimeService_GetMethodParameters(const char * MethodName)
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

    if (0 == strcmp(MethodName, METHODNAME_ManageTime))
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
            value.chars = (char *) TYPENAME_boolean;
            pArgs->ft->addArg(pArgs, PARAMNAME_GetRequest,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_datetime;
            pArgs->ft->addArg(pArgs, PARAMNAME_TimeData,&value,CMPI_chars);
            value.chars = "ref CIM_ManagedElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_ManagedElement,&value,CMPI_chars);
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

/* IBM_TimeService Class Service Function */
CMPIStatus Lenovo_TimeServiceService( 
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
    char **properties = NULL;
    char *className = NULL;




    CMPIInstance *inst = NULL;
    char *method;
    CMPIArgs *in;
    CMPIArgs *out;

    if (actionID == CLASS_SERVICE_ISA_LITE)
    {
        va_start(argptr, op);
        className = va_arg(argptr, char *);
        va_end(argptr);
    }

    rc = CIMClassUtil_CheckClassName(actionID, mi, ctx, rslt, op, 
                                     className,
                                     (char *) CLASSNAME_Lenovo_IBM_TimeService,
                                     CIM_TimeServiceService);
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
            rc = IBM_TimeService_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_TimeService_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_TimeService_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_TIMESERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_TimeService_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_TIMESERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_TimeService_InstAgent_Destroy;
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
            rc = IBM_TimeService_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_TimeService_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_TimeService_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_TimeService_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_TimeService_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_TimeService_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_TimeService_InstAgent_GetMaxIndex;
            break;
    
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_TimeService_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_TimeService_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;
    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_TimeService_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_TimeService_GetMethodParameters(method);
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
GenNotSupportInstanceMICreateInstance(IBM_TimeService);
// GenNotSupportInstanceMIModifyInstance(IBM_TimeService);
GenNotSupportInstanceMIDeleteInstance(IBM_TimeService);
GenNotSupportInstanceMIExecQuery(IBM_TimeService);
GenNotSupportInstanceMICleanup(IBM_TimeService);

/* MI factory function */
CMInstanceMIStub( IBM_TimeService_,
                  Lenovo_TimeService_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_TimeService);

CMMethodMIStub( IBM_TimeService_,
                Lenovo_TimeService_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_TIMESERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_TimeServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_TimeService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TimeService;\
    Arg.GetNextInstIndex = IBM_TimeService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_TimeServiceKeyPropertyList;\
    Arg.PropertyList = IBM_TimeServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_TimeServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TimeServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_TimeService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_TimeService_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_TimeService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TimeService;\
    Arg.GetNextInstIndex = IBM_TimeService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_TimeServiceKeyPropertyList;\
    Arg.PropertyList = IBM_TimeServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_TimeServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TimeServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_TimeService Class Service Function */
CMPIStatus Lenovo_TimeServiceService( 
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

/* Gets the Arg of Class IBM_TimeService Function */
sClassUtilArg IBM_TimeService_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_TIMESERVICE_ARG( Arg );

    return (Arg);
}

#endif
