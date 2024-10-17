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
const int M=400005;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,cnt;
int prt[N],dep[N],flag[M];
int h[N],fa[N],sum[N],vis[N];
struct edge{int to,next;}d[M];
struct Edge{int s,t;}e[M];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void DFS(int x,int depth){
	dep[x]=depth;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		prt[y]=x;DFS(y,depth+1);
	}
}
int Union(int x,int y){
	x=Find(x);y=Find(y);
	if(x==y)return x;
	if(dep[x]<dep[y])swap(x,y);
	fa[x]=Union(prt[x],y);
	sum[fa[x]]+=sum[x];
	return fa[x];
}
int main(){
//	freopen("alliance.in","r",stdin);
//	freopen("alliance.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)sum[i]=1;
	for(int i=1;i<=m+p;i++){
		int x=Find(e[i].s=read());
		int y=Find(e[i].t=read());
		if(x!=y){
			fa[x]=y;flag[i]=1;
			Add(e[i].s,e[i].t);
			Add(e[i].t,e[i].s);
		}
	}
	for(int i=1;i<=n;i++)if(!vis[i])DFS(i,1);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		if(!flag[i])Union(e[i].s,e[i].t);
	}
	for(int i=m+1;i<=m+p;i++){
		if(flag[i]){
			printf("No\n");
			continue;
		}
		Union(e[i].s,e[i].t);
		printf("%d\n",sum[Find(e[i].s)]);
	}
	return 0;
}