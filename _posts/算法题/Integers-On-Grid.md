---
title: Integers On Grid
date: 2021-11-06 21:56:34
tags: 算法题
---

# 来源
[ABC224E](https://atcoder.jp/contests/abc224/tasks/abc224_e)
一道atcoder的图论题

# 题意

给你一个`H * W`的方格矩形，其中有`N`个格子有正整数，其他的格子数字都是`0`, 每个有正整数的格子上面都有一块木板，你可以让一个木板从一个方格`A`，传送到另一个方格`B`，但是要遵循下列条件：

  1. `B`的数字严格大于`A`的数字
  2. `B`和`A`在同一行或者同一列

对于每个木板，输出它最多能传送多少次

# 题解
看到这个我们很容易就可以想到反向建图之后，跑拓扑排序。对于每行每列按照非`0`格子的数字从大到小，对编号进行排序，每个点对所有数字小于自己中，数字最大的点建边，但是这样可能会出现`N * N`级别的边。所以在每个数字相同的点集合之间建边需要一个特殊的点，拓扑排序记录每个点是第几层，最后除以`2`就可以（去掉特殊点对距离的影响）。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 4;

vector<int> ro[MAXN], co[MAXN];
struct Pot { int x, y, a; } p[MAXN];
int h,w,n, cn;
int ans[MAXN * 4];
int du[MAXN * 4];
vector<vector<int>> G;

inline bool Cmp(const int & x, const int & y) {
  return p[x].a < p[y].a;
}

void build(vector<int>& o) {
  sort(o.begin(), o.end(), Cmp);
  int l = 0, r = 0;
  int lastp = -1;
  for (int i = 1; i < o.size(); i++) {
    if (p[o[i]].a == p[o[i-1]].a) {
      r ++;
      if (lastp != -1) {
        G[o[i]].push_back(lastp);
        du[lastp] ++;
      }
    } else {
      lastp = ++cn;
      for (int j = l; j <= r; j++) {
        G[lastp].push_back(o[j]);
        du[o[j]] ++;
      }
      l = r = i;
      G[o[i]].push_back(lastp);
      du[lastp] ++;
    }

  }
}

int main() {
  scanf("%d%d%d",&h,&w,&n);
  G.resize(n * 4 + 5);
  cn = n;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].a);
    ro[p[i].x].push_back(i);
    co[p[i].y].push_back(i);
  }
  for (int i = 0; i < MAXN; i++) {
    if (!ro[i].empty()) {
      build(ro[i]); 
    }
    if (!co[i].empty()) {
      build(co[i]);  
    }
  }
  queue<int>q;
  for (int i = 1; i <= n; i++) {
    if (du[i] == 0) {
      q.push(i);
      ans[i] = 0;
    }
  }
  while (!q.empty()) {
    int x = q.front(); q.pop();
    for (int to : G[x]) {
      du[to] --;
      if (du[to] <= 0) {
        ans[to] = ans[x] + 1;
        q.push(to);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d\n", ans[i] / 2);
  }
  return 0;
}
```