#include "NcrModM.h"
#define ll long long

int ncr(int n, int r){
	if (r > n)return 0;
	if (n == r)return 1;
	if (r > n - r) r = n - r;
	if (r == 0)return 1;
	if (r == 1)return n;
	int ret = 1;
	for (int i = n; i > n - r; --i){
		ret *= i;
		ret /= n - i + 1;
	}
	return ret;
}

void NcrModM::testMsmallPrime(){//Lucas' theorem
	int n, r, m; cin >> n >> r >> m;
	int ret = 1;
	while (n || r){
		int dn = n%m;
		int dr = r%m;
		ret = (ret * ncr(dn, dr)) % m;
		n /= m; r /= m;
	}
	cout << ret << endl;
}

int NcrModM::testMsmallPrime(int n, int r, int m){//Lucas' theorem
	int ret = 1;
	while (n || r){
		int dn = n%m;
		int dr = r%m;
		ret = (ret * ncr(dn, dr)) % m;
		n /= m; r /= m;
	}
	return ret;
}

ll expo(ll x, ll n, ll m){
	ll ret = 1, sq = x;
	while (n){
		if (n & 1){
			ret = (ret * sq) % m;
		}
		n >>= 1;
		sq = (sq * sq) % m;
	}
	return ret;
}

void NcrModM::testMlargePrime(){//inverse modulo
	ll n, r, m; cin >> n >> r >> m;
	ll ret = 1;
	for (ll i = n; i > n - r; --i){
		ret = (ret * i) % m;
	}
	for (ll i = 1; i <= r; ++i){
		ret = (ret * expo(i, m - 2, m)) % m;
	}
	cout << ret << endl;
}

int const NN = 1e6 + 6;
int p[NN], tot = 0;
bool b[NN];

void pre(){
	p[tot++] = 2;
	for (int i = 3; i < NN; i += 2){
		if (b[i])continue;
		p[tot++] = i;
		for (int j = 1; j*i < NN; ++j){
			b[j*i] = true;
		}
	}
}

void NcrModM::testMnonPrime(){//CRT
	int n, r, m; cin >> n >> r >> m;
	pre();
	int num = m;
	vector<int> vv;
	for (int i = 0; i < tot && p[i] * p[i] <= num; ++i){
		if (num%p[i])continue;
		int ret = 1;
		while (num%p[i] == 0){
			ret *= p[i]; num /= p[i];
		}
		vv.push_back(ret);
	}
	if (num > 1)vv.push_back(num);
	vector<int>vv1;
	for (int i = 0; i < vv.size(); ++i){
		vv1.push_back(testMsmallPrime(n, r, vv[i]));
	}
	int ret = 0;
	for (int i = 0; i < vv1.size(); ++i){
		ret = (ret + vv1[i] * (m / vv[i])) % m;
	}
	cout << ret << endl;
}