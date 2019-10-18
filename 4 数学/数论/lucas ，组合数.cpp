LL qpow(LL a,LL b,LL m){
	LL ans = 1;
	a %= m;
	while(b > 0){
		if(b&1)
		   ans = ans*a%m;
		   a = a*a%m;
		   b >>= 1;
	}
	return ans;
}
LL C(LL n,LL m,LL p){
	if(m > n) return 0;
	LL tmp1 = 1,tmp2 = 1;
	m = min(n-m,m);
	for(LL i = 1;i <= m; ++i){
		tmp1 = tmp1*(n-m+i)%p;
		tmp2 = tmp2*i%p;
	}
	return tmp1*qpow(tmp2,p-2,p)%p;
}
LL lucas(LL n, LL m, LL p){
	if(m == 0)
	  return 1;
	return lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;
}


#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if (!b) {x = 1; y = 0; return a;}
	ll res = exgcd(b, a % b, x, y), t;
	t = x; x = y; y = t - a / b * y;
	return res;
}

ll p;

inline ll power(ll a, ll b, ll mod)
{
	ll sm;
	for (sm = 1; b; b >>= 1, a = a * a % mod)if (b & 1)
			sm = sm * a % mod;
	return sm;
}

ll fac(ll n, ll pi, ll pk)
{
	if (!n)return 1;
	ll res = 1;
	for (register ll i = 2; i <= pk; ++i)
		if (i % pi)(res *= i) %= pk;
	res = power(res, n / pk, pk);
	for (register ll i = 2; i <= n % pk; ++i)
		if (i % pi)(res *= i) %= pk;
	return res * fac(n / pi, pi, pk) % pk;
}

inline ll inv(ll n, ll mod)
{
	ll x, y;
	exgcd(n, mod, x, y);
	return (x += mod) > mod ? x - mod : x;
}

inline ll CRT(ll b, ll mod) {return b * inv(p / mod, mod) % p * (p / mod) % p;}

const int MAXN = 11;

ll n, m;


inline ll C(ll n, ll m, ll pi, ll pk)
{
	ll up = fac(n, pi, pk), d1 = fac(m, pi, pk), d2 = fac(n - m, pi, pk);
	ll k = 0;
	for (register ll i = n; i; i /= pi)k += i / pi;
	for (register ll i = m; i; i /= pi)k -= i / pi;
	for (register ll i = n - m; i; i /= pi)k -= i / pi;
	return up * inv(d1, pk) % pk * inv(d2, pk) % pk * power(pi, k, pk) % pk;
}

inline ll exlucus(ll n, ll m)
{
	ll res = 0, tmp = p, pk;
	static int lim = sqrt(p) + 5;
	for (register int i = 2; i <= lim; ++i)if (tmp % i == 0)
		{
			pk = 1; while (tmp % i == 0)pk *= i, tmp /= i;
			(res += CRT(C(n, m, i, pk), pk)) %= p;
		}
	if (tmp > 1)(res += CRT(C(n, m, tmp, tmp), tmp)) %= p;
	return res;
}

int main()
{
	scanf("%lld%lld%lld", &n, &m, &p);
	printf("%d\n", exlucus(n, m));
	return 0;
}
