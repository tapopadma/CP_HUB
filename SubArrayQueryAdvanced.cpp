#include "SubArrayQueryAdvanced.h"
#define Fill(a,val) memset(a,val,sizeof a)

int const NN = 3e4 + 4;
int ar1[NN];
int const BLK = 400;
int T[BLK][NN];
int block[NN];

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
		block[i] = i / BLK;
		U(block[i], ar1[i], +1);
	}
	int q; cin >> q;
	while (q--){
		int type; cin >> type;
		if (type == 0){
			int x, val; cin >> x >> val;
			U(block[x], ar1[x], -1);
			ar1[x] = val;
			U(block[x], ar1[x], +1);
		}
		else{
			int L, R, k; cin >> L >> R >> k;
			int ans = 0;
			if (block[L] != block[R]){
				if (L <= R){
					int bl = block[L], br = block[R];
					while (block[L] == bl){
						ans += ar1[L++] < k;
					}
					while (block[R] == br){
						ans += ar1[R--] < k;
					}
					for (int i = block[L]; i <= block[R]; ++i){
						ans += Q(i, k - 1);
					}
				}
			}
			else{
				while (L <= R){
					ans += ar1[L++] < k;
				}
			}
			cout << ans << endl;
		}
	}
}