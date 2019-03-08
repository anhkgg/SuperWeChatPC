#include "stdafx.h"
#include "common.h"
#include "util.h"
#include "mhook.h"

bool IsSupportedWxVersion(
    const SuppWxCfg* cfg,
    INT cfg_count,
    DWORD* offset/* = NULL*/,
    BYTE* orig_code/* = NULL*/,
    DWORD* orig_code_count/* = NULL*/,
    BYTE* fake_code/* = NULL*/,
    DWORD* fake_code_count/* = NULL*/)
{
    TCHAR tszDllPath[MAX_PATH] = { 0 };

    GetModuleFileName(NULL, tszDllPath, MAX_PATH);
    PathRemoveFileSpec(tszDllPath);
    PathAppend(tszDllPath, WECHATWINDLL);

    TCHAR version[100] = { 0 };
    if (!GetFileVersion(tszDllPath, version))
    {
        return false;
    }

    for (int i = 0; i < cfg_count; i++) {
        if (!_tcsicmp(cfg[i].version, version)) {
            if (offset) {
                *offset = cfg[i].revoke_offset;
            }
            if (orig_code) {
                memcpy(orig_code, cfg[i].code.orig_code, cfg[i].code.orig_code_count);
            }
            if (fake_code) {
                memcpy(fake_code, cfg[i].code.fake_code, cfg[i].code.fake_code_count);
            }
            if (orig_code_count) {
                *orig_code_count = cfg[i].code.orig_code_count;
            }
            if (fake_code_count) {
                *fake_code_count = cfg[i].code.fake_code_count;
            }
            return true;
        }
    }

    return false;
}

int HookTemplate(HMODULE hMod, const SuppWxCfg* OffArray, int len, PVOID* orig, PVOID fake)
{
    DWORD offset = 0;
    if (IsSupportedWxVersion(
        OffArray,
        len,
        &offset))
    {
        *orig = (PVOID)((DWORD)hMod + offset);
        if (!Mhook_SetHook((PVOID*)orig, fake)) {
            *orig = NULL;
            return ERROR_INVALID_ADDRESS;
        }
        else {
            return ERROR_SUCCESS;
        }
    }
    else {
        return ERROR_NOT_SUPPORTED;
    }
}