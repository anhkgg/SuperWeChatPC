## 普通用户使用SuperWeChatPC

超级电脑端微信，支持多开，支持防消息撤销，支持语音消息备份...

### 1. 新版本

持续更新版本，直接下载[sdk/SuperWeChat.zip](https://github.com/anhkgg/SuperWeChatPC/raw/master/sdk/SuperWeChat.zip)即可。

默认开启消息防撤回功能，如果需要开启语音备份功能，请使用`SuperWeChat(语音备份).bat`获取输入一下命令：

```
SuperWeChat.exe c:\wxmsg
```

### 2. 仅需要多开

~~下载[bin/WeChat多开v0.0.1.exe](https://github.com/anhkgg/SuperWeChatPC/raw/master/bin/WeChat%E5%A4%9A%E5%BC%80v0.0.1.exe)，双击即可直接使用。~~

**请注意：** 由于微信更新，`2.6.8.52`以后，老版本`WeChat多开v0.0.1.exe`已经失效，请直接使用[sdk/SuperWechat.zip](https://github.com/anhkgg/SuperWeChatPC/raw/master/sdk/SuperWeChat.zip)，也可通过公众号获取。

### 3. 老版本v1.1.3

支持防消息撤销，支持语音消息备份，更新支持到微信`2.6.7.40`

下载[bin/v1.1.3.zip](https://github.com/anhkgg/SuperWeChatPC/raw/master/bin/v1.1.3.zip)使用。

1. 双击运行WeChat多开(防撤销).exe即可。
2. 如更新了WeChatResource.dll，请使用如下参数运行：`WeChat多开(防撤销).exe n`。
3. `superwx.ini`配置如下：
```
	[config]
	revokemsg=1  #0：关闭防消息撤销，1：打开消息防撤销
	voicemsg=c:\ #填入备份语音消息的目录，空为关闭语音消息备份功能
```
