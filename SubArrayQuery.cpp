#include "SubArrayQuery.h"

int const NN = 1e5 + 5;
int ar[NN];
int bit[NN];
struct qry{
	int x, y, k;
};
qry Q[NN];
vector<pair<pair<int, int>, pair<int, int> > > vv;
int ans[NN];

int Qrybit(int val){
	int ret = 0;
	while (val){
		ret += bit[val]; val -= val&-val;
	}
	return ret;
}

void Updbit(int val){
	int idx = val;
	while (idx < NN){
		++bit[idx]; idx += idx&-idx;
	}
}

void SubArrayQuery::testSubArrayQuery(){//Offline query ... It counts the numbers less than k in the interval ar[x..y]
	int n; cin >> n;
	for (int i = 1; i <= n; ++i)cin >> ar[i], bit[i] = 0;
	int q; cin >> q;
	for (int i = 0; i < q; ++i){
		cin >> Q[i].x >> Q[i].y >> Q[i].k;
		if (Q[i].x - 1 > 0)
			vv.push_back(make_pair(make_pair(Q[i].x - 1, Q[i].k), make_pair(i, 0)));
		vv.push_back(make_pair(make_pair(Q[i].y, Q[i].k), make_pair(i, 1)));
		ans[i] = 0;
	}
	sort(vv.begin(), vv.end());
	int it = 0, sz = vv.size();
	for (int i = 1; i <= n && it < sz; ++i){
		Updbit(ar[i]);
		int x = vv[it].first.first;
		int k = vv[it].first.second;
		int index = vv[it].second.first;
		int col = vv[it].second.second;
		while (x == i){
			if (col){
				ans[index] += Qrybit(k - 1);
			}
			else{
				ans[index] -= Qrybit(k - 1);
			}
			it++;
			if (it == sz)break;
			x = vv[it].first.first;
			k = vv[it].first.second;
			index = vv[it].second.first;
			col = vv[it].second.first;
		}
		
	}
	for (int i = 0; i < q; ++i){
		cout << ans[i] << endl;
	}
}