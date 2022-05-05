#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 4;
int a[MAXN];
int f[MAXN][2];
int n; 
int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        if (i == 1) f[i][0] = 1;
        else {
            if (a[i] > a[i - 1]) {
                f[i][0] = f[i-1][0] + 1;
            } else {
                f[i][0] = 1;
            }
        }
    }
    if (n == 1) return puts("1"),0;
    f[n][1] = 1;
    for (int i = n - 1; i >= 1; i--) {
        if (a[i+1] > a[i]) {
            f[i][1] = f[i+1][1] + 1;
        } else {
            f[i][1] = 1;
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (1 < i && i < n && a[i-1] + 1 < a[i+1]) {
            res = max(res, f[i-1][0] + f[i+1][1] + 1);
        }
        if (i < n && a[i+1] > 1) {
            res = max(res, f[i+1][1] + 1);
        }
        if (1 < i) {
            res = max(res, f[i-1][0] + 1);
        }
    }
    printf("%d\n", res);
    return 0;
}