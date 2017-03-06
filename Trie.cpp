#include "Trie.h"

Node::Node(){
	for (int i = 0; i < 26; ++i)
		this->child[i] = NULL;
	isLeaf = false;
}

Trie::Trie(){
	this->root = new Node();
}

void Trie::insert_(Node * root, string s){
	Node *p = root;
	for (int i = 0; i < s.length(); ++i){
		int idx = s[i] - 'a';
		if (p->child[idx] == NULL){
			p->child[idx] = new Node();
		}
		p = p->child[idx];
	}
	p->isLeaf = true;
}

void Trie::insert(string s){
	this->insert_(this->root, s);
}

bool Trie::search_(Node * root, string s){
	if (root == NULL)
		return false;
	Node *p = root;
	for (int i = 0; i < s.length(); ++i){
		int idx = s[i] - 'a';
		if (p->child[idx] == NULL)
			return false;
		p = p->child[idx];
	}
	return p->isLeaf;
}

void Trie::search(string s){
	if (this->search_(this->root, s)){
		puts("Found");
	}
	else{
		puts("Not Found");
	}
}

bool Trie::isFreeNode(Node * root){
	if (root == NULL)
		return false;
	for (int i = 0; i < 26; ++i){
		if (root->child[i] != NULL)
			return false;
	}
	return true;
}

void Trie::remove_(Node *root, string s, int it){
	if (it == s.length())
		return;
	if (root == NULL){
		puts("String Search Failed!");
		return;
	}
	int idx = s[it] - 'a';
	if (it == s.length() - 1){
		if (root->child[idx] == NULL || !root->child[idx]->isLeaf){
			puts("String Search Failed!");
			return;
		}		
	}	
	remove_(root->child[idx], s, it + 1);
	if (this->isFreeNode(root->child[idx])){
		delete root->child[idx];
		root->child[idx] = NULL;
	}
}

void Trie::remove(string s){
	this->remove_(root, s, 0);
}

void Trie::testTrie(){
	int q; cin >> q;
	while (q--){
		cout << "1.add\n2.search\n3.delete\n";
		int k; cin >> k;
		if (k == 1){
			string s; cin >> s;
			this->insert(s);
		}
		else if (k == 2){
			string s; cin >> s;
			this->search(s);
		}
		else{
			string s; cin >> s;
			this->remove(s);
		}
	}
}