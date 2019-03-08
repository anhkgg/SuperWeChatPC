#pragma once

#include <windows.h>
#include "../common/rpc.h"

int StartSDKServer(DWORD pid);
void StopSDKServer();
int ConnectSDKServer(RPC_WSTR* StringBinding);
int DisconnectSDKServer(RPC_WSTR* StringBinding);