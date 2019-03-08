#include "stdafx.h"
#include "sdk.h"
#include "weixin.h"

//#include "../common/sdkinf.h"
//https ://blog.csdn.net/xxxluozhen/article/details/5605818 
//#pragma comment(lib, "..\\WeChatSDKCore\\Release\\WeChatRs.lib")
//#include "../../common/sdkinf.h"
#include "sdkdef_h.h"
#include "rpcutil.h"

//TODO: edit the file to add interface


void RpcLoop()
{
    StartSDKServer(GetCurrentProcessId());
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

//sdkdef.idl

int WSDKInitialize(void)
{
    OutputDebugString(L"sdk::Initialize");
    return 0;
}

int WSDKUninitialize()
{
    OutputDebugString(L"sdk::Uninitialize");
    //TODO: uninit
    return 0;
}

int WSDKAntiRevokeMsg(void)
{
    OutputDebugString(L"sdk::AntiRevokeMsg");
    return CoreFakeRevokeMsg();
}

int WSDKUnAntiRevokeMsg(void)
{
    OutputDebugString(L"sdk::UnAntiRevokeMsg");
    CoreRestoreRevokeMsg();
    return 0;
}

int WSDKStartSaveVoiceMsg(
    /* [string][in] */ wchar_t *path)
{
    OutputDebugString(L"sdk::StartSaveVoiceMsg");
    return CoreSaveVoiceMsg(path);
}

int WSDKStopSaveVoiceMsg(void)
{
    OutputDebugString(L"sdk::StopSaveVoiceMsg");
    return CoreUnSaveVoiceMsg();
}

int WSDKSendTextMsg(
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *msg)
{
    OutputDebugString(L"sdk::SendTextMsg");
    return CoreSendTxtMsg(wxid, msg);
}

int  WSDKSendImageMsg(
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *path)
{
    OutputDebugString(L"sdk::SendImageMsg");
    return CoreSendImageMsg(wxid, path);
}

int WSDKRecvTextMsg(unsigned int funptr)
{
    OutputDebugString(L"sdk::RecvTextMsg");
    return CoreRecvTextMsg(funptr);
}

int WSDKRecvTransferMsg(unsigned int funptr)
{
    OutputDebugString(L"sdk::RecvTransferMsg");
    return CoreRecvTransferMsg(funptr);
}

int WSDKRecvPayMsg(unsigned int funptr)
{
    OutputDebugString(L"sdk::RecvPayMsg");
    return CoreRecvPayMsg(funptr);
}