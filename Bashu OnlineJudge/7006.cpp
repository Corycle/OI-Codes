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
const ll INF=1e18;
const int inf=0x3f3f3f3f;
const int M=5e4+5;
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	G0: 1 => x    G1: n => x
	G2: x => 1    G3: x => n
*/
ll Ans;
int n,m;
struct Node{int x,y,c,d;}E[M];
struct edge{int to,next,dist;};
struct Graph{
	edge d[M];
	ll dis[N],Dis[N];
	int s,cnt,h[N],vis[N],vst[M],pre[N];
	void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
	void Dijkstra(){
		for(int i=1;i<=n;i++){dis[i]=INF;vis[i]=0;}
		dis[s]=0;
		for(int k=1;k<=n;k++){
			int x=0,Min=inf;
			for(int j=1;j<=n;j++)if(!vis[j]&&dis[j]<Min){Min=dis[j];x=j;}
			if(!x)break;vis[x]=1;
			for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(dis[y]>dis[x]+d[i].dist){dis[y]=dis[x]+d[i].dist;pre[y]=i;}}
		}
		for(int i=1;i<=n;i++)vst[pre[i]]=1;
	}
	void Reverse(int id){
		for(int i=1;i<=n;i++){Dis[i]=INF;vis[i]=0;}
		Dis[s]=0;
		for(int k=1;k<=n;k++){
			int x=0,Min=inf;
			for(int j=1;j<=n;j++)if(!vis[j]&&Dis[j]<Min){Min=Dis[j];x=j;}
			if(!x)break;vis[x]=1;
			for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(Dis[y]>Dis[x]+d[i].dist&&i!=id)Dis[y]=Dis[x]+d[i].dist;}
		}
	}
	ll Solve(int x,int id){
		if(!vst[id])return dis[x];
		Reverse(id);return Dis[x];
	}
}G[4];
ll GetAns1(int i){
	if(!G[0].vst[i])return min(G[0].dis[n],G[0].dis[E[i].y]+E[i].c+G[3].Solve(E[i].x,i));
	G[0].Reverse(i);return min(G[0].Dis[n],G[0].Dis[E[i].y]+E[i].c+G[3].Solve(E[i].x,i));
}
ll GetAns2(int i){
	if(!G[1].vst[i])return min(G[1].dis[1],G[1].dis[E[i].y]+E[i].c+G[2].Solve(E[i].x,i));
	G[1].Reverse(i);return min(G[1].Dis[1],G[1].Dis[E[i].y]+E[i].c+G[2].Solve(E[i].x,i));
}
int main(){
//	freopen("bus.in","r",stdin);
//	freopen("bus.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		E[i].x=read();E[i].y=read();E[i].c=read();E[i].d=read();
		G[0].Add(E[i].x,E[i].y,E[i].c);G[1].Add(E[i].x,E[i].y,E[i].c);
		G[2].Add(E[i].y,E[i].x,E[i].c);G[3].Add(E[i].y,E[i].x,E[i].c);
	}
	G[0].s=G[2].s=1;G[1].s=G[3].s=n;
	for(int i=0;i<4;i++)G[i].Dijkstra();Ans=G[0].dis[n]+G[1].dis[1];
	for(int i=1;i<=m;i++)Ans=min(Ans,GetAns1(i)+GetAns2(i)+E[i].d);
	printf("%lld\n",Ans>=INF?-1:Ans);
	return 0;
}