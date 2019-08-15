/*
扩展文件发送，取消100M限制
*/

#include "stdafx.h"
#include "util.h"
#include "weixin.h"

#include <string>
#include <vector>

const SuppWxCfg g_Supported_Wechat_handleDropFile_Version[] = {
    { TEXT("2.6.8.65"), 0xDF347 + 2 ,{6, {0x00, 0x00, 0x40, 0x06, 0x0F, 0x8C}, 6, {0x00, 0x00, 0x00, 0x00, 0x0f, 0x8D}}},
};

const SuppWxCfg g_Supported_Wechat_RealDropFile_Version[] = {
    { TEXT("2.6.8.65"), 0x9A34C + 2 ,{6, {0x00, 0x00, 0x40, 0x06, 0x0F, 0x8C}, 6, {0x00, 0x00, 0x00, 0x00, 0x0f, 0x8D}}},
};

const SuppWxCfg g_Supported_MainWndprocessData_Version[] = {
    { TEXT("2.6.8.65"), 0x1FA196 + 3 ,{6, {0x00, 0x00, 0x40, 0x06, 0x0F, 0x87}, 6, {0x00, 0x00, 0x00, 0x00, 0x0f, 0x86}}},
};

const SuppWxCfg g_Supported_AppMsgMgr__Instance_Version[] = {
    { TEXT("2.6.8.65"), 0x6BB00 ,{0}},
};

const SuppWxCfg g_Supported_AppMsgMgr__sendFile_Version[] = {
    { TEXT("2.6.8.65"), 0x2382E0 ,{0}},
};


#pragma pack(push, 1)
typedef struct _WxString
{
    wchar_t* buf;
    int len;
    int maxlen;
    int unk1;
    int unk2;
}WxString, *PWxString;//14

#pragma pack(pop)

DWORD pfn_AppMsgMgr__Instance = 0;
//DWORD pfn_AppMsgMgr__sendFile = 0;
typedef void(__stdcall* PFN_AppMsgMgr__sendFile)(int unk, wchar_t* wxid, int len1, int maxlen1, int unk1, int unk2, wchar_t* path, int len2, int maxlen2, int unk3, int un4, int a1, int a2, int a3, int a4, int a5, int a6);
PFN_AppMsgMgr__sendFile pfn_AppMsgMgr__sendFile = NULL;


#define FILE_SIZE_100M (100*1024*1024)
#define FILE_SIZE_99M (10*1024*1024)

int XxGetFileSize(WCHAR* filepath)
{
    DWORD filesize = 0;
    HANDLE hFile = CreateFile(filepath, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        filesize = GetFileSize(hFile, NULL);
        CloseHandle(hFile);
    }
    else {
        int n = GetLastError();
    }
    
    return filesize;
}

char* XxGetFileData(WCHAR* filepath)
{
    char* p = NULL;
    DWORD filesize = 0;
    HANDLE hFile = CreateFile(filepath, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        filesize = GetFileSize(hFile, NULL);
        if (filesize) {
            p = new char[filesize];
            ReadFile(hFile, p, filesize, &filesize, NULL);
        }
        CloseHandle(hFile);
    }
    return p;
}

bool XxWriteFileData(WCHAR* filepath, char* data, DWORD size)
{
    HANDLE hFile = CreateFile(filepath, GENERIC_ALL, 0,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        WriteFile(hFile, data, size, &size, NULL);
        CloseHandle(hFile);
        return true;
    }
    return false;
}

bool SplitFile(WCHAR* filepath, std::vector<std::wstring> &filevec)
{
    DWORD FileSize = XxGetFileSize(filepath);
    if (FileSize <= 0) {
        return false;
    }

    DWORD SplitCount = FileSize / FILE_SIZE_99M;
    DWORD LastFileSize = FileSize % FILE_SIZE_99M;

    char* pData = XxGetFileData(filepath);
    if (pData) {
        for (int i = 0; i < SplitCount; i++) {
            WCHAR file[MAX_PATH] = { 0 };
            swprintf(file, MAX_PATH, L"%s_%d", filepath, i+1);
            filevec.push_back(file);
            XxWriteFileData(file, pData + i * FILE_SIZE_99M, FILE_SIZE_99M);
        }

        if (LastFileSize) {
            WCHAR file[MAX_PATH] = { 0 };
            swprintf(file, MAX_PATH, L"%s_%d", filepath, SplitCount + 1);
            filevec.push_back(file);
            XxWriteFileData(file, pData + SplitCount * FILE_SIZE_99M, LastFileSize);
        }
        delete[] pData;
        return true;
    }
    return false;
}

