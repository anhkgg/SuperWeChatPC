#pragma once

#include "stdafx.h"


int GetWeChatPath(WCHAR* Path);
int GetWeChatWinPath(WCHAR* Path);
int GetWeChatVersion(WCHAR* version);
bool GetFileVersion(LPTSTR lpszFilePath, LPTSTR version);
