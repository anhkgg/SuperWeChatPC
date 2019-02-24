#pragma once

int WXOpenWechat();
bool WXIsWechatAlive(DWORD pid);
int WXInitialize(DWORD pid);
int WXUninitialize(DWORD pid);
bool WXIsWechatSDKOk(DWORD pid);

int WXAntiRevokeMsg(DWORD pid);
int WXUnAntiRevokeMsg(DWORD pid);
int WXSaveVoiceMsg(DWORD pid, const wchar_t* path);
int WXUnSaveVoiceMsg(DWORD pid);

int WXSendTextMsg(DWORD pid, const wchar_t* wxid, const wchar_t* msg);

void WXSendGroupTextMsg();
void WXSendImageMsg();
void WXSendVoiceMsg();
void WXAddFriend();
void WXAddGroupFriends();
void WXAcceptFriend();
void WXDeleteFriend();
void WXGetUserWxid();