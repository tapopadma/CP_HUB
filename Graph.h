#include<bits/stdc++.h>
using namespace std;

class Graph{
private:
	vector<int> *g_;
	vector<pair<int, int> > *G_;
	bool *visited_;
	int *cost;
	int **weightMatrix;
	int **dist;
	int n_, m_;
	void dfs(int);
	void bfs(int);
	void dijkstra(int);
	const static int INF = 1000000009;
public:
	Graph();
	void testDFS();
	void testBFS();
	void testDijkstra();
	void testFloydWarshall();
	void loadGraph_unweighted_directed();
	void loadGraph_weighted_undirected(bool);
};