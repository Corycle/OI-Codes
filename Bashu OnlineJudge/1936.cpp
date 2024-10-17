#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,i,j,k,l,a[1005],f[1001];
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		for(j=1;j<i;j++){
			if(i%j==0)a[i]+=j;
		}
	}
	for(j=1;j<=n;j++){
		for(i=1;i<=n;i++){
			if(j>=i)f[j]=max(f[j],f[j-i]+a[i]);
		}
	}
	cout<<f[n];
	return 0;
}
