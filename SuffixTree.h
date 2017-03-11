#include <bits/stdc++.h>
using namespace std;

class SuffixNode{
public:
	int depth, begin, end;
	SuffixNode **children;
	SuffixNode *parent, *suffixLink;
	SuffixNode(int, int, int, SuffixNode *);
	bool contains(int);
};

class SuffixTree{
public:
	SuffixNode *buildSuffixTree(string);
	int findLCS(SuffixNode *, int, int);
	void findLCS(string, string);
	void testSuffixTree();
};
