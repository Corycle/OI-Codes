#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
long long a[105][105],f[105][105],b[105][105],n,m,i,j,k;
char dzh[105][105];
int main(){
	cin>>n>>m;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>dzh[i][j];
			a[i][j]=dzh[i][j]-'0';
		}
	}
	f[1][1]=a[1][1];
	for(i=1;i<=m;i++){
		b[1][i]=1;
		if(i>1)f[1][i]=f[1][i-1]+a[1][i];	
	}
	for(i=1;i<=n;i++){
		b[i][1]=1;
		if(i>1)f[i][1]=f[i-1][1]+a[i][1];
	}
	for(i=2;i<=n;i++){
		for(j=2;j<=m;j++){
			f[i][j]=max(f[i-1][j],f[i][j-1])+a[i][j];
			if(f[i-1][j]==f[i][j-1])b[i][j]=b[i-1][j]+b[i][j-1];
			else if(f[i-1][j]>f[i][j-1])b[i][j]=b[i-1][j];
			else b[i][j]=b[i][j-1];
		}
	}
	cout<<f[n][m]<<endl<<b[n][m];
	return 0;
}
