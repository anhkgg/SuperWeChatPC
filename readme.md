
# 概述

`SuperWeChatPC`刚开始仅仅只是`PC`微信多开工具，后来慢慢增加了更多功能，感谢朋友们的支持。

为了方便更多开发者能够在`PC`微信做更多有意义的事情，现改变项目方向，提供两个针对不同人群的功能。

1. 普通用户依然可以直接使用原来的多开工具，直接下载可执行程序即可。[下载地址](https://github.com/anhkgg/SuperWeChatPC/archive/v1.1.3.zip)，详细使用方法请看[普通用户使用SuperWeChatPC](docs/normal.md)。
2. 针对开发者，提供`WeChatSDK`，开放操作微信的各种接口，可以进行二次开发，具体使用方法请看[WeChatSDK开发指南](docs/sdk.md)。

`SuperWeChatPC`支持功能：
1. 全版本无限多开
2. 消息防撤销，有撤销提示（`>=2.6.7.40`）
3. 语音消息备份（`>=2.6.6.28`）
4. 消息发送接口（`>=2.6.6.44`）
5. 接受消息接口，3种消息（`>=2.6.7.40`)

**`WeChatSDK`目前已经开放`C++`、`Python`、`Java`、`C#`接口。** 具体请看[WeChatSDK开发指南](docs/sdk.md)。

更新详情请看[更新日志](docs/update.md)

刚发布几天，发现在几个下载站出现了`SuperWeChatPC`的下载，特此加上编译好的文件`hash`信息，请下载后自行检查文件是否被修改。

[hash信息](hash.txt)

另外本项目仅在`github`发布，其他渠道下载的文件出现任何问题，与作者和本项目无关。

# 技术内幕

技术细节请参考文章：

1. [https://mp.weixin.qq.com/s/bb7XMxop7e8rd7YqQ88nyA](https://mp.weixin.qq.com/s/bb7XMxop7e8rd7YqQ88nyA)（多开）
2. [https://mp.weixin.qq.com/s/E7N6LzAH4p88Gu4f_qwGlg](https://mp.weixin.qq.com/s/E7N6LzAH4p88Gu4f_qwGlg)（消息防撤销）
3. [https://mp.weixin.qq.com/s/h9d8aO79OvkpV9bknVT60A](https://mp.weixin.qq.com/s/h9d8aO79OvkpV9bknVT60A)（备份语音）
4. [https://mp.weixin.qq.com/s/uUXB9AHtnhCsD7gAfFYRoA](https://mp.weixin.qq.com/s/uUXB9AHtnhCsD7gAfFYRoA)（消息发送接口）

欢迎PR或提供意见建议。

**感谢**

1. [https://github.com/martona/mhook](https://github.com/martona/mhook)

### 声明

**<label style="color:red">本项目仅供技术研究，请勿用于任何商业用途，请勿用于非法用途，如有任何人凭此做何非法事情，均于作者无关，特此声明。</label>**

<br/><br/>

**开源不易，无数深夜的寒风需要你的点滴暖意。**

![img](pay.png)