
#include "stdafx.h"
#include "mhook.h"
#include <tchar.h>
#include "weixin.h"
#include "sdk.h"
#include <map>
#include <string>

#pragma comment(lib, "User32.lib")

const SuppWxCfg g_Supported_wxTextMsg_Version[] = {
    { TEXT("2.6.7.40"), 0x2E7980 ,{0}}, //
};

const SuppWxCfg g_Supported_wxMoneyMsg_Version[] = {
    //{ TEXT("2.6.7.40"), 0x235C30 ,{0}}, //voiicemsg
    { TEXT("2.6.7.40"), 0x180730 ,{0}}, //
};

typedef int(__stdcall* PFNVoiceDecode)(int a1, int a2, int voice);
typedef int(__stdcall* PFNVoiceDecodeInternal)(int voice, int size, int from, int a4);

//typedef void(__stdcall* PFNRecvMoney)(int a1, pwxmsg msg, int msg1);
typedef void(__stdcall* PFNRecvMoney)();
PFNRecvMoney pfnRecvMoneyMsg = NULL;
unsigned int pfnRecvTransferMsgClk = NULL;
unsigned int pfnRecvPayMsgClk = NULL;


//
//typedef struct _RECV_MSG
//{
//    char unk[0x40];//
//    wstring wxid1;//40
//    wstring wxid2;//4c
//    char unk1[0x10];//58
//    wstring msg;//68 
//    char unk2[0x10];//74
//    ;//84
//}

typedef struct _RECV_MSG_PACK
{
    pwxmsg msg;
    pwxmsg msg_end;
    void* unk;
}RecvMsgPack, *PRecvMsgPack;

typedef int(__stdcall* PFNRecvMsg)(PRecvMsgPack msg);
PFNRecvMsg pfnRecvTextMsg = NULL;
unsigned int pfnRecvTextMsgClk = NULL;

int __stdcall fakeRecvTextMsg(PRecvMsgPack msg)
{
    __asm {
        pushad;
        pushfd;
    }
    int this_ = 0;
    __asm mov this_, ecx;

    if (msg && msg->msg) {
        if (pfnRecvTextMsgClk) {
            CoreWSDKClkRecvTextMsg(
                pfnRecvTextMsgClk,
                msg->msg->wxid1.buf,
                msg->msg->msg.buf
            );
        }
    }

    __asm {
        popfd;
        popad;
    }

    //__asm mov ecx, this_;
    //int ret = pfnRecvTextMsg(msg);
    int result = 0;

    __asm {
        mov eax, msg; //ERROR: lea eax, msg
        push eax;
        mov ecx, this_;
        call pfnRecvTextMsg;
        mov result, eax;
    }

    return result;
}

void fakeRecvMoneyInternal(pwxmsg msg)
{
    //OutputDebugStringW(msg->msg.buf);
    if (wcsstr(msg->msg.buf, L"![CDATA[微信转账]]"))
    {
        wchar_t* money = SplitStr(msg->msg.buf,
            L"![CDATA[微信转账]]></title><des><![CDATA[",
            L"。");
        wchar_t* transferid = SplitStr(msg->msg.buf,
            L"<transferid><![CDATA[",
            L"]]></transferid>");

        if (money) {
            /*wchar_t recv_msg[4000] = { 0 };
            wsprintfW(recv_msg, L"%ws: %ws", msg->wxid1.buf, money);
            OutputDebugStringW(recv_msg);*/

            if (pfnRecvTransferMsgClk) {
                CoreWSDKClkRecvTransferMsg(
                    pfnRecvTransferMsgClk,
                    msg->wxid1.buf,
                    transferid,
                    money
                );
            }

            delete[] money;
        }
        if (transferid) {
            delete[] transferid;
        }
    }
    else if (wcsstr(msg->msg.buf, L"<PayMsgType>9</PayMsgType>"))
    {
        wchar_t* tradeno = SplitStr(msg->msg.buf,
            L"<outtradeno>",
            L"</outtradeno>");

        if (tradeno) {
            wchar_t* username = SplitStr(msg->msg.buf,
                L"<username><![CDATA[",
                L"]]></username>");

            wchar_t* money = SplitStr(msg->msg.buf,
                L"<fee>",
                L"</fee>");

            //OutputDebugStringW(money);

            wchar_t money1[100] = { 0 };
            int mm = _wtoi(money);
            double m = (double)mm / 100;
            StringCbPrintfW(money1, 100, L"%.2f", m);         

            if (money && username) {

                /*OutputDebugStringW(msg->msg.buf);

                OutputDebugStringW(money1);
                OutputDebugStringW(tradeno);
                OutputDebugStringW(username);*/

                if (pfnRecvPayMsgClk) {
                    CoreWSDKClkRecvPayMsg(
                        pfnRecvPayMsgClk,
                        username,
                        tradeno,
                        money1
                    );
                }

                delete[] username;
                delete[] money;
            }
        }
    }
}

