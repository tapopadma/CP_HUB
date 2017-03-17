#include "Graph.h"

Graph::Graph(){
}

void Graph::loadGraph_unweighted_directed(){
	cin >> this->n_;
	this->g_ = new vector<int>[n_];
	cin >> this->m_;
	for (int i = 0; i < m_; ++i){
		int u, v; cin >> u >> v;
		g_[u].push_back(v);
	}
	this->visited_ = new bool[n_];
	for (int i = 0; i < n_; ++i)
		visited_[i] = false;
}

void Graph::dfs(int node){
	cout << node; putchar(' ');
	for (vector<int>::iterator it = g_[node].begin(); it != g_[node].end(); ++it){
		int x = *it;
		if (visited_[x])continue;
		visited_[x] = true;
		dfs(x);
	}
}

void Graph::testDFS(){
	this->loadGraph_unweighted_directed();
	int start; cin >> start;
	this->visited_[start] = true;
	this->dfs(start);
}

void Graph::testBFS(){
	this->loadGraph_unweighted_directed();
	int start; cin >> start;
	this->visited_[start] = true;
	this->bfs(start); puts("");
}

void Graph::bfs(int node){
	queue<int>Q; Q.push(node); this->visited_[node] = true;
	while (!Q.empty()){
		int x = Q.front(); Q.pop();
		cout << x << " ";
		for (vector<int>::iterator it = this->g_[x].begin(); it != this->g_[x].end(); ++it){
			int xx = *it;
			if (this->visited_[xx])continue;
			this->visited_[xx] = true;
			Q.push(xx);
		}
	}
	puts("");
}

void Graph::loadGraph_weighted_undirected(bool smallGraph = false){
	cin >> this->n_;
	this->G_ = new vector<pair<int, int> >[n_];	
	if (smallGraph){
		this->weightMatrix = new int *[n_];
		for (int i = 0; i < n_; ++i){
			this->weightMatrix[i] = new int[n_];
			for (int j = 0; j < n_;++j) weightMatrix[i][j] = INF;
		}
	}
	cin >> this->m_;
	this->p = new pair<int, pair<int, int> >[m_];
	for (int i = 0; i < m_; ++i){
		int u, v, w; cin >> u >> v >> w;
		G_[u].push_back(pair<int, int>(v, w));
		G_[v].push_back(pair<int, int>(u, w));
		p[i] = make_pair(w, make_pair(u, v));
		if (smallGraph){
			weightMatrix[u][v] = weightMatrix[v][u] = w;
		}
	}
	this->cost = new int[n_];
	for (int i = 0; i < n_; ++i)
		cost[i] = INF;
}

void Graph::dijkstra(int source){
	cost[source] = 0;
	set<pair<int, int> > Q;
	Q.insert(pair<int, int>(cost[source], source));
	while (!Q.empty()){
		int x = Q.begin()->second;
		int dx = Q.begin()->first;
		Q.erase(Q.begin());
		for (vector<pair<int, int> >::iterator it = G_[x].begin();
			it != G_[x].end(); ++it){
			int xx = (*it).first;
			int dxx = (*it).second;
			if (dx + dxx < cost[xx]){
				Q.erase(pair<int, int>(cost[xx], xx));
				cost[xx] = dx + dxx;
				Q.insert(pair<int, int>(cost[xx], xx));
			}
		}
	}
	cout << "Distance of nodes from node " << source << ":\n";
	for (int i = 0; i < n_; ++i){
		cout << i << ". " << cost[i] << "\n";
	}
}

void Graph::testDijkstra(){
	this->loadGraph_weighted_undirected();
	int source; cin >> source;
	this->dijkstra(source);
}

