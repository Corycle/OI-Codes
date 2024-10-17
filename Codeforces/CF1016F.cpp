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
const ll INF=1e18;
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,flag;
ll dis[N],Max[N],f1,f2,Ans;
int h[N],fa[N],num[N],vis[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void DFS(int x,ll dist){
	dis[x]=dist;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,dist+d[i].dist);
	}
}
void dfs(int x,ll dist){
	Max[x]=dist;vis[x]=1;num[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		dfs(y,dist+d[i].dist);
		num[x]+=num[y];
		Max[x]=max(Max[x],Max[y]);
	}
	if(num[x]>=3)flag=1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){int x=read(),y=read(),z=read();Add(x,y,z);Add(y,x,z);}
	DFS(1,0);
	ll Sum=dis[n],Min=INF,tmp=-INF,lst=-INF;Ans=-INF;
	for(int x=n;fa[fa[x]];x=fa[x])Min=min(Min,dis[x]-dis[fa[fa[x]]]);
	for(int x=n;x;x=fa[x])vis[x]=1;
	for(int x=n,y=0;x;y=x,x=fa[x]){
		dfs(x,0);
		if(Max[x]||Max[y])tmp=max(tmp,lst);
		Ans=max(Ans,Max[x]+dis[x]+tmp);
		tmp=max(tmp,lst);lst=Max[x]-dis[x];
	}
	while(m--){
		int dist=read();ll Answer=-INF;
		if(dist>=Min||flag)Answer=max(Answer,Sum);
		else Answer=max(Answer,Sum+min(0ll,Ans+dist));
		printf("%lld\n",Answer);
	}
	return 0;
}
/*
8 1
2 1 5
8 7 13
2 6 3
3 8 14
4 5 6
4 3 4
5 6 4
2
*/
