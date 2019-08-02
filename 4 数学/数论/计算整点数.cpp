#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
int main()
{
    int x1,y1,x2,y2,x3,y3;
    while(cin>>x1)
    {
        if(x1==-1) break;
        cin>>y1>>x2>>y2>>x3>>y3;
        int a1 = x2-x1,b1 = y2-y1;
        int a2 = x3-x1,b2 = y3-y1;
        double S = abs((double)a1*b2-b1*a2)/2.0;
        int ab = __gcd(abs(x1-x2),abs(y1-y2))+1;
        int bc= __gcd(abs(x3-x2),abs(y3-y2))+1;
        int ac= __gcd(abs(x1-x3),abs(y1-y3))+1;
        int s = ab + bc + ac - 3;
        printf("%.1f ",S);
        printf("%lld %d %d %d\n",(ll)S-s/2+1,ab-2,bc-2,ac-2);
    }
    return 0;
}
