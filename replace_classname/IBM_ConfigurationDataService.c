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

//For get user privilege
#include <emerson/securitymgr/sm.h>
#include "LogUtil.h"

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_ConfigurationDataService class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_ConfigurationDataService = (CMPIUint8 *)CLASSNAMETEXT_IBM_ConfigurationDataService;

/* Property List */
static const char * const IBM_ConfigurationDataServicePropertyList[] = 
{
    PROPERTYNAME_FileTransferTimeout,
    PROPERTYNAME_SystemProfilesMode,
    PROPERTYNAME_TransferServiceAliveTimeout
};

/* Key property List */
static const char * const IBM_ConfigurationDataServiceKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_CONFIGURATIONDATASERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_ConfigurationDataServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ConfigurationDataService;\
    Arg.GetKeyProperty = IBM_ConfigurationDataService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ConfigurationDataService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ConfigurationDataService_GetProperty;\
    Arg.KeyPropertyList = IBM_ConfigurationDataServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ConfigurationDataServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ConfigurationDataServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ConfigurationDataServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_CONFIGURATIONDATASERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_ConfigurationDataServiceAssociations;\
    Arg.AgentInit = IBM_ConfigurationDataService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ConfigurationDataService_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ConfigurationDataService;\
    Arg.GetKeyProperty = IBM_ConfigurationDataService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ConfigurationDataService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ConfigurationDataService_GetProperty;\
    Arg.KeyPropertyList = IBM_ConfigurationDataServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ConfigurationDataServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ConfigurationDataServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ConfigurationDataServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_CONFIGURATIONDATASERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_ConfigurationDataServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_CONFIGURATIONDATASERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_ConfigurationDataServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ConfigurationDataService;\
    Arg.GetKeyProperty = IBM_ConfigurationDataService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ConfigurationDataService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ConfigurationDataService_GetProperty;\
    Arg.KeyPropertyList = IBM_ConfigurationDataServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ConfigurationDataServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ConfigurationDataServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ConfigurationDataServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_CONFIGURATIONDATASERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_ConfigurationDataServiceAssociations;\
    Arg.AgentInit = IBM_ConfigurationDataService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ConfigurationDataService_InstAgent_Destroy;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#else
#define PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ConfigurationDataService;\
    Arg.GetKeyProperty = IBM_ConfigurationDataService_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_ConfigurationDataService_InstAgent_GetNext;\
    Arg.GetProperty = IBM_ConfigurationDataService_GetProperty;\
    Arg.KeyPropertyList = IBM_ConfigurationDataServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ConfigurationDataServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ConfigurationDataServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ConfigurationDataServiceKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_CONFIGURATIONDATASERVICEASSONUM;\
    Arg.AssocArray = G_sLenovo_ConfigurationDataServiceAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.u16Reserved = 0;\
    Arg.u16ErrCode = 0;
#endif
#endif

