#pragma once

bool GetFileVersion(LPTSTR lpszFilePath, LPTSTR version);
void Patch(PVOID addr, DWORD size, PVOID code);
