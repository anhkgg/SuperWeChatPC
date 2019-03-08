#include "stdafx.h"
#include "sdk.h"
#include "rpcutil.h"
#include "sdkclk_h.h"

//for sdkclk.idl

int CoreWSDKClkRecvTextMsg(
    /* [in] */ unsigned int funptr,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *msg)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(&StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = WSDKClkRecvTextMsg(funptr, GetCurrentProcessId(), wxid, msg);
        }
            RpcExcept(1)
        {
            printf("RPC Exception %d/n", RpcExceptionCode());
        }
        RpcEndExcept

            DisconnectSDKServer(&StringBinding);
    }
    return ret;
}

int CoreWSDKClkRecvTransferMsg(
    /* [in] */ unsigned int funptr,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *tid,
    /* [string][in] */ wchar_t *msg)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(&StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = WSDKClkRecvTransferMsg(funptr, GetCurrentProcessId(), wxid, tid, msg);
        }
            RpcExcept(1)
        {
            printf("RPC Exception %d/n", RpcExceptionCode());
        }
        RpcEndExcept

            DisconnectSDKServer(&StringBinding);
    }
    return ret;
}

int CoreWSDKClkRecvPayMsg(
    /* [in] */ unsigned int funptr,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *tid,
    /* [string][in] */ wchar_t *msg)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(&StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = WSDKClkRecvPayMsg(funptr, GetCurrentProcessId(), wxid, tid, msg);
        }
            RpcExcept(1)
        {
            printf("RPC Exception %d/n", RpcExceptionCode());
        }
        RpcEndExcept

            DisconnectSDKServer(&StringBinding);
    }
    return ret;
}