#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1e9+7;
LL qpow(LL a,LL b){LL s= 1;while(b>0){if(b&1)s = s*a%mod; a = a*a%mod,b >>=1;}return s;}

const int maxn = 2e5+10;
int Prime[maxn],tot;
bool vis[maxn];
int gp1[maxn],gp2[maxn];
int g1[maxn*2],g2[maxn*2];
LL val[maxn*2];
int id1[maxn],id2[maxn],cnt;
LL n,sqr;
void init(int N){
	for(int i = 2;i <= N; ++i){
		if(!vis[i])Prime[++tot] = i;
		for(int j = 1;j <= tot&&i*Prime[j]<=N; ++j){
			vis[i*Prime[j]] = 1;
			if(i%Prime[j]==0) break;
		}
	}
	for(int i = 1;i <= tot; ++i){
		gp1[i] = (gp1[i-1]+Prime[i])%mod;
		gp2[i] = (gp2[i-1]+1ll*Prime[i]*Prime[i])%mod;
	}
}
const LL inv2 = qpow(2,mod-2),inv6 = qpow(6,mod-2);
inline int S1(LL n){n%=mod;return n*(n+1)%mod*inv2%mod;}
inline int S2(LL n){n%=mod;return n*(n+1)%mod*(2*n+1)%mod*inv6%mod;}
inline int id(LL t){return t <= sqr?id1[t]:id2[n/t];}

// sum(f[i])(i \in P)
void Getp(){
	cnt = 0;
	for(LL i = 1,j;i <= n;i = j+1){
		j = n/(n/i);
		val[++cnt] = n/i;
		g1[cnt] = S1(n/i)-1;
		g2[cnt] = S2(n/i)-1;
		if(val[cnt] <= sqr) id1[val[cnt]] = cnt;
		else id2[n/val[cnt]]= cnt;
	}
	for(int i = 1;i <= tot; ++i){
		LL t = 1ll*Prime[i]*Prime[i];
		for(int j = 1;j <= cnt&&t <= val[j];++j){
			int p = id(val[j]/Prime[i]);
			g1[j] = (g1[j]-1ll*Prime[i]*(g1[p]-gp1[i-1]))%mod;
			g2[j] = (g2[j]-1ll*Prime[i]*Prime[i]%mod*(g2[p]-gp2[i-1]))%mod;
		}
	}
}
int S(LL now,int t){
	if(now <= Prime[t]) return 0;
	int p = id(now);
	LL res = (g2[p]-g1[p]-1ll*(gp2[t]-gp1[t]))%mod;
	for(int i = t+1;i <= tot&&1ll*Prime[i]*Prime[i]<=now; ++i){
		LL pe = Prime[i];
		for(int j = 1;pe <= now;++j,pe *= Prime[i]){
			int o = pe%mod;
			res = (res+1ll*o*(o-1)%mod*(S(now/pe,i)+(j!=1)))%mod;
		}
	}
	return res;
}
int main(void){
	cin>>n;sqr = sqrt(n+0.5);
	init(sqr);
	Getp();
	cout<<(S(n,0)+1+mod)%mod<<endl;
	return 0;
}
