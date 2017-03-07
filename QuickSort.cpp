#include "QuickSort.h"

int partition(int *a, int n, int lo, int hi){
	int i = lo - 1;
	int pivot = a[hi];
	for (int j = lo; j < hi; ++j){
		if (a[j] <= pivot){
			++i;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[hi]);
	return i + 1;
}

void quick_sort(int *a, int n, int lo, int hi){//o(nlogn) worst case: O(n**2)
	if (lo < hi){
		int piv = partition(a, n, lo, hi);
		quick_sort(a, n, lo, piv - 1);
		quick_sort(a, n, piv + 1, hi);
	}
}

void QuickSort::testQuickSort(){
	int n; cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; ++i){
		cin >> a[i];
	}
	quick_sort(a, n, 0, n - 1);
	for (int i = 0; i < n; ++i){
		cout << a[i] << " ";
	}
}