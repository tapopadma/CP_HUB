#include <bits/stdc++.h>
using namespace std;

const int MX = 1e9;

class TreapNode{
public:
	int key, priority;
	TreapNode *left, *right;
	TreapNode(){
	}
	TreapNode(int _key){
		key = _key;
		priority = rand()%MX;
		left = right = NULL;
	}
};

class Treap:public TreapNode{
private:
	TreapNode *root;
	TreapNode * _insert(TreapNode *, int);
	TreapNode * balance(TreapNode *);
	TreapNode * _erase(TreapNode *, int);
	TreapNode * _search(TreapNode *, int);
	void inorder(TreapNode *);
	TreapNode * leftRotate(TreapNode*);
	TreapNode * rightRotate(TreapNode*);
public:
	Treap(){
		root = NULL;
	}
	void search(int);
	void insert(int);
	void erase(int);
	void print();
	void testTreap();
};