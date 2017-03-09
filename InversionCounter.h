#include <bits/stdc++.h>
using namespace std;

class InversionCounter
{
	int *a, n;
	int mergeThese(int,int,int);
	int mergeSortForInversion(int,int);
public:
	void testInversionDivideConquer();
	void testInversionSegmentTree();
	void testInversionFenwickTree();
};