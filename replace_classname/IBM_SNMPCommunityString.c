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
/* Retreive ADAM var */
#include <emerson/ab/avct_dm_ADAMLib.h>
#include <emerson/ab/avct_dm_VarList.h>
#include <emerson/ab/avct_SharedMem.h>
#include <emerson/ab/avct_SharedList.h>

/* Include base class' header file here */
/* TBD */

#ifdef _BROKER_SFCB
#include <mimacs.h>
CMPIBroker *TheBroker;
#endif

/* IBM_SNMPCommunityString class name */
const CMPIUint8 *CLASSNAME_Lenovo_IBM_SNMPCommunityString = (CMPIUint8 *)CLASSNAMETEXT_IBM_SNMPCommunityString;

/* Property List */
static const char * const IBM_SNMPCommunityStringPropertyList[] = 
{
    PROPERTYNAME_CommunityString,
    PROPERTYNAME_ElementName,
    PROPERTYNAME_EnabledState,
    PROPERTYNAME_NameFormat,
    PROPERTYNAME_TransportAddresses,
    PROPERTYNAME_TypeOfAccess
};

/* Key property List */
static const char * const IBM_SNMPCommunityStringKeyPropertyList[] = 
{
    PROPERTYNAME_CreationClassName,
    PROPERTYNAME_Name,
    PROPERTYNAME_SystemCreationClassName,
    PROPERTYNAME_SystemName
};

#ifndef _CEMGR_SW
#ifdef _BROKER_SFCB
#if IBM_SNMPCOMMUNITYSTRING_INIT_SUPPORT /* You can turn on this flag in IBM_SNMPCommunityStringAgent.h */
#define PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPCommunityString;\
    Arg.GetKeyProperty = IBM_SNMPCommunityString_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPCommunityString_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPCommunityString_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPCommunityStringKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPCommunityStringPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPCommunityStringPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPCommunityStringKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPCOMMUNITYSTRINGASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPCommunityStringAssociations;\
    Arg.AgentInit = IBM_SNMPCommunityString_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SNMPCommunityString_InstAgent_Destroy;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPCommunityString;\
    Arg.GetKeyProperty = IBM_SNMPCommunityString_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPCommunityString_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPCommunityString_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPCommunityStringKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPCommunityStringPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPCommunityStringPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPCommunityStringKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPCOMMUNITYSTRINGASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPCommunityStringAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.AssocTable = NULL;\
    Arg.AssocTableSize = 0;\
    Arg.pNameSpace = "root/cimv2";
#endif

#else
#if IBM_SNMPCOMMUNITYSTRING_INIT_SUPPORT /* You can turn on this flag in IBM_SNMPCommunityStringAgent.h */
#define PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPCommunityString;\
    Arg.GetKeyProperty = IBM_SNMPCommunityString_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPCommunityString_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPCommunityString_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPCommunityStringKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPCommunityStringPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPCommunityStringPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPCommunityStringKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPCOMMUNITYSTRINGASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPCommunityStringAssociations;\
    Arg.AgentInit = IBM_SNMPCommunityString_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SNMPCommunityString_InstAgent_Destroy;
#else
#define PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg) \
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPCommunityString;\
    Arg.GetKeyProperty = IBM_SNMPCommunityString_GetKeyProperty;\
    Arg.GetNextInstIndex = IBM_SNMPCommunityString_InstAgent_GetNext;\
    Arg.GetProperty = IBM_SNMPCommunityString_GetProperty;\
    Arg.KeyPropertyList = IBM_SNMPCommunityStringKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPCommunityStringPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPCommunityStringPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPCommunityStringKeyPropertyList)/sizeof(char *);\
    Arg.AssocNo = G_u32Lenovo_SNMPCOMMUNITYSTRINGASSONUM;\
    Arg.AssocArray = G_sLenovo_SNMPCommunityStringAssociations;\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;
#endif
#endif

/* Get Properties value */
CMPIData IBM_SNMPCommunityString_GetProperty( 
                                              CMPICount nInstIndex,
                                              CMPICount nPropIndex,
                                              void *pAgentDataPtr)
{
    CMPIData data = {CMPI_null, CMPI_badValue, {0}};
    void *pValue;
    UINT32 u32Type;

    data.state = CMPI_badValue;

    pValue = IBM_SNMPCommunityString_InstAgent_GetProperty(nInstIndex, nPropIndex, &u32Type, pAgentDataPtr);

    if (u32Type != AGENT_INVALID_TYPE)
    {
        data = CIMClassUtil_CovertPtrToCMPIData(pValue, u32Type);
        CIMClassUtil_FreePtr(pValue, u32Type);
    }
    return (data);
}

