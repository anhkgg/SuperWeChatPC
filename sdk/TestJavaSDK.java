import com.sun.jna.Library;
import com.sun.jna.WString;

//https://www.cnblogs.com/huangzijian/p/6638710.html

public class TestJavaSDK {
    public static void main(String[] argv) throws Exception {
        System.out.println("hello java WechatSDK");

        int pid = WeChatSDK.sdk.WXOpenWechat();
        if(pid <= 0) {
            System.out.println("hello java WechatSDK");
            return;
        }

        System.out.println("pid: " + pid);

        System.out.println("wait for...");
        System.in.read();

        System.out.println(WeChatSDK.sdk.WXIsWechatAlive(pid));
        System.out.println(WeChatSDK.sdk.WXIsWechatSDKOk(pid));
        System.out.println(WeChatSDK.sdk.WXInitialize(pid));
        System.out.println("wait for...");
        System.in.read();
        System.out.println(WeChatSDK.sdk.WXSendTextMsg(pid, new WString("wxid_xxxx"), new WString("This is a java sdk test msg")));

        System.in.read();
    }
}