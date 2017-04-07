#include "Treap.h"

Treap::Treap(){
	root = NULL;
}

void Treap::insert(int key){
	root = _insert(root, key);
}

Node * Treap::_insert(Node * root, int key){
	if(root == NULL){
		return Node(key);
	}
	if(root->key >= key){
		root->left = _insert(root->left, key);
	}
	else{
		root->right = _insert(root->right, key);
	}
	root = balance(root);
}

Node * Treap::balance(Node * root){
	if(root->left != NULL && root->left->priority > root->priority){
		root = rightRotate(root);
	}
	if(root->right != NULL && root->right->priority > root->priority){
		root = leftRotate(root);
	}
}