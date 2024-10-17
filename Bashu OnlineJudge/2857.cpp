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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int h[N],fa[N],prt[N],son[N],top[N];
int id[N],sum[N],dep[N],dis[N],pos[N];
struct edge{int to,next,dist;}d[N*20];
struct Edge{int s,t,dist;}e[N*20];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
bool cmp(Edge x,Edge y){
	return x.dist<y.dist;
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Kruskal(){
	int num=0;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=e[i].s,y=e[i].t;
		int fx=Find(x),fy=Find(y);
		if(fx==fy)continue;
		fa[fx]=fy;num++;
		Add(x,y,e[i].dist);
		Add(y,x,e[i].dist);
		if(num==n-1)break;
	}
}
void DFS1(int x,int depth){
	sum[x]=1;dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==prt[x])continue;
		prt[y]=x;dis[y]=d[i].dist;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;
	pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==son[x]||y==prt[x])continue;
		DFS2(y,y);
	}
}
struct Segment_Tree{
	struct Tree{int Max;}t[N*4];
	void Pushup(int p){
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
	void Build(int p,int l,int r){
		if(l==r){
			t[p].Max=dis[pos[l]];
			return;
		}
		int mid=(l+r)>>1;
		Build(lson);
		Build(rson);
		Pushup(p);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].Max;
		int mid=(l+r)>>1;
		return max(Ask(x,y,lson),Ask(x,y,rson));
	}
}tree;
int Ask(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=max(ans,tree.Ask(id[top[x]],id[x],1,1,n));
		x=prt[top[x]];//并查集的父亲和树的父亲弄错搞自闭了！！！ 
	}
	if(x==y)return ans;
	if(dep[x]>dep[y])swap(x,y);
	ans=max(ans,tree.Ask(id[son[x]],id[y],1,1,n));
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].dist=read();
	}
	Kruskal();
	DFS1(1,1);
	DFS2(1,1);
	tree.Build(1,1,n);
	int T=read();
	while(T--){
		int x=read(),y=read();
		printf("%d\n",Ask(x,y));
	}
	return 0;
}