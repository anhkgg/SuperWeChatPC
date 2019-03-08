#include "stdafx.h"
#include "sdk.h"
#include "../WeChatSDKCore/sdkclk_h.h"

//callback

int WSDKClkRecvTextMsg(
    /* [in] */ unsigned int funptr,
    /* [in] */ int pid,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *msg)
{
    OutputDebugStringA("sdkclk: WSDKClkRecvTextMsg");
    if (funptr)
    {
        ((PFNRECVTEXTMSG_CALLBACK)funptr)(pid, wxid, msg);
    }
    return 0;
}

int WSDKClkRecvTransferMsg(
    /* [in] */ unsigned int funptr,
    /* [in] */ int pid,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t* tid,
    /* [string][in] */ wchar_t *msg)
{
    OutputDebugStringA("sdkclk: WSDKClkRecvTransferMsg");
    if (funptr)
    {
        ((PFNRECVMONEYMSG_CALLBACK)funptr)(pid, wxid, tid, msg);
    }
    return 0;
}

int WSDKClkRecvPayMsg(
    /* [in] */ unsigned int funptr,
    /* [in] */ int pid,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t* tid,
    /* [string][in] */ wchar_t *msg)
{
    OutputDebugStringA("sdkclk: WSDKClkRecvPayMsg");
    if (funptr)
    {
        ((PFNRECVMONEYMSG_CALLBACK)funptr)(pid, wxid, tid, msg);
    }
    return 0;
}