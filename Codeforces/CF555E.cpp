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
#include<unordered_map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
unordered_map<int,int>E[N];
int n,m,Q,tot,scc,Num,cnt=1;
int h[N],b[N],fa[N],id[N],vis[N*2],Tim[N];
int dfn[N],low[N],dep[N],sum[N],son[N],top[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;Tim[x]=Num;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x])vis[i]=vis[i^1]=1;
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
void dfs(int x){
	b[x]=scc;
	for(int i=h[x];i;i=d[i].next){
		if(!vis[i]&&!b[d[i].to])dfs(d[i].to);
	}
}
struct Tree{int vis[2],tag[2];};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int c){t[p].vis[c]=t[p].tag[c]=1;}
	void Pushdown(int p){
		if(t[p].tag[0]){update(p<<1,0);update(p<<1|1,0);t[p].tag[0]=0;}
		if(t[p].tag[1]){update(p<<1,1);update(p<<1|1,1);t[p].tag[1]=0;}
	}
	void Update(int x,int y,int c,int p,int l,int r){
		if(y<l||x>r)return;t[p].vis[c]=1;
		if(x<=l&&r<=y){update(p,c);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,c,lson);Update(x,y,c,rson);
	}
	int Query(int x,int y,int c,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].vis[c];
		int mid=(l+r)>>1;Pushdown(p);
		return Query(x,y,c,lson)|Query(x,y,c,rson);
	}
}tree;
void DFS1(int x,int depth){
	sum[x]=1;dep[x]=depth;
	for(auto y:G[x]){
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;id[x]=++tot;if(son[x])DFS2(son[x],tp);
	for(auto y:G[x])if(y!=fa[x]&&y!=son[x])DFS2(y,y);
}
int LCA(int x,int y){
	while(top[x]!=top[y]){if(dep[top[x]]<dep[top[y]])swap(x,y);x=fa[top[x]];}
	return dep[x]<dep[y]?x:y;
}
void Cover(int x,int y,int c){
	if(x==y)return;
	while(top[x]!=top[y]){
		tree.Update(id[top[x]],id[x],c,1,1,scc);
		if(tree.Query(id[top[x]],id[x],c^1,1,1,scc)){puts("No");exit(0);}
		x=fa[top[x]];
	}
	if(x!=y){
		tree.Update(id[son[y]],id[x],c,1,1,scc);
		if(tree.Query(id[son[y]],id[x],c^1,1,1,scc)){puts("No");exit(0);}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	int fst=0;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		if(!fst)fst=x;
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=n;i++){Num++;if(!dfn[i])Tarjan(i,0);}
	for(int i=1;i<=n;i++)if(!b[i]){scc++;dfs(i);}
	for(int x=1;x<=n;x++){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(b[x]!=b[y]&&!E[b[x]][b[y]]){
				E[b[x]][b[y]]=1;
				G[b[x]].push_back(b[y]);
			}
		}
	}
	tot=0;
	for(int i=1;i<=scc;i++){
		if(!id[i]){DFS1(i,1);DFS2(i,i);}
	}
	while(Q--){
		int x=read(),y=read();
		if(Tim[x]!=Tim[y]){puts("No");return 0;}
		x=b[x];y=b[y];int z=LCA(x,y);
		Cover(x,z,0);Cover(y,z,1);
	}
	puts("Yes");
	return 0;
}
