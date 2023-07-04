#include <bits/stdc++.h>
using namespace std;

const int MAXN = 104;
const int MAXK = 504;

double f[2][MAXN][MAXK];
short vis[2][MAXN][MAXK];
int n,m,k;
int h[2][MAXN];
int c[MAXN];
vector<pair<int,int>> G[MAXN];
double dfs(int x, int rest_k, int p) {
    if (vis[p][x][rest_k]) return f[p][x][rest_k];
    double Di = 0;
    double sum_x = 0;
    f[p][x][rest_k] = h[p][x];
    
    for (int i = 0; i < G[x].size(); i++) {
        int to = G[x][i].first;
        int way_time = G[x][i].second;
        if (c[to] > rest_k - c[x] - way_time) continue;
        Di += 1.0;
        sum_x += dfs(to, rest_k - c[x] - way_time, p);
    }
    vis[p][x][rest_k] = 1;
    if (Di > 0) f[p][x][rest_k] += sum_x / Di;
    return f[p][x][rest_k];
}
int main() {
    scanf("%d%d%d",&n,&m,&k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &c[i], &h[0][i], &h[1][i]);
    }
    for (int i = 1; i <= m; i++) {
        int x,y,t;
        scanf("%d%d%d",&x,&y,&t);
        G[x].push_back({y, t});
        G[y].push_back({x, t});
    }
    double ans0 = 0, ans1 = 0;
    for (int i = 1; i <= n; i++) {
        ans0 += dfs(i, k, 0) / n;
        ans1 += dfs(i, k, 1) / n;
    }
    printf("%.5f %.5f\n", ans0, ans1);
    return 0;
}