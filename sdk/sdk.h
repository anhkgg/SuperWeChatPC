#pragma once

int WXOpenWechat();
bool WXIsWechatAlive(DWORD pid);
int WXInitialize(DWORD pid);
int WXUninitialize(DWORD pid);
bool WXIsWechatSDKOk(DWORD pid);

int WXGetWechatVersion(wchar_t* version);

int WXGetWechat(const wchar_t* wxid);//打开已经启动的微信

int WXAntiRevokeMsg(DWORD pid);
int WXUnAntiRevokeMsg(DWORD pid);
int WXSaveVoiceMsg(DWORD pid, const wchar_t* path);
int WXUnSaveVoiceMsg(DWORD pid);

int WXSendTextMsg(DWORD pid, const wchar_t* wxid, const wchar_t* msg);
int WXSendImageMsg(DWORD pid, const wchar_t* wxid, const wchar_t* path);

typedef int(*PFNRECVTEXTMSG_CALLBACK)(int pid, wchar_t* wxid, wchar_t* msg);
int WXRecvTextMsg(DWORD pid, PFNRECVTEXTMSG_CALLBACK funptr);

typedef int(*PFNRECVMONEYMSG_CALLBACK)(int pid, wchar_t* wxid, wchar_t* tid, wchar_t* msg);
int WXRecvTransferMsg(DWORD pid, PFNRECVMONEYMSG_CALLBACK funptr);
int WXRecvPayMsg(DWORD pid, PFNRECVMONEYMSG_CALLBACK funptr);

void WXSendGroupTextMsg();
void WXSendImageMsg();
void WXSendVoiceMsg();
void WXAddFriend();
void WXAddGroupFriends();
void WXAcceptFriend();
void WXDeleteFriend();
void WXGetUserWxid();