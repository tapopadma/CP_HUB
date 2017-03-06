#include <bits/stdc++.h>
#include "SuffixArray.h"
using namespace std;

#define MAXN 65536//2^16
#define MAXLG 17
//char s[MAXN];

struct entry
{
	int nr[2];
	int p;
} L[MAXN];

int P[MAXLG][MAXN];
int N, i;
int stp, cnt;

int cmp(entry a, entry b){
	return a.nr[0] == b.nr[0] ? a.nr[1] < b.nr[1] : a.nr[0] < b.nr[0];
}

int lcp(int x, int y, int n, int stp){//O(logn)
	int ret = 0; 
	if (x == y) return n - x;
	for (int k = stp - 1; k >= 0 && x < N && y < N; k--){
		if (P[k][x] == P[k][y]){
			x += 1 << k, y += 1 << k, ret += 1 << k;
		}
	}
	return ret;
}

void SuffixArray::testSuffixArray(){//O(n*logn*logn)
	string s; cin >> s;
	int n = s.length();
	for (int i = 0; i < n; ++i){
		P[0][i] = s[i] - 'a';
	}
	for (int stp = 1,cnt=1; cnt < n; ++stp, cnt <<= 1){
		for (int i = 0; i < n; ++i){
			L[i].nr[0] = P[stp - 1][i];
			L[i].nr[1] = ((i + cnt) < n ? P[stp - 1][i + cnt] : -1);
			L[i].p = i;
		}
		sort(L, L + n, cmp);
		for (int i = 0; i < n; ++i){
			P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0]
				&& L[i].nr[1] == L[i - 1].nr[1] ? P[stp][L[i - 1].p] : i;
		}
	}
	for (int i = 0; i < n; ++i){
		cout << L[i].p << " ";
	}
	cout << endl;
	cout << lcp(0, 1, n, stp);
}

/***********************************************************************/
#define N 10000000
char str[N];
int H = 0, Bucket[N], nBucket[N], c;

struct Suffix{
	int idx; // Suffix starts at idx, i.e. it's str[ idx .. L-1 ]
	bool operator<(const Suffix& sfx) const
		// Compares two suffixes based on their first 2H symbols,
		// assuming we know the result for H symbols.
	{
		if (H == 0) return str[idx] < str[sfx.idx];
		else if (Bucket[idx] == Bucket[sfx.idx])
			return (Bucket[idx + H] < Bucket[sfx.idx + H]);
		else
			return (Bucket[idx] < Bucket[sfx.idx]);
	}
	bool operator==(const Suffix& sfx) const
	{
		return !(*this < sfx) && !(sfx < *this);
	}
} Pos[N];

int UpdateBuckets(int len)
{
	int start = 0, id = 0, c = 0;
	for (int i = 0; i < len; i++)
	{
		/*
		If Pos[i] is not equal to Pos[i-1], a new bucket has started.
		*/
		if (i != 0 && !(Pos[i] == Pos[i - 1]))
		{
			start = i;
			id++;
		}
		if (i != start) // if there is bucket with size larger than 1, we should continue ...
			c = 1;
		nBucket[Pos[i].idx] = id; // Bucket for suffix starting at Pos[i].idx is id ...
	}
	memcpy(Bucket, nBucket, 4 * len);
	return c;
}

void SuffixSort(int len)
{
	for (int i = 0; i < len; i++) Pos[i].idx = i;
	// H == 0, Sort based on first Character.
	sort(Pos, Pos + len);
	// Create initial buckets
	c = UpdateBuckets(len);
	for (H = 1; c; H *= 2) {
		// Sort based on first 2*H symbols, assuming that we have sorted based on first H character
		sort(Pos, Pos + len);
		// Update Buckets based on first 2*H symbols
		c = UpdateBuckets(len);
	}
}

void SuffixArray::testSuffixArray_adv(){//O(nlogn)
	cin >> str;
	int len = strlen(str) + 1;
	int cl = clock();
	SuffixSort(len);
	cerr << (clock() - cl) * 0.001 << endl;
	for (int i = 0; i < len; i++){
		cout << "'" << str + Pos[i].idx << "'" << endl;
	}
}