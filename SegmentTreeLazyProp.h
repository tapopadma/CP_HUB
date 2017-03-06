#include<bits/stdc++.h>
using namespace std;

class Node_STLP{
public:
	int sum;
	int add;
	Node_STLP();
	Node_STLP(int, int);
};

class SegmentTreeLazyProp :public Node_STLP{
	Node_STLP *Tree;
	int n;
public:
	SegmentTreeLazyProp(int);
	void BuildTree(int, int, int);
	void Add(int, int, int, int, int, int);
	int Sum(int, int, int, int, int);
	void testLazyPropagation();
};