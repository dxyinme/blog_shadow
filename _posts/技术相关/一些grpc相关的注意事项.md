---
title: 一些grpc相关的注意事项
date: 2022-10-29 10:00:01
tags: 技术相关
---

# 写在前面
最近闲来无事，想要搞一个个人的cpp开发脚手架，项目地址在[这里](https://github.com/dxyinme/ezlib)，欢迎大家参与。
在这个项目里面我遇到了一些跟grpc相关的问题，刚好想要总结一下，就写写个blog记录一下好了。

# http/https-proxy
如果你的机器开着代理，请务必给grpc使用的host配置NO_PROXY，如下：
```bash
NO_PROXY=localhost,127.0.0.0/8,::1,grpc.test.com
```
否则可能会出现发包或者回包失败的情况。当然这也有可能是我的代理的问题

