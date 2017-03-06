#include <bits/stdc++.h>
#include "BinarySearch.h"
using namespace std;

void BinarySearch::testBinarySearch(){
	int n; cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i){
		cin >> a[i];
	}
	int k;
	cin >> k;
	sort(a, a + n);
	int lo = 0, hi = n - 1, mid;
	while (lo <= hi){
		mid = (lo + hi) >> 1;
		if (a[mid] == k){
			cout << "Number found!"; return;
		}
		if (a[mid] > k)hi = mid - 1;
		else lo = mid + 1;
	}
	cout << "The number doesn't exist!";
}