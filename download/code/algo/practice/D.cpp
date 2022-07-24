#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 4;
using ll = long long ;
const ll mod = 998244353;

ll a, b;

ll fp(ll x, ll y) {
    if (y == 0) return 1;
    ll tmp = fp(x, y/2);
    if (y & 1) {
        return tmp * tmp % mod * x % mod;
    } else {
        return tmp * tmp % mod;
    }
}

ll rev(ll x) {
    return fp(x, mod - 2);
}

ll S(ll v) {
    ll p1 = (a+b) * v % mod;
    ll p2 = - (a+b) * (1 + v) % mod * v % mod * rev(2) % mod;
    ll p3 = v * (v + 1) % mod * (2*v + 1) % mod * rev(6) % mod;
    return ((p1 + p2 + p3) % mod * ( -1 ) + mod) % mod;
}

int w33ha() {
    scanf("%lld%lld",&a, &b);
    cout << S(a) << endl;
    cout << S(b) << endl;
    printf("%lld\n", (S(b) - S(a) + mod) % mod);
    return 0;
}

int main() {
    int T; scanf("%d",&T);
    while (T--) w33ha();    
    return 0;
}