// 素数个数
#include <bits/stdc++.h>
#define rin(i,a,b) for(int i=(a);i<=(b);++i)
#define irin(i,a,b) for(int i=(a);i>=(a);--i)
#define trav(i,a) for(int i=head[(a)];i;i=e[i].nxt)
typedef long long LL;
using std::cin;
using std::cout;
using std::endl;

inline LL read(){
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
}

const LL MAXN=10000000005;
const LL MOD=2999999;
LL n,prm[200005],cnt;
LL num[200005],g[200005],tot;
bool vis[200005];
struct Hash_Table{
    int head[MOD+5],nxt[200005],siz;
    LL to[200005],val[200005];
    inline void insert(LL x,LL y){
        ++siz;
        nxt[siz]=head[x%MOD];
        to[siz]=y;
        val[siz]=x;
        head[x%MOD]=siz;
    }
    inline LL operator [] (LL x){
        for(register int i=head[x%MOD];i;i=nxt[i])
            if(val[i]==x) return to[i];
    }
}mp;

void pre_process(LL n){
    rin(i,2,n){
        if(!vis[i]) prm[++cnt]=i;
        for(register int j=1;j<=cnt&&i*prm[j]<=n;++j){
            vis[i*prm[j]]=1;
            if(i%prm[j]==0) break;
        }
    }
}

int main(){
    n=read();
    pre_process((LL)(sqrt(n)+0.5));
    LL nxti;
    for(register LL i=1;i<=n;i=nxti){
        nxti=n/(n/i)+1;
        num[++tot]=n/i;
        mp.insert(num[tot],tot);
        g[tot]=num[tot]-1;
    }
    rin(i,1,cnt){
        rin(j,1,tot){
            if(prm[i]*prm[i]>num[j]) break;
            int k=mp[num[j]/prm[i]];
            g[j]-=g[k]-(i-1);
        }
    }
    printf("%lld",g[1]);
    return 0;
}
