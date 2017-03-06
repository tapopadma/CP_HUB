#include "heap.h"

void heap::testHeapSort(){
	cin >> n;
	h = new int[n + 1];
	index = 0;
	for (int i = 1; i <= n; ++i){
		int x; cin >> x;
		h[++index] = x; int idx = index;
		while ((idx >> 1) && h[idx >> 1] > h[idx]){
			swap(h[idx >> 1], h[idx]); idx >>= 1;
		}
	}
	while (index){
		cout << h[1]<<" ";
		swap(h[1], h[index--]);
		int idx = 1;
		while ((idx << 1) <= index){
			if ((idx << 1) + 1 > index){
				if (h[idx << 1] < h[idx]){
					swap(h[idx << 1], h[idx]);
				}
				break;
			}
			else{
				int mn = min(h[idx << 1], h[1 + (idx << 1)]);
				if (mn >= h[idx])break;
				if (mn == h[idx << 1]){
					swap(h[idx << 1], h[idx]); idx <<= 1;
				}
				else{
					swap(h[1 + (idx << 1)], h[idx]); idx <<= 1; idx++;
				}
			}
		}
	}
	puts("");
}