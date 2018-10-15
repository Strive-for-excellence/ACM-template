#include<set>
#include<map>
#include<stack>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long ll;
const int maxn = 1e6 + 10;
const int seed = 131;
const ll MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
using namespace std;
int m[2][2] = {0, 0, 0, 1};
int Nim_Mul_Power(int x, int y){
    if(x < 2) return m[x][y];
    int a = 0;
    for(; ; a++){
        if(x >= (1 << (1 << a)) && x < (1 << (1 << (a + 1))))
            break;
    }
    int m = 1 << (1 << a);
    int p = x / m, s = y / m, t = y % m;
    int d1 = Nim_Mul_Power(p, s);
    int d2 = Nim_Mul_Power(p, t);
    return (m * (d1 ^ d2)) ^ Nim_Mul_Power(m / 2, d1);
}
int Nim_Mul(int x, int y){
    if(x < y) return Nim_Mul(y, x);
    if(x < 2) return m[x][y];
    int a = 0;
    for(; ; a++){
        if(x >= (1 << (1 << a)) && x < (1 << (1 << (a + 1))))
            break;
    }
    int m = 1 << (1 << a);
    int p = x / m, q = x % m, s = y / m, t = y % m;
    int c1 = Nim_Mul(p, s), c2 = Nim_Mul(p, t) ^ Nim_Mul(q, s), c3 = Nim_Mul(q, t);
    return (m * (c1 ^ c2)) ^ c3 ^ Nim_Mul_Power(m / 2, c1);
}
int main(){
    int T;
    scanf("%d", &T);
    int ans;
    while(T--){
        ans = 0;
        int n, x, y;
        scanf("%d", &n);
        while(n--){
            scanf("%d%d", &x, &y);
            ans ^= Nim_Mul(x, y);
        }
        if(ans)
            printf("Have a try, lxhgww.\n");
        else
            printf("Don't waste your time.\n");
    }
    return 0;
}
