ll ex_gcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x = 1;
        y = 0;
        return a;
    }
    ll g = ex_gcd(b,a%b,y,x);
    y -= a / b * x;
    return g;
}
ll China(ll n){
    ll m1 = m[0],a1 = a[0];
    ll m2,a2,k1,k2,x0,g,c;
    lcm = m[0];
    for(int i = 1; i < n; i++){
        m2 = m[i];
        a2 = a[i];
        c = a2 - a1;
        g = ex_gcd(m1,m2,k1,k2);
        lcm = lcm * m[i] / gcd(lcm,m[i]);
        if(c % g){
            flag = false;
            return 0;
        }
        x0 = k1 * c / g;
        ll t = m2 / g;
        x0 = (x0 % t + t) % t;
        a1 += m1 * x0;
        m1 = m2 / g * m1;
    }
    return a1;
}
