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
#include <emerson/aim/libaim.h>


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_FFDCService class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_FFDCService = (CMPIUint8 *)CLASSNAMETEXT_IBM_FFDCService;

/* Property List */
static const char * const IBM_FFDCServicePropertyList[] = 
{
    PROPERTYNAME_CaptureTimeout,
    PROPERTYNAME_FileTransferTimeout,
    PROPERTYNAME_TransferServiceAliveTimeout
};

/* Key property List */
static const char * const IBM_FFDCServiceKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_FFDCSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_FFDCServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FFDCService;\
    Arg.GetKeyProperty = IBM_FFDCService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_FFDCService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_FFDCService_GetProperty;\
    Arg.KeyPropertyList = IBM_FFDCServiceKeyPropertyList;\
    Arg.PropertyList = IBM_FFDCServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_FFDCServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FFDCServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_FFDCSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_FFDCServiceAssociations;\
    Arg.AgentInit = IBM_FFDCService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_FFDCService_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FFDCService;\
    Arg.GetKeyProperty = IBM_FFDCService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_FFDCService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_FFDCService_GetProperty;\
    Arg.KeyPropertyList = IBM_FFDCServiceKeyPropertyList;\
    Arg.PropertyList = IBM_FFDCServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_FFDCServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FFDCServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_FFDCSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_FFDCServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_FFDCSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_FFDCServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FFDCService;\
    Arg.GetKeyProperty = IBM_FFDCService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_FFDCService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_FFDCService_GetProperty;\
    Arg.KeyPropertyList = IBM_FFDCServiceKeyPropertyList;\
    Arg.PropertyList = IBM_FFDCServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_FFDCServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FFDCServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_FFDCSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_FFDCServiceAssociations;\
    Arg.AgentInit = IBM_FFDCService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_FFDCService_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FFDCService;\
    Arg.GetKeyProperty = IBM_FFDCService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_FFDCService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_FFDCService_GetProperty;\
    Arg.KeyPropertyList = IBM_FFDCServiceKeyPropertyList;\
    Arg.PropertyList = IBM_FFDCServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_FFDCServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FFDCServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_FFDCSERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_FFDCServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_FFDCService_GetProperty( 
                                      CMPICount nInstIndex,
                                      CMPICount nPropIndex,
                                      void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_FFDCService_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_FFDCService_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_FFDCService, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_FFDCService, &rc);
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
        data = IBM_FFDCService_GetProperty(nInstIndex, nKeyIndex | IBM_FFDCSERVICE_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_FFDCService_GenerateObjectPath( 
                                                    char **properties,
                                                    CMPICount InstIndex,
                                                    void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_FFDCService_GetInstance( 
                                        CMPIInstanceMI *mi,
                                        const CMPIContext *ctx,
                                        const CMPIResult *rslt,
                                        const CMPIObjectPath *op,
                                        const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_FFDCService_EnumInstances( 
#else
CMPIStatus IBM_FFDCService_EnumerateInstances( 
#endif
                                               CMPIInstanceMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_FFDCService_EnumInstanceNames( 
#else
CMPIStatus IBM_FFDCService_EnumerateInstanceNames( 
#endif
                                                   CMPIInstanceMI *mi,
                                                   const CMPIContext *ctx,
                                                   const CMPIResult *rslt,
                                                   const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_FFDCService_Associators( 
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
    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_FFDCService_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_FFDCService_References( 
                                       CMPIAssociationMI *mi,
                                       const CMPIContext *ctx,
                                       const CMPIResult *rslt,
                                       const CMPIObjectPath *op,
                                       const char *resultClass,
                                       const char *role,
                                       const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_FFDCService_ReferenceNames( 
                                           CMPIAssociationMI *mi,
                                           const CMPIContext *ctx,
                                           const CMPIResult *rslt,
                                           const CMPIObjectPath *op,
                                           const char *resultClass,
                                           const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_FFDCService_ModifyInstance(
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
    CMPIUint64 intervalTime = 0;
    UINT16 u16FileTransferTimeoutSec = 0;    

    if (inst == NULL)
    {
        return (rc);
    }

    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);

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

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_FFDCServicePropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

	/* Read FileTransferTimeout from input property */
	data = inst->ft->getProperty(inst, PROPERTYNAME_FileTransferTimeout, &rc);
    if ((CMPI_goodValue == data.state) && (CMPI_RC_OK == rc.rc) && (CMPI_dateTime == data.type))
    {
        if (CMPIFALSE == (data.value.dateTime->ft->isInterval(data.value.dateTime, &rc)) || (rc.rc != CMPI_RC_OK))
        {
   			printf("[IBM_FFDCService_ModifyInstance] Invalid value.\n");
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; /* Invalid type */
       		CMPIDataRelease(&data);
            goto CLEAN;
        }
        else
        {
            /* Get binary value (micro-sec) */
            intervalTime = data.value.dateTime->ft->getBinaryFormat(data.value.dateTime, &rc);
            if(CMPI_RC_OK == rc.rc)
            {
            	//printf("[IBM_FFDCService_ModifyInstance] intervalTime is %d.\n", intervalTime);
                u16FileTransferTimeoutSec = (intervalTime / 1000000);
            	//printf("[IBM_FFDCService_ModifyInstance] u16FileTransferTimeoutSec is %d.\n", u16FileTransferTimeoutSec);
            }
            else
            {
            	printf("[IBM_FFDCService_ModifyInstance] Faild to get input value.\n");
                rc.rc = CMPI_RC_ERR_FAILED;
        		CMPIDataRelease(&data);                
                goto CLEAN;            
            }
        }
    }
	else
	{
    	printf("[IBM_FFDCService_ModifyInstance] Faild to get input.\n");
		rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;	/* CMPI_RC_ERR_NO_SUCH_PROPERTY */
		CMPIDataRelease(&data);
		goto CLEAN;
	}

	CMPIDataRelease(&data);

    if (aim_config_set_int("ffdc_transfer_timeout", u16FileTransferTimeoutSec, TRUE))
    {
    	rc.rc = CMPI_RC_OK;
    }
    else
    {
        rc.rc = CMPI_RC_ERR_FAILED;
       	printf("[IBM_FFDCService_ModifyInstance] Faild to call aim_config_set_int().\n");        
    }

    /* check static property values if neccessary */
    /* call modify API here */
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
CMPIStatus IBM_FFDCService_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg);

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
    if (0 == strcmp(method, "EndDataCollection"))
    {
        value.uint32 = IBM_FFDCService_InstAgent_EndDataCollection((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "ExportData"))
    {
        value.uint32 = IBM_FFDCService_InstAgent_ExportData((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "StartDataCollection"))
    {
        value.uint32 = IBM_FFDCService_InstAgent_StartDataCollection((UINT32) nIndex, in, out);
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
CMPIData *IBM_FFDCService_GetMethodName()
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
    nameArray = (void*) TheBroker.eft->newArray(&TheBroker, 3, CMPI_chars, &status);

    if(!nameArray)
    {
        return (NULL);
    }

    /* add method name */
    value.chars = (char *) METHODNAME_EndDataCollection;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_ExportData;
    nameArray->ft->setElementAt(nameArray, 1, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_StartDataCollection;
    nameArray->ft->setElementAt(nameArray, 2, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

CMPIData *IBM_FFDCService_GetMethodParameters(const char * MethodName)
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

    if (0 == strcmp(MethodName, METHODNAME_EndDataCollection))
    {
        iMethID = 0;
    }
    else if (0 == strcmp(MethodName, METHODNAME_ExportData))
    {
        iMethID = 1;
    }
    else if (0 == strcmp(MethodName, METHODNAME_StartDataCollection))
    {
        iMethID = 2;
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
            value.chars = (char *) TYPENAME_boolean;
            pArgs->ft->addArg(pArgs, PARAMNAME_InitializationNeeded,&value,CMPI_chars);
            value.chars = "ref IBM_FFDCData";
            pArgs->ft->addArg(pArgs, PARAMNAME_DataCollectionType,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ExportURI,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Username,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Password,&value,CMPI_chars);
            break;

        case 2:
            value.chars = (char *) TYPENAME_boolean;
            pArgs->ft->addArg(pArgs, PARAMNAME_InitializationNeeded,&value,CMPI_chars);
            value.chars = "ref IBM_FFDCData";
            pArgs->ft->addArg(pArgs, PARAMNAME_DataCollectionType,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_RequestedScheme,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_URI,&value,CMPI_chars);
            break;

    }

    data->value.args = pArgs;
    data->type = CMPI_args;
    data->state = CMPI_goodValue;
    return (data);
}
#endif

/* IBM_FFDCService Class Service Function */
CMPIStatus Lenovo_FFDCServiceService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_FFDCService,
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
            rc = IBM_FFDCService_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_FFDCService_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_FFDCService_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_FFDCSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_FFDCService_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_FFDCSERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_FFDCService_InstAgent_Destroy;
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
            rc = IBM_FFDCService_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_FFDCService_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_FFDCService_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_FFDCService_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_FFDCService_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_FFDCService_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_FFDCService_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE:
            /* modify instance service */
            va_start(argptr, op);
            inst = va_arg(argptr, CMPIInstance *);
            rc = IBM_FFDCService_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_FFDCService_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_FFDCService_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_FFDCService_GetMethodParameters(method);
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
GenNotSupportInstanceMICreateInstance(IBM_FFDCService);
//GenNotSupportInstanceMIModifyInstance(IBM_FFDCService);
GenNotSupportInstanceMIDeleteInstance(IBM_FFDCService);
GenNotSupportInstanceMIExecQuery(IBM_FFDCService);
GenNotSupportInstanceMICleanup(IBM_FFDCService);

/* MI factory function */
CMInstanceMIStub( IBM_FFDCService_,
                  Lenovo_FFDCService_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_FFDCService);

CMMethodMIStub( IBM_FFDCService_,
                Lenovo_FFDCService_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_FFDCSERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_FFDCServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_FFDCService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FFDCService;\
    Arg.GetNextInstIndex = IBM_FFDCService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_FFDCServiceKeyPropertyList;\
    Arg.PropertyList = IBM_FFDCServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_FFDCServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FFDCServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_FFDCService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_FFDCService_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_FFDCService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_FFDCService;\
    Arg.GetNextInstIndex = IBM_FFDCService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_FFDCServiceKeyPropertyList;\
    Arg.PropertyList = IBM_FFDCServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_FFDCServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_FFDCServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_FFDCService Class Service Function */
CMPIStatus Lenovo_FFDCServiceService( 
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

/* Gets the Arg of Class IBM_FFDCService Function */
sClassUtilArg IBM_FFDCService_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_FFDCSERVICE_ARG( Arg );

    return (Arg);
}

#endif