// void __stdcall fakeRecvMoney(int a1, pwxmsg msg, int msg1) //0x235C30 2.6.7.40
void __stdcall fakeRecvMoney()
{
    __asm {
        pushad;
        pushfd;
    }

    DWORD dwEcx = 0;
    __asm mov dwEcx, ecx;

    fakeRecvMoneyInternal((pwxmsg)dwEcx);

    __asm {
        popfd;
        popad;
    }

    if (pfnRecvMoneyMsg) {
        __asm mov ecx, dwEcx;
        pfnRecvMoneyMsg();
    }
}

int InitRecvTextMsg()
{
    HMODULE hMod = GetModuleHandleA("WechatWin.dll");
    if (hMod == NULL) {
        return ERROR_NOT_ALL_ASSIGNED;
    }

    if (pfnRecvTextMsg) {
        return ERROR_SUCCESS;
    }

    int ret = HookTemplate(hMod,
        g_Supported_wxTextMsg_Version,
        ARRAYSIZE(g_Supported_wxTextMsg_Version),
        (PVOID*)&pfnRecvTextMsg,
        fakeRecvTextMsg);

    return ret;
}

void UnInitRecvTextMsg()
{
    if (pfnRecvTextMsg) {
        Mhook_Unhook((PVOID*)&pfnRecvTextMsg);
    }
}

int InitRecvMoneyMsg()
{
    HMODULE hMod = GetModuleHandleA("WechatWin.dll");
    if (hMod == NULL) {
        return ERROR_NOT_ALL_ASSIGNED;
    }

    if (pfnRecvMoneyMsg) {
        return ERROR_SUCCESS;
    }

    int ret = HookTemplate(hMod,
        g_Supported_wxMoneyMsg_Version,
        ARRAYSIZE(g_Supported_wxMoneyMsg_Version),
        (PVOID*)&pfnRecvMoneyMsg,
        fakeRecvMoney);
    
    return ret;
}

void UnInitRecvMoneyMsg()
{
    if (pfnRecvMoneyMsg) {
        Mhook_Unhook((PVOID*)&pfnRecvMoneyMsg);
    }
}

int CoreRecvTextMsg(unsigned int funptr)
{
    if (funptr) {
        int ret = InitRecvTextMsg();
        if (ret == ERROR_SUCCESS) {
            pfnRecvTextMsgClk = funptr;
        }
        return ret;
    }
    else {
        UnInitRecvTextMsg();
        pfnRecvTextMsgClk = NULL;
        return ERROR_SUCCESS;
    }
}

int CoreRecvTransferMsg(unsigned int funptr)
{
    if (funptr) {
        int ret = InitRecvMoneyMsg();
        if (ret == ERROR_SUCCESS) {
            pfnRecvTransferMsgClk = funptr;
        }
        return ret;
    }
    else {
        UnInitRecvMoneyMsg();
        pfnRecvTransferMsgClk = NULL;
        return ERROR_SUCCESS;
    }
}

int CoreRecvPayMsg(unsigned int funptr)
{
    if (funptr) {
        int ret = InitRecvMoneyMsg();
        if (ret == ERROR_SUCCESS) {
            pfnRecvPayMsgClk = funptr;
        }
        return ret;
    }
    else {
        UnInitRecvMoneyMsg();
        pfnRecvPayMsgClk = NULL;
        return ERROR_SUCCESS;
    }
}