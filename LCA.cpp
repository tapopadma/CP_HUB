#include "LCA.h"

int const NN = 1e5 + 5;
int pa[NN][20];
int depth[NN];
vector<int> g[NN];

void dfs(int x, int y){//O(n)
	pa[x][0] = y;
	if(y != -1) depth[x] = depth[y] + 1;
	for(vector<int>::iterator it=g[x].begin();it!=g[x].end();++it){
		int xx = *it;
		if(xx == y)continue;
		dfs(xx, x);
	}
}

int getLCA(int x, int y){//O(log(depth[x]))
	if(depth[x] < depth[y]) swap(x, y);
	int logV = 1;
	while(1<<logV <= depth[x])++logV;
	--logV;
	for(int i=logV;i>=0;--i){
		if(depth[x]-(1<<i) >= depth[y]){
			x = pa[x][i];
		}
	}
	if(x == y)
		return x;
	for(int i=logV;i>=0;--i){
		if(pa[x][i] != -1 && pa[x][i] != pa[y][i]){
			x = pa[x][i];
			y = pa[y][i];
		}
	}
	return pa[x][0];
}

void LCA::testLCA(){
	int n;cin>>n;
	for(int i=1;i<n;++i){
		int u, v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int j=0;j<20;++j){
		for(int i=1;i<=n;++i)
			pa[i][j]=-1;
	}
	memset(depth, 0, sizeof depth);
	dfs(1,-1);
	for(int j=1;j<20;++j){
		for(int i=1;i<=n;++i){
			if(pa[i][j-1] != -1)
				pa[i][j] = pa[pa[i][j-1]][j-1];
		}
	}
	int q;cin>>q;
	while(q--){
		int x, y;cin>>x>>y;
		cout<<getLCA(x, y)<<endl;
	}
}