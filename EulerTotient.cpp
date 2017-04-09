#include "EulerTotient.h"

int phi(int n) {
	int result = n;
	for (int i = 2; i*i <= n; ++i){
		if (n % i)continue;
		while (n % i == 0)
			n /= i;
		result -= result / i;
	}
	if (n > 1)
		result -= result / n;
	return result;
}

void EulerTotient::testEulerTotient(){
	int n; cin >> n;
	//find the number of numbers less than n whose gcd with n = 1
	cout << phi(n) << endl;
}