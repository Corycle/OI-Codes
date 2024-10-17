#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,m,a[355],b[5],f[50][50][50][50],i,j,k,l,maxx;
int main(){
	cin>>n>>m;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<=m;i++){cin>>j;b[j]++;}
	for(i=0;i<=b[1];i++){
		for(j=0;j<=b[2];j++){
			for(k=0;k<=b[3];k++){
				for(l=0;l<=b[4];l++){
					maxx=0;
					if(i)maxx=max(maxx,f[i-1][j][k][l]);
					if(j)maxx=max(maxx,f[i][j-1][k][l]);
					if(k)maxx=max(maxx,f[i][j][k-1][l]);
					if(l)maxx=max(maxx,f[i][j][k][l-1]);
					f[i][j][k][l]=maxx+a[1+i+j*2+k*3+l*4];
				}
			}
		}
	}
	cout<<f[b[1]][b[2]][b[3]][b[4]];
	return 0;
}