/* Get Key Properties value */
CMPIData IBM_SNMPCommunityString_GetKeyProperty( 
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
        data.value.string = TheBroker->eft->newString(TheBroker, (char *) CLASSNAME_Lenovo_IBM_SNMPCommunityString, &rc);
        #else
        data.value.string = TheBroker.eft->newString(&TheBroker, CLASSNAME_Lenovo_IBM_SNMPCommunityString, &rc);
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
        data = IBM_SNMPCommunityString_GetProperty(nInstIndex, nKeyIndex | IBM_SNMPCOMMUNITYSTRING_KEYPROPERTY, pAgentDataPtr);
    }
    return (data);
}

/* Generate ObjectPath with index */
CMPIObjectPath *IBM_SNMPCommunityString_GenerateObjectPath( 
                                                            char **properties,
                                                            CMPICount InstIndex,
                                                            void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);
    return (CIMClassUtil_GenerateObjectPath(properties, InstIndex, &Arg, pAgentDataPtr) );
}

/* InstanceMI.getInstance */
CMPIStatus IBM_SNMPCommunityString_GetInstance( 
                                                CMPIInstanceMI *mi,
                                                const CMPIContext *ctx,
                                                const CMPIResult *rslt,
                                                const CMPIObjectPath *op,
                                                const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);
    return (CIMClassUtil_GetInstance(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstances */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SNMPCommunityString_EnumInstances( 
#else
CMPIStatus IBM_SNMPCommunityString_EnumerateInstances( 
#endif
                                                       CMPIInstanceMI *mi,
                                                       const CMPIContext *ctx,
                                                       const CMPIResult *rslt,
                                                       const CMPIObjectPath *op,
                                                       const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);
    return (CIMClassUtil_EnumerateInstances(mi, ctx, rslt, op, (const char **) properties, &Arg) );
}

/* InstanceMI.enumerateInstanceNames */
#ifdef _BROKER_SFCB
CMPIStatus IBM_SNMPCommunityString_EnumInstanceNames( 
#else
CMPIStatus IBM_SNMPCommunityString_EnumerateInstanceNames( 
#endif
                                                           CMPIInstanceMI *mi,
                                                           const CMPIContext *ctx,
                                                           const CMPIResult *rslt,
                                                           const CMPIObjectPath *op)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);
    return (CIMClassUtil_EnumerateInstanceNames(mi, ctx, rslt, op, &Arg) );
}

#ifndef _BROKER_SFCB
/* Generate Association */
CMPIStatus IBM_SNMPCommunityString_Associators( 
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
    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);
    return (CIMClassUtil_Associators(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties, &Arg) );
}

/* Generate Instance with index */
CMPIStatus IBM_SNMPCommunityString_AssociatorNames( 
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
    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);
    return (CIMClassUtil_AssociatorNames(mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, &Arg) );
}

/* Reference related function */
CMPIStatus IBM_SNMPCommunityString_References( 
                                               CMPIAssociationMI *mi,
                                               const CMPIContext *ctx,
                                               const CMPIResult *rslt,
                                               const CMPIObjectPath *op,
                                               const char *resultClass,
                                               const char *role,
                                               const char **properties)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);
    return (CIMClassUtil_References(mi, ctx, rslt, op, resultClass, role, (const char **) properties, &Arg) );
}

CMPIStatus IBM_SNMPCommunityString_ReferenceNames( 
                                                   CMPIAssociationMI *mi,
                                                   const CMPIContext *ctx,
                                                   const CMPIResult *rslt,
                                                   const CMPIObjectPath *op,
                                                   const char *resultClass,
                                                   const char *role)
{
    sClassUtilArg Arg;
    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);
    return (CIMClassUtil_ReferenceNames(mi, ctx, rslt, op, resultClass, role, &Arg) );
}
#endif

/* Check selector set*/
CMPICount IBM_SNMPCommunityString_CheckSelectorSet( 
                                                    const CMPIObjectPath *op,
                                                    CMPIBoolean bAllKey,
                                                    void *pAgentDataPtr)
{
    sClassUtilArg Arg;
    CMPICount nIndex = 0;
    CMPICount nNextIndex;

    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);
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

