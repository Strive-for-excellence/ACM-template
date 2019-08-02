
https://blog.csdn.net/werkeytom_ftd/article/details/53812718
https://www.luogu.org/problem/P5170  模板公式


#pragma GCC optimize(3)
#include <bits/stdc++.h>

typedef long long ll;
const int mod = 998244353;

const ll inv2 = 499122177;
const ll inv6 = 166374059;

struct Query {
    ll f, g, h;
};

Query solve(ll a, ll b, ll c, ll n) {
/*
注，类欧几里得算法
问题：给定n,a,b,c;求i from 0 to n 求
f:(a*i+b)/c;
g:i*(a*i+b)/c
h:((a*i+b)/c)^2
对998244353取模的值
不包含纵坐标为0的点
*/
    Query ans, tmp;
    if (a == 0) {
        ans.f = (n + 1) * (b / c) % mod;
        ans.g = (b / c) * n % mod * (n + 1) % mod * inv2 % mod;
        ans.h = (n + 1) * (b / c) % mod * (b / c) % mod;
        return ans;
    }
    if (a >= c || b >= c) {
        tmp = solve(a % c, b % c, c, n);
        ans.f = (tmp.f + (a / c) * n % mod * (n + 1) % mod * inv2 % mod + (b / c) * (n + 1) % mod) % mod;
        ans.g = (tmp.g + (a / c) * n % mod * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod + (b / c) * n % mod * (n + 1) % mod * inv2 % mod) % mod;
        ans.h = ((a / c) * (a / c) % mod * n % mod * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod +
                (b / c) * (b / c) % mod * (n + 1) % mod + (a / c) * (b / c) % mod * n % mod * (n + 1) % mod +
                tmp.h + 2 * (a / c) % mod * tmp.g % mod + 2 * (b / c) % mod * tmp.f % mod) % mod;
        return ans;
    }
    ll m = (a * n + b) / c;
    tmp = solve(c, c - b - 1, a, m - 1);
    ans.f = (n * (m % mod) % mod - tmp.f) % mod;
    ans.g = (n * (n + 1) % mod * (m % mod) % mod - tmp.f - tmp.h) % mod * inv2 % mod;
    ans.h = (n * (m % mod) % mod * ((m + 1) % mod) % mod - 2 * tmp.g - 2 * tmp.f - ans.f) % mod;
    return ans;
}
int main() {
    ll t ;scanf("%lld",&t);
    ll n, a, b, c;
    while (t--) {
        scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
        Query ans = solve(a, b, c, n);
        printf("%lld %lld %lld\n", (ans.f + mod) % mod, (ans.h + mod) % mod, (ans.g + mod) % mod);
    }
    return 0;
}