WxString* NewWxString1(WxString* t, WCHAR* val)
{
    /*if (wcslen(val) < 0x10) {

    }*/
    memset(t, 0, sizeof(WxString));
    WCHAR* p = new WCHAR[wcslen(val) + 1];
    memset(p, 0, (wcslen(val) + 1) * 2);
    memcpy(p, val, wcslen(val) * 2);
    t->buf = p;
    t->len = wcslen(val);
    t->maxlen = wcslen(val) + 1;
    t->unk1 = t->unk2 = 0;
    return t;
}

void DelWxString1(WxString* t)
{
    if (t && t->buf) {
        delete[] t->buf;
        t->buf = NULL;
        t->len = t->maxlen = 0;
    }
}

void SendFileMsg(WCHAR* wxid, WCHAR* path)
{
    char buff[0x45C] = { 0 };
    WxString towxid = { 0 };
    WxString filepath = { 0 };

    NewWxString1(&towxid, wxid);
    NewWxString1(&filepath, path);

    /*
    0:000:x86> dd esp
    00f7db98  00f7e4d8 1058e130 00000014 00000020
    00f7dba8  00000000 00000000 11826e08 00000026
    00f7dbb8  00000040 00000000 00000000 00000000
    00f7dbc8  00000000 00000000 00000000 00000000
    00f7dbd8  c9e17f00
    */
    __asm {
        push 0;//is_root_dir

        push 0;
        push 0;
        push 0;
        push 0;
        push 0;

        //0x44 / 4 = 0x11 = 17
        push filepath.unk2;
        push filepath.unk1;
        push filepath.maxlen;
        push filepath.len;
        push filepath.buf;

        push towxid.unk2;
        push towxid.unk1;
        push towxid.maxlen;
        push towxid.len;
        push towxid.buf;

        lea eax, buff;
        push eax;
        call pfn_AppMsgMgr__Instance;
        mov ecx, eax;
        call pfn_AppMsgMgr__sendFile;
    }

    //DelWxString1(&towxid);
    //DelWxString1(&filepath);
}

bool ExtendSendFile(DWORD dwEcx, wchar_t* wxid, WCHAR* filepath)
{
    std::vector<std::wstring> filevec;
    if (SplitFile(filepath, filevec) && filevec.size() > 0) {
        //__debugbreak();
        for (int i = 0; i < filevec.size(); i++) {
            SendFileMsg(wxid, (WCHAR*)filevec[i].c_str());
        }
        return true;
    }
    return false;
}

bool fakeWechatSendMsgInternal(DWORD dwEcx, wchar_t* wxid, wchar_t* filepath)
{
    int filesize = XxGetFileSize(filepath);
    if (filesize > FILE_SIZE_100M) {
        return ExtendSendFile(dwEcx, wxid, filepath);
    }

    return false;
}

void __stdcall fakeWechatSendMsg1(int unk, wchar_t* wxid, int len1, int maxlen1, int unk1, int unk2, wchar_t* path, int len2, int maxlen2, int unk3, int unk4, int a1, int a2, int a3, int a4, int a5, int a6)
{
    DWORD dwEcx;
    __asm {
        pushad;
        pushfd;
        mov dwEcx, ecx;
    }

    if (fakeWechatSendMsgInternal(dwEcx, wxid, path)) {
        /*__asm {
            popfd;
            popad;
        }
        goto EXIT;*/
    }

    __asm {
        popfd;
        popad;
    }

    if (pfn_AppMsgMgr__sendFile) {
        __asm {
            push a6;
            push a5;
            push a4;
            push a3;
            push a2;
            push a1;

            push unk4;
            push unk3;
            push maxlen2;
            push len2;
            push path;

            push unk2;
            push unk1;
            push maxlen1;
            push len1;
            push wxid;

            push unk;
            mov ecx, dwEcx;
            call pfn_AppMsgMgr__sendFile;
        }
    }
EXIT:
    __asm {
        nop;
    }
}

