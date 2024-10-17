#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int f[10005][1005],i,j,k,n;
int main(){
	cin>>n>>k;
	for(i=1;i<=n;i++){
		for(j=1;j<=k;j++){
			if(i<j)f[i][j]=0;
			else if(j==1)f[i][j]=1;
			else if(i==j)f[i][j]=1;
			else f[i][j]=f[i-1][j-1]+f[i-j][j];
			f[i][j]%=10003;
		}
	}
	cout<<f[n][k]%10003;
	return 0;
}