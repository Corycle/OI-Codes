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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,Root;
int h[N],a[N],L[N],R[N],fa[N],sum[N],son[N],pos[N],dep[N],top[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Tree{ll sum,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(ll x,int p,int l,int r){
		t[p].tag+=x;
		t[p].sum+=x*(r-l+1);
	}
	void Pushdown(int p,int l,int r){
		if(t[p].tag){
			int mid=(l+r)>>1;
			update(t[p].tag,lson);
			update(t[p].tag,rson);
			t[p].tag=0;
		}
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].sum=a[pos[l]];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	void Update(int x,int y,ll v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(v,p,l,r);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update(x,y,v,lson);Update(x,y,v,rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	ll Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree;
void DFS1(int x,int depth){
	sum[x]=1;dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[L[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
	R[x]=tot;
}
int LCA1(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int LCA2(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		if(y==fa[top[x]])return top[x];
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?son[x]:son[y];
}
int Dist(int x,int y,int z){return dep[x]+dep[y]-dep[z]*2;}
void Update(int x,int y,ll v){
	int z=LCA1(x,y),p1=LCA1(x,Root),p2=LCA1(y,Root);
	if(Dist(x,y,z)==Dist(x,Root,p1)+Dist(y,Root,p2)){tree.Update(1,n,v,1,1,n);return;}
	if(!(L[z]<=L[Root]&&R[Root]<=R[z])){tree.Update(L[z],R[z],v,1,1,n);return;}
	if(dep[p1]<dep[p2]){swap(x,y);swap(p1,p2);}
	tree.Update(1,n,v,1,1,n);
	int p=LCA2(Root,p1);
	tree.Update(L[p],R[p],-v,1,1,n);
}
ll Query(int x){
	if(x==Root)return tree.Query(1,n,1,1,n);
	if(!(L[x]<=L[Root]&&R[Root]<=R[x]))return tree.Query(L[x],R[x],1,1,n);
	int p=LCA2(x,Root);
	return tree.Query(1,n,1,1,n)-tree.Query(L[p],R[p],1,1,n);
}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	Root=1;
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	while(m--){
		int op=read();
		if(op==1)Root=read();
		if(op==2){
			int x=read(),y=read();
			Update(x,y,read());
		}
		if(op==3){
			int x=read();
			printf("%lld\n",Query(x));
		}
	}
	return 0;
}