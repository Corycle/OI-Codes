#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,root;
int h[N],fa[N],val[N],sum[N];
int id[N],dep[N],son[N],top[N],pos[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Segment_Tree{
	struct Tree{int Min;}t[N*4];
	void Pushup(int p){
		t[p].Min=min(t[p<<1].Min,t[p<<1|1].Min);
	}
	void Build(int p,int l,int r){
		if(l==r){
			t[p].Min=val[pos[l]];
			return;
		}
		int mid=(l+r)>>1;
		Build(lson);
		Build(rson);
		Pushup(p);
	}
	void Change(int x,int y,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){
			t[p].Min=y;
			return;
		}
		int mid=(l+r)>>1;
		Change(x,y,lson);
		Change(x,y,rson);
		Pushup(p);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||r<x)return inf;
		if(x<=l&&r<=y)return t[p].Min;
		int mid=(l+r)>>1;
		return min(Ask(x,y,lson),Ask(x,y,rson));
	}
}tree;
void DFS1(int x,int depth){
	sum[x]=1;dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
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
		if(y==son[x])continue;
		DFS2(y,y);
	}
}
int lca(int x,int y){//return LCA(x,y)'s son
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		if(fa[top[x]]==y)return top[x];
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return son[x];
}
int Ask(int x){
	int fx=lca(x,root);
	int fy=fa[fx];
	if(root==x)return tree.Ask(1,sum[1],1,1,n);
	if(fy!=x)return tree.Ask(id[x],id[x]+sum[x]-1,1,1,n);
	if(fy==x){
		int ans=inf;
		ans=min(ans,tree.Ask(1,id[fx]-1,1,1,n));
		ans=min(ans,tree.Ask(id[fx]+sum[fx],n,1,1,n));
		return ans;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		fa[i]=read();
		val[i]=read();
		Add(fa[i],i);
	}
	root=1;
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	while(m--){
		char s[5];
		scanf("%s",s+1);
		if(s[1]=='E')root=read();
		if(s[1]=='V'){
			int x=read(),y=read();
			tree.Change(id[x],y,1,1,n);
			val[x]=y;
		}
		if(s[1]=='Q'){
			int x=read();
			printf("%d\n",Ask(x));
		}
	}
	return 0;
}
/*
8 100
0 3
1 4
1 2
3 2
1 3
2 4
5 1
5 6
*/