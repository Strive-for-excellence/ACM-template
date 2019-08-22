const int maxn = 3000+10;
LL a[maxn];
// int dp[maxn];
int fac[maxn],invfac[maxn];
int dp[maxn][maxn];
int p;
int mod;
void Add(int &a,int b){
	a += b;
	if(a >= mod)
		a -= mod;
}

int ans[maxn],tmp[maxn];
int main(void)
{
	
	cin>>p;
	invfac[0] = fac[0] = 1;
	for(int i = 1;i < p; ++i)
		fac[i] = fac[i-1]*i%p;
	invfac[p-1] = qpow(fac[p-1],p-2,p);
	for(int i = p-2;i > 0;--i)
		invfac[i] = invfac[i+1]*(i+1)%p; 
	mod = p;
	for(int i = 0;i < p; ++i)
		cin>>a[i];
	dp[0][1] = 1;
	for(int i = 1;i < p; ++i){
		for(int j = 0;j <= p; ++j){
			dp[i][j] =( mod-1ll*i*dp[i-1][j]%mod)%mod;
			if(j) Add(dp[i][j], dp[i-1][j-1]);
		}
	}
	for(int i = 0;i < p; ++i){
		if(!a[i]) continue;
		for(int j = p-1;j >= 0; --j)
			tmp[j] = (dp[p-1][j+1]+1ll*tmp[j+1]*i%mod)%mod;
		int  sign = 1;
		if((p-i-1)&1) sign = -1;
		for(int j = 0;j < p; ++j){
			LL t = 1;
				t = t*invfac[i]%mod;
				t = (sign*t*invfac[p-i-1]%mod+mod)%mod;

			Add(ans[j],t*tmp[j]%mod+mod);
		}

	}
    
    for(int  i =0;i < p; ++i)
    	cout<<(ans[i]%mod+mod)%mod<<" ";
    cout<<endl;
   return 0;
}


