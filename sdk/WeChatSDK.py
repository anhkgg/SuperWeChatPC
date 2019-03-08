#coding = utf8

import ctypes, os, sys
#https://blog.csdn.net/zmnbehappy/article/details/78697185

class WXSDK():
    def __init__(self):
        self.sdk = ctypes.CDLL("WeChatSDK.dll")

    def WXOpenWechat(self):
        self.pid = self.sdk.WXOpenWechat()
        return self.pid

    def WXIsWechatAlive(self):
        return self.sdk.WXIsWechatAlive(self.pid)

    def WXInitialize(self):
        return self.sdk.WXInitialize(self.pid)

    def WXUninitialize(self):
        return self.sdk.WXUninitialize(self.pid)

    def WXIsWechatSDKOk(self):
        return self.sdk.WXIsWechatSDKOk(self.pid)

    #def WXGetWechat(self, wxid):
    #    self.pid = self.sdk.WXGetWechat(self.pid, wxid)
    #    return self.pid

    def WXAntiRevokeMsg(self):
        return self.sdk.WXAntiRevokeMsg(self.pid)

    def WXUnAntiRevokeMsg(self):
        return self.sdk.WXUnAntiRevokeMsg(self.pid)

    def WXSaveVoiceMsg(self, path):
        return self.sdk.WXSaveVoiceMsg(self.pid, path)

    def WXUnSaveVoiceMsg(self):
        return self.sdk.WXUnSaveVoiceMsg(self.pid)

    def WXSendTextMsg(self, wxid, msg):
        return self.sdk.WXSendTextMsg(self.pid, wxid, msg)

    #def WXSendImageMsg(self, wxid, path):
    #    return self.sdk.WXSendImageMsg(self.pid, wxid, path)

if __name__ == "__main__":
    wxsdk = WXSDK()
    print(wxsdk.WXOpenWechat())
    input("wait for...")
    print(wxsdk.WXIsWechatAlive())
    print(wxsdk.WXIsWechatSDKOk())
    print(wxsdk.WXInitialize())
    input("wait for...")
    print(wxsdk.WXSendTextMsg("wxid_n11111", "This is a python sdk test msg"))