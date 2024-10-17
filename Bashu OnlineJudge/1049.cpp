#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int i,j,k,t,m,dzh[105],v[105],f[105][1005];
int main(){
	cin>>t>>m;
	for(i=1;i<=m;i++)cin>>dzh[i]>>v[i];
	for(i=1;i<=m;i++){
		for(j=1;j<=t;j++){
			if(j>=dzh[i])f[i][j]=max(f[i-1][j],f[i-1][j-dzh[i]]+v[i]);
			else f[i][j]=f[i-1][j];
		}
	}
	cout<<f[m][t]<<endl;
	return 0;
}