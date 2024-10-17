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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int Lim=1e6;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N];
int n,m,tot;
int fa[N],id[N],pos[N],sum[N],son[N],dep[N],top[N],Root[N];
vector<int>G[N];
struct Node{
	ll k,b,l,r;
	ll F(ll x){return k*x+b;}
}P[N];
struct Tree{int l,r,id;};
struct LC_Segment_Tree{
	int tot;
	Tree t[N*400];
	void Insert(int x,int y,int id,int &p,int l,int r){
		int mid=(l+r)>>1;
		tot++;t[tot]=t[p];p=tot;
		if(x<=l&&r<=y){
			if(P[t[p].id].F(mid)<P[id].F(mid))swap(id,t[p].id);
			if(P[t[p].id].F(l)<P[id].F(l))Insert(x,y,id,t[p].l,l,mid);
			if(P[t[p].id].F(r)<P[id].F(r))Insert(x,y,id,t[p].r,mid+1,r);
			return;
		}
		if(x<=mid)Insert(x,y,id,t[p].l,l,mid);
		if(y>mid)Insert(x,y,id,t[p].r,mid+1,r);
	}
	ll Query(int x,int p,int l,int r){
		if(x<l||x>r||!p)return 0;
		if(l==r)return P[t[p].id].F(x);
		int mid=(l+r)>>1;
		return max(P[t[p].id].F(x),max(Query(x,t[p].l,l,mid),Query(x,t[p].r,mid+1,r)));
	}
}lc_sgt;
struct Segment_Tree{
	vector<pii>F[N*4];
	void Insert(int x,int y,int X,int id,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){F[p].push_back(mp(X,id));return;}
		int mid=(l+r)>>1;
		Insert(x,y,X,id,lson);Insert(x,y,X,id,rson);
	}
	void Solve(int p,int l,int r){
		if(!F[p].empty()){
			int Root=0;lc_sgt.tot=0;
			for(int i=l;i<=r;i++)lc_sgt.Insert(P[pos[i]].l,P[pos[i]].r,pos[i],Root,0,Lim);
			for(auto tmp:F[p])Ans[tmp.scd]=max(Ans[tmp.scd],lc_sgt.Query(tmp.fst,Root,0,Lim));
		}
		if(l==r)return;
		int mid=(l+r)>>1;
		Solve(lson);Solve(rson);
	}
}tree;
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(auto y:G[x]){
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	Root[x]=(x==top[x]?0:Root[fa[x]]);
	lc_sgt.Insert(P[x].l,P[x].r,x,Root[x],0,Lim);
	if(son[x])DFS2(son[x],tp);
	for(auto y:G[x])if(y!=fa[x]&&y!=son[x])DFS2(y,y);
}
void Update(int x,int y,int X,int i){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Ans[i]=max(Ans[i],lc_sgt.Query(X,Root[x],0,Lim));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	tree.Insert(id[x],id[y],X,i,1,1,n);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		P[i].k=read();P[i].b=read();
		P[i].l=read();P[i].r=read();
	}
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),X=read();
		Update(x,y,X,i);
	}
	tree.Solve(1,1,n);
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}