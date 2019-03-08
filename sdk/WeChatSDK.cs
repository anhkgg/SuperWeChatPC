using System;
using System.Runtime.InteropServices;

namespace WeChatSDK
{
    class WeChatSDK
    {
        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public uint WXOpenWechat();

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public bool WXIsWechatAlive(uint pid);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public int WXInitialize(uint pid);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public int WXUninitialize(uint pid);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public bool WXIsWechatSDKOk(uint pid);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public int WXGetWechat(string wxid);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public int WXAntiRevokeMsg(uint pid);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public int WXUnAntiRevokeMsg(uint pid);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        extern static public int WXSaveVoiceMsg(uint pid, string path);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public int WXUnSaveVoiceMsg(uint pid);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        extern static public int WXSendTextMsg(uint pid, string wxid, string msg);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate int RecvMsgCallback(uint pid, string wxid, string msg);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public delegate int RecvPayMsgCallback(uint pid, string wxid, string id, string msg);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public int WXRecvTextMsg(uint pid, RecvMsgCallback funptr);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public int WXRecvTransferMsg(uint pid, RecvPayMsgCallback funptr);

        [DllImport(@"WeChatSDK.dll", CallingConvention = CallingConvention.Cdecl)]
        extern static public int WXRecvPayMsg(uint pid, RecvPayMsgCallback funptr);
    }
}