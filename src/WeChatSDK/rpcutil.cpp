#include "stdafx.h"
#include "../common/rpcdef.h"
#include "../common/rpc.h"
#include "../WeChatSDKCore/sdkdef_h.h"
#include "../WeChatSDKCore/sdkclk_h.h"

// for sdkdef.idl

int ConnectSDKServer(DWORD pid, RPC_WSTR* StringBinding)
{
    WCHAR wszEndPoint[MAX_PATH] = { 0 };
    wsprintf(wszEndPoint, L"%ws_%d", g_Endpoint, pid);
    RPC_STATUS status = RpcConnectServer((RPC_WSTR)wszEndPoint, &WechatRs_IfHandle, StringBinding);
    return status;
}

int DisconnectSDKServer(DWORD pid, RPC_WSTR* StringBinding)
{
    RpcDisconnectServer(&WechatRs_IfHandle, StringBinding);
    return 0;
}

//for sdkclk.idl

int StartSDKClkServer()
{
    WCHAR wszEndPoint[MAX_PATH] = { 0 };
    wsprintf(wszEndPoint, L"%ws", g_ClkEndpoint);
    return RpcStartService((RPC_WSTR)wszEndPoint, WechatSDKClk_v1_0_s_ifspec);
}

void StopSDKClkServer()
{
    RpcStopService();
}