void Graph::testFloydWarshall(){
	this->loadGraph_weighted_undirected(true);
	dist = new int*[n_];
	for (int i = 0; i < n_; ++i)dist[i] = new int[n_];
	for (int i = 0; i < n_; ++i){
		for (int j = 0; j < n_; ++j){
			dist[i][j] = weightMatrix[i][j];
		}
	}
	for (int k = 0; k < n_; ++k){
		for (int i = 0; i < n_; ++i){
			for (int j = 0; j < n_; ++j){
				if (dist[i][k] + dist[k][j] < dist[i][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	for (int i = 0; i < n_; ++i){
		for (int j = i + 1; j < n_; ++j){
			cout << "Distance between " << i << " & " << j << " : " << dist[i][j] << endl;
		}
	}
}

int Find(int x, UnionFind *pa){
	if (pa[x].parent != x)
		return pa[x].parent = Find(pa[x].parent, pa);
	return pa[x].parent;
}

void Union(int x, int y, UnionFind *pa){
	int xx = Find(x, pa);
	int yy = Find(y, pa);
	if (pa[xx].rank == pa[yy].rank){
		pa[yy].parent = xx;
		pa[xx].rank++;
	}
	else if (pa[xx].rank > pa[yy].rank){
		pa[yy].parent = xx;
	}
	else{
		pa[xx].parent = yy;
	}
}

void Graph::KruskalMST(){//O(mlogn)
	cin >> n_;
	cin >> m_;
	p = new pair<int, pair<int, int> >[m_];
	for (int i = 0; i < m_; ++i){
		cin >> p[i].second.first >> p[i].second.second >> p[i].first;
	}
	sort(p, p + m_);
	UnionFind *pa = new UnionFind[n_];
	for (int i = 0; i < n_; ++i){
		pa[i].parent = i;
		pa[i].rank = 0;
	}
	int tot = 0;
	for (int i = 0; i < m_; ++i){
		int u = p[i].second.first;
		int v = p[i].second.second;
		int w = p[i].first;
		if (Find(u, pa) == Find(v, pa))continue;
		Union(u, v, pa);
		tot += w;
	}
	cout << "MST cost: " << tot << endl;
}

void Graph::PrimMST(){
	loadGraph_weighted_undirected();
	int x = 0;
	set<pair<int, int> > Q;
	cost[0] = 0;
	Q.insert(pair<int, int>(cost[0], 0));
	visited_ = new bool[n_];
	for (int i = 0; i < n_; ++i) visited_[i] = false;	
	int ans = 0;
	while (!Q.empty()){
		pair<int, int> pp = *Q.begin();
		int x = pp.second;
		int dx = pp.first;
		Q.erase(pair<int, int>(dx, x));
		visited_[x] = true;
		ans += dx;
		for (vector<pair<int, int> >::iterator it = G_[x].begin(); it != G_[x].end(); ++it){
			int xx = (*it).first;
			int dxx = (*it).second;
			if (dxx < cost[xx] && !visited_[xx]){
				Q.erase(pair<int, int>(cost[xx], xx));
				cost[xx] = dxx;
				Q.insert(pair<int, int>(cost[xx], xx));
			}
		}
	}
	cout << "MST cost: " << ans << endl;
}

void Graph::testMST(char c){
	if(c == 'K') KruskalMST();
	else PrimMST();
}

void Graph::dfs1(int node){
	for (vector<int>::iterator it = g_[node].begin(); it != g_[node].end(); ++it){
		int x = *it;
		if (visited_[x])continue;
		visited_[x] = true;
		dfs1(x);
	}
	St.push(node);
}

void Graph::dfs2(int node){
	cout << node << " ";
	for (vector<int>::iterator it = gTR_[node].begin(); it != gTR_[node].end(); ++it){
		int x = *it;
		if (visited_[x])continue;
		visited_[x] = true;
		dfs2(x);
	}
}

void Graph::testSCC(){
	loadGraph_unweighted_directed();
	for (int i = 0; i < n_; ++i){
		if (visited_[i])continue;
		visited_[i] = true;
		dfs1(i);
	}
	for (int i = 0; i < n_; ++i){
		visited_[i] = false;
	}
	gTR_ = new vector<int>[n_];
	for (int i = 0; i < n_; ++i){
		for (vector<int>::iterator it = g_[i].begin(); it != g_[i].end(); ++it){
			int j = *it;
			gTR_[j].push_back(i);
		}
	}
	while (!St.empty()){
		int node = St.top(); St.pop();
		if (visited_[node])continue;
		visited_[node] = true;
		dfs2(node); cout << endl;
	}
}