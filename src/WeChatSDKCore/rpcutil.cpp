
#include "rpcutil.h"
#include "../common/rpcdef.h"
#include "sdkdef_h.h"
#include "sdkclk_h.h"
//for sdkdef.idl

int StartSDKServer(DWORD pid)
{
    WCHAR wszEndPoint[MAX_PATH] = { 0 };
    wsprintf(wszEndPoint, L"%ws_%d", g_Endpoint, pid);
    return RpcStartService((RPC_WSTR)wszEndPoint, WechatSDK_v1_0_s_ifspec);
}

void StopSDKServer()
{
    RpcStopService();
}

//for sdkclk.idl

int ConnectSDKServer(RPC_WSTR* StringBinding)
{
    WCHAR wszEndPoint[MAX_PATH] = { 0 };
    wsprintf(wszEndPoint, L"%ws", g_ClkEndpoint);
    RPC_STATUS status = RpcConnectServer((RPC_WSTR)wszEndPoint, &WechatRsClk_IfHandle, StringBinding);
    return status;
}

int DisconnectSDKServer(RPC_WSTR* StringBinding)
{
    RpcDisconnectServer(&WechatRsClk_IfHandle, StringBinding);
    return 0;
}