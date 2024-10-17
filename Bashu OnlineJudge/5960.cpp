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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
struct edge{int to,next;}d[N*2];
int h[N],fa[N],id[N],pos[N],dep[N],sum[N],son[N],top[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
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
struct Tree{int sum1,sum2;};
struct Segment_Tree{
	Tree t[N*4];
	void Update(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].sum1++;return;}
		int mid=(l+r)>>1;Update(x,y,lson);Update(x,y,rson);
	}
	void Insert(int x,int p,int l,int r){
		t[p].sum2++;
		if(l==r)return;int mid=(l+r)>>1;
		x<=mid?Insert(x,lson):Insert(x,rson);
	}
	int Query1(int x,int p,int l,int r){
		if(l==r)return t[p].sum1;
		int mid=(l+r)>>1;
		return (x<=mid?Query1(x,lson):Query1(x,rson))+t[p].sum1;
	}
	int Query2(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum2;
		int mid=(l+r)>>1;
		return Query2(x,y,lson)+Query2(x,y,rson);
	}
}tree;
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return id[x]<=id[y]?x:y;
}
int Query(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=tree.Query2(id[top[x]],id[x],1,1,n);
		x=fa[top[x]];
	}
	if(id[x]>id[y])swap(x,y);
	return ans+tree.Query2(id[x],id[y],1,1,n);
}
void Update(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		tree.Update(id[top[x]],id[x],1,1,n);
		x=fa[top[x]];
	}
	if(id[x]>id[y])swap(x,y);
	tree.Update(id[x],id[y],1,1,n);
}
int main(){
//	freopen("meet.in","r",stdin);
//	freopen("meet.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	DFS1(1,1);DFS2(1,1);
	m=read();
	while(m--){
		int x=read(),y=read(),z=LCA(x,y);
		printf("%d\n",tree.Query1(id[z],1,1,n)+Query(x,y)-tree.Query2(id[z],id[z],1,1,n));
		tree.Insert(id[z],1,1,n);Update(x,y);
	}
	return 0;
}