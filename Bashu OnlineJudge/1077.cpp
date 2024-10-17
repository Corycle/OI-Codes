#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int n,a[101][101],i,j;
int main(){
	cin>>n;
	memset(a,0,sizeof(a));
	for(i=1;i<=n;i++)
		for(j=1;j<=i;j++)
		cin>>a[i][j];
	for(i=2;i<=n;i++)
		for(j=1;j<=i;j++)
			a[i][j]+=max(a[i-1][j-1],a[i-1][j]);	
	j=0;
	for(i=1;i<=n;i++)
	j=max(j,a[n][i]);
	cout<<j;
	return 0;
}
