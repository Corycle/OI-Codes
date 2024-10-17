#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int i,j,k,l,f[20],n;
int main(){
	cin>>n;
	f[0]=1;
	for(i=1;i<=n;i++)
		for(j=1;j<=i;j++)
			f[i]=f[i]+f[j-1]*f[i-j];

	cout<<f[n];
	return 0;
}