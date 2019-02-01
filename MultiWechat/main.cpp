#include <Windows.h>
#include <TlHelp32.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi")
#include "main.h"
#include <stdio.h>

#pragma comment(lib, "Advapi32")
#pragma comment(lib, "Shell32")

//进程提权
BOOL ElevatePrivileges()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken))
		return FALSE;
	LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&tkp.Privileges[0].Luid);
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if(!AdjustTokenPrivileges(hToken,FALSE,&tkp,sizeof(TOKEN_PRIVILEGES),NULL,NULL))
	{
		return FALSE;
	}

	return TRUE;
}

HANDLE DuplicateHandleEx(DWORD pid, HANDLE h, DWORD flags)
{
	HANDLE hHandle = NULL;

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if(hProc)
	{
		if(!DuplicateHandle(hProc,
			(HANDLE)h, GetCurrentProcess(),
			&hHandle, 0, FALSE, /*DUPLICATE_SAME_ACCESS*/flags))
		{
			hHandle = NULL;
		}
	}

	CloseHandle(hProc);
	return hHandle;
}

int GetProcIds(LPWSTR Name, DWORD* Pids)
{
	PROCESSENTRY32 pe32 = {sizeof(pe32)};
	int num = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnap)
	{
		if(Process32First(hSnap, &pe32))
		{
			do {
				if(!wcsicmp(Name, pe32.szExeFile))
				{
					if(Pids)
					{
						Pids[num++] = pe32.th32ProcessID;
					}
				}
			} while(Process32Next(hSnap, &pe32));
		}
		CloseHandle(hSnap);
	}

	return num;
}

BOOL IsTargetPid(DWORD Pid, DWORD* Pids, int num)
{
	for(int i=0; i<num; i++)
	{
		if(Pid == Pids[i])
		{
			return TRUE;
		}
	}
	return FALSE;
}

int PatchWeChat()
{
	DWORD dwSize = 0;
	POBJECT_NAME_INFORMATION pNameInfo;
	POBJECT_NAME_INFORMATION pNameType;
	PVOID pbuffer = NULL;
	NTSTATUS Status;
	int nIndex = 0;
	DWORD dwFlags = 0;
	char szType[128] = {0};
	char szName[512] = {0};

	ElevatePrivileges();

	DWORD Pids[100] = {0};

	DWORD Num = GetProcIds(L"WeChat.exe", Pids);
	if(Num == 0)
	{
		return 0;
	}
		
	if(!ZwQuerySystemInformation)
	{
		goto Exit0;
	}

	pbuffer = VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);

	if(!pbuffer)
	{
		goto Exit0;
	}

	Status = ZwQuerySystemInformation(SystemHandleInformation, pbuffer, 0x1000, &dwSize);

	if(!NT_SUCCESS(Status))
	{
		if (STATUS_INFO_LENGTH_MISMATCH != Status)
		{
			goto Exit0;
		}
		else
		{
			// 这里大家可以保证程序的正确性使用循环分配稍好
			if (NULL != pbuffer)
			{
				VirtualFree(pbuffer, 0, MEM_RELEASE);
			}

			if (dwSize*2 > 0x4000000)  // MAXSIZE
			{
				goto Exit0;
			}

			pbuffer = VirtualAlloc(NULL, dwSize*2, MEM_COMMIT, PAGE_READWRITE);

			if(!pbuffer)
			{
				goto Exit0;
			}

			Status = ZwQuerySystemInformation(SystemHandleInformation, pbuffer, dwSize*2, NULL);

			if(!NT_SUCCESS(Status))
			{
				goto Exit0;    
			}
		}
	}

	PSYSTEM_HANDLE_INFORMATION1 pHandleInfo = (PSYSTEM_HANDLE_INFORMATION1)pbuffer;

	for(nIndex = 0; nIndex < pHandleInfo->NumberOfHandles; nIndex++)
	{
		if(IsTargetPid(pHandleInfo->Handles[nIndex].UniqueProcessId, Pids, Num))
		{
			//
			HANDLE hHandle = DuplicateHandleEx(pHandleInfo->Handles[nIndex].UniqueProcessId, 
										(HANDLE)pHandleInfo->Handles[nIndex].HandleValue,
										DUPLICATE_SAME_ACCESS
										);
			if(hHandle == NULL) continue;
	
			Status = NtQueryObject(hHandle, ObjectNameInformation, szName, 512, &dwFlags);

			if (!NT_SUCCESS(Status))
			{
				CloseHandle(hHandle);
				continue;
			}

			Status = NtQueryObject(hHandle, ObjectTypeInformation, szType, 128, &dwFlags);

			if (!NT_SUCCESS(Status))
			{
				CloseHandle(hHandle);
				continue;
			}

			pNameInfo = (POBJECT_NAME_INFORMATION)szName;
			pNameType = (POBJECT_NAME_INFORMATION)szType;

			WCHAR TypName[1024] = {0};
			WCHAR Name[1024] = {0};

			wcsncpy(TypName, (WCHAR*)pNameType->Name.Buffer, pNameType->Name.Length/2);
			wcsncpy(Name, (WCHAR*)pNameInfo->Name.Buffer, pNameInfo->Name.Length/2);

			// 匹配是否为需要关闭的句柄名称
			if (0 == wcscmp(TypName, L"Mutant"))
			{
				//WeChat_aj5r8jpxt_Instance_Identity_Mutex_Name
				//if (wcsstr(Name, L"_WeChat_App_Instance_Identity_Mutex_Name"))
				if (wcsstr(Name, L"_WeChat_") &&
					wcsstr(Name, L"_Instance_Identity_Mutex_Name"))
				{
					CloseHandle(hHandle);

					hHandle = DuplicateHandleEx(pHandleInfo->Handles[nIndex].UniqueProcessId, 
						(HANDLE)pHandleInfo->Handles[nIndex].HandleValue,
						DUPLICATE_CLOSE_SOURCE
						);

					if(hHandle)
					{
						printf("+ Patch wechat success!\n");
						CloseHandle(hHandle);
					}
					else
					{
						printf("- Patch error: %d\n", GetLastError());
					}

					goto Exit0;
				}
			}

			CloseHandle(hHandle);
		}
		
	}

