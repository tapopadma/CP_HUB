#include <bits/stdc++.h>
using namespace std;

class BIT{
private:
	int n;
	int *T;
	int *a;
	int q;
public:
	void testSumQuery();
	int Q(int);
	void U(int, int);
};