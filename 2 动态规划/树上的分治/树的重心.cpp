const int maxn = 2e4+100;
vector<int> G[maxn];
int dp[maxn];
int n;
int dfs(int node,int fa){
	int Max = 0;
	dp[node] = 0;
	int sum = 0;
	for(int i = 0;i < G[node].size(); ++i){
		if(fa==G[node][i])continue;
		int tmp = dfs(G[node][i],node);
		sum += tmp;
		Max = max(Max,tmp);
	}
	sum++;
	dp[node] = max(n-sum,Max);
	return sum;
}
int main(void)
{
	int T;
	cin>>T;
	while(T--){
		scanf("%d",&n);
		for(int i = 1;i <= n; ++i) G[i].clear();
		for(int i = 1;i <= n-1; ++i){
			int u,v;
			scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}

		dfs(1,-1);
		int Min = n;
		int ans;
		// for(int i = 1;i <= n; ++i) dp[i] = max(n-dp[i],dp[i]);
		for(int i = 1;i <= n; ++i) 
			if(dp[i] < Min) {
				ans = i;
				Min = dp[i];
		}
		printf("%d %d\n",ans,dp[ans]);
	}
   

   return 0;
}

/*
