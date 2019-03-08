#pragma once

#include <windows.h>

#define WECHATWINDLL TEXT("WeChatWin.dll")
#define WECHATRESOURCE TEXT("WeChatResource.dll")
#define ORGWECHATRESOURCE TEXT("WeChatResource.dll.1")

typedef struct _FAKE_WX_CODE
{
    DWORD orig_code_count;
    BYTE orig_code[100];
    DWORD fake_code_count;
    BYTE fake_code[100];
}FakeWxCode, *PFakeWxCode;

typedef struct _SUP_WX_CFG
{
    const TCHAR* version;
    DWORD revoke_offset;
    FakeWxCode code;
}SuppWxCfg, *PSuppWxCfg;

bool IsSupportedWxVersion(
    const SuppWxCfg* cfg,
    INT cfg_count,
    DWORD* offset = NULL,
    BYTE* orig_code = NULL,
    DWORD* orig_code_count = NULL,
    BYTE* fake_code = NULL,
    DWORD* fake_code_count = NULL);

int HookTemplate(HMODULE hMod, const SuppWxCfg* OffArray, int len, PVOID* orig, PVOID fake);