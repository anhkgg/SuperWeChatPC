#include "stdafx.h"
#include <Rpc.h>
#include <TlHelp32.h>

#include "openwechat.h"
#include "sdk.h"
#include "inject.h"
#include "util.h"

//#include "../common/sdkinf.h"
#include "../WeChatSDKCore/sdkdef_h.h"
#include "rpcutil.h"

//#pragma comment(lib, "..\\WeChatSDKCore\\Release\\WeChatRc.lib")
#pragma comment(lib, "inject.lib")

#define WECHAREXE L"WeChat.exe"
#define WECHATWINDLL L"WeChatWin.dll"
#define WECHATSDKDLL L"WeChatSDK.dll"
#define WECHATINJECTDLL L"WeChatSDKCore.dll"

//TODO: edit the file to add interface

bool g_IsSDKInited = false;


void RpcLoop()
{
    OutputDebugString(L"start wechatsdk rpc");
    StartSDKClkServer();
    OutputDebugString(L"exit..wechatsdk.rpc");
}

int InitSDK()
{
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RpcLoop, NULL, 0, NULL);
    return ERROR_SUCCESS;
}

void UninitSDK()
{
    if (g_IsSDKInited) {
        g_IsSDKInited = false;
        StopSDKClkServer();
    }
}


int WXOpenWechat()
{
    int ret = -1;
    DWORD pid = 0;

    ret = OpenWeChat(&pid);

    return pid;
}

int WXGetWechat(const wchar_t* wxid)
{
    int ret = 0;
    PROCESSENTRY32 pe32 = { sizeof(pe32) };

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) {
        return 0;
    }

    if (Process32First(hSnap, &pe32)) {
        do {
            if (!_wcsnicmp(pe32.szExeFile, WECHAREXE, wcslen(WECHAREXE))) {
                ret = pe32.th32ProcessID;
                //TODO: //WXGetSelfWxid();
                break;
            }
        } while (Process32Next(hSnap, &pe32));
    }
    return ret;
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

//for sdk interface

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

    //WSDKInitialize(); //rpc还未启动

    if (!g_IsSDKInited) {
        if (InitSDK() == ERROR_SUCCESS) {
            g_IsSDKInited = true;
        }
    }

    return ERROR_SUCCESS;
}

int WXUninitialize(DWORD pid)
{
    UninitSDK();
    //EnjectDll
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == ERROR_SUCCESS) {
        RpcTryExcept
        {
            ret = WSDKUninitialize();
        }
            RpcExcept(1)
        {
            //printf("RPC Exception %d/n", RpcExceptionCode());
            return false;
        }
        RpcEndExcept

        DisconnectSDKServer(pid, &StringBinding);
        
        EnjectDll(pid, WECHATINJECTDLL);

        return ERROR_SUCCESS;
    }
    return -1;
}

int WXGetWechatVersion(wchar_t* version)
{
    return GetWeChatVersion(version);
}

bool WXIsWechatSDKOk(DWORD pid)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == ERROR_SUCCESS) {
        RpcTryExcept
        {
            ret = WSDKInitialize();
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
            ret = WSDKAntiRevokeMsg();
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
            ret = WSDKUnAntiRevokeMsg();
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
            ret = WSDKStartSaveVoiceMsg((wchar_t *)path);
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
            ret = WSDKStopSaveVoiceMsg();
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
            ret = WSDKSendTextMsg((wchar_t*)wxid, (wchar_t*)msg);
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

int WXSendImageMsg(DWORD pid, const wchar_t* wxid, const wchar_t* path)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = WSDKSendImageMsg((wchar_t*)wxid, (wchar_t*)path);
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

int WXRecvTextMsg(DWORD pid, PFNRECVTEXTMSG_CALLBACK funptr)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = WSDKRecvTextMsg((unsigned int)funptr);
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

int WXRecvTransferMsg(DWORD pid, PFNRECVMONEYMSG_CALLBACK funptr)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = WSDKRecvTransferMsg((unsigned int)funptr);
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

int WXRecvPayMsg(DWORD pid, PFNRECVMONEYMSG_CALLBACK funptr)
{
    RPC_WSTR StringBinding = NULL;
    int ret = ConnectSDKServer(pid, &StringBinding);
    if (ret == 0) {
        // 下面是调用服务端的函数了
        RpcTryExcept
        {
            ret = WSDKRecvPayMsg((unsigned int)funptr);
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