#include "stdafx.h"
#include "hook.h"
#include "voice.h"

#include "mhook.h"
#pragma comment(lib, "mhook.lib")

extern WxFuncConfig g_WxFuncConfig;

const SuppWxCfg g_Supported_wxVoiceMsg_Version[] = {
    //{ TEXT("2.6.5.38"), 0x247EF1 ,{3, {0x8A, 0x45, 0xF3}, 3, {0x33, 0xc0, 0x90}}},
    //{ TEXT("2.6.6.25"), 0x24BA81 ,{3, {0x8A, 0x45, 0xF3}, 3, {0x33, 0xc0, 0x90}}},
    { TEXT("2.6.6.28"), 0x24D5A0 ,{0}}, //voiicemsg
    { TEXT("2.6.6.44"), 0x24D970 ,{0}}, //voiicemsg
    { TEXT("2.6.7.32"), 0x254ED0 ,{0}}, //voiicemsg
    { TEXT("2.6.7.40"), 0x254F50 ,{0}}, //voiicemsg
};

bool InitHook()
{
    HMODULE hMod = GetModuleHandle(WECHATWINDLL);
    if (hMod == NULL) {
        return false;
    }

    TCHAR voiceMsgPath[MAX_PATH] = { 0 };

    if (g_WxFuncConfig.IsSaveVoiceMsg(voiceMsgPath)) {
        SetSildDirPath(voiceMsgPath);
        DWORD voiceMsgOffset = 0;
        if (IsSupportedWxVersion(
            g_Supported_wxVoiceMsg_Version,
            ARRAYSIZE(g_Supported_wxVoiceMsg_Version),
            &voiceMsgOffset)) {
            PVOID* p = GetOrigVocieDecodeInternal();
            *p = (PVOID)((DWORD)hMod + voiceMsgOffset);
            if (!Mhook_SetHook(p, fakeVoiceDecodeInternal)) {
                *p = NULL;
            }
        }
    }
    return true;
}

void UninitHook()
{
    PVOID* p = GetOrigVocieDecodeInternal();
    if (*p) {
        Mhook_Unhook(p);
    }
}