Exit0:
	if (NULL != pbuffer)
	{
		VirtualFree(pbuffer, 0, MEM_RELEASE);
	}

	return 0;
}


bool InstallRevokeDll(LPWSTR Path, bool Update)
{
	WCHAR wszDll[MAX_PATH] = { 0 };
	WCHAR wszDllOrig[MAX_PATH] = { 0 };
	WCHAR wszDll1[MAX_PATH] = { 0 };
    WCHAR wszConfig[MAX_PATH] = { 0 };
    WCHAR wszConfig1[MAX_PATH] = { 0 };

	GetModuleFileName(NULL, wszDll, MAX_PATH);
	PathRemoveFileSpec(wszDll);    
   
    wcscpy_s(wszConfig1, Path);
    PathAppend(wszConfig1, L"superwx.ini");
    wcscpy_s(wszConfig, wszDll);
    PathAppend(wszConfig, L"superwx.ini");

    CopyFile(wszConfig, wszConfig1, false);

    wcscpy_s(wszDll1, Path);
	PathAppend(wszDll, L"WeChatResource.dll");
	PathAppend(wszDll1, L"WeChatResource.dll.1");
	wcscpy_s(wszDllOrig, Path);
	PathAppend(wszDllOrig, L"WeChatResource.dll");
	
	if (!PathFileExists(wszDll1)) {
		MoveFile(wszDllOrig, wszDll1);
	}

	if (Update) {
		MoveFileEx(wszDll, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
	}
	CopyFile(wszDll, wszDllOrig, false);

	return true;
}

void OpenWeChat(bool Update)
{
	//HKEY_CURRENT_USER\Software\Tencent\WeChat InstallPath = xx
	HKEY hKey = NULL;
	if(ERROR_SUCCESS != RegOpenKey(HKEY_CURRENT_USER, L"Software\\Tencent\\WeChat", &hKey))
	{
		return;
	}
	
	DWORD Type = REG_SZ;
	WCHAR Path[MAX_PATH] = {0};
	DWORD cbData = MAX_PATH*sizeof(WCHAR);
	if(ERROR_SUCCESS != RegQueryValueEx(hKey, L"InstallPath", 0, &Type, (LPBYTE)Path, &cbData))
	{
		goto __exit;
	}

	InstallRevokeDll(Path, Update);
	
	PathAppend(Path, L"WeChat.exe");

	ShellExecute(NULL, L"Open", Path, NULL, NULL, SW_SHOW);
	
__exit:
	if(hKey)
	{
		RegCloseKey(hKey);
	}
}


int main(int argc, char* argv[])
{
	//TEST
	//\Sessions\1\BaseNamedObjects\_WeChat_App_Instance_Identity_Mutex_Name
	//HANDLE hMutex = CreateMutexA(NULL, FALSE, "_WeChat_App_Instance_Identity_Mutex_Name");	
	//HANDLE hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, "_WeChat_App_Instance_Identity_Mutex_Name");
	//DUPLICATE_CLOSE_SOURCE

	printf("------------------------------------------------------------\n");
	printf("--------------- WeChat电脑端多开器(防撤销）-----------------\n");
	printf("--------------- 2018年11月30日 Anhkgg -----------------------\n");
	printf("--------------- CopyRight (C) 2018 by Anhkgg ---------------\n");
	printf("------------------------------------------------------------\n\n");
	
	
	PatchWeChat();

	printf("+ Patch Finish!\n");

	printf("+ Start new wechat!\n");

	bool update = false;

	if (argc == 2 && argv[1][0] == 'n') {
		update = true;
		printf("+ Update...\n");
	}

	OpenWeChat(update);

	printf("+ Exit...\n");

	//getchar();
	return 0;
}