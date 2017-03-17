#include<bits/stdc++.h>
using namespace std;

class UnionFind{
public:
	int parent;
	int rank;
};

class Graph{
private:
	vector<int> *g_, *gTR_;
	pair<int, pair<int, int> > *p;
	vector<pair<int, int> > *G_;
	bool *visited_;
	int *cost;
	int **weightMatrix;
	int **dist;
	int n_, m_;
	void dfs(int);
	void dfs1(int);
	void dfs2(int);
	void bfs(int);
	void dijkstra(int);
	void KruskalMST();
	void PrimMST();
	const static int INF = 1000000009;
	stack<int>St;
public:
	Graph();
	void testDFS();
	void testBFS();
	void testDijkstra();
	void testMST(char);
	void testFloydWarshall();
	void testSCC();
	void loadGraph_unweighted_directed();
	void loadGraph_weighted_undirected(bool);
};