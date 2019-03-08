#pragma once

#include <windows.h>

//proc_name: process name
int GetProcID(const WCHAR* _proc_name);
//path: process name
//dllpath: dll full path
bool InjectDll(const WCHAR* path, const WCHAR* dllpath);
//pid: process id
//dllpath: dll full path
bool InjectDll1(DWORD pid, const WCHAR* dllpath);
//
bool EnjectDll(DWORD pid, const WCHAR* dllname);