//eb wechatwin+ 0xDF347 + 2 0x00 0x00 0x00 0x00 0x0f 0x8D
//eb wechatwin+ 0x9A34C + 2 0x00 0x00 0x00 0x00 0x0f 0x8D
//eb wechatwin+ 0x1FA196 + 3 0x00 0x00 0x00 0x00 0x0f 0x86
//选择文件能够超过100M
int EnableDropFileEx()
{
    BYTE code[6] = { 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8D };
    DWORD code_count = 6;
    DWORD offset = 0;
    BYTE code1[6] = { 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8D };
    DWORD code_count1 = 6;
    DWORD offset1 = 0;
    BYTE code2[6] = { 0x00, 0x00, 0x00, 0x00, 0x0f, 0x87 };
    DWORD code_count2 = 6;
    DWORD offset2 = 0;
    if (!IsSupportedWxVersion(
        g_Supported_Wechat_handleDropFile_Version,
        ARRAYSIZE(g_Supported_Wechat_handleDropFile_Version),
        &offset,
        NULL,
        NULL,
        code,
        &code_count) ||
        !IsSupportedWxVersion(
            g_Supported_Wechat_RealDropFile_Version,
            ARRAYSIZE(g_Supported_Wechat_RealDropFile_Version),
            &offset1,
            NULL,
            NULL,
            code1,
            &code_count1) ||
        !IsSupportedWxVersion(
            g_Supported_MainWndprocessData_Version,
            ARRAYSIZE(g_Supported_MainWndprocessData_Version),
            &offset2,
            NULL,
            NULL,
            code2,
            &code_count2)) {
        
        return ERROR_NOT_SUPPORTED;
    }

    HMODULE hMod = GetModuleHandle(WECHATWINDLL);
    if (!hMod) {
        return GetLastError();
    }

    //Wechat_handleDropFile
    PVOID addr = (BYTE*)hMod + offset;
    Patch(addr, code_count, code);

    //Wechat_RealDropFile
    PVOID addr1 = (BYTE*)hMod + offset1;
    Patch(addr1, code_count1, code1);

    //MainWndprocessData
    PVOID addr2 = (BYTE*)hMod + offset2;
    Patch(addr2, code_count2, code2);

    //Wechat_handleDropFile
    /*
    filesize > 100M
    .text:100DF347 07C 81 FE 00 00 40 06                             cmp     esi, 6400000h
    .text:100DF34D 07C 0F 8C 10 FF FF FF                             jl      loc_100DF263
    =>
    filesize < 0
    */
    //char PatchCode1[6] = { 0x00, 0x00, 0x00, 0x00,/*cmp esi, 0*/
    //                       0x0f, 0x8D}; /*jge, jnl*/

    //Wechat_RealDropFile
    /*
    filesize > 100M
    .text:1009A34C 0AC 81 FE 00 00 40 06                             cmp     esi, 6400000h
    .text:1009A352 0AC 0F 8E 04 FF FF FF                             jle     loc_1009A25C
    =>
    filesize < 0
    */
    //char PatchCode2[6] = { 0x00, 0x00, 0x00, 0x00,/*cmp esi, 0*/
    //                      0x0f, 0x8D}; /*jge, jnl*/

    int ret = 0;

    if (pfn_AppMsgMgr__Instance == NULL)
    {
        DWORD AppMsgMgr__Instance_Offset = 0;
        DWORD AppMsgMgr__sendFile_Offset = 0;

        if (!IsSupportedWxVersion(
            g_Supported_AppMsgMgr__Instance_Version,
            ARRAYSIZE(g_Supported_AppMsgMgr__Instance_Version),
            &AppMsgMgr__Instance_Offset))
        {
            return ERROR_NOT_SUPPORTED;
        }
        pfn_AppMsgMgr__Instance = ((DWORD)hMod + AppMsgMgr__Instance_Offset);

        ret = HookTemplate(hMod,
            g_Supported_AppMsgMgr__sendFile_Version,
            ARRAYSIZE(g_Supported_AppMsgMgr__sendFile_Version),
            (PVOID*)&pfn_AppMsgMgr__sendFile,
            fakeWechatSendMsg1);
    }

    return ret;
}