---
title: 一些grpc相关的注意事项
date: 2022-10-29 10:00:01
tags: 技术相关
---

# http/https-proxy
如果你的机器开着代理，请务必给grpc使用的host配置NO_PROXY，如下：
```bash
NO_PROXY=localhost,127.0.0.0/8,::1,grpc.test.com
```
否则可能会出现发包或者回包失败的情况。当然这也有可能是我的代理的问题

# go-grpc
在golang项目下可能会出现生成的pb文件package或者位置不对的问题，现在一般推荐使用gowork，让整个项目变得更bazel化之后，
使用protoc就会方便很多。