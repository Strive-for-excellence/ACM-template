
#include <bits/stdc++.h>
#define mem(ar,num) memset(ar,num,sizeof(ar))
#define me(ar) memset(ar,0,sizeof(ar))
#define lowbit(x) (x&(-x))
#define Pb push_back
#define  FI first
#define  SE second
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define IOS ios::sync_with_stdio(false)
#define DEBUG cout<<endl<<"DEBUG"<<endl; 
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int    prime = 999983;
const int    INF = 0x7FFFFFFF;
const LL     INFF =0x7FFFFFFFFFFFFFFF;
const double pi = acos(-1.0);
const double inf = 1e18;
const double eps = 1e-6;
const LL     mod = 1e9 + 7;
LL qpow(LL a,LL b){LL s=1;while(b>0){if(b&1)s=s*a%mod;a=a*a%mod;b>>=1;}return s;}
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
int dr[2][4] = {1,-1,0,0,0,0,-1,1};
LL n,sqr;
const int maxn = 100100;
int Prime[maxn],vis[maxn],tot,gp1[maxn],gp2[maxn];
const int inv2 = qpow(2,mod-2),inv6 = qpow(6,mod-2);
LL w[maxn*2],sw;
int g1[maxn*2],g2[maxn*2];
int id1[maxn],id2[maxn];

int S(LL x, int y) {
	if (Prime[y] >= x) return 0;
	int  p = x <= sqr ? id1[x] : id2[n / x];
	int ret = ((0LL + g2[p] - g1[p] - (gp2[y] - gp1[y])) % mod + mod) % mod;
	for (int i = y + 1; i <= tot && 1LL * Prime[i]*Prime[i] <= x; ++i) {
		LL pe = Prime[i];
		for (int e = 1; pe <= x; ++e, pe *= Prime[i]) {
			int o = pe % mod;
			ret = (ret + 1LL * o * (o - 1) % mod * (S(x / pe, i) + (e != 1))) % mod;
		}
	}
	return ret;
}

int main(void){
	scanf("%lld",&n);
	sqr = sqrt(n);
	vis[1] = 1;
	for(int i = 2;i <= sqr; ++i){
		if(!vis[i]) Prime[++tot] = i;
		for(int j = 1;j <= tot&&i*Prime[j] <= sqr; ++j){
			vis[i*Prime[j]] = 1;
			if(i%Prime[j] == 0) break;
		}
	}
	for(int i = 1;i <= tot; ++i)
		gp1[i] =(gp1[i-1]+Prime[i])%mod,gp2[i]=(gp2[i-1]+1ll*Prime[i]*Prime[i])%mod;
	for(LL l = 1,r;l <= n; l = r+1){
		r = n/(n/l);
		w[++sw] = n/r;
		g1[sw] = w[sw]%mod;
		g2[sw] = 1ll*g1[sw]*(g1[sw]+1)%mod*(2*g1[sw]+1)%mod*inv6%mod-1;
		g1[sw] = 1ll*g1[sw]*(g1[sw]+1)%mod*inv2%mod-1;
		if(n/r <= sqr) id1[n/r] =sw;
		else id2[r] = sw;
	}
	for(int i= 1;i <= tot; ++i){
		LL tmp = 1ll*Prime[i]*Prime[i];
		for(int j = 1;j <= sw&&tmp <= w[j];++j){
			LL p = w[j]/Prime[i];
			p = (p <= sqr?id1[p]:id2[n/p]);
			g1[j] = (g1[j]-1ll*Prime[i]*(g1[p]-gp1[i-1])%mod+mod)%mod;
			g2[j] = (g2[j]-1ll*Prime[i]*Prime[i]%mod*(g2[p]-gp2[i-1])%mod+mod)%mod;

		}

	}
	printf("%lld\n",(S(n,0)%mod+mod+1)%mod);

	return 0;
}
