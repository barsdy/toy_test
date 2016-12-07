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
#include <emerson/cemgr/swe_function_table.h>

#ifndef _BROKER_SFCB
#include "MethodNames.h"
#endif
/* Include class header files */
#include <RegisterClass.h>

/* Include agent header files */
#include <RegisterClassAgent.h>

#include "../AssociationTable.h"

#include <emerson/ab/avct_dm_ADAMLib.h>
#include <emerson/ab/avct_ipc.h>
#include <emerson/ab/avct_SharedMem.h>
#include <emerson/ab/avct_SharedList.h>


#define MAX_SESSIONTERMINATESEQ_LEN (14)


/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_TextRedirectionSAP class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_TextRedirectionSAP = (CMPIUint8 *)CLASSNAMETEXT_IBM_TextRedirectionSAP;

/* Property List */
static const char * const IBM_TextRedirectionSAPPropertyList[] = 
{
    PROPERTYNAME_BaudRate,
    PROPERTYNAME_CLIMode,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EnabledState,
    PROPERTYNAME_NumberOfStopBits,
    PROPERTYNAME_ParityInfo,
    PROPERTYNAME_RequestedState,
    PROPERTYNAME_SessionTerminateSequence,
    PROPERTYNAME_TextFlowType
};

/* Key property List */
static const char * const IBM_TextRedirectionSAPKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_TEXTREDIRECTIONSAP_INIT_SUPPORT /* You can turn on this flag in IBM_TextRedirectionSAPAgent.h */
#define PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TextRedirectionSAP;\
    Arg.GetKeyProperty = IBM_TextRedirectionSAP_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_TextRedirectionSAP_InstAgent_GetNext;\
    Arg.GetProperty = IBM_TextRedirectionSAP_GetProperty;\
    Arg.KeyPropertyList = IBM_TextRedirectionSAPKeyPropertyList;\
    Arg.PropertyList = IBM_TextRedirectionSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_TextRedirectionSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TextRedirectionSAPKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_TEXTREDIRECTIONSAPASSONUM;\
    Arg.AssocArray = G_sLenovo_TextRedirectionSAPAssociations;\
    Arg.AgentInit = IBM_TextRedirectionSAP_InstAgent_Init;\
    Arg.AgentDestroy = IBM_TextRedirectionSAP_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TextRedirectionSAP;\
    Arg.GetKeyProperty = IBM_TextRedirectionSAP_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_TextRedirectionSAP_InstAgent_GetNext;\
    Arg.GetProperty = IBM_TextRedirectionSAP_GetProperty;\
    Arg.KeyPropertyList = IBM_TextRedirectionSAPKeyPropertyList;\
    Arg.PropertyList = IBM_TextRedirectionSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_TextRedirectionSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TextRedirectionSAPKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_TEXTREDIRECTIONSAPASSONUM;\
    Arg.AssocArray = G_sLenovo_TextRedirectionSAPAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_TEXTREDIRECTIONSAP_INIT_SUPPORT /* You can turn on this flag in IBM_TextRedirectionSAPAgent.h */
