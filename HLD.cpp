#include "HLD.h"
#ifndef ONLINE_JUDGE
#define tr(a, it) for (decltype(a.begin()) it = a.begin(); it != a.end(); ++it)
#else
#define tr(a, it) for (typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#endif
int const NN = 1e4 + 4;
struct data{
	int first, second, index;
	data(int f, int s, int i) :first(f), second(s), index(i){}
};
vector<data> g[NN];
int p[NN][15];
int h[NN], sz[NN], arr[NN], T[NN * 4], indexx[NN];
int chainNumber[NN], posInArr[NN], chainFather[NN], total = 1;
int chainIndex = 1;

void performHLD(int node, int prev, int cost, int index){
	if (chainFather[chainIndex] == -1){
		chainFather[chainIndex] = node;
	}
	arr[total] = cost;
	indexx[index] = total;
	chainNumber[node] = chainIndex;
	posInArr[node] = total++;
	int mx = -1, idx = -1;
	for (int i = 0; i < g[node].size(); ++i){
		int vx = g[node][i].first;
		if (vx == prev)continue;
		if (sz[vx] > mx){
			mx = sz[vx]; idx = i;
		}
	}
	if (mx == -1)
		return;
	performHLD(g[node][idx].first, node, g[node][idx].second, g[node][idx].index);
	for (int i = 0; i < g[node].size(); ++i){
		if (i == idx)continue;
		if (g[node][i].first == prev)continue;
		++chainIndex;
		performHLD(g[node][i].first, node, g[node][i].second, g[node][i].index);
	}
}

int Q(int i, int l, int r, int x, int y){
	if (x > y)
		return -1;
	if (x > r or y < l)
		return -1;
	if (x <= l and r <= y){
		return T[i];
	}
	int m = (l + r) >> 1;
	int il = i << 1, ir = il | 1;
	return max(Q(il, l, m, x, y), Q(ir, 1 + m, r, x, y));
}

void U(int i, int l, int r, int x, int val){
	if (x > r or x < l)
		return;
	if (l == r){
		T[i] = val;
	}
	else{
		int m = (l + r) >> 1;
		int il = i << 1, ir = il | 1;
		U(il, l, m, x, val);
		U(ir, 1 + m, r, x, val);
		T[i] = max(T[il], T[ir]);
	}
}

void B(int i, int l, int r){
	if (l == r){
		T[i] = arr[l];
	}
	else{
		int m = (l + r) >> 1;
		int il = i << 1;
		int ir = il | 1;
		B(il, l, m);
		B(ir, 1 + m, r);
		T[i] = max(T[il], T[ir]);
	}
}

int query(int u, int v){
	if (u == v)return 0;
	int chainU = chainNumber[u];
	int ans = -1;
	while (true){
		int chainV = chainNumber[v];
		if (chainU == chainV){
			int posU = posInArr[u] + 1;
			int posV = posInArr[v];
			int res = Q(1, 1, total, posU, posV);
			ans = max(ans, res);
			break;
		}
		int fatherV = chainFather[chainV];
		int pos1 = posInArr[fatherV], pos2 = posInArr[v];
		int res = Q(1, 1, total, pos1, pos2);
		ans = max(ans, res);
		v = p[fatherV][0];
	}
	return ans;
}

int LCA_HLD(int x, int y){
	if (h[x] > h[y])
		swap(x, y);
	int del = h[y] - h[x];
	for (int i = 0; i < 15; ++i){
		if ((del >> i) & 1){
			y = p[y][i];
		}
	}
	if (x == y)
		return x;
	for (int i = 14; i >= 0; --i){
		if (p[x][i] != p[y][i]){
			x = p[x][i];
			y = p[y][i];
		}
	}
	return p[x][0];
}

void solve(int a, int b){
	int lca = LCA_HLD(a, b);
	int ans1 = query(lca, a);
	int ans2 = query(lca, b);
	cout << max(ans1, ans2) << endl;
}

void dfs_HLD(int node, int prev){
	p[node][0] = prev;
	if (prev == -1)h[node] = 0;
	else h[node] = h[prev] + 1;
	sz[node] = 1;
	tr(g[node], it){
		data var = *it;
		int vx = var.first;
		if (vx == prev)continue;
		dfs_HLD(vx, node);
		sz[node] += sz[vx];
	}
}

void HLD::testHLD(){
	int t; cin>>t; while (t--){
		int n; cin>>n;
		total = chainIndex = 1;
		for (int i = 1; i <= n; ++i){
			chainFather[i] = -1;
			g[i].clear();
		}
		for (int i = 1; i < n; ++i){
			int a, b, c;
			cin >> a; cin >> b; cin >> c;
			g[a].push_back(data(b, c, i));
			g[b].push_back(data(a, c, i));
		}
		for (int i = 1; i <= n; ++i){
			for (int j = 0; j < 15; ++j)
				p[i][j] = -1;
		}
		dfs_HLD(1, -1);
		for (int j = 1; j < 15; ++j){
			for (int i = 1; i <= n; ++i){
				p[i][j] = (p[i][j - 1] == -1 ? -1 : p[p[i][j - 1]][j - 1]);
			}
		}
		performHLD(1, -1, -1, -1); --total;
		B(1, 1, total);
		while (true){
			char s[100]; cin >> s;
			if (s[0] == 'D')break;
			int a, b; cin >> a; cin >> b;
			if (s[0] == 'Q'){
				solve(a, b);
			}
			else{
				U(1, 1, total, indexx[a], b);
			}
		}
	}
}