/* Get Properties value */
CMPIData IBM_ConfigurationDataService_GetProperty( 
                                                   CMPICount nInstIndex,
                                                   CMPICount nPropIndex,
                                                   void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_ConfigurationDataService_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_ConfigurationDataService_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_ConfigurationDataService, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_ConfigurationDataService, &rc);
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
        data = IBM_ConfigurationDataService_GetProperty(nInstIndex, nKeyIndex | IBM_CONFIGURATIONDATASERVICE_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_ConfigurationDataService_GenerateObjectPath( 
                                                                 char **properties,
                                                                 CMPICount InstIndex,
                                                                 void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_ConfigurationDataService_GetInstance( 
                                                     CMPIInstanceMI *mi,
                                                     const CMPIContext *ctx,
                                                     const CMPIResult *rslt,
                                                     const CMPIObjectPath *op,
                                                     const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ConfigurationDataService_EnumInstances( 
#else
CMPIStatus IBM_ConfigurationDataService_EnumerateInstances( 
#endif
                                                            CMPIInstanceMI *mi,
                                                            const CMPIContext *ctx,
                                                            const CMPIResult *rslt,
                                                            const CMPIObjectPath *op,
                                                            const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_ConfigurationDataService_EnumInstanceNames( 
#else
CMPIStatus IBM_ConfigurationDataService_EnumerateInstanceNames( 
#endif
                                                                CMPIInstanceMI *mi,
                                                                const CMPIContext *ctx,
                                                                const CMPIResult *rslt,
                                                                const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_ConfigurationDataService_Associators( 
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
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_ConfigurationDataService_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_ConfigurationDataService_References( 
                                                    CMPIAssociationMI *mi,
                                                    const CMPIContext *ctx,
                                                    const CMPIResult *rslt,
                                                    const CMPIObjectPath *op,
                                                    const char *resultClass,
                                                    const char *role,
                                                    const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_ConfigurationDataService_ReferenceNames( 
                                                        CMPIAssociationMI *mi,
                                                        const CMPIContext *ctx,
                                                        const CMPIResult *rslt,
                                                        const CMPIObjectPath *op,
                                                        const char *resultClass,
                                                        const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

CMPIStatus IBM_ConfigurationDataService_InvokeMethod( 
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
    char *pszTmp = NULL;

    enum
    {
       NULL_USER_REQUEST = 0,
       ACCESS_TO_CONTEXT,       // can user access this level of functionality?
       MODIFY_REQUEST,          // modify request (SAVE, RESTORE, CLEAR)
       BROWSE_REQUEST,          // navigation only (no attempt to modify anything)
       MTCE_REQUEST             // RSA maintenance (RESTART, POWER/RESTART, SERVER mgmt)
    };

    char nameString[MAX_STR_LEN] = {0};
    UINT32 u32Role = 0;
    CMPIUint32 ACCESS_DENIED = 5;
    sClassUtilArg Arg;
    
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);

    if (Arg.AgentInit)
    {
        pAgentDataPtr = Arg.AgentInit(0);
    }

    CMPIGetUserNameFromContext(ctx, nameString);
    //logTraceCIM(LOG_LEV_INFO, "%s()- nameString is %s.", __FUNCTION__, nameString);
    CMPIGetUserRoleFromContext(ctx, &u32Role);
    if (!sm_imm_authorized(u32Role, CONFIGURATION_FILE_ACTION, MTCE_REQUEST))
    {
        value.uint32 = ACCESS_DENIED;
        logTraceCIM(LOG_LEV_ERROR, "%s- authorization<name:%s and role:%d> failed\n", __FUNCTION__,nameString,u32Role);
        CMReturnData(rslt, &value, CMPI_uint32);CMReturnDone(rslt);
    }
    else
    {
        pszTmp = Strdup(nameString);
        value.chars = pszTmp;
        in->ft->addArg(in, "UserNameInContext", &value, CMPI_charsptr);
        value.uint32 = u32Role;
        in->ft->addArg(in, "UserPrivilidgeInContext", &value, CMPI_uint32);
    }


    /* Get index of instance by objectpath */
    nIndex = CIMClassUtil_GetObjectpathIdx(op, CMPITRUE, pAgentDataPtr, &Arg);
    if (nIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }

    /* invoke method */
    if (0 == strcmp(method, "BackupToByteStream"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_BackupToByteStream((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "EndConfigurationBackup"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_EndConfigurationBackup((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "ExportConfiguration"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_ExportConfiguration((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "ExportConfigurationDescriptor"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_ExportConfigurationDescriptor((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "GetSystemProfilesStatus"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_GetSystemProfilesStatus((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "ImportConfiguration"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_ImportConfiguration((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "ManageSystemProfiles"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_ManageSystemProfiles((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "RequestSystemProfilesSettings"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_RequestSystemProfilesSettings((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "RestoreDefault"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_RestoreDefault((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "RestoreFromByteStream"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_RestoreFromByteStream((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else if (0 == strcmp(method, "StartConfigurationBackup"))
    {
        value.uint32 = IBM_ConfigurationDataService_InstAgent_StartConfigurationBackup((UINT32) nIndex, in, out);
        CMReturnData(rslt, &value, CMPI_uint32);
		CMReturnDone(rslt);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_METHOD_NOT_FOUND;
    }

CLEAN:
    
    ExistFree(pszTmp);
    
    if (Arg.AgentDestroy)
    {
        Arg.AgentDestroy(pAgentDataPtr);
    }

    return (rc);
}

#ifndef _BROKER_SFCB
CMPIData *IBM_ConfigurationDataService_GetMethodName()
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
    nameArray = (void*) TheBroker.eft->newArray(&TheBroker, 11, CMPI_chars, &status);

    if(!nameArray)
    {
        return (NULL);
    }

    /* add method name */
    value.chars = (char *) METHODNAME_BackupToByteStream;
    nameArray->ft->setElementAt(nameArray, 0, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_EndConfigurationBackup;
    nameArray->ft->setElementAt(nameArray, 1, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_ExportConfiguration;
    nameArray->ft->setElementAt(nameArray, 2, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_ExportConfigurationDescriptor;
    nameArray->ft->setElementAt(nameArray, 3, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_GetSystemProfilesStatus;
    nameArray->ft->setElementAt(nameArray, 4, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_ImportConfiguration;
    nameArray->ft->setElementAt(nameArray, 5, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_ManageSystemProfiles;
    nameArray->ft->setElementAt(nameArray, 6, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_RequestSystemProfilesSettings;
    nameArray->ft->setElementAt(nameArray, 7, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_RestoreDefault;
    nameArray->ft->setElementAt(nameArray, 8, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_RestoreFromByteStream;
    nameArray->ft->setElementAt(nameArray, 9, &value, CMPI_chars);
    value.chars = (char *) METHODNAME_StartConfigurationBackup;
    nameArray->ft->setElementAt(nameArray, 10, &value, CMPI_chars);
    data->value.array = nameArray;
    data->type = CMPI_ARRAY;
    data->state = CMPI_goodValue;
    return (data);
}

CMPIData *IBM_ConfigurationDataService_GetMethodParameters(const char * MethodName)
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

    if (0 == strcmp(MethodName, METHODNAME_BackupToByteStream))
    {
        iMethID = 0;
    }
    else if (0 == strcmp(MethodName, METHODNAME_EndConfigurationBackup))
    {
        iMethID = 1;
    }
    else if (0 == strcmp(MethodName, METHODNAME_ExportConfiguration))
    {
        iMethID = 2;
    }
    else if (0 == strcmp(MethodName, METHODNAME_ExportConfigurationDescriptor))
    {
        iMethID = 3;
    }
    else if (0 == strcmp(MethodName, METHODNAME_GetSystemProfilesStatus))
    {
        iMethID = 4;
    }
    else if (0 == strcmp(MethodName, METHODNAME_ImportConfiguration))
    {
        iMethID = 5;
    }
    else if (0 == strcmp(MethodName, METHODNAME_ManageSystemProfiles))
    {
        iMethID = 6;
    }
    else if (0 == strcmp(MethodName, METHODNAME_RequestSystemProfilesSettings))
    {
        iMethID = 7;
    }
    else if (0 == strcmp(MethodName, METHODNAME_RestoreDefault))
    {
        iMethID = 8;
    }
    else if (0 == strcmp(MethodName, METHODNAME_RestoreFromByteStream))
    {
        iMethID = 9;
    }
    else if (0 == strcmp(MethodName, METHODNAME_StartConfigurationBackup))
    {
        iMethID = 10;
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
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_PassPhrase,&value,CMPI_chars);
            value.chars = "A uint8";
            pArgs->ft->addArg(pArgs, PARAMNAME_Data,&value,CMPI_chars);
            break;

        case 1:
            break;

        case 2:
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ExportURI,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Username,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Password,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_PassPhrase,&value,CMPI_chars);
            break;

        case 3:
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ExportURI,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Username,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Password,&value,CMPI_chars);
            break;

        case 4:
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = "ref CIM_ConcreteJob";
            pArgs->ft->addArg(pArgs, PARAMNAME_Job,&value,CMPI_chars);
            value.chars = "A uint8";
            pArgs->ft->addArg(pArgs, PARAMNAME_Data,&value,CMPI_chars);
            break;

        case 5:
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ImportURI,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Username,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_Password,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_PassPhrase,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ErrorInfo,&value,CMPI_chars);
            break;

        case 6:
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_uint16;
            pArgs->ft->addArg(pArgs, PARAMNAME_Mode,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_boolean;
            pArgs->ft->addArg(pArgs, PARAMNAME_ConfigAvailable,&value,CMPI_chars);
            value.chars = "ref CIM_ConcreteJob";
            pArgs->ft->addArg(pArgs, PARAMNAME_Job,&value,CMPI_chars);
            break;

        case 7:
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_boolean;
            pArgs->ft->addArg(pArgs, PARAMNAME_GetRequest,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_LDAPServerIP,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_uint16;
            pArgs->ft->addArg(pArgs, PARAMNAME_LDAPServerPort,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_LDAPUserID,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_LDAPPassword,&value,CMPI_chars);
            break;

        case 8:
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = "ref IBM_ConfigurationData";
            pArgs->ft->addArg(pArgs, PARAMNAME_CurrentConfig,&value,CMPI_chars);
            break;

        case 9:
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_PassPhrase,&value,CMPI_chars);
            value.chars = "A uint8";
            pArgs->ft->addArg(pArgs, PARAMNAME_Data,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_ErrorInfo,&value,CMPI_chars);
            break;

        case 10:
            value.chars = "ref CIM_ManagedSystemElement";
            pArgs->ft->addArg(pArgs, PARAMNAME_Element,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_RequestedScheme,&value,CMPI_chars);
            value.chars = (char *) TYPENAME_string;
            pArgs->ft->addArg(pArgs, PARAMNAME_PassPhrase,&value,CMPI_chars);
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


CMPIStatus IBM_ConfigurationDataService_ModifyInstance(
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
    UINT64 u64FileTransferTimeoutSec = 0;    
	
    if (inst == NULL)
    {
        return (rc);
    }
	
    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg);

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

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_ConfigurationDataServicePropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto CLEAN;
    }
    if (ctx == NULL)
    {
	    rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto CLEAN;
    }

	/* Read FileTransferTimeout from input property */
	data = inst->ft->getProperty(inst, PROPERTYNAME_FileTransferTimeout, &rc);
    if ((CMPI_goodValue == data.state) && (CMPI_RC_OK == rc.rc) && (CMPI_dateTime == data.type))
    {
        if (CMPIFALSE == (data.value.dateTime->ft->isInterval(data.value.dateTime, &rc)) || (rc.rc != CMPI_RC_OK))
        {
   			printf("[IBM_ConfigurationDataService_ModifyInstance] Invalid value.\n");
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; /* Invalid type */
       		CMPIDataRelease(&data);
            goto CLEAN;
        }
        else
        {
            /* Get binary value (micro-sec) */
            intervalTime = data.value.dateTime->ft->getBinaryFormat(data.value.dateTime, &rc);
            if (CMPI_RC_OK == rc.rc)
            {
            	//printf("[IBM_ConfigurationDataService_ModifyInstance] intervalTime is %llu.\n", intervalTime);
                u64FileTransferTimeoutSec = (intervalTime / 1000000);
            	//printf("[IBM_ConfigurationDataService_ModifyInstance] u64FileTransferTimeoutSec is %llu.\n", u64FileTransferTimeoutSec);
            }
            else
            {
            	printf("[IBM_ConfigurationDataService_ModifyInstance] Faild to get input value.\n");
                rc.rc = CMPI_RC_ERR_FAILED;
        		CMPIDataRelease(&data);                
                goto CLEAN;
            }
        }
    }
	else
	{
    	printf("[IBM_ConfigurationDataService_ModifyInstance] Faild to get input.\n");
		rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;	/* CMPI_RC_ERR_NO_SUCH_PROPERTY */
		CMPIDataRelease(&data);
        goto CLEAN;
	}

	CMPIDataRelease(&data);

    if (aim_config_set_int("conf_transfer_timeout", u64FileTransferTimeoutSec, TRUE))
    {
    	rc.rc = CMPI_RC_OK;
    }
    else
    {
        rc.rc = CMPI_RC_ERR_FAILED;
       	printf("[IBM_ConfigurationDataService_ModifyInstance] Faild to call aim_config_set_int().\n");        
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


/* IBM_ConfigurationDataService Class Service Function */
CMPIStatus Lenovo_ConfigurationDataServiceService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_ConfigurationDataService,
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
            rc = IBM_ConfigurationDataService_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_ConfigurationDataService_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_ConfigurationDataService_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_CONFIGURATIONDATASERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_ConfigurationDataService_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_CONFIGURATIONDATASERVICE_INIT_SUPPORT
            rc.msg = (void*) &IBM_ConfigurationDataService_InstAgent_Destroy;
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
            rc = IBM_ConfigurationDataService_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_ConfigurationDataService_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ConfigurationDataService_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_ConfigurationDataService_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_ConfigurationDataService_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_ConfigurationDataService_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_ConfigurationDataService_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_ConfigurationDataService_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_ConfigurationDataService_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_ConfigurationDataService_GetMethodParameters(method);
            va_end(argptr);
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_MODIFYINSTANCE:
            
            /* modify instance service */
			va_start(argptr, op);																				
			inst = va_arg(argptr, CMPIInstance *); 
			properties = va_arg(argptr, char **);
			rc = IBM_ConfigurationDataService_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **) properties);
			va_end(argptr);	
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
GenNotSupportInstanceMICreateInstance(IBM_ConfigurationDataService);
//GenNotSupportInstanceMIModifyInstance(IBM_ConfigurationDataService);
GenNotSupportInstanceMIDeleteInstance(IBM_ConfigurationDataService);
GenNotSupportInstanceMIExecQuery(IBM_ConfigurationDataService);
GenNotSupportInstanceMICleanup(IBM_ConfigurationDataService);

/* MI factory function */
CMInstanceMIStub( IBM_ConfigurationDataService_,
                  Lenovo_ConfigurationDataService_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_ConfigurationDataService);

CMMethodMIStub( IBM_ConfigurationDataService_,
                Lenovo_ConfigurationDataService_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_CONFIGURATIONDATASERVICE_INIT_SUPPORT /* You can turn on this flag in IBM_ConfigurationDataServiceAgent.h */
#define PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ConfigurationDataService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ConfigurationDataService;\
    Arg.GetNextInstIndex = IBM_ConfigurationDataService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ConfigurationDataServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ConfigurationDataServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ConfigurationDataServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ConfigurationDataServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_ConfigurationDataService_InstAgent_Init;\
    Arg.AgentDestroy = IBM_ConfigurationDataService_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG(Arg) \
    Arg.AgentGetProperty = IBM_ConfigurationDataService_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_ConfigurationDataService;\
    Arg.GetNextInstIndex = IBM_ConfigurationDataService_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_ConfigurationDataServiceKeyPropertyList;\
    Arg.PropertyList = IBM_ConfigurationDataServicePropertyList;\
    Arg.propertyNo = sizeof(IBM_ConfigurationDataServicePropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_ConfigurationDataServiceKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_ConfigurationDataService Class Service Function */
CMPIStatus Lenovo_ConfigurationDataServiceService( 
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

/* Gets the Arg of Class IBM_ConfigurationDataService Function */
sClassUtilArg IBM_ConfigurationDataService_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_CONFIGURATIONDATASERVICE_ARG( Arg );

    return (Arg);
}

#endif
