#include<iostream>
#include<iomanip>
#include<queue>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
char c;
long long read(){
	long long res=0,bj=1;
	while(c<'0'||c>'9'){if(c=='-') bj=-1; c=getchar();};
	while(c>='0'&&c<='9'){res=res*10+c-'0'; c=getchar();};
	return res*bj;
}
int n,m;
long long d[105][105],g[105][105];
long double num[105];
int main(){
	n=read(),m=read();
	memset(d,0x3f,sizeof(d));
	for(int i=1;i<=m;i++){
		int x,y;
		x=read(),y=read();
		d[x][y]=read();
		d[y][x]=d[x][y];
		g[x][y]=g[y][x]=1;
	}
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		if(i==j||i==k||j==k) continue;
		if(d[i][k]==0x3f3f3f3f||d[k][j]==0x3f3f3f3f) continue;
		if(d[i][k]+d[k][j]==d[i][j]) g[i][j]+=g[i][k]*g[k][j];
		if(d[i][k]+d[k][j]<d[i][j]) d[i][j]=d[i][k]+d[k][j],g[i][j]=g[i][k]*g[k][j];
	}
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		if(i==j||i==k||j==k) continue;
		if(d[i][k]+d[k][j]==d[i][j]){
			num[k]+=double(g[i][k]*g[k][j])/double(g[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%.3LF\n",num[i]);
	}
	return 0;
}