/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
#define tree Segment_Tree
using namespace std;
const int inf=0x3f3f3f3f;
const int Lim=1000000000;
const int M=1000005;
const int N=100005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,cnt,tot,Answer,sav[N];
int h[N],id[N],pre[N],pos[N],dep[N],vis[M];
int F[N],fa[N],top[N],sum[N],son[N],Ans[M];
struct Edge{int s,t,id,dist;}e[M];
struct edge{int to,next,dist,id;}d[N*2];
bool cmp(Edge A,Edge B){return A.dist<B.dist;}
int Find(int x){return x==F[x]?x:F[x]=Find(F[x]);}
void Add(int x,int y,int z,int id){
	d[++cnt]=(edge){y,h[x],z,id};h[x]=cnt;
}
void Kruskal(){
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++)F[i]=i;
	for(int i=1;i<=m;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		F[Find(x)]=Find(y);vis[i]=1;
		Add(e[i].s,e[i].t,e[i].dist,e[i].id);
		Add(e[i].t,e[i].s,e[i].dist,e[i].id);
	}
}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;pre[y]=i;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
namespace Segment_Tree{
	struct Tree{int Min,Max;}t[N*4];
	void Build(int p,int l,int r){
		t[p].Min=Lim;
		if(l==r){t[p].Max=d[pre[pos[l]]].dist;return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].Min=min(t[p].Min,z);return;}
		int mid=(l+r)>>1;Update(x,y,z,lson);Update(x,y,z,rson);
	}
	void Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Answer=max(Answer,t[p].Max);return;}
		int mid=(l+r)>>1;Ask(x,y,lson);Ask(x,y,rson);
	}
	void Solve(int Min,int p,int l,int r){
		if(l==r){Ans[d[pre[pos[l]]].id]=min(Min,t[p].Min);return;}
		int mid=(l+r)>>1;Min=min(Min,t[p].Min);
		Solve(Min,lson);Solve(Min,rson);
	}
};
void Query(int x,int y){
	Answer=-inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		if(sav[x]=-1)tree::Ask(id[top[x]],id[x],1,1,n);
		else Answer=max(Answer,sav[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	if(x!=y)tree::Ask(id[son[x]],id[y],1,1,n);
}
void Update(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		tree::Update(id[top[x]],id[x],z,1,1,n);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	if(x!=y)tree::Update(id[son[x]],id[y],z,1,1,n);
}
int main(){
//	freopen("easy.in","r",stdin);
//	freopen("easy.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].id=i;
		e[i].s=read();
		e[i].t=read();
		e[i].dist=read();
	}
	Kruskal();
	DFS1(1,1);DFS2(1,1);
	tree::Build(1,1,n);
	for(int i=1;i<=n;i++)sav[i]=-1;
	for(int i=1;i<=m;i++){
		if(vis[i])continue;
		Query(e[i].s,e[i].t);
		Ans[e[i].id]=Answer;
		Update(e[i].s,e[i].t,e[i].dist);
	}
	tree::Solve(Lim,1,1,n);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}