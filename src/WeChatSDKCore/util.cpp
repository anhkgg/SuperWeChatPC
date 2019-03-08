#include "stdafx.h"
#include "util.h"

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

void Patch(PVOID addr, DWORD size, PVOID code)
{
	DWORD lpOldPro = 0;
	if (!VirtualProtect((LPVOID)addr, size, PAGE_EXECUTE_READWRITE, &lpOldPro))
	{
		return;
	}
	memcpy((char*)addr, (char*)code, size);

	if (!VirtualProtect((LPVOID)addr, size, lpOldPro, &lpOldPro))
	{
	}
}

PVOID NextAddr(PVOID addr, DWORD asm_size /*= 5*/)
{
    return (char*)addr + asm_size;
}

LONG JmpOffset(PVOID dst, PVOID next)
{
    return (LONG)dst - (LONG)next;
}

LONG CallOffset(PVOID addr, DWORD callsize)
{
    return *((LONG*)((char*)addr + callsize));
}

LONGLONG CallOffset64(PVOID addr, DWORD callsize)
{
    return *((LONGLONG*)((char*)addr + callsize));
}

PVOID CallTarget(PVOID addr, DWORD callsize, DWORD codesize)
{
    PVOID next = NextAddr(addr, codesize);
    LONG offset = CallOffset(addr, callsize);
    return (PVOID)((LONG)next + offset);
}

//E8 D0 FC 22 00 call    sub_104830B0
void InlineHookE8(PVOID src, PVOID target, PVOID* orgfun)
{
    BYTE code[5] = { 0xE8, 0x00, 0x00, 0x00, 0x00 };

    PVOID next = NextAddr((PVOID)src, 5);
    LONG offset = JmpOffset(target, next);
    
    if (orgfun) {
        *orgfun = CallTarget(src, 1, 5);
    }

    *((DWORD*)&code[1]) = offset;
    Patch(src, 5, code);
}

wchar_t* SplitStr(const wchar_t* src, const wchar_t* f1, const wchar_t* f2)
{
    const wchar_t* p = wcsstr(src, f1);
    if (p == NULL) {
        return NULL;
    }
    p = p + wcslen(f1);
    const wchar_t* p1 = wcsstr(p, f2);
    if (p1 == NULL) {
        return NULL;
    }

    int len = p1 - p;
    if (len <= 0) {
        return NULL;
    }
    wchar_t* dst = new wchar_t[len + 2];
    if (dst == NULL) {
        return NULL;
    }
    memset(dst, 0, (len + 2) * sizeof(wchar_t));
    memcpy(dst, p, len * sizeof(wchar_t));

    return dst;
}