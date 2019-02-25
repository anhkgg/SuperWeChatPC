#pragma once
#include <windows.h>

typedef int(* SDK_Initialize)(void);

typedef int(*SDK_UnInitialize)(void);

typedef int(* SDK_AntiRevokeMsg)(void);

typedef int(* SDK_UnAntiRevokeMsg)(void);

typedef int(* SDK_StartSaveVoiceMsg)(
    /* [string][in] */ wchar_t *path);

typedef int(* SDK_StopSaveVoiceMsg)(void);

typedef int(* SDK_SendTextMsg)(
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *msg);

typedef int(*SDK_SendImageMsg)(
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *path);

typedef struct _WECHAT_SDK_INTERFACE
{
    SDK_Initialize Initialize;
    SDK_UnInitialize UnInitialize;
    SDK_AntiRevokeMsg AntiRevokeMsg;
    SDK_UnAntiRevokeMsg UnAntiRevokeMsg;
    SDK_StartSaveVoiceMsg StartSaveVoiceMsg;
    SDK_StopSaveVoiceMsg StopSaveVoiceMsg;
    SDK_SendTextMsg SendTextMsg;
    SDK_SendImageMsg SendImageMsg;
}WechatSDKInterface, *PWechatSDKInterface;