# 更新日志

**2019年8月15日**
1. 新增增强文件发送功能，打破微信100M限制。
2. 大文件(大于100M)发送默认开启，并不影响原有功能。

注意：目前接收方并未开发自动合并功能（毕竟使用SDK的人少），所以接收方需手工合并（工作量并不大）。

```
//使用windows原生命令合并文件
copy /b Test_100M.pdf._1+Test_100M.pdf._2+Test_100M.pdf._3 Test_100M.pdf
```

**2019年3月8日**
1. 发布Python、Java、C#的SDK，版本1.3.0
2. 升级防撤消功能，有撤销提醒
3. 增加接受消息接口（3种）

**2019年2月24日**
1. 开放WeChatSDK，提供丰富的操作微信的接口
2. 保留v1.1.3老版本，[下载地址](https://github.com/anhkgg/SuperWeChatPC/tree/master/bin)
3. 普通用户也可使用sdk目录下SuperWeChatPC.exe使用最新的功能

**2019年2月22日(v1.1.3)**
1. v1.1.3.3，更新支持2.6.7.40
2. bin目录为最新可执行文件[下载地址](https://github.com/anhkgg/SuperWeChatPC/tree/master/bin)

**2019年2月16日(v1.1.3)**
1. v1.1.3.2，更新支持2.6.6.44
2. bin目录为最新可执行文件[下载地址](https://github.com/anhkgg/SuperWeChatPC/tree/master/bin)

**2019年2月13日(v1.1.3)**
1. 更新支持2.6.7.32
2. bin目录为最新可执行文件[下载地址](https://github.com/anhkgg/SuperWeChatPC/tree/master/bin)

**2019年2月1日(v1.1.3)**
1. 增加支持语音消息备份（仅支持2.6.6.28），只是个demo，有特殊需要请自行修改或者联系我。
2. 增加`superwx.ini`配置文件，可自行开关防消息撤销和语音消息备份
3. [下载地址](https://github.com/anhkgg/SuperWeChatPC/releases/tag/v1.1.3)

**2018年12月28日(v1.1.2)**
1. 更新支持微信（2.6.6.28）
2. 更新支持随机mutex多开
3. [下载地址](https://github.com/anhkgg/SuperWeChatPC/releases/tag/v1.1.2)

**2018年11月30日(v1.1.1)**：
1. 增加消息防撤销功能，暂时只支持固定版本(2.6.5.38，2.6.6.25），如有需要请联系我兼容或者自行修改。
2. MultiWeChat增加更新安装防撤消插件和更新插件功能。
3. [下载地址](https://github.com/anhkgg/multi_wechat_pc/releases/tag/v1.1.1)
4. multi_wechat_pc更名为SuperWeChatPC

**v0.0.1**：
1. 仅支持多开功能，[下载地址](https://github.com/anhkgg/multi_wechat_pc/releases/tag/v0.0.1)