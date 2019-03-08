using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using static WeChatSDK.WeChatSDK;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                uint pid = WXOpenWechat();
                Console.WriteLine("WXOpenWechat pid:" + pid);

                while (!WXIsWechatAlive(pid))
                {
                    Console.Write(".");
                    Thread.Sleep(100);
                }

                Console.WriteLine("initialize sdk...");

                Console.WriteLine(WXInitialize(pid));

                while (!WXIsWechatSDKOk(pid))
                {
                    Console.Write(".");
                    Thread.Sleep(100);
                }

                Console.WriteLine("sdk ok...");

                WXAntiRevokeMsg(pid);
                WXSaveVoiceMsg(pid, "c:\\wxmsg");

                WXRecvPayMsg(pid, RecvMoneyMsg);

                Console.ReadLine();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        static int RecvMoneyMsg(UInt32 pid, string wxid, string id, string msg)
        {
            Console.WriteLine(wxid + ":" + msg);
            return 0;
        }
    }
}