#define PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TextRedirectionSAP;\
    Arg.GetKeyProperty = IBM_TextRedirectionSAP_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_TextRedirectionSAP_InstAgent_GetNext;\
    Arg.GetProperty = IBM_TextRedirectionSAP_GetProperty;\
    Arg.KeyPropertyList = IBM_TextRedirectionSAPKeyPropertyList;\
    Arg.PropertyList = IBM_TextRedirectionSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_TextRedirectionSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TextRedirectionSAPKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_TEXTREDIRECTIONSAPASSONUM;\
    Arg.AssocArray = G_sLenovo_TextRedirectionSAPAssociations;\
    Arg.AgentInit = IBM_TextRedirectionSAP_InstAgent_Init;\
    Arg.AgentDestroy = IBM_TextRedirectionSAP_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TextRedirectionSAP;\
    Arg.GetKeyProperty = IBM_TextRedirectionSAP_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_TextRedirectionSAP_InstAgent_GetNext;\
    Arg.GetProperty = IBM_TextRedirectionSAP_GetProperty;\
    Arg.KeyPropertyList = IBM_TextRedirectionSAPKeyPropertyList;\
    Arg.PropertyList = IBM_TextRedirectionSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_TextRedirectionSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TextRedirectionSAPKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_TEXTREDIRECTIONSAPASSONUM;\
    Arg.AssocArray = G_sLenovo_TextRedirectionSAPAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_TextRedirectionSAP_GetProperty( 
                                             CMPICount nInstIndex,
                                             CMPICount nPropIndex,
                                             void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_TextRedirectionSAP_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_TextRedirectionSAP_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_TextRedirectionSAP, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_TextRedirectionSAP, &rc);
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
        data = IBM_TextRedirectionSAP_GetProperty(nInstIndex, nKeyIndex | IBM_TEXTREDIRECTIONSAP_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_TextRedirectionSAP_GenerateObjectPath( 
                                                           char **properties,
                                                           CMPICount InstIndex,
                                                           void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_TextRedirectionSAP_GetInstance( 
                                               CMPIInstanceMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_TextRedirectionSAP_EnumInstances( 
#else
CMPIStatus IBM_TextRedirectionSAP_EnumerateInstances( 
#endif
                                                      CMPIInstanceMI *mi,
                                                      const CMPIContext *ctx,
                                                      const CMPIResult *rslt,
                                                      const CMPIObjectPath *op,
                                                      const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_TextRedirectionSAP_EnumInstanceNames( 
#else
CMPIStatus IBM_TextRedirectionSAP_EnumerateInstanceNames( 
#endif
                                                          CMPIInstanceMI *mi,
                                                          const CMPIContext *ctx,
                                                          const CMPIResult *rslt,
                                                          const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_TextRedirectionSAP_Associators( 
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
    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_TextRedirectionSAP_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_TextRedirectionSAP_References( 
                                              CMPIAssociationMI *mi,
                                              const CMPIContext *ctx,
                                              const CMPIResult *rslt,
                                              const CMPIObjectPath *op,
                                              const char *resultClass,
                                              const char *role,
                                              const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_TextRedirectionSAP_ReferenceNames( 
                                                  CMPIAssociationMI *mi,
                                                  const CMPIContext *ctx,
                                                  const CMPIResult *rslt,
                                                  const CMPIObjectPath *op,
                                                  const char *resultClass,
                                                  const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_TextRedirectionSAP_CheckSelectorSet( 
                                                   const CMPIObjectPath *op,
                                                   CMPIBoolean bAllKey,
                                                   void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);
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


/* Modify Serial Configuration */
CMPIStatus IBM_TextRedirectionSAP_ModifyInstance(
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
    CMPIData data;
    CMPIString *dataStr = NULL;
    UINT32 u32BaudRate = 0;
    UINT32 u32NumberOfStopBits = 0;
    UINT32 u32ParityInfo = 0;
    UINT32 u32CLIMode = 0;
    UINT8 au8SessionTerminateSeq[MAX_SESSIONTERMINATESEQ_LEN+1];
    char *szSessionTerminateSeq = NULL;
    int iLenSessionTerminateSeq = 0;
    UINT8 au8ParityInfo[10];
    char pNameString[MAX_STR_LEN] = {0};

    AVCT_DM_VarListStatus    varStatus;  /* ADAM status code */
    AVCT_DM_VarListError     varError;   /* ADAM error code */

    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);

    /* Check SelectorSet */
    instIndex = IBM_TextRedirectionSAP_CheckSelectorSet(op, CMPITRUE, NULL);
    if (instIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        goto ERR_EXIT;
    }

    if (!CIMClassUtil_CheckAllPropertyExistence(inst, &Arg, IBM_TextRedirectionSAPPropertyList))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  // CMPI_RC_ERR_NO_SUCH_PROPERTY 
        goto ERR_EXIT;
    }

    if (ctx == NULL)
    {
	    rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
	    goto ERR_EXIT;
    }

    /* Read BaudRate from input property */
    data = inst->ft->getProperty(inst, IBM_TextRedirectionSAPPropertyList[0], &rc);
    if (data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;    
    }

	dataStr = CMPIData2String(&data);
    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;
    } 		
    printf("BaudRate data type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc)); 	   
	u32BaudRate = atoi(dataStr->ft->getCharPtr(dataStr, &rc));

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

	//Set BaudRate
    switch (u32BaudRate)
    {
        case 3:
            u32BaudRate = 9600;
            break;
        case 4:
            u32BaudRate = 19200;
            break;
        case 5:
            u32BaudRate = 38400;
            break;
        case 6:
            u32BaudRate = 57600;
            break;
        case 7:
            u32BaudRate = 115200;
            break;
        default:
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto ERR_EXIT;               
    }
	
    varStatus = SETVARVALUE(UINT, AVCT_DM_DEFVARLIST, 0, 0, true,
                            "s/SerialRedirection/config/baud_rate", &varError, u32BaudRate);

    printf("Set BaudRate-> ret(%i)\n", varStatus); 

    
    if (varStatus != AVCT_DM_VarListStatus_OK)
    {
        printf("modify u32BaudRate error[%d]\n", varStatus);
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }

    /**** Read NumberOfStopBits from input property */
    data = inst->ft->getProperty(inst, IBM_TextRedirectionSAPPropertyList[4], &rc);
    if (data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;    
    }

	dataStr = CMPIData2String(&data);
    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);    
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;
    } 		
    printf("NumberOfStopBits data type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc)); 	   
	u32NumberOfStopBits = atoi(dataStr->ft->getCharPtr(dataStr, &rc));

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

	//Set NumberOfStopBits
    switch (u32NumberOfStopBits)
    {
        case 1:
            u32NumberOfStopBits = 1;
            break;
        case 3:
            u32NumberOfStopBits = 2;
            break;
        default:
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto ERR_EXIT;               
    }

    varStatus = SETVARVALUE(UINT, AVCT_DM_DEFVARLIST, 0, 0, true,
                            "s/SerialRedirection/config/stopbit_num", &varError, u32NumberOfStopBits);

    printf("Set NumberOfStopBits-> ret(%i)\n", varStatus); 

    
    if (varStatus != AVCT_DM_VarListStatus_OK)
    {
        printf("modify u32NumberOfStopBits error[%d]\n", varStatus);
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }

    /**** Read ParityInfo from input property */
    data = inst->ft->getProperty(inst, IBM_TextRedirectionSAPPropertyList[5], &rc);
    if (data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;    
    }

	dataStr = CMPIData2String(&data);
    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);    
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;
    } 		
    printf("ParityInfo data type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc)); 	   
	u32ParityInfo = atoi(dataStr->ft->getCharPtr(dataStr, &rc));

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

	//Set ParityInfo
    memset(au8ParityInfo, 0, sizeof (au8ParityInfo));

    switch (u32ParityInfo)
    {
        case 0:
            snprintf((char *)au8ParityInfo, sizeof(au8ParityInfo), "%s", "none");
            break;
        case 1:
            snprintf((char *)au8ParityInfo, sizeof(au8ParityInfo), "%s", "even");
            break;
        case 2:
            snprintf((char *)au8ParityInfo, sizeof(au8ParityInfo), "%s", "odd");
            break;
        case 3:
            snprintf((char *)au8ParityInfo, sizeof(au8ParityInfo), "%s", "mark");
            break;
        case 4:
            snprintf((char *)au8ParityInfo, sizeof(au8ParityInfo), "%s", "space");
            break;
        default:
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto ERR_EXIT;               
    }


    varStatus = SETVARVALUE(STRING, AVCT_DM_DEFVARLIST, 0, 0, true,
                            "s/SerialRedirection/config/parity_info", &varError, (char *)au8ParityInfo);

    printf("Set ParityInfo-> ret(%i)\n", varStatus); 

    
    if (varStatus != AVCT_DM_VarListStatus_OK)
    {
        printf("modify u32ParityInfo error[%d]\n", varStatus);
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }

    /**** Read CLIMode from input property */
    data = inst->ft->getProperty(inst, IBM_TextRedirectionSAPPropertyList[1], &rc);
    if (data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;    
    }

	dataStr = CMPIData2String(&data);
    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);    
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;
    } 		
    printf("CLIMode data type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc)); 	   
	u32CLIMode = atoi(dataStr->ft->getCharPtr(dataStr, &rc));

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

	//Set CLIMode
    switch (u32CLIMode)
    {
        case 0:
        case 1:
        case 2:
            break;
        default:
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto ERR_EXIT;
    }	
    varStatus = SETVARVALUE(UINT, AVCT_DM_DEFVARLIST, 0, 0, true,
                            "s/SerialRedirection/config/cli_mode", &varError, u32CLIMode);

    printf("Set CLIMode-> ret(%i)\n", varStatus); 

    
    if (varStatus != AVCT_DM_VarListStatus_OK)
    {
        printf("modify u32CLIMode error[%d]\n", varStatus);
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }

    /* Read SessionTerminateSeq from input property */
    data = inst->ft->getProperty(inst, IBM_TextRedirectionSAPPropertyList[7], &rc);
    if (data.state != CMPI_goodValue)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY; */
        goto ERR_EXIT;
    }   
    dataStr = CMPIData2String(&data);   
    if(dataStr == NULL)
    {
        CMPIDataRelease(&data);    
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto ERR_EXIT;
    }       
    
    memset(au8SessionTerminateSeq, 0, sizeof (au8SessionTerminateSeq));
    szSessionTerminateSeq = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
    iLenSessionTerminateSeq = strlen(szSessionTerminateSeq);
    memcpy(au8SessionTerminateSeq, szSessionTerminateSeq, (MAX_SESSIONTERMINATESEQ_LEN >= iLenSessionTerminateSeq) ? iLenSessionTerminateSeq : MAX_SESSIONTERMINATESEQ_LEN);
    printf("iLenSessionTerminateSeq=%d\n", iLenSessionTerminateSeq);
    printf("SessionTerminateSeq data type:[%X] Value:[%s]\n", data.type, (char *)dataStr->ft->getCharPtr(dataStr, &rc));       

    SafeCMRelease(dataStr);
    CMPIDataRelease(&data);

    //Set SessionTerminateSeq
    printf("au8SessionTerminateSeq=%s \n\n", au8SessionTerminateSeq);
    varStatus = SETVARVALUE(STRING, AVCT_DM_DEFVARLIST, 0, 0, true,
                            "s/SerialRedirection/config/keystroke", &varError, (char *)au8SessionTerminateSeq);
    printf("Set SessionTerminateSeq-> ret(%i)\n", varStatus); 

    
    if (varStatus != AVCT_DM_VarListStatus_OK)
    {
        rc.rc = CMPI_RC_ERR_INVALID_HANDLE;
        goto ERR_EXIT;
    }

    CMPIGetUserNameFromContext(ctx, pNameString);
    if(sw_msg_dispatcher(SW_MSGID_SERIAL_PORT_CLI_MODE_CHANGED, pNameString) != CEM_RC_OK)
    {
        printf("Generate sw message %d failed!!\n", SW_MSGID_SERIAL_PORT_CLI_MODE_CHANGED);
    }
	rc.rc = CMPI_RC_OK;

ERR_EXIT:
    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
}

CMPIStatus IBM_TextRedirectionSAP_InvokeMethod( 
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
    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg);

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
    if (0 == strcmp(method, "RequestStateChange"))
    {
        value.uint32 = IBM_TextRedirectionSAP_InstAgent_RequestStateChange((UINT32) nIndex, in, out);
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
CMPIData *IBM_TextRedirectionSAP_GetMethodName()
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

CMPIData *IBM_TextRedirectionSAP_GetMethodParameters(const char * MethodName)
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

/* IBM_TextRedirectionSAP Class Service Function */
CMPIStatus Lenovo_TextRedirectionSAPService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_TextRedirectionSAP,
                                     CIM_TextRedirectionSAPService);
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
            rc = IBM_TextRedirectionSAP_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_TextRedirectionSAP_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_TextRedirectionSAP_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_TEXTREDIRECTIONSAP_INIT_SUPPORT
            rc.msg = (void*) &IBM_TextRedirectionSAP_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_TEXTREDIRECTIONSAP_INIT_SUPPORT
            rc.msg = (void*) &IBM_TextRedirectionSAP_InstAgent_Destroy;
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
            rc = IBM_TextRedirectionSAP_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_TextRedirectionSAP_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_TextRedirectionSAP_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_TextRedirectionSAP_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_TextRedirectionSAP_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_TextRedirectionSAP_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_TextRedirectionSAP_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_INVOKEMETHOD: 
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            in = va_arg(argptr, CMPIArgs *);
            out = va_arg(argptr, CMPIArgs *);
            rc = IBM_TextRedirectionSAP_InvokeMethod(mi, ctx, rslt, op, method, in, out);
            va_end(argptr);
            break;

        case CLASS_SERVICE_GETMETHODNAMES:
            rc.msg = (void *) IBM_TextRedirectionSAP_GetMethodName();
            rc.rc = CMPI_RC_OK;
            break;

        case CLASS_SERVICE_GETPARAMETERS:
            va_start(argptr, op);
            method = va_arg(argptr, char *);
            rc.msg = (void *) IBM_TextRedirectionSAP_GetMethodParameters(method);
            va_end(argptr);
            rc.rc = CMPI_RC_OK;
            break;
        case CLASS_SERVICE_MODIFYINSTANCE: 
            /* modify instance service */
            va_start( argptr, op ); 																				
            inst = va_arg(argptr, CMPIInstance *); 
            properties = va_arg(argptr, char **);
            rc = IBM_TextRedirectionSAP_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_TextRedirectionSAP);
//GenNotSupportInstanceMIModifyInstance(IBM_TextRedirectionSAP);
GenNotSupportInstanceMIDeleteInstance(IBM_TextRedirectionSAP);
GenNotSupportInstanceMIExecQuery(IBM_TextRedirectionSAP);
GenNotSupportInstanceMICleanup(IBM_TextRedirectionSAP);

/* MI factory function */
CMInstanceMIStub( IBM_TextRedirectionSAP_,
                  Lenovo_TextRedirectionSAP_,
                  TheBroker,
                  CMNoHook);

GenNotSupportMethodMICleanup(IBM_TextRedirectionSAP);

CMMethodMIStub( IBM_TextRedirectionSAP_,
                Lenovo_TextRedirectionSAP_,
                TheBroker,
                CMNoHook);

#endif

#else
#if IBM_TEXTREDIRECTIONSAP_INIT_SUPPORT /* You can turn on this flag in IBM_TextRedirectionSAPAgent.h */
#define PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg) \
    Arg.AgentGetProperty = IBM_TextRedirectionSAP_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TextRedirectionSAP;\
    Arg.GetNextInstIndex = IBM_TextRedirectionSAP_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_TextRedirectionSAPKeyPropertyList;\
    Arg.PropertyList = IBM_TextRedirectionSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_TextRedirectionSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TextRedirectionSAPKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_TextRedirectionSAP_InstAgent_Init;\
    Arg.AgentDestroy = IBM_TextRedirectionSAP_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG(Arg) \
    Arg.AgentGetProperty = IBM_TextRedirectionSAP_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_TextRedirectionSAP;\
    Arg.GetNextInstIndex = IBM_TextRedirectionSAP_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_TextRedirectionSAPKeyPropertyList;\
    Arg.PropertyList = IBM_TextRedirectionSAPPropertyList;\
    Arg.propertyNo = sizeof(IBM_TextRedirectionSAPPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_TextRedirectionSAPKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_TextRedirectionSAP Class Service Function */
CMPIStatus Lenovo_TextRedirectionSAPService( 
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

/* Gets the Arg of Class IBM_TextRedirectionSAP Function */
sClassUtilArg IBM_TextRedirectionSAP_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_TEXTREDIRECTIONSAP_ARG( Arg );

    return (Arg);
}

#endif
