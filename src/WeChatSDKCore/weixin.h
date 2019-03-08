
#pragma once
#include <windows.h>

#pragma pack(push, 1)

typedef struct _WXSTRING
{
    wchar_t* buf;
    int len;
    int maxlen;
    DWORD unk1;
    DWORD unk2;
}WXString, *PWXString;//14

typedef struct _WXSTRING_ANSI
{
    char* buf;
    int len;
    int maxlen;
    DWORD unk1;
    DWORD unk2;
}WXStringAnsi, *PWXStringAnsi;

//typedef WXString wxstring;
//typedef PWXString pwxstring;
//typedef WXStringAnsi wxstring_ansi;
//typedef PWXStringAnsi pwxstring_ansi;

////////////////////////////////////////////////////////////////////
//发送消息相关
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
    wxstring wxid1;//40
    wxstring_ansi wxid1_ansi;//4c
    char unk1[0x10];//58
    wxstring msg;//68 
    wxstring_ansi msg_ansi;//74
    char unk2[0x50];//80
    char unk3[0x44];//d0
    wxstring wxid2;//0x114
    DWORD unk4;//120
    DWORD unk5;//124
    wxstring hash;//128
    //134  
} wxmsg, *pwxmsg;

////////////////////////////////////////////////////////////////////
//联系人
typedef struct _WXBUFFER
{
    union {
        char buf[0x10];
        struct {
            char* buf;
            DWORD unk1;
            DWORD unk2;
            DWORD unk3;
        } p;
    } buf;
    DWORD buf_len;//10
    DWORD buf_len1;//14 >0x10 使用nickbuf
}WxBuffer, *PWxBuffer;//18

typedef struct _USERINFO0
{
    char unk1[0x3c];//
    WxBuffer wxid;//3c
    WxBuffer infox;//54
    WxBuffer infox1;//6c
    char unk6[0x30];//84
    WxBuffer nick;;//b4
    char unk7[0x14c];//cc
    WxBuffer name;//218
} LoginUser;

typedef struct _USERINFO
{
    struct _USERINFO* next;
    DWORD unk1;//4
    struct _USERINFO* next1;//8
    BYTE unk3;//c
    BYTE flag;//d
    BYTE unk4;
    BYTE unk5;
    WXString wxid;//0x10
    //DWORD unk6;//1c
    //DWORD unk7;//20
    DWORD unk8;//24 val
    DWORD unk9;//28
    DWORD unk10;//2c
    WXString wxid1;//30
    //DWORD unk11_1;//3c
    //DWORD unk11_2;//40
    WXString name;//44 微信号
    //DWORD unk11_3;//50
    //DWORD unk11_4;//54
    WXString info0;//58
    //DWORD unk11_5;//64
    //DWORD unk11_6;//68
    DWORD unk12;//6c
    DWORD unkflag;//70
    DWORD unk13_1;//74
    WXString beizhu;//78
    //DWORD unk13_2;//84
    //DWORD unk13_3;//88
    WXString nick;//8c 昵称
    char unk14[0x28];//a0
    DWORD unkflag1;//c8
    WXString nick1;// cc short piny
    //DWORD unk15;//d8
    //DWORD unk16;//dc
    WXString nick2;//e0 full piny
    char unk17[0x28];//f4
    WXString photo;//11c 
    WXString photo1;//130
    char* hash;//144 0x20
    DWORD unk18_1;//148
    DWORD unk18_2;//14c
    DWORD unk18_3;//150
    DWORD unkflag2;//154
    DWORD unkflag3;//158
    DWORD unk18_4;//15c
    DWORD unk18_5;//160
    DWORD unkflag4;//164
    DWORD unkflag5;//168
    DWORD unk18_6;//16c
    char unk19[0x4c];//170 flag
    WXString qianming;//1bc
    WXString country;//1d0
    WXString city;//1f4
    WXString city1;//208
    char unk20[0x60];//21c
    WXString xx;//27c
    DWORD unk20_1;//290
    DWORD unk20_2;//294
    DWORD unk21;//298
    WXString pic;//29c
}UserInfo, *PUserInfo;//3DC
#pragma pack(pop)


int CoreFakeRevokeMsg();
void CoreRestoreRevokeMsg();

int CoreSaveVoiceMsg(wchar_t *path);
int CoreUnSaveVoiceMsg(void);

int CoreSendTxtMsg(WCHAR* wxid, WCHAR* msg);
int CoreSendImageMsg(WCHAR* wxid, WCHAR* path);

int CoreRecvTextMsg(unsigned int funptr);
int CoreRecvTransferMsg(unsigned int funptr);
int CoreRecvPayMsg(unsigned int funptr);
