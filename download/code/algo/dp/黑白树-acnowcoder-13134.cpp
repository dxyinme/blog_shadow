#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 4;

int ans;
int fa[MAXN];
int k[MAXN];
int f[MAXN];
vector<int> G[MAXN];

void dfs(int x, int Fa) {
    for (int i = 0; i < G[x].size(); i++) {
        int to = G[x][i];
        if (to != Fa) {
            dfs(to, x);
            k[x] = max(k[x], k[to] - 1);
            f[x] = max(f[x], f[to] - 1);
        }
    }
    if (f[x] == 0) {
        f[x] = k[x];
        ans ++;
    }
}

int main() {
    int n;
    ans = 0;
    scanf("%d",&n);
    for (int i = 2; i <= n; i++) {
        scanf("%d",&fa[i]);
        G[fa[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d",&k[i]);
    }
    
    dfs(1, 0);
    printf("%d\n",ans);
    return 0;
}