#include<bits/stdc++.h>
using namespace std;

class Node{
public:
	Node * child[26];
	bool isLeaf;
	Node();
};

class Trie:public Node{
private:
	Node * root;
	void insert_(Node *, string);
	bool search_(Node *, string);
	void remove_(Node *, string, int);
	bool isFreeNode(Node *);
public:
	Trie();
	void testTrie();
	void insert(string);
	void search(string);
	void remove(string);
};