
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
//������Ϣ���
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
//��ϵ��
typedef struct _USERINFO_NAME
{
    union {
        char nick[0x10];
        struct {
            char* nickbuf;
            DWORD unk1;
            DWORD unk2;
            DWORD unk3;
        } p;
    } nick;
    DWORD nick_len;//10
    DWORD nick_len1;//14 >0x10 ʹ��nickbuf
}USERINFO_NAME;//18

typedef struct _USERINFO0
{
    char unk1[0x3c];//
    USERINFO_NAME wxid;//3c
    USERINFO_NAME infox;//54
    USERINFO_NAME infox1;//6c
    char unk6[0x30];//84
    USERINFO_NAME nick;;//b4
} USERINFO;

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
    WXString name;//44 ΢�ź�
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
    WXString nick;//8c �ǳ�
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


int FakeRevokeMsg();
void RestoreRevokeMsg();

int SaveVoiceMsg(wchar_t *path);
int UnSaveVoiceMsg(void);

int SendTxtMsg(WCHAR* wxid, WCHAR* msg);
int SendImageMsg(WCHAR* wxid, WCHAR* path);