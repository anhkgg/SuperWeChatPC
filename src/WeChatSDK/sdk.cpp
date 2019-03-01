#include "stdafx.h"
#include <Rpc.h>
#include <TlHelp32.h>

#include "openwechat.h"
#include "sdk.h"
#include "inject.h"

#include "../common/sdkinf.h"
#pragma comment(lib, "..\\WeChatSDKCore\\Release\\WeChatRc.lib")
#pragma comment(lib, "inject.lib")

#define WECHATWINDLL L"WeChatWin.dll"
#define WECHATSDKDLL L"WeChatSDK.dll"
#define WECHATINJECTDLL L"WeChatSDKCore.dll"

//TODO: edit the file to add interface

//int ConnectSDKServer0(DWORD pid);
//int DisconnectSDKServer0(DWORD pid);

int ConnectSDKServer(DWORD pid, RPC_WSTR* StringBinding);
int DisconnectSDKServer(DWORD pid, RPC_WSTR* StringBinding);
int GetSDKInterface(PWechatSDKInterface p);

WechatSDKInterface g_SDKInf = { 0 };

int WXOpenWechat()
{
    int ret = -1;
    DWORD pid = 0;

    ret = OpenWeChat(&pid);

    return pid;
}

bool WXIsWechatAlive(DWORD pid)
{
    bool ret = false;
    MODULEENTRY32W me32 = { sizeof(me32) };

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (hSnap == INVALID_HANDLE_VALUE) {
        return false;
    }
    if (Module32FirstW(hSnap, &me32)) {
        do {
            if (!_wcsnicmp(me32.szModule, WECHATWINDLL, wcslen(WECHATWINDLL))) {
                ret = true;
                break;
            }
        } while (Module32NextW(hSnap, &me32));
    }
    CloseHandle(hSnap);
    return ret;
}

int WXInitialize(DWORD pid)
{
    WCHAR DllPath[MAX_PATH] = { 0 };

    GetModuleFileNameW(GetModuleHandleW(WECHATSDKDLL), DllPath, MAX_PATH);
    PathRemoveFileSpecW(DllPath);
    PathAppendW(DllPath, WECHATINJECTDLL);

    OutputDebugStringW(DllPath);

    if (!PathFileExistsW(DllPath)) {
        OutputDebugStringW(L"WeChatSDKCore.dll not found");
        return ERROR_FILE_NOT_FOUND;
    }

    if (!InjectDll1(pid, DllPath)) {
        OutputDebugStringW(L"InjectDll1 failed");
        return -1;
    }

    if (g_SDKInf.Initialize == NULL) {
        GetSDKInterface(&g_SDKInf);
    }

    return ERROR_SUCCESS;
}

int WXUninitialize(DWORD pid)
{
    //EnjectDll
    return 0;
}

bool WXIsWechatSDKOk(DWORD pid)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == ERROR_SUCCESS) {
        RpcTryExcept
        {
            ret = g_SDKInf.Initialize();
        }
            RpcExcept(1)
        {
            //printf("RPC Exception %d/n", RpcExceptionCode());
            return false;
        }
        RpcEndExcept

        DisconnectSDKServer(pid, &StringBinding);
        return true;
    }
    return false;
}

int WXAntiRevokeMsg(DWORD pid)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = g_SDKInf.AntiRevokeMsg();
        }
            RpcExcept(1)
        {
            printf("RPC Exception %d/n", RpcExceptionCode());
        }
        RpcEndExcept
        
        DisconnectSDKServer(pid, &StringBinding);
    }
    return ret;
}

int WXUnAntiRevokeMsg(DWORD pid)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = g_SDKInf.UnAntiRevokeMsg();
        }
            RpcExcept(1)
        {
            printf("RPC Exception %d/n", RpcExceptionCode());
        }
        RpcEndExcept

        DisconnectSDKServer(pid, &StringBinding);
    }
    return ret;
}

int WXSaveVoiceMsg(DWORD pid, const wchar_t* path)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = g_SDKInf.StartSaveVoiceMsg((wchar_t *)path);
        }
            RpcExcept(1)
        {
            printf("RPC Exception %d/n", RpcExceptionCode());
        }
        RpcEndExcept

        DisconnectSDKServer(pid, &StringBinding);
    }
    return ret;
}
int WXUnSaveVoiceMsg(DWORD pid)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = g_SDKInf.StopSaveVoiceMsg();
        }
            RpcExcept(1)
        {
            printf("RPC Exception %d/n", RpcExceptionCode());
        }
        RpcEndExcept

        DisconnectSDKServer(pid, &StringBinding);
    }
    return ret;
}

int WXSendTextMsg(DWORD pid, const wchar_t* wxid, const wchar_t* msg)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = g_SDKInf.SendTextMsg((wchar_t*)wxid, (wchar_t*)msg);
        }
            RpcExcept(1)
        {
            printf("RPC Exception %d/n", RpcExceptionCode());
        }
        RpcEndExcept

        DisconnectSDKServer(pid, &StringBinding);
    }
    return ret;
}