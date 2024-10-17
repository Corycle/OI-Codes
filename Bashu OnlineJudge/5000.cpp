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
const int N=30005;
const int M=15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
struct edge{int to,next,dist;}d[N*2];
int a[N],h[N],fa[N],dep[N],son[N],sum[N],top[N];ll dis[N];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
/*========Prepare========*/
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;dis[y]=dis[x]+d[i].dist;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
ll Dist(int x,int y){
	if(!x||!y)return 0;
	return dis[x]+dis[y]-dis[LCA(x,y)]*2;
}
/*========Tree Divide========*/
int Root,prt[N],vis[N],Max[N],pre[N];
ll f[N][M][2],g[N][M][2],num[N][M][2];
void Find(int x,int Fa,int Size){
	Max[x]=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa||vis[y])continue;
		Find(y,x,Size);
		sum[x]+=sum[y];
		Max[x]=max(Max[x],sum[y]);
	}
	Max[x]=max(Max[x],Size-sum[x]);
	if(!Root||Max[Root]>Max[x])Root=x;
}
void dfs1(int x,int Fa,int rt,ll dist){
	for(int i=0;i<M;i++){
		g[rt][i][(a[x]>>i)&1]+=dist;
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa||vis[y])continue;
		dfs1(y,x,rt,dist+d[i].dist);
	}
}
void dfs2(int x,int Fa,int rt,ll dist){
	sum[x]=1;
	for(int i=0;i<M;i++){
		num[rt][i][(a[x]>>i)&1]++;
		f[rt][i][(a[x]>>i)&1]+=dist;
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa||vis[y])continue;
		dfs2(y,x,rt,dist+d[i].dist);
		sum[x]+=sum[y];
	}
}
void Divide(int x,int Fa,int Size){
	Root=0;Find(x,0,Size);
	int dist=Dist(x,Fa);
	dfs1(x,0,Root,dist);
	dfs2(Root,0,Root,0);
	x=Root;
	pre[x]=Dist(x,Fa);
	prt[x]=Fa;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Divide(y,x,sum[y]);
	}
}
/*========Solve========*/
ll Ans;
ll Query(int x){
	int p=x;ll ans=0;
	for(int i=0;i<M;i++)ans+=f[x][i][((a[x]>>i)&1)^1]*(1<<i);
	while(prt[x]){
		int dlt=Dist(p,prt[x]);
		for(int i=0;i<M;i++){
			int tmp=((a[p]>>i)&1)^1;
			ans+=(f[prt[x]][i][tmp]-g[x][i][tmp]+dlt*(num[prt[x]][i][tmp]-num[x][i][tmp]))*(1<<i);
		}
		x=prt[x];
	}
	return ans;
}
void Change(int x,int data){
	int p=x;
	for(int i=0;i<M;i++){
		num[x][i][(a[x]>>i)&1]--;g[x][i][(a[x]>>i)&1]-=pre[x];
		num[x][i][(data>>i)&1]++;g[x][i][(data>>i)&1]+=pre[x];
	}
	while(prt[x]){
		int dis1=Dist(p,prt[x]),dis2=Dist(p,prt[prt[x]]);
		for(int i=0;i<M;i++){
			num[prt[x]][i][(a[p]>>i)&1]--;f[prt[x]][i][(a[p]>>i)&1]-=dis1;g[prt[x]][i][(a[p]>>i)&1]-=dis2;
			num[prt[x]][i][(data>>i)&1]++;f[prt[x]][i][(data>>i)&1]+=dis1;g[prt[x]][i][(data>>i)&1]+=dis2;
		}
		x=prt[x];
	}
	a[p]=data;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS1(1,1);DFS2(1,1);Divide(1,0,n);
	for(int i=1;i<=n;i++)Ans+=Query(i);
	m=read();
	while(m--){
		int x=read(),y=read();
		Ans-=Query(x)*2;
		Change(x,y);
		Ans+=Query(x)*2;
		printf("%lld\n",Ans/2);
	}
	return 0;
}