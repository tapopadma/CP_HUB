#include "Treap.h"

void Treap::testTreap(){
	srand(time(NULL));//to generate unique sequence of random numbers every time code is run
	Treap t;
	t.insert(50); t.insert(30); t.insert(20);
	t.insert(40); t.insert(70); t.insert(60); t.insert(80);

	cout << "Inorder traversal of the given tree \n";
	t.print();

	cout << "\nDelete 20\n"; t.erase(20);
	cout << "Inorder traversal of the modified tree \n";
	t.print();

	cout << "\nDelete 30\n"; t.erase(30);
	cout << "Inorder traversal of the modified tree \n";
	t.print();

	cout << "\nDelete 50\n"; t.erase(50);
	cout << "Inorder traversal of the modified tree \n";
	t.print(); t.search(50);
}

void Treap::inorder(TreapNode* root){
	if (root){
		inorder(root->left);
		cout << "key: " << root->key << " | priority: %d "
			<< root->priority;
		if (root->left)
			cout << " | left child: " << root->left->key;
		if (root->right)
			cout << " | right child: " << root->right->key;
		cout << endl;
		inorder(root->right);
	}
}

void Treap::print(){
	inorder(root);
}

void Treap::search(int key){
	cout << (_search(root, key) == NULL ? "-" : "+");
}

TreapNode* Treap::_search(TreapNode* root, int key){
	if (root == NULL || root->key == key)
		return root;
	if (root->key < key)
		return _search(root->right, key);
	return _search(root->left, key);
}

TreapNode * Treap::_erase(TreapNode * root, int key){
	if (root == NULL)
		return root;
	if (key < root->key)
		root->left = _erase(root->left, key);
	else if (key > root->key)
		root->right = _erase(root->right, key);
	else if (root->left == NULL){
		TreapNode *temp = root->right; delete root; root = temp;
	}
	else if (root->right == NULL){
		TreapNode *temp = root->left; delete root; root = temp;
	}
	else if (root->left->priority < root->right->priority){
		root = leftRotate(root);
		root->left = _erase(root->left, key);
	}
	else{
		root = rightRotate(root);
		root->right = _erase(root->right, key);
	}
	return root;
}

void Treap::erase(int key){
	root = _erase(root, key);
}

void Treap::insert(int key){
	root = _insert(root, key);
}

TreapNode * Treap::_insert(TreapNode * root, int key){
	if(root == NULL){
		return new TreapNode(key);
	}
	if(root->key >= key){
		root->left = _insert(root->left, key);
	}
	else{
		root->right = _insert(root->right, key);
	}
	root = balance(root);
	return root;
}

TreapNode * Treap::balance(TreapNode * root){
	if(root->left != NULL && root->left->priority > root->priority){
		root = rightRotate(root);
	}
	if(root->right != NULL && root->right->priority > root->priority){
		root = leftRotate(root);
	}
	return root;
}

TreapNode * Treap::leftRotate(TreapNode *x){
	TreapNode *y = x->right, *T2 = y->left;
	y->left = x;
	x->right = T2;
	return y;
}

TreapNode *Treap::rightRotate(TreapNode *y){
	TreapNode * x = y->left, *T2 = x->right;
	x->right = y; y->left = T2;
	return x;
}