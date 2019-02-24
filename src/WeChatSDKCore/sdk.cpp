#include "stdafx.h"
#include "sdk.h"
#include "weixin.h"

#include "../common/sdkinf.h"
//https ://blog.csdn.net/xxxluozhen/article/details/5605818 
#pragma comment(lib, "..\\WeChatSDKCore\\Release\\WeChatRs.lib")

//TODO: edit the file to add interface

int GetSDKInterface(PWechatSDKInterface p);
int StartSDKServer(DWORD pid, PWechatSDKInterface p);
void StopSDKServer();

void RpcLoop()
{
    WechatSDKInterface p = { 0 };
    GetSDKInterface(&p);
    StartSDKServer(GetCurrentProcessId(), &p);
    OutputDebugString(L"exit...rpc");
}

int InitSDK()
{
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RpcLoop, NULL, 0, NULL);
    return GetLastError();
}

void UnInitSDK()
{
    StopSDKServer();
}

int Initialize(void)
{
    OutputDebugString(L"sdk::Initialize");
    return 0;
}

int AntiRevokeMsg(void)
{
    OutputDebugString(L"sdk::AntiRevokeMsg");
    return FakeRevokeMsg();
}

int UnAntiRevokeMsg(void)
{
    OutputDebugString(L"sdk::UnAntiRevokeMsg");
    RestoreRevokeMsg();
    return 0;
}

int StartSaveVoiceMsg(
    /* [string][in] */ wchar_t *path)
{
    OutputDebugString(L"sdk::StartSaveVoiceMsg");
    return SaveVoiceMsg(path);
}

int StopSaveVoiceMsg(void)
{
    OutputDebugString(L"sdk::StopSaveVoiceMsg");
    return UnSaveVoiceMsg();
}

int SendTextMsg(
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *msg)
{
    OutputDebugString(L"sdk::SendTextMsg");
    return SendTxtMsg(wxid, msg);
}

//put the function pointer to WeChatRs.dll
int GetSDKInterface(PWechatSDKInterface p)
{
    if (p) {
        p->Initialize = Initialize;
        p->AntiRevokeMsg = AntiRevokeMsg;
        p->UnAntiRevokeMsg = UnAntiRevokeMsg;
        p->StartSaveVoiceMsg = StartSaveVoiceMsg;
        p->StopSaveVoiceMsg = StopSaveVoiceMsg;
        p->SendTextMsg = SendTextMsg;
    }

    return 0;
}