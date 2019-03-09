#include "stdafx.h"
#include <tchar.h>
#include <strsafe.h>

#pragma comment(lib, "Version.lib")

bool GetFileVersion(LPTSTR lpszFilePath, LPTSTR version)
{

    if (_tcslen(lpszFilePath) > 0 && PathFileExists(lpszFilePath))
    {
        VS_FIXEDFILEINFO *pVerInfo = NULL;
        DWORD dwTemp, dwSize;
        BYTE *pData = NULL;
        UINT uLen;

        dwSize = GetFileVersionInfoSize(lpszFilePath, &dwTemp);
        if (dwSize == 0)
        {
            return false;
        }

        pData = new BYTE[dwSize + 1];
        if (pData == NULL)
        {
            return false;
        }

        if (!GetFileVersionInfo(lpszFilePath, 0, dwSize, pData))
        {
            delete[] pData;
            return false;
        }

        if (!VerQueryValue(pData, TEXT("\\"), (void **)&pVerInfo, &uLen))
        {
            delete[] pData;
            return false;
        }

        DWORD verMS = pVerInfo->dwFileVersionMS;
        DWORD verLS = pVerInfo->dwFileVersionLS;
        DWORD major = HIWORD(verMS);
        DWORD minor = LOWORD(verMS);
        DWORD build = HIWORD(verLS);
        DWORD revision = LOWORD(verLS);
        delete[] pData;

        StringCbPrintf(version, 0x20, TEXT("%d.%d.%d.%d"), major, minor, build, revision);

        return true;
    }

    return false;
}


int GetWeChatPath(WCHAR* Path)
{
    int ret = -1;
    //HKEY_CURRENT_USER\Software\Tencent\WeChat InstallPath = xx
    HKEY hKey = NULL;
    if (ERROR_SUCCESS != RegOpenKey(HKEY_CURRENT_USER, L"Software\\Tencent\\WeChat", &hKey))
    {
        ret = GetLastError();
        return ret;
    }

    DWORD Type = REG_SZ;
    // WCHAR Path[MAX_PATH] = { 0 };
    DWORD cbData = MAX_PATH * sizeof(WCHAR);
    if (ERROR_SUCCESS != RegQueryValueEx(hKey, L"InstallPath", 0, &Type, (LPBYTE)Path, &cbData))
    {
        ret = GetLastError();
        goto __exit;
    }

    PathAppend(Path, L"WeChat.exe");

__exit:
    if (hKey)
    {
        RegCloseKey(hKey);
    }

    return ERROR_SUCCESS;
}

int GetWeChatWinPath(WCHAR* Path)
{
    int ret = GetWeChatPath(Path);
    if (ret != ERROR_SUCCESS) {
        return ret;
    }

    PathRemoveFileSpecW(Path);
    PathAppendW(Path, L"WeChatWin.dll");

    return ret;
}

int GetWeChatVersion(WCHAR* version)
{
    WCHAR Path[MAX_PATH] = { 0 };

    int ret = GetWeChatWinPath(Path);
    if (ret != ERROR_SUCCESS) {
        return ret;
    }

    ret = GetFileVersion(Path, version);

    return ret;
}