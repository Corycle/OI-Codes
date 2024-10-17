#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
using namespace std;
int x,y,z,p;
int f[1005][105],n,m,i,j,k,l=1; 
int main(){
	cin>>m>>n;n--;
	while(cin>>x>>y>>z>>p){
		if(n%z!=0)continue;
		x+=n/z;
		f[x][y]+=p;
		l=max(l,x);
	}
	for(i=l-1;i>=0;i--){
		for(j=1;j<=m;j++){
			x=0;
			for(y=j-2;y<=j+2;y++)
				x=max(f[i+1][y],x);
			f[i][j]+=x;
		}
	}
	cout<<f[0][m/2+1];
	return 0;
}
