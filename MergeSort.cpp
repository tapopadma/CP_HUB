#include<bits/stdc++.h>
#include "MergeSort.h"
using namespace std;

void merge_both(int *a, int lo, int mid, int hi){
	int tot = hi - lo + 1;
	int *b = new int[tot];
	int it = 0;
	int it1 = lo;
	int it2 = mid + 1;
	while (it1 <= mid || it2 <= hi){
		if (it1 > mid){
			b[it++] = a[it2++];
			continue;
		}
		if (it2 > hi){
			b[it++] = a[it1++];
			continue;
		}
		int n1 = a[it1];
		int n2 = a[it2];
		if (n1 < n2){
			b[it++] = a[it1++];
		}
		else{
			b[it++] = a[it2++];
		}
	}
	for (int i = 0, j = lo; i < tot; ++i, ++j)a[j] = b[i];
}

void merge_sort(int *a, int n, int lo, int hi){
	if (lo >= hi)return;
	int mid = (lo + hi) >> 1;
	merge_sort(a, n, lo, mid);
	merge_sort(a, n, mid + 1, hi);
	merge_both(a, lo, mid, hi);
}

void MergeSort::testMergeSort(){
	int n; cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i){
		cin >> a[i];
	}
	merge_sort(a, n, 0, n - 1);
	for (int i = 0; i < n; ++i){
		cout << a[i] << " ";
	}
	cout << endl;
}