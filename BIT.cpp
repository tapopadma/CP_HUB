#include "BIT.h"

int BIT::Q(int idx){
	int ret = 0;
	while (idx){
		ret += T[idx]; idx -= idx&-idx;
	}
	return ret;
}

void BIT::U(int idx, int val){
	while (idx <= n){
		T[idx] += val; idx += idx&-idx;
	}
}

void BIT::testSumQuery(){
	cin >> n;
	T = new int[n + 1];
	a = new int[n + 1];
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	cin >> q;
	for (int i = 1; i <= n; ++i) T[i] = 0;
	for (int i = 1; i <= n; ++i){
		for (int j = i; j <= n; j += j&-j){
			T[j] += a[i];
		}
	}
	while (q--){
		int t, x, y;
		cin >> t; cin >> x >> y;
		if (t == 1){//sum from x to y			
			cout << Q(y) - Q(x - 1) << endl;
		}
		else if (t == 2){//add y to a[x]
			U(x, y);
		}
	}
}