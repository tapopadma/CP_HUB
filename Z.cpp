#include "Z.h"

int const NN = 1e6 + 6;
int z[NN];

void buildZ(string s){
	int n = s.length();
	for (int i = 0; i < n; ++i)z[i] = 0;
	int L = 0, R = 0;
	for (int i = 1; i < n; ++i){
		if (i > R){
			L = R = i;
			while (R < n && s[R - L] == s[R])++R;
			z[i] = R - L; --R;
		}
		else{
			int k = i - L;
			if (z[k] < R - i + 1) z[i] = z[k];
			else {
				L = i;
				while (R < n && s[R - L] == s[R]) R++;
				z[i] = R - L; R--;
			}
		}
	}
}

void printOccurence(string T, string P){
	int n = T.length(), m = P.length();
	buildZ(P+T);
	T = P + T;
	n = m + n;
	for (int i = 0; i < n; ++i){
		if (z[i] >= m){
			cout << "matching pattern found at: " << i + 1 - m << endl;
		}
	}
}

void Z::testZ(){
	string T, P;
	cin >> T >> P;
	printOccurence(T, P);
}