#define MyPrint(fmt, args...) do { \
            FILE *fp = fopen("/dev/console", "a+"); \
            if (fp) \
            { \
                fprintf(fp, "###: " fmt "\n", ## args); \
                fclose(fp); \
            } \
        }while( 0 ) ;

/* Modify CommunityString, TypeOfAccess, TransportAddresses   */
CMPIStatus IBM_SNMPCommunityString_ModifyInstance(
                                      CMPIInstanceMI *mi, 
                                      const CMPIContext *ctx, 
                                      const CMPIResult *rslt, 
                                      const CMPIObjectPath *op,
                                      const CMPIInstance * inst,
                                      const char **properties
                                      )
{
    //sClassUtilArg Arg;   
    CMPIStatus rc = {CMPI_RC_ERR_INVALID_PARAMETER, NULL};
   
    CMPICount instIndex,nCount = 0;
    CMPIData data;
    char *pInputCommunityString = NULL;
    //char szName[32]={0};
    char* pIPAddr=NULL;
    //char* pName=NULL;
    int iLen = 0;
  
    CMPIString *dataStr = NULL;
    //CMPIUint16 AccessType=0;
    UINT16 uAccessType=0;
    CMPIArray *pAddresses ;
    int i,j;
    AVCT_DM_VarListStatus    varStatus;
    AVCT_DM_VarListError     varError;
    int bSetValue =0;
    CMOHandle g_coHandle=0;
    char szInputCommunityString[16]={0};
    char adam_var_name[64]={0};
    char adam_row_name[64]={0};    
    char swe_username[MAX_STR_LEN] = {0};
    char szIPAddr[NUM_OF_TRANSPORT_ADDRESSES][64];
    char ip_addr[64]={0};

    memset(szIPAddr, (char)0, sizeof(szIPAddr));

    if(inst==NULL)
    {
       rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
       return (rc);
    }

    //PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg);

    /* Check SelectorSet */
    instIndex = IBM_SNMPCommunityString_CheckSelectorSet(op, CMPITRUE, NULL);
    if (instIndex == INSTANCE_INDEX_INVALID)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
        return (rc);
    }
    
#if 0

    /* 0.Name  -Key property        */
    /* Determine the index of instance from this property */
    data = inst->ft->getProperty(inst,"Name", &rc);
    if ((data.state != CMPI_goodValue)||(rc.rc!= CMPI_RC_OK))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY; */
        goto EXIT;
    }   
    dataStr = CMPIData2String(&data);   
    if(dataStr == NULL)
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* CMPI_RC_ERR_NO_SUCH_PROPERTY */
        goto EXIT;
    }  
    pName = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
    iLen = strlen(pName);
#if 1
    if((iLen >=sizeof(szName))||(iLen==0))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* Invalid community length */
        goto EXIT;

    }
#endif
    strncpy(szName, pName, sizeof(szName));
    sscanf(szName, "SNMPCommunityString:%d", &commStringIndex);
    /* check index is valid */
    if((commStringIndex > 3)||(commStringIndex <=0))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* Invalid community length */
        goto EXIT;

    }
