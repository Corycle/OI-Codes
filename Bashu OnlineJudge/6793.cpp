#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=30005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,k,cnt,root;
int fa[N],h[N],tp[N],sum[N];
int dep[N],son[N],prt[N],val[N];
struct edge{int to,next;}d[N];
struct Edge{int s,t,data;}e[N];
bool cmp(Edge x,Edge y){return x.data<y.data;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Kruskal(){
	int num=n,tot=n*2;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=tot;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		fa[x]=fa[y]=++num;
		val[num]=e[i].data;
		Add(num,x);Add(num,y);
		if(num==tot-1)break;
	}
}
void DFS1(int x,int depth){
	dep[x]=depth;
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		DFS1(y,depth+1);
		prt[y]=x;sum[x]+=sum[y];
		if(!son[x]||sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int top){
	tp[x]=top;
	if(son[x])DFS2(son[x],top);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==prt[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
int lca(int x,int y){
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]<dep[tp[y]])swap(x,y);
		x=prt[tp[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].data=read();
	}
	Kruskal();
	root=n+n-1;
	DFS1(root,1);
	DFS2(root,root);
	while(k--){
		int x=read(),y=read();
		int z=lca(x,y);
		printf("%d\n",val[z]);
	}
	return 0;
}