
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
typedef pair<int,int> P;
const int maxn = 6e6+10,N = maxn-1;
int Prime[maxn],phi[maxn],miu[maxn],cnt;
int sumu[maxn],sump[maxn];
bool vis[maxn];
void init(void){
	// 线性筛预处理u(i) 和phi(i) 的前缀和4
	miu[1] = 1,phi[1] = 1;
	for(int i = 2;i <= N; ++i){
		if(!vis[i]){
			Prime[++cnt] = i;
			miu[i] = -1;
			phi[i] = i-1;
		}
		for(int j = 1;j <= cnt; ++j){
			if(i*Prime[j] > N) break;
			if(i%Prime[j]){
				vis[i*Prime[j]] = 1;
				miu[i*Prime[j]] = -miu[i];
				phi[i*Prime[j]] = phi[i]*phi[Prime[j]];
			}
			else{
				// 
				vis[i*Prime[j]] = 1;
				miu[i*Prime[j]] = 0;
				phi[i*Prime[j]] = phi[i]*Prime[j];
				// if(i == 2){
				// 	cout<<miu[i*Prime[j]]<<endl;
				// }
				break;
			}

		}
	}
	for(int i = 1;i <= N; ++i)
	 sump[i] = (sump[i-1]+phi[i])%mod,sumu[i] =sumu[i-1]+miu[i];
}
unordered_map<LL,LL> ma;
const LL inv2 = qpow(2,mod-2);
LL get(LL n){
	if(n <= N) return sump[n];
	if(ma[n] != 0) return ma[n];
	LL res = 0;
	for(LL i = 2;i <= n; ){
		LL j = n/(n/i);
		res = (res+1ll*(j-i+1)*get(n/i))%mod;
		i = j+1;
	}
	res = 1ll*n%mod*((n+1)%mod)%mod*inv2%mod-res+mod;
	return ma[n] = res%mod;
}
int main(void)
{
	init();
	LL N;cin>>N;
	cout<<get(N)<<endl;
   return 0;
}
