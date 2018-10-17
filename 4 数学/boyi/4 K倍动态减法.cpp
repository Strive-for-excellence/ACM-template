
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
const int maxn = 2e6+100;
int a[maxn],b[maxn];
int main(void)
{
    int T;
    cin>>T;
    for(int kase  = 1;kase <= T; ++kase){
        int n,k;
        cin>>n>>k;
        a[0] = 1,b[0] = 1;
        int i = 0,j = 0;
        while(a[i] < n){
            i++;
            a[i] = b[i-1]+1;
            if(a[j+1] * k < a[i])  j++;
            if(a[j] * k < a[i])  b[i] = b[j]+a[i];
            else      b[i] = a[i]; 

        }
        printf("Case %d: ",kase);
        if(a[i] == n) {
            puts("lose");
            continue;
        } 
        // i--;
        while(i >= 0){
            if(n-a[i] > 0)
                n -= a[i];
            if(n == a[i]) break;
            i--;
        }
        printf("%d\n",n);
    }

   return 0;
}
