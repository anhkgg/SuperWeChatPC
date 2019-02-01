#include "stdafx.h"
#include "voice.h"

typedef struct _wxstring
{
    wchar_t* buf;
    int len;
    int maxlen;
}wxstring, *pwxstring;

typedef struct _wxstring_ansi
{
    char* buf;
    int len;
    int maxlen;
}wxstring_ansi, *pwxstring_ansi;

typedef struct _wxmsg
{
    char unk[0x40];//
    wxstring wxid1;//40 from
    wxstring_ansi wxid1_ansi;//4c
    char unk1[0x10];//58
    wxstring msg;//68 xml
    wxstring_ansi msg_ansi;//74
    char unk2[0x50];//80
    char unk3[0x44];//d0
    wxstring wxid2;//0x114
    DWORD unk4;//120
    DWORD unk5;//124
    wxstring hash;//128
    //134  
} wxmsg, *pwxmsg;


typedef int(__stdcall* PFNVoiceDecodeInternal)(int voice, int size, int from, int a4);

PFNVoiceDecodeInternal pfnVoiceDecodeInternal = NULL;
TCHAR SildDirPath[MAX_PATH] = { 0 };

void CreateSilkDir(const TCHAR* path)
{
    TCHAR pathDir[MAX_PATH] = { 0 };

    _tcscpy_s(pathDir, path);
    if (!PathFileExists(pathDir)) {
        PathRemoveFileSpec(pathDir);
        CreateSilkDir(pathDir);
        CreateDirectory(path, NULL);
    }
}

void* Silk2Mp3(void* data, int size)
{
    //https://github.com/kn007/silk-v3-decoder
    return NULL;
}

void SaveSilk(void* data, int size, const TCHAR* path, const TCHAR* name)
{
    DWORD dwWritten = 0;
    TCHAR FullPath[MAX_PATH] = { 0 };

    _tcscpy_s(FullPath, path);
    PathAppend(FullPath, name);

    if (PathFileExists(FullPath)) {
        return;
    }

    CreateSilkDir(path);

    if (PathFileExists(path)) {
        HANDLE hFile = CreateFile(FullPath, GENERIC_ALL, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            //TODO: convert silk to mp3
            Silk2Mp3(data, size);
            WriteFile(hFile, data, size, &dwWritten, NULL);
            CloseHandle(hFile);
        }
    }
}

VOID SetSildDirPath(const TCHAR* path)
{
    _tcscpy_s(SildDirPath, path);
}

PVOID * GetOrigVocieDecodeInternal()
{
    return (PVOID *)&pfnVoiceDecodeInternal;
}

/*
<msg><voicemsg endflag="1" cancelflag="0" forwardflag="0" voiceformat="4" voicelength="1176" length="1334" bufid="147445261304397871" clientmsgid="41626136333438996633636200230013013119fdd53b1f494102" fromusername="wxid_xxxfdfds22" /></msg>
*/
const WCHAR* GetBufId(const WCHAR* xml, WCHAR* bufid)
{
    const WCHAR* p = _tcsstr(xml, L"bufid=\"");
    if (p) {
        p = p + _tcslen(L"bufid=\"");
        WCHAR* p1 = (WCHAR*)_tcsstr(p, L"\"");
        if (p1) {
            memcpy(bufid, p, (p1 - p) * sizeof(WCHAR));
        }
    }
    return bufid;
}

int __stdcall fakeVoiceDecodeInternal(int voice, int size, int from, int a4)
{
    wxmsg* m = (wxmsg*)from;
    WCHAR bufid[100] = { 0 };
    TCHAR name[MAX_PATH] = { 0 };
    PVOID pData = (PVOID)voice;
    int nDataSize = size;
  

    if (SildDirPath) {
        wsprintf(name, TEXT("%ws_%ws.silk"), m->wxid1.buf, GetBufId((const WCHAR*)(m->msg.buf), bufid));
        SaveSilk(pData, nDataSize, SildDirPath, name);
    }

    return pfnVoiceDecodeInternal(voice, size, from, a4);
}
 