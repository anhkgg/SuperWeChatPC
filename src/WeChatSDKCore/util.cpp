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