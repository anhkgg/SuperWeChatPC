

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for sdkclk.idl:
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


#ifndef __sdkclk_h_h__
#define __sdkclk_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __WechatSDKClk_INTERFACE_DEFINED__
#define __WechatSDKClk_INTERFACE_DEFINED__

/* interface WechatSDKClk */
/* [implicit_handle][version][uuid] */ 

int WSDKClkRecvTextMsg( 
    /* [in] */ unsigned int funptr,
    /* [in] */ int pid,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *msg);

int WSDKClkRecvTransferMsg( 
    /* [in] */ unsigned int funptr,
    /* [in] */ int pid,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *tid,
    /* [string][in] */ wchar_t *msg);

int WSDKClkRecvPayMsg( 
    /* [in] */ unsigned int funptr,
    /* [in] */ int pid,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *tid,
    /* [string][in] */ wchar_t *msg);


extern handle_t WechatRsClk_IfHandle;


extern RPC_IF_HANDLE WechatSDKClk_v1_0_c_ifspec;
extern RPC_IF_HANDLE WechatSDKClk_v1_0_s_ifspec;
#endif /* __WechatSDKClk_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


