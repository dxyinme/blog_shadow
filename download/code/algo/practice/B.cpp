#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 4;

int n, m;
int col[204][204];
int b[204];
bitset<204> bo[204];

int w33ha() {
    scanf("%d%d",&n,&m);
    for (int i = 0; i <= 201; i++) bo[i].reset();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d",&col[i][j]);
            bo[col[i][j]].set(i);
        }
    }
    bitset<204> ans;
    ans.flip();
    vector<int> rets;
    for (int i = 1; i <= m; i++) {
        scanf("%d",&b[i]);
        ans &= bo[b[i]];
        rets.push_back(ans.count());
    }
    for (auto v : rets) {
        printf("%d ", v);
    }
    puts("");
    return 0;
}

int main() {
    int T; scanf("%d",&T);
    while (T--) w33ha();    
    return 0;
}