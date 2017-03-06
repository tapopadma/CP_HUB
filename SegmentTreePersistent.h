#include <bits/stdc++.h>
using namespace std;

struct node
{
	int count;
	node *left, *right;

	node(int count, node *left, node *right) :
		count(count), left(left), right(right) {}

	node* insert(int l, int r, int w);
};

class SegmentTreePersistent{
public:
	void testSegmentTreePersistent();
};