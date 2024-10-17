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
const int N=500005;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int h[N],fa[N],dep[N];
int top[N],sum[N],son[N];
struct edge{int to,next;}d[N*2];
inline void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
	d[++cnt]=(edge){x,h[y]};h[y]=cnt;
}
inline void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(register int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		sum[x]+=sum[y];DFS1(y,depth+1);
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
inline void DFS2(int x,int tp){
	top[x]=tp;
	if(son[x])DFS2(son[x],tp);
	for(register int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
struct Segment_Tree{
	struct Tree{int ans;}t[N*4];
	inline void Pushup(int p){
		t[p].ans=lca(t[p<<1].ans,t[p<<1|1].ans);
	}
	inline void Build(int p,int l,int r){
		if(l==r){t[p].ans=l;return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		Pushup(p);
	}
	inline int Ask(int x,int y,int p,int l,int r){
		if(x<=l&&r<=y)return t[p].ans;
		int mid=(l+r)>>1;
		if(y<=mid)return Ask(x,y,lson);
		else if(x>mid)return Ask(x,y,rson);
		else return lca(Ask(x,y,lson),Ask(x,y,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(register int i=2;i<=n;i++){
		int x=read(),y=read();Add(x,y);
	}
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	m=read();
	while(m--){
		int x=read(),y=read();
		printf("%d\n",tree.Ask(x,y,1,1,n));
	}
	return 0;
}