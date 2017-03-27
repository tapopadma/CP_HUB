#include <bits/stdc++.h>
#include "KMP.h"
using namespace std;

void getLPS(int *lps, string P){
	int len = 0;

	int M = P.length();

	lps[0] = 0; 
	int i = 1;
	while (i < M){
		if (P[i] == P[len]){
			len++;
			lps[i] = len;
			i++;
		}
		else { 
			if (len != 0){
				len = lps[len - 1];
			}
			else
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
	int i = 0;  
	int j = 0;  
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

		else if (i < n && P[j] != T[i])
		{
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
}
