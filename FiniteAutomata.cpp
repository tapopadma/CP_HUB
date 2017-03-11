#include "FiniteAutomata.h"

#define NO_OF_CHARS 256

int const NN = 1e5 + 5;
int TF[NN][NO_OF_CHARS];

int getNextState(string P, int m, int state, int x){
	if (state < m && x == P[state])
		return state + 1;

	int ns, i;
	for (ns = state; ns > 0; ns--){
		if (P[ns - 1] == x){
			for (i = 0; i < ns - 1; i++){
				if (P[i] != P[state - ns + 1 + i])
					break;
			}
			if (i == ns - 1)
				return ns;
		}
	}
	return 0;
}

void computeTF(string P, int m){
	int state, x;
	for (state = 0; state <= m; ++state){
		for (x = 0; x < NO_OF_CHARS; ++x){
			TF[state][x] = getNextState(P, m, state, x);
		}
	}
}

void computeTransFun(string P, int m){
	int i, lps = 0, x;
	for (x = 0; x < NO_OF_CHARS; x++){
		TF[0][x] = 0;
	}
	TF[0][P[0]] = 1;

	for (i = 1; i <= m; i++){
		for (x = 0; x < NO_OF_CHARS; x++){
			TF[i][x] = TF[lps][x];
		}
		TF[i][P[i]] = i + 1;
		if (i < m)
			lps = TF[lps][P[i]];
	}
}

void search__(string T, string P){
	int m = P.length();
	int n = T.length();
	//computeTF(P, m); //Naive
	computeTransFun(P, m);//O(m)

	int i, state = 0;
	for (i = 0; i < n; i++){
		state = TF[state][T[i]];
		if (state == m){
			printf("\nfound at %d", i - m + 1);
		}
	}
}

void FiniteAutomata::testPatternMatching(){
	string T, P; cin >> T >> P;
	search__(T, P);
}