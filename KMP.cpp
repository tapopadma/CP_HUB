#include <bits/stdc++.h>
#include "KMP.h"
using namespace std;

void getLPS(int *lps, string P){
	// length of the previous longest prefix suffix
	int len = 0;

	int M = P.length();

	lps[0] = 0; // lps[0] is always 0

	// the loop calculates lps[i] for i = 1 to M-1
	int i = 1;
	while (i < M){
		if (P[i] == P[len]){
			len++;
			lps[i] = len;
			i++;
		}
		else { // (P[i] != P[len])
			// This is tricky. Consider the example.
			// AAACAAAA and i = 7. The idea is similar 
			// to search step.
			if (len != 0){
				len = lps[len - 1];

				// Also, note that we do not increment
				// i here
			}
			else // if (len == 0)
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

void KMP::testKMP(){
	string T, P;
	cin >> T >> P;
	int *lps = new int[P.length()];
	getLPS(lps, P);
	int n = T.length();
	int m = P.length();
	int i = 0;  // index for txt[]
	int j = 0;  // index for pat[]
	while (i < n)
	{
		if (P[j] == T[i])
		{
			j++;
			i++;
		}

		if (j == m)
		{
			printf("Found pattern at index %d \n", i - j);
			j = lps[j - 1];
		}

		// mismatch after j matches
		else if (i < n && P[j] != T[i])
		{
			// Do not match lps[0..lps[j-1]] characters,
			// they will match anyway
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
}