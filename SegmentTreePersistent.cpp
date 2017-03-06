/*
By Anudeep Nekkanti
Editorial at www.blog.anudeep.com/persistent-segment-trees-explained-with-spoj-problems
Question at http://www.spoj.com/problems/COT/
O( (N+M) * log N )
*/

#include "SegmentTreePersistent.h"

#define fd(i,a,b) for(int i=a; i>=b; i--)

#define N 111111
#define LN 19
int v[N], pa[N][LN], RM[N], depth[N], maxi = 0;
vector <int> adj[N];
map <int, int> M;


int LCA(int u, int v){
	if (depth[u] < depth[v])
		return LCA(v, u);

	int diff = depth[u] - depth[v];

	for (int i = 0; i < LN; ++i){
		if ((diff >> i) & 1){
			u = pa[u][i];
		}
	}

	if (u != v)
	{
		for (int i = LN - 1; i >= 0; --i){
			if (pa[u][i] != pa[v][i]){
				u = pa[u][i];
				v = pa[v][i];
			}			
		}
		u = pa[u][0];
	}

	return u;
}

int query(node *a, node *b, node *c, node *d, int l, int r, int k)
{
	if (l + 1 == r)
	{
		return l;
	}

	int count = a->left->count + b->left->count - c->left->count - d->left->count;
	int m = (l + r) >> 1;

	if (count >= k)
		return query(a->left, b->left, c->left, d->left, l, m, k);

	// We do not have enough on left, go right, remove left elements count
	return query(a->right, b->right, c->right, d->right, m, r, k - count);
}

node *root[N];
node *null = new node(0, NULL, NULL); //see line 135

node * node::insert(int l, int r, int w)
{
	if (l <= w && w < r)
	{
		// With in the range, we need a new node
		if (l + 1 == r)
		{
			return new node(this->count + 1, null, null);
		}

		int m = (l + r) >> 1;

		return new node(this->count + 1, this->left->insert(l, m, w), this->right->insert(m, r, w));
	}

	// Out of range, we can use previous tree node.
	return this;
}

void dfs(int cur, int prev)
{
	pa[cur][0] = prev;
	depth[cur] = (prev == -1 ? 0 : depth[prev] + 1);

	// Construct the segment tree for this node using parent segment tree	
	// This is the formula we derived
	root[cur] = (prev == -1 ? null : root[prev])->insert(0, maxi, M[v[cur]]);

	for (int i = 0; i < adj[cur].size(); ++i){
		if (adj[cur][i] != prev){
			dfs(adj[cur][i], cur);
		}
	}
}

void SegmentTreePersistent::testSegmentTreePersistent(){
	int n, m;

	cin >> n >> m;

	for (int i = 0; i < n; ++i){
		cin >> v[i];
		M[v[i]];
	}

	maxi = 0;
	for (map <int, int > ::iterator it = M.begin(); it != M.end(); it++){
		M[it->first] = maxi;
		RM[maxi] = it->first;
		maxi++;
	}
	for (int i = 1; i < n;++i){
		int u, v; cin >> u >> v;
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	memset(pa, -1, sizeof pa);
	null->left = null->right = null;
	dfs(0, -1);
	for (int i = 0; i < LN - 1; ++i){
		for (int j = 0; j < n; ++j){
			if (pa[j][i] != -1){
				pa[j][i + 1] = pa[pa[j][i]][i];
			}
		}
	}

	for (int j = 1; j < LN - 1; ++j){
		for (int i = 0; i < n; ++i){
			pa[i][j] = (pa[i][j - 1] == -1 ? -1 :
				pa[pa[i][j - 1]][j - 1]);
		}
	}

	while (m--){
		int u, v, k;
		cin >> u >> v >> k;
		u--; v--;

		int lca = LCA(u, v);
		int ans = query(root[u], root[v], root[lca], 
			(pa[lca][0] == -1 ? null : root[pa[lca][0]]), 0, maxi, k);
		printf("%d\n", RM[ans]);
	}
}