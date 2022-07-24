#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 4;

int n;
int a[MAXN];

int w33ha() {
    scanf("%d",&n);
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        int x; scanf("%d",&x);
        ret ^= x;
    }
    printf("%d\n", ret);
    return 0;
}

int main() {
    int T; scanf("%d",&T);
    while (T--) w33ha();    
    return 0;
}