#endif

    //TODO
    printf("instIndex(%d)\n", instIndex);

    /* check index is valid  or not                                                    */
    /* in current design, there are three community string table here */ 
    /* index should be between 0~2 */
    if((instIndex >= NUM_OF_CUMMUNITY_STRING) || (instIndex < 0))
    {
        rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* Invalid community length */
        return (rc);

    }
    /* adam row name */
    snprintf(adam_row_name, sizeof(adam_row_name),"%s[%d]",VAR_COMMUNITY_TABLE,(instIndex+1));

    /* Get input property  */
    
    /* 1.CommunityString  */
    data = inst->ft->getProperty(inst,PROPERTYNAME_CommunityString, &rc);
    if ((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
    {
        dataStr = CMPIData2String(&data);   
        if(dataStr == NULL)
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto EXIT;
        } 

        pInputCommunityString = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
        if(pInputCommunityString==NULL)
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER; 
            goto EXIT;
        }

        iLen = strlen(pInputCommunityString);
        if(iLen >=sizeof(szInputCommunityString))
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;  /* Invalid community length */
            goto EXIT;
        }

        if (iLen >= 0)
        {
            memcpy(szInputCommunityString, pInputCommunityString, iLen);
            /* Set "CommunityString"  */ 
#if 1
            varStatus = SETCOLVALUE(STRING,
                                    AVCT_DM_DEFVARLIST,
                                    g_coHandle, 0, false,
                                    adam_row_name,
                                    VAR_COMMUNITY_TABLE_NAME,
                                    &varError,
                                    szInputCommunityString);
#else
            snprintf(adam_var_name, sizeof(adam_var_name),"%s[%d]/%s",VAR_COMMUNITY_TABLE,(instIndex+1),VAR_COMMUNITY_TABLE_NAME);
            varStatus = SETVARVALUE(STRING,
                                    AVCT_DM_DEFVARLIST,
                                    g_coHandle, 0, false,
                                    adam_var_name,
                                    &varError,
                                    szInputCommunityString);
#endif
            if(varStatus != AVCT_DM_VarListStatus_OK)
            {
                /* set failed */
                rc.rc = CMPI_RC_ERR_FAILED;
                goto EXIT;
            }
            bSetValue=1;
        
            /* Set username for software event 75 */
            CMPIGetUserNameFromContext(ctx, swe_username);
            if (AVCT_DM_VarListError_OK == varError) 
            {
                varStatus = SETVARVALUE(STRING,
                                        AVCT_DM_DEFVARLIST,
                                        g_coHandle, 0, false,
                                        VAR_SNMP_SWE_USERNAME,
                                        &varError,
                                        swe_username);
            }
            /* failed to set adam var */
            if (AVCT_DM_VarListError_OK != varError) 
            {
                rc.rc = CMPI_RC_ERR_FAILED;
                goto EXIT;
            }
        }
        
        SafeCMRelease(dataStr);
        dataStr = NULL;
        CMPIDataRelease(&data);
    }

    /* 2.TypeOfAccess */
    data = inst->ft->getProperty(inst,"TypeOfAccess", &rc);
    if ((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
    {
        if(data.type == CMPI_uint16)
        {
            uAccessType = (&data)->value.uint16; /* 1,2,3 */
        }
        else
        {
            goto EXIT;
        }
        /* check uAccessType is valid value */
        if((uAccessType!=TYPE_OF_ACCESS_READ_ONLY)&&(uAccessType!=TYPE_OF_ACCESS_READ_WRITE)&&(uAccessType!=TYPE_OF_ACCESS_TRAPS))
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto EXIT;

        }

#if 1
        varStatus = SETCOLVALUE(UINT,
                                AVCT_DM_DEFVARLIST,
                                g_coHandle, 0, false,
                                adam_row_name,
                                VAR_COMMUNITY_TABLE_VIEWTYPE,
                                &varError,
                                uAccessType);

#else
        snprintf(adam_var_name, sizeof(adam_var_name),"%s[%d]/%s",VAR_COMMUNITY_TABLE,(instIndex+1),VAR_COMMUNITY_TABLE_VIEWTYPE);
        varStatus = SETVARVALUE(UINT,
                                AVCT_DM_DEFVARLIST,
                                g_coHandle, 0, false,
                                adam_var_name,
                                &varError,
                                uAccessType);
#endif
        if(varStatus !=0)
        {
            /* set failed */
            rc.rc = CMPI_RC_ERR_FAILED;
            goto EXIT;
           
        }
        bSetValue=1;
        CMPIDataRelease(&data);
    }
    else
    {
        rc.rc = CMPI_RC_ERR_FAILED;
        goto EXIT;

    }

    /* 3.TransportAddresses */
    data = inst->ft->getProperty(inst,"TransportAddresses", &rc);
    if ((data.state == CMPI_goodValue)&&(rc.rc== CMPI_RC_OK))
    {
        if (data.type & CMPI_ARRAY) 
        {
            pAddresses = data.value.array;
            nCount = pAddresses->ft->getSize(pAddresses, &rc);
            /* check input # of addresses */
            if(nCount != NUM_OF_TRANSPORT_ADDRESSES)
            {
                /* invalid # of addreesses */
                rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
                goto EXIT;
            }

            for ( j = 0; j < NUM_OF_TRANSPORT_ADDRESSES; j++)
            {
                CMPIData sTransportData;
                sTransportData = pAddresses->ft->getElementAt(pAddresses, j, &rc);
                if ((CMPI_goodValue != sTransportData.state)||(rc.rc!=CMPI_RC_OK))
                {
                    //CMPIDataRelease(&sTransportData);
                    //rc.rc = CMPI_RC_ERR_FAILED; /* get element failed */
                    //goto EXIT;
                    continue;
                }

                dataStr = CMPIData2String(&sTransportData);
                CMPIDataRelease(&sTransportData);
                if (dataStr == NULL)
                {
                    rc.rc = CMPI_RC_ERR_FAILED; /* convert to string failed */
                    goto EXIT;
                }

                pIPAddr = (char *) dataStr->ft->getCharPtr(dataStr, &rc);
                if (pIPAddr )
                {
                    if(strlen(pIPAddr) >= sizeof(szIPAddr[j]))
                    {
                        rc.rc = CMPI_RC_ERR_FAILED; /* length is over 64*/
                        goto EXIT;
                    }
                    strncpy(szIPAddr[j],pIPAddr,strlen(pIPAddr));
                }
                else
                {
                    rc.rc = CMPI_RC_ERR_FAILED; /* convert to string failed */
                    goto EXIT;
                }

                SafeCMRelease(dataStr);
                dataStr = NULL;
            }

            for(i=0; i<NUM_OF_TRANSPORT_ADDRESSES; i++)
            {
                snprintf(adam_var_name, sizeof(adam_var_name),"%s[%d]/%s%d",VAR_COMMUNITY_TABLE,(instIndex+1),VAR_COMMUNITY_TABLE_IP,(i+1));
                memset(ip_addr, 0, sizeof (ip_addr));

	            varStatus = GETVARVALUE(STRING,
			                                    AVCT_DM_DEFVARLIST,
			                                    0,
			                                    0,
			                                    false,
			                                    adam_var_name,
			                                    &varError,
			                                    (void *) &ip_addr,sizeof(ip_addr));
                
                if (varStatus == AVCT_DM_VarListStatus_OK)
                {
                    if (0 != strcmp(ip_addr, szIPAddr[i]))
                    {
                        varStatus = SETVARVALUE(STRING,
                                                AVCT_DM_DEFVARLIST,
                                                g_coHandle, 0, false,
                                                adam_var_name,
                                                &varError,
                                                szIPAddr[i]);
                        
                        if(varStatus !=0)
                        {
                            /* set failed */
                            rc.rc = CMPI_RC_ERR_FAILED;
                            goto EXIT;
                        }
                    }
                }
            }
            
            bSetValue=1;
            CMPIDataRelease(&data);
        }
        else
        {
            rc.rc = CMPI_RC_ERR_INVALID_PARAMETER;
            goto EXIT;
        }
    }

    if(bSetValue==1)
    {
        rc.rc = CMPI_RC_OK;
        return (rc);
    }

   
EXIT:
    
    SafeCMRelease(dataStr);

    CMPIDataRelease(&data);
    {
        CMPIValue value;
        value.uint32 = rc.rc;
        CMReturnData(rslt, &value, CMPI_uint32);
        CMReturnDone(rslt);
    }

    return (rc);
 
}


