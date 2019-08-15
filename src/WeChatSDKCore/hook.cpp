#include "stdafx.h"
#include "hook.h"
#include "voice.h"

#include "mhook.h"
#pragma comment(lib, "mhook.lib")

extern WxFuncConfig g_WxFuncConfig;

bool InitHook()
{
    EnableDropFileEx();
    return true;
}

void UninitHook()
{
    
}