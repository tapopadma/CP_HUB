#include "RMQ.h"

int const NN = 2e5 + 5;
int a[NN];
int M[NN][20];

int LOG(int n){
	if (n == 1)return 0;
	return 1 + LOG(n >> 1);
}

void RMQ::testRMQ(){
	int n; cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i){
		M[i][0] = i;
	}
	for (int j = 1; 1 << j <= n; ++j){
		for (int i = 0; i + (1 << (j - 1)) < n; ++i){
			if (a[M[i][j - 1]] < a[M[i + (1 << (j - 1))][j - 1]])
				M[i][j] = M[i][j - 1];
			else
				M[i][j] = M[i + (1 << (j - 1))][j - 1];
		}
	}
	int q; cin >> q;
	while (q--){
		int x, y; cin >> x >> y; --x; --y;
		int k = LOG(y - x + 1);
		cout << min(a[M[x][k]], a[M[y - (1 << k) + 1][k]]) << endl;
	}
}