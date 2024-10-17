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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
struct Edge{int x,y;}E[N];
int n,m,tot,fa[N],id[N],pos[N],son[N],sum[N],dep[N],top[N];
struct Segment_Tree{
	int t[N*4];
	void Init(){memset(t,0x3f,sizeof(t));}
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p]=min(t[p],val);return;}
		int mid=(l+r)>>1;Update(x,y,val,lson);Update(x,y,val,rson);
	}
	int Query(int x,int p,int l,int r){
		if(l==r)return t[p];int mid=(l+r)>>1;
		return min(t[p],(x<=mid?Query(x,lson):Query(x,rson)));
	}
}tree;
void Update(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		tree.Update(id[top[x]],id[x],z,1,1,n);
		x=fa[top[x]];
	}
	if(id[x]>id[y])swap(x,y);
	if(x!=y)tree.Update(id[son[x]],id[y],z,1,1,n);
}
void DFS1(int x,int depth){
	sum[x]=1;dep[x]=depth;
	for(auto y:G[x]){
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(auto y:G[x])if(y!=fa[x]&&y!=son[x])DFS2(y,y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);E[i]=(Edge){x,y};}
	DFS1(1,1);DFS2(1,1);tree.Init();
	for(int i=1;i<=m;i++){int x=read(),y=read();Update(x,y,read());}
	for(int i=1;i<n;i++){int ans=tree.Query(max(id[E[i].x],id[E[i].y]),1,1,n);printf("%d\n",ans!=inf?ans:-1);}
	return 0;
}
