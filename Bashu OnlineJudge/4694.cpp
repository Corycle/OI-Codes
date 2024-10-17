/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
const int M=22;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,D,cnt;
int a[N],b[N],h[N],f[N][M],g[N][M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x,int fa){
	f[x][0]=g[x][0]=a[x]*b[x];
	for(int i=1;i<=D;i++)f[x][i]=a[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		for(int j=D;j>=0;j--)f[x][j]=min(f[x][j]+f[y][j+1],min(f[x][j]+g[y][j],g[x][j+1]+f[y][j+1]));
		for(int j=D;j>=0;j--)f[x][j]=min(f[x][j],f[x][j+1]);
		g[x][0]=f[x][0];
		for(int j=1;j<=D;j++)g[x][j]=g[x][j]+g[y][j-1];
		for(int j=1;j<=D;j++)g[x][j]=min(g[x][j],g[x][j-1]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();D=read();
	for(int i=1;i<=n;i++)a[i]=read();
	m=read();
	for(int i=1;i<=m;i++)b[read()]=1;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	memset(f,0x3f,sizeof(f));
	DFS(1,0);
	int Ans=inf;
	for(int i=0;i<=D;i++)Ans=min(Ans,f[1][i]);
	printf("%d",Ans);
	return 0;
}