// 初始化ljc,调用chipolla 求解x的二次剩余
namespace com {
ll W, W0, ljc;
struct comp {
	ll x, y;
	comp(ll xx = 0, ll yy = 0) {x = xx, y = yy;}
};
comp operator * (comp a, comp b) {
	return comp((a.x * b.x % ljc + a.y * b.y % ljc * W % ljc) % ljc, (a.y * b.x % ljc + a.x * b.y % ljc) % ljc);
}
inline ll fast_pow(ll a, ll b, ll p) {
	ll t = 1; a %= p;
	while (b) {
		if (b & 1) t = t * a % p;
		b >>= 1; a = a * a % p;
	}
	return t;
}
inline comp cfast_pow(comp a, ll b, ll p) {
	comp t = comp(1, 0);
	while (b) {
		if (b & 1) t = t * a;
		b >>= 1; a = a * a;
	}
	return t;
}
inline pair<ll, ll> Cipolla(ll x) {
	if (fast_pow(x, (ljc - 1) >> 1, ljc) == ljc - 1) return make_pair(-1, -1);
	srand(time(NULL));
	while (1) {
		W0 = rand() % ljc; W = (W0 * W0 % ljc - x + ljc) % ljc;
		if (fast_pow(W, (ljc - 1) >> 1, ljc) == ljc - 1) break;
	}
	comp a = cfast_pow(comp(W0, 1), (ljc + 1) >> 1, ljc);
	return make_pair(min(a.x, ljc - a.x), max(a.x, ljc - a.x));
}
}
