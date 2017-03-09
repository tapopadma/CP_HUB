#include "InversionCounter.h"

int InversionCounter::mergeThese(int l, int m, int r){	
	int *b = new int[r-l+1];
	int i=l,j=m+1,k=0,ret=0;
	while(i<=m||j<=r){
		if(i>m){
			b[k++]=a[j++];continue;
		}
		if(j>r){
			b[k++]=a[i++];continue;
		}
		if(a[i]<=a[j]){
			b[k++]=a[i++];
		}
		else{
			b[k++]=a[j++];
			ret += m-i+1;
		}
	}
	for(int i=l;i<=r;++i)a[i]=b[i-l];
	//for(int i=0;i<n;++i)cout<<a[i]<<endl;cout<<l<<" "<<m<<" "<<r<<endl;puts("---");
	return ret;
}

int InversionCounter::mergeSortForInversion(int l, int r){
	if(l==r)return 0;
	int m = (l + r)>>1;
	return mergeSortForInversion(l, m) + mergeSortForInversion(1+m,r)+mergeThese(l,m,r);
}

void InversionCounter::testInversionDivideConquer(){
	cin>>n;
	a = new int[n];
	for(int i=0;i<n;++i)
		cin>>a[i];
	cout<<"Number of Inversions: "<<mergeSortForInversion(0, n-1)<<endl;
}

int const NN = 1e5 + 5;
int Ts[3*NN];

int Qs(int i, int l, int r, int x, int y){
	if(x > r || y < l)
		return 0;
	if(x<=l && r<=y)
		return Ts[i];
	int m = (l+r)>>1;
	return Qs(2*i,l,m,x,y)+Qs(1+2*i,1+m,r,x,y);
}

void Us(int i, int l, int r, int idx){
	if(idx > r || idx < l)return;
	if(l == r){
		++Ts[i];
		return;
	}
	int m = (l + r)>>1;
	if(idx > m) Us(2*i+1,m+1,r,idx);
	else Us(2*i,l,m,idx);
	Ts[i] = Ts[2*i] + Ts[1+2*i];
}

void InversionCounter::testInversionSegmentTree(){
	memset(Ts, 0, sizeof Ts);
	cin>>n;
	a = new int[n+1];
	int ans = 0;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		ans += i - Qs(1,1,n,1,a[i]) - 1;
		Us(1,1,n,a[i]);
	}
	cout<<"Number of Inversions: "<<ans<<endl;
}

int Tf[NN];

int Qf(int idx){
	int ret = 0;
	while(idx){
		ret += Tf[idx];idx-=idx&-idx;
	}
	return ret;
}

void Uf(int idx){
	while(idx < NN){
		++Tf[idx];idx+=idx&-idx;
	}
}

void InversionCounter::testInversionFenwickTree(){
	memset(Tf, 0, sizeof Tf);
	cin>>n;
	a = new int[n+1];
	int ans = 0;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		ans += i - Qf(a[i]) - 1;
		Uf(a[i]);
	}
	cout<<"Number of Inversions: "<<ans<<endl;
}