/* IBM_SNMPCommunityString Class Service Function */
CMPIStatus Lenovo_SNMPCommunityStringService( 
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
                                     (char *) CLASSNAME_Lenovo_IBM_SNMPCommunityString,
                                     CIM_SNMPCommunityStringService);
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
            rc = IBM_SNMPCommunityString_GetInstance((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCES: /* enumerateInstancese */
            va_start(argptr, op);
            properties = va_arg(argptr, char **);
            rc = IBM_SNMPCommunityString_EnumerateInstances((CMPIInstanceMI*) mi, ctx, rslt, op, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ENUMERATEINSTANCENAMES: /* enumerateInstanceNames */
            rc = IBM_SNMPCommunityString_EnumerateInstanceNames((CMPIInstanceMI*) mi, ctx, rslt, op);
            break;

    #endif
        case CLASS_SERVICE_INSTAGENT_INIT: /* init memory space */
        #if IBM_SNMPCOMMUNITYSTRING_INIT_SUPPORT
            rc.msg = (void*) &IBM_SNMPCommunityString_InstAgent_Init;
        #else
            rc.msg = NULL;
        #endif
            break;

        case CLASS_SERVICE_INSTAGENT_DESTROY: /* destroy memory space */
        #if IBM_SNMPCOMMUNITYSTRING_INIT_SUPPORT
            rc.msg = (void*) &IBM_SNMPCommunityString_InstAgent_Destroy;
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
            rc = IBM_SNMPCommunityString_Associators((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_ASSOCIATORNAMES: /*associatorNames*/
            va_start(argptr, op);
            asscClass = (char *)  va_arg(argptr,  const char *);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            resultRole = (char *) va_arg(argptr,  const char *);
            rc = IBM_SNMPCommunityString_AssociatorNames((CMPIAssociationMI *) mi, ctx, rslt, op, asscClass, resultClass, role, resultRole);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCES: /*references*/
            va_start(argptr, op);
            properties = (char **)  va_arg(argptr,  char **);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SNMPCommunityString_References((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role, (const char **) properties);
            va_end(argptr);
            break;

        case CLASS_SERVICE_REFERENCENAMES: /*referenceNames*/
            va_start(argptr, op);
            resultClass = (char *) va_arg(argptr,  const char *);
            role = (char *) va_arg(argptr,  const char *);
            rc = IBM_SNMPCommunityString_ReferenceNames((CMPIAssociationMI *) mi, ctx, rslt, op, resultClass, role);
            va_end(argptr);
            break;

    #endif
        case CLASS_SERVICE_GENERATE_OBJECTPATH: 
            rc.msg = (void*) &IBM_SNMPCommunityString_GenerateObjectPath;
            break;

        case CLASS_SERVICE_INSTAGENT_NEXT_INDEX: 
            rc.msg = (void*) &IBM_SNMPCommunityString_InstAgent_GetNext;
            break;

        case CLASS_SERVICE_INSTAGENT_MAX_INDEX: 
            rc.msg = (void*) &IBM_SNMPCommunityString_InstAgent_GetMaxIndex;
            break;

    #ifndef _BROKER_SFCB
        case CLASS_SERVICE_MODIFYINSTANCE: 
            /* modify instance service */
            va_start( argptr, op );                                                                                 
            inst = va_arg(argptr, CMPIInstance *);
            properties = va_arg(argptr, char **);
            rc = IBM_SNMPCommunityString_ModifyInstance((CMPIInstanceMI*) mi, ctx, rslt, op, inst, (const char **)properties);
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
GenNotSupportInstanceMICreateInstance(IBM_SNMPCommunityString);
//GenNotSupportInstanceMIModifyInstance(IBM_SNMPCommunityString);
GenNotSupportInstanceMIDeleteInstance(IBM_SNMPCommunityString);
GenNotSupportInstanceMIExecQuery(IBM_SNMPCommunityString);
GenNotSupportInstanceMICleanup(IBM_SNMPCommunityString);

/* MI factory function */
CMInstanceMIStub( IBM_SNMPCommunityString_,
                  Lenovo_SNMPCommunityString_,
                  TheBroker,
                  CMNoHook);

#endif

#else
#if IBM_SNMPCOMMUNITYSTRING_INIT_SUPPORT /* You can turn on this flag in IBM_SNMPCommunityStringAgent.h */
#define PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SNMPCommunityString_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPCommunityString;\
    Arg.GetNextInstIndex = IBM_SNMPCommunityString_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SNMPCommunityStringKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPCommunityStringPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPCommunityStringPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPCommunityStringKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = IBM_SNMPCommunityString_InstAgent_Init;\
    Arg.AgentDestroy = IBM_SNMPCommunityString_InstAgent_Destroy;\
    Arg.pNameSpace = "root/cimv2";
#else
#define PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG(Arg) \
    Arg.AgentGetProperty = IBM_SNMPCommunityString_InstAgent_GetProperty;\
    Arg.ClassName = CLASSNAME_Lenovo_IBM_SNMPCommunityString;\
    Arg.GetNextInstIndex = IBM_SNMPCommunityString_InstAgent_GetNext;\
    Arg.KeyPropertyList = IBM_SNMPCommunityStringKeyPropertyList;\
    Arg.PropertyList = IBM_SNMPCommunityStringPropertyList;\
    Arg.propertyNo = sizeof(IBM_SNMPCommunityStringPropertyList)/sizeof(char *);\
    Arg.KeyPropertyNo = sizeof(IBM_SNMPCommunityStringKeyPropertyList)/sizeof(char *);\
    Arg.AgentInit = NULL;\
    Arg.AgentDestroy = NULL;\
    Arg.pNameSpace = "root/cimv2";
#endif

/* IBM_SNMPCommunityString Class Service Function */
CMPIStatus Lenovo_SNMPCommunityStringService( 
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

/* Gets the Arg of Class IBM_SNMPCommunityString Function */
sClassUtilArg IBM_SNMPCommunityString_GetArg()
{
    sClassUtilArg Arg;

    PREPARE_CLASSUTIL_IBM_SNMPCOMMUNITYSTRING_ARG( Arg );

    return (Arg);
}

#endif
