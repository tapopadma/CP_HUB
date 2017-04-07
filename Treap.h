#include <bits/stdc++.h>
using namespace std;

const int MX = 1e9;

class Node{
public:
	int key, priority;
	Node *left, *right;
	Node(){
	}
	Node(int _key){
		key = _key;
		priority = rand()%MX;
		left = right = NULL;
	}
};

class Treap:public Node{
private:
	Node *root;
	Node * _insert(Node *, int);
	Node * balance(Node *);
public:
	Treap();
	void insert(int);
	void erase(int);
	void print();
};