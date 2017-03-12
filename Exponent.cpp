#include "Exponent.h"
typedef long long ll;
ll const mod = 1e9 + 7;

ll expo(ll x, ll n){
	ll ret = 1, sq = x;
	while (n){
		if (n & 1) ret = (ret * sq) % mod;
		n >>= 1;
		sq = (sq * sq) % mod;
	}
	return ret;
}

void Exponent::testExponent(){
	ll x, n; cin >> x >> n;
	cout << expo(x, n) << endl;
}