#pragma once
#include <windows.h>
#include <Rpc.h>

long RpcStartService(RPC_WSTR pszEndPoint, RPC_IF_HANDLE ifHandle);
void RpcStopService();
long RpcConnectServer(RPC_WSTR EndPoint, handle_t *IfHandle, RPC_WSTR *StringBinding);
long RpcDisconnectServer(handle_t *IfHandle, RPC_WSTR *StringBinding);