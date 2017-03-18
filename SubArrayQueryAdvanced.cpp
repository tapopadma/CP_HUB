#include "SubArrayQueryAdvanced.h"
#define Fill(a,val) memset(a,val,sizeof a)

int const NN = 3e4 + 4;
int ar1[NN];
int const BLK = 400;
int T[BLK][NN];

void U(int bl, int idx, int val){
	while (idx < NN){
		T[bl][idx] += val; idx += idx&-idx;
	}
}

int Q(int bl, int idx){
	int ret = 0;
	while (idx){
		ret += T[bl][idx]; idx -= idx&-idx;
	}
	return ret;
}

void SubArrayQueryAdvanced::testSubArrayQueryAdvanced(){
	Fill(T, 0);
	int n; cin >> n;
	for (int i = 1; i <= n; ++i){
		cin >> ar1[i];
		U(i / BLK, ar1[i], +1);
	}
	int q; cin >> q;
	while (q--){
		int type; cin >> type;
		if (type == 0){
			int x, val; cin >> x >> val;
			U(x / BLK, ar1[x], -1);
			ar1[x] = val;
			U(x / BLK, ar1[x], +1);
		}
		else{
			int L, R, k; cin >> L >> R >> k;
			int ans = 0;
			while (L <= R && L%BLK != 0){
				ans += ar1[L++] > k;
			}
			while (L <= R && R%BLK != BLK - 1){
				ans += ar1[R--] > k;
			}
			if (L < R){
				int bl = L / BLK, br = R / BLK;
				for (int i = bl; i <= br; ++i){
					ans += BLK - Q(i, k);
				}
			}
			cout << ans << endl;
		}
	}
}