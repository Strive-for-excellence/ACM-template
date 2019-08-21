/*
下标访问比较节省空姐
*/
int f[maxn][19];
void ST_prework() {
    for (int i = 1; i <= n; ++i) f[i][0] = i;
    int t = log(n) / log(2) + 1;
    for (int j = 1; j < t; ++j) {
        for (int i = 1; i <= n - (1 << j) + 1; ++i)
            if (a[f[i][j - 1]] > a[f[i + (1 << (j - 1))][j - 1]])
                f[i][j] = f[i][j - 1];
            else
                f[i][j] = f[i + (1 << (j - 1))][j - 1];
    }
}
int  ST_query(int l, int r) {
    int k = log(r - l + 1) / log(2);
    if (a[f[l][k]] > a[f[r - (1 << k) + 1][k]])
        return f[l][k];
    else
        return f[r - (1 << k) + 1][k];
}
