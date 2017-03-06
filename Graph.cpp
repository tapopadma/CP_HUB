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
	for (int i = 0; i < m_; ++i){
		int u, v, w; cin >> u >> v >> w;
		G_[u].push_back(pair<int, int>(v, w));
		G_[v].push_back(pair<int, int>(u, w));
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