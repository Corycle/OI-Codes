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
#include<set>
#define ll long long
#define set_it set<Node>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,cnt,tot;
struct node{int x,y;}F[N];
struct edge{int to,next;}d[N*2];
int a[N],id[N],Sum[N],pos[N],Ans[N];
int h[N],fa[N],sum[N],son[N],dep[N],top[N];
struct Node{
	int l,r,id;
	friend bool operator<(Node A,Node B){
		return A.r<B.r;
	}
}P[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
/*========Prepare========*/
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
/*========Solve========*/
set<Node>S;
Node tmp[N];
vector<Node>V;
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=m;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	int Query(int l,int r){return Ask(r)-Ask(l-1);}
}tree;
void Insert(int l,int r,int p){
	int num=0;V.clear();
	set_it L=S.lower_bound((Node){l,l,0});
	set_it R=S.lower_bound((Node){r,r,0});
	for(set_it t=L;t!=S.end();t++){
		Node x=(*t);
		if(x.l>r)break;
		V.push_back(x);
		tree.Add(x.id,-(Sum[x.r]-Sum[x.l-1]));
		if(x.l<l)tmp[++num]=(Node){x.l,l-1,x.id};
		if(x.r>r)tmp[++num]=(Node){r+1,x.r,x.id};
		if(t==R)break;
	}
	for(auto x:V)S.erase(x);
	S.insert((Node){l,r,p});
	tree.Add(p,Sum[r]-Sum[l-1]);
	for(int i=1;i<=num;i++){
		S.insert(tmp[i]);
		tree.Add(tmp[i].id,Sum[tmp[i].r]-Sum[tmp[i].l-1]);
	}
}
void Update(int p){
	int x=F[p].x,y=F[p].y;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Insert(id[top[x]],id[x],p);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	Insert(id[x],id[y],p);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=n;i++)a[i]=1;
	for(int i=1;i<n;i++)a[n+i]=-1;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,n+i);Add(n+i,x);
		Add(y,n+i);Add(n+i,y);
	}
	for(int i=1;i<=m;i++){F[i].x=read();F[i].y=read();}
	for(int i=1;i<=Q;i++){P[i].l=read();P[i].r=read();P[i].id=i;}
	n=2*n-1;DFS1(1,1);DFS2(1,1);sort(P+1,P+Q+1);
	for(int i=1;i<=n;i++)Sum[i]=Sum[i-1]+a[pos[i]];
	for(int i=1,p=1;i<=Q;i++){
		while(p<=P[i].r)Update(p++);
		Ans[P[i].id]=tree.Query(P[i].l,P[i].r);
	}
	for(int i=1;i<=Q;i++)printf("%d\n",Ans[i]);
	return 0;
}