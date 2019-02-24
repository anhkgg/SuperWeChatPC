#pragma once

#include <windows.h>

class WxFuncConfig
{
public:
    WxFuncConfig();
    ~WxFuncConfig();

    bool IsRevokeMsg();
    bool IsSaveVoiceMsg(TCHAR* path);
private:
    void Init();

private:
    TCHAR m_configPath[MAX_PATH];
};