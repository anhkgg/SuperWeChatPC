import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.WString;

//https://blog.csdn.net/gcangle/article/details/8504629
 
public interface WeChatSDK extends Library {
	WeChatSDK sdk  = (WeChatSDK)Native.loadLibrary("WeChatSDK", WeChatSDK.class);
    public int WXOpenWechat();
    public boolean WXIsWechatAlive(int pid);
    public int WXInitialize(int pid);
    public int WXUninitialize(int pid);
    public boolean WXIsWechatSDKOk(int pid);

    public int WXAntiRevokeMsg(int pid);
    public int WXUnAntiRevokeMsg(int pid);
    public int WXSaveVoiceMsg(int pid, WString path);
    public int WXUnSaveVoiceMsg(int pid);

    public int WXSendTextMsg(int pid, WString wxid, WString msg);
}