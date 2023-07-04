#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 4;
using ll = long long ;

int a[MAXN], n;


int w33ha() {
    scanf("%d",&n);
    int it = -1;
    for (int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        if (a[i] == 0) it = i;
    }
    if (n == 1) return puts("No Solution"),0;
    int l = -1, r = -1;
    int res = 1e9 + 7;
    for (int i = it - 1; i >= 1; i--) {
        l = a[i] + 1;
        if (r == -1) {
            r = a[i] + 1;
        } else {
            r = max(0, r - a[i]);
        }
        int rot = max(l, r);
        res = min(res, rot);
        r = max(r, a[i] + 1);
    }
    l = -1, r = -1;
    for (int i = it + 1; i <= n; i++) {
        l = a[i] + 1;
        if (r == -1) {
            r = a[i] + 1;
        } else {
            r = max(0, r - a[i]);
        }
        int rot = max(l, r);
        res = min(res, rot);
        r = max(r, a[i] + 1);
    }
    printf("%d\n", res);
    return 0;
}

int main() {
    int T; scanf("%d",&T);
    while (T--) w33ha();
    return 0;
}