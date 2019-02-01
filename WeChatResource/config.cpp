#include "stdafx.h"
#include "config.h"

#define CONFIGFILE TEXT("superwx.ini")

WxFuncConfig::WxFuncConfig()
{
    Init();
}

WxFuncConfig::~WxFuncConfig()
{

}

void WxFuncConfig::Init()
{
    TCHAR tszCfgPath[MAX_PATH] = { 0 };

    GetModuleFileName(GetModuleHandle(WECHATRESOURCE), tszCfgPath, MAX_PATH);
    PathRemoveFileSpec(tszCfgPath);
    PathAppend(tszCfgPath, CONFIGFILE);

    _tcscpy_s(m_configPath, tszCfgPath);
}

bool WxFuncConfig::IsRevokeMsg()
{
    return GetPrivateProfileInt(TEXT("config"), TEXT("revokemsg"), 0, m_configPath) != 0;
}

bool WxFuncConfig::IsSaveVoiceMsg(TCHAR * path)
{
    TCHAR voiceMsgPath[MAX_PATH] = { 0 };

    GetPrivateProfileString(TEXT("config"), TEXT("voicemsg"), TEXT(""), voiceMsgPath, MAX_PATH, m_configPath);
    if (_tcslen(voiceMsgPath) > 0) {
        if (path) {
            _tcscpy_s(path, MAX_PATH, voiceMsgPath);
        }
        return true;
    }
    else {
        return false;
    }
}

