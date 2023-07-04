#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 4;
char sa[14];
char sb[14];
int a[14], b[14];
int main() {
    scanf("%s%s", sa+1, sb+1);
    for (int i = 1; i <= 3; i++) {
        a[i] = sa[i] - '0';
        b[i] = sb[i] - '0';
        b[i] += a[i];
        b[i] %= 3;
        printf("%d", b[i]);
    }
    puts("");
    return 0;
}