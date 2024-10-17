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
const int Inv2=5e8+5;
const int Mod=1e9+9;
const int M=30005;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,cnt,Ans;
int h[N],rd[N],dis[N],vis[N],deg[N],a[N][N],f[N],g[N][N];
struct edge{int to,next;}d[M];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int mod(int x){return x>=Mod?x-Mod:x;}
void Dijkstra(){
	for(int i=1;i<=n;i++)dis[i]=inf;dis[S]=0;
	for(int i=1;i<=n;i++){
		int k=0,Min=inf;
		for(int j=1;j<=n;j++)if(!vis[j]&&dis[j]<Min){k=j;Min=dis[j];}
		if(!k)break;vis[k]=1;
		for(int j=1;j<=n;j++)if(a[k][j]!=inf)dis[j]=min(dis[j],dis[k]+a[k][j]);
	}
	if(dis[T]==inf){puts("0");exit(0);}
}
void Build(){
	for(int x=1;x<=n;x++){
		for(int y=1;y<=n;y++){
			if(x==y)continue;
			if(dis[y]==dis[x]+a[x][y]){Add(x,y);deg[y]++;}
		}
	}
	for(int i=1;i<=n;i++)rd[i]=deg[i];
}
void Calc(int sx){
	queue<int>q;
	for(int i=1;i<=n;i++)deg[i]=rd[i];
	for(int i=1;i<=n;i++)if(!deg[i])q.push(i);g[sx][sx]=1;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(!(--deg[y]))q.push(y);
			g[sx][y]=mod(g[sx][y]+g[sx][x]);
		}
	}
}
int Sqr(int x){return 1ll*x*x%Mod;}
void Solve(){
	queue<int>q;
	for(int i=1;i<=n;i++)deg[i]=rd[i];
	for(int i=1;i<=n;i++)if(!deg[i])q.push(S);
	while(q.size()){
		int x=q.front();q.pop();f[x]=Sqr(g[S][x]);
		for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(!(--deg[y]))q.push(y);}
		for(int y=1;y<=n;y++){if(y==S||y==x)continue;f[x]=mod(f[x]-1ll*f[y]*Sqr(g[y][x])%Mod+Mod);}
	}
}
int main(){
//	freopen("path.in","r",stdin);
//	freopen("path.out","w",stdout);
	n=read();m=read();S=read();T=read();memset(a,0x3f,sizeof(a));
	for(int i=1;i<=m;i++){int x=read(),y=read();a[x][y]=min(a[x][y],read());}
	Dijkstra();Build();for(int i=1;i<=n;i++)Calc(i);Solve();
	if(dis[T]==a[S][T])printf("%d\n",mod(1ll*mod(f[T]-1)*Inv2%Mod+1));
	else printf("%lld\n",1ll*f[T]*Inv2%Mod);
	return 0;
}