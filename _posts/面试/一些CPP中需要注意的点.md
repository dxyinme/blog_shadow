---
title: "一些CPP中需要注意的点"
date: 2025-07-21 21:42:49
tags: 面试
---

# 内存对齐

很多时候你需要计算自己创建出来的结构体的size，给出下面这个结构体
```c++
struct A
{
    int32_t a;
    int64_t b;
    char e[25];
    int c;
    char d;
};

struct AlignA
{
    int32_t a;
    int64_t b;
    int c;
    char d;
    char e[25];
} __attribute__((aligned));
```
`sizeof(A)`的值是多少 -> 56

`sizeof(AlignA)`的值是多少 -> 48


# 线程跟进程的差别
1. 线程之间共享地址空间，每个进程有自己的地址空间
2. 线程的资源占用更小，线程是处理器调度的基本单位

# 线程安全
## 锁
### 互斥锁
### 可重入锁
### 不可重入锁
### 自旋锁
获取锁的时候将循环等待(tryLock), 由于不会发生线程状态的切换，减少了线程上下文切换的损耗，但是循环等待会消耗更多的CPU
## 无锁队列
