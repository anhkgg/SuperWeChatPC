#pragma once

int CoreWSDKClkRecvTextMsg(
    /* [in] */ unsigned int funptr,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *msg);

int CoreWSDKClkRecvTransferMsg(
    /* [in] */ unsigned int funptr,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *tid,
    /* [string][in] */ wchar_t *msg);

int CoreWSDKClkRecvPayMsg(
    /* [in] */ unsigned int funptr,
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *tid,
    /* [string][in] */ wchar_t *msg);