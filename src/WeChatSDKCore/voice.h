#pragma once

VOID SetSildDirPath(const TCHAR* path);
PVOID* GetOrigVocieDecodeInternal();
int __stdcall fakeVoiceDecodeInternal(int voice, int size, int from, int a4);