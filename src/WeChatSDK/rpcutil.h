#pragma once

#include "stdafx.h"

int ConnectSDKServer(DWORD pid, RPC_WSTR* StringBinding);
int DisconnectSDKServer(DWORD pid, RPC_WSTR* StringBinding);
int StartSDKClkServer();
void StopSDKClkServer();