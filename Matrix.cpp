#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<char> vc;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const double EPS = 1e-9;
const int INF = 1 << 29;
#define mp make_pair
#define el putchar('\n')
#define sp putchar(' ')
#define Fill(a, val) memset(a, val, sizeof a)
#define all(a) a.begin(), a.end()
#define tr(a, it) for (typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define in(n) scanf("%d", &n)
#define inl(n) scanf("%I64d", &n)
#define out(n) printf("%d", n);
#define outl(n) printf("%I64d", n);

int const NN = 1e3 + 3;

class Matrix{
public:
	int a[100][100];
	int r;
	int c;
	Matrix();
	Matrix operator +(const Matrix&);
	Matrix operator *(const Matrix&);
	Matrix operator ^(int);
	void display();
};

Matrix::Matrix(){
	memset(a, 0, sizeof a);
}

Matrix Matrix::operator +(const Matrix &m){
	for(int i=0;i<r;++i){
		for(int j=0;j<c;++j)
			a[i][j] += m.a[i][j];
	}
	return *this;
}

void Matrix::display(){
	puts("-----");
	for(int i=0;i<r;++i){
		for(int j=0;j<c;++j){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	puts("-----");
}

Matrix Matrix::operator *(const Matrix &m){
	Matrix res;
	res.r = r;res.c = m.c;
	for(int i=0;i<r;++i){
		for(int j=0;j<m.c;++j){
			int sum = 0;
			for(int k=0;k<c;++k){
				sum += a[i][k] * m.a[k][j];
			}
			res.a[i][j] = sum;
		}
	}
	return res;
}

Matrix Matrix::operator ^(int power){
	assert(r == c);
	Matrix ret;
	ret.r = ret.c = r;
	for(int i=0;i<r;++i)
		ret.a[i][i] = 1;
	Matrix sq;
	sq.r = sq.c = r;
	sq = (*this);
	while(power){
		if(power & 1){
			ret = ret * sq;
		}
		power >>= 1;
		sq = sq * sq;
	}
	return ret;
}

int main(){
	Matrix m;
	m.r = m.c = 2;
	m.a[0][0] = 1;
	m.a[0][1] = 2;
	m.a[1][0] = 3;
	m.a[1][1] = 4;
	m = m ^ 10;
	m.display();
	return 0;
}

