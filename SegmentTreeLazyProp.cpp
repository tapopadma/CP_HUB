#include "SegmentTreeLazyProp.h"

Node_STLP::Node_STLP(){
	sum = 0;
	add = 0;
}

Node_STLP::Node_STLP(int _sum, int _add){
	sum = _sum;
	add = _add;
}

SegmentTreeLazyProp::SegmentTreeLazyProp(int n){
	//Check this
	this->n = n;
	Tree = new Node_STLP[5 * n + 5];
}

void SegmentTreeLazyProp::BuildTree(int i, int l, int r){
	Tree[i] = Node_STLP(0, 0);
	if (l == r)
		return;
	int m = (l + r) >> 1;
	BuildTree(2 * i, l, m);
	BuildTree(1 + 2 * i, 1 + m, r);
}

void SegmentTreeLazyProp::Add(int i, int l, int r, int a, int b, int v){
	if (a > r || b < l)
		return;
	if (a <= l && r <= b){
		Tree[i].add += v;
	}
	else {
		int m = (l + r) >> 1;
		Add(2 * i, l, m, a, b, v);
		Add(1 + 2 * i, 1 + m, r, a, b, v);
		Tree[i].sum = Tree[2 * i].sum + Tree[2 * i].add*(m - l + 1) + 
			Tree[1 + 2 * i].sum + Tree[1 + 2 * i].add*(r - m);
	}
}

int SegmentTreeLazyProp::Sum(int i, int l, int r, int a, int b){
	if (a > r || b < l)
		return 0;
	if (a <= l && r <= b)
		return Tree[i].sum + Tree[i].add*(r - l + 1);
	int m = (l + r) >> 1;
	return Sum(2 * i, l, m, a, b) + Sum(1 + 2 * i, 1 + m, r, a, b) + 
		Tree[i].add*(min(b, r) - max(a, l) + 1);
}

void SegmentTreeLazyProp::testLazyPropagation(){
	int c;
	cin >> c;
	this->BuildTree(1, 1, n);
	while (c--){
		int type;
		cin >> type;
		if (type == 0){
			int p, q, v;
			cin >> p >> q >> v;
			this->Add(1, 1, n, p, q, v);
		}
		else {
			int p, q;
			cin >> p >> q;
			cout << this->Sum(1, 1, n, p, q) << endl;
		}
	}
}