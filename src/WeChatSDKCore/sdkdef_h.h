

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for sdkdef.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __sdkdef_h_h__
#define __sdkdef_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __WechatSDK_INTERFACE_DEFINED__
#define __WechatSDK_INTERFACE_DEFINED__

/* interface WechatSDK */
/* [implicit_handle][version][uuid] */ 

int WSDKInitialize( void);

int WSDKUninitialize( void);

int WSDKAntiRevokeMsg( void);

int WSDKUnAntiRevokeMsg( void);

int WSDKStartSaveVoiceMsg( 
    /* [string][in] */ wchar_t *path);

int WSDKStopSaveVoiceMsg( void);

int WSDKSendTextMsg( 
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *msg);

int WSDKSendImageMsg( 
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *path);

int WSDKRecvTextMsg( 
    /* [in] */ unsigned int funptr);

int WSDKRecvTransferMsg( 
    /* [in] */ unsigned int funptr);

int WSDKRecvPayMsg( 
    /* [in] */ unsigned int funptr);


extern handle_t WechatRs_IfHandle;


extern RPC_IF_HANDLE WechatSDK_v1_0_c_ifspec;
extern RPC_IF_HANDLE WechatSDK_v1_0_s_ifspec;
#endif /* __WechatSDK_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


