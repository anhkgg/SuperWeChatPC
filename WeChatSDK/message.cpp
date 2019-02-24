#include "stdafx.h"
#include "message.h"


typedef struct _WECHAT_SDK_MESSAGE
{
    int size;//
    int major;//函数功能号
    int minor;//0：调用，1：返回值
    void* callback;//
    char buf[1];
}WechatSdkMsg, *PWechatSdkMsg;

//client
