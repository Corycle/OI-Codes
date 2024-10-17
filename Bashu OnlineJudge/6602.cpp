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
char s[10];
vector<int>G[N];
int n,m,Q,tot,num,scc,cnt=1;
int a[N],h[N],st[N],fa[N],id[N],pos[N];
int sum[N],dep[N],son[N],dfn[N],low[N],top[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Heap{
	priority_queue<int,vector<int>,greater<int> >q1,q2;
	void Insert(int x){q1.push(x);}
	void Delete(int x){q2.push(x);}
	int Top(){
		while(!q1.empty()&&!q2.empty()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return (q1.empty()?0:q1.top());
	}
}F[N];
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;st[++num]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				int k=0;scc++;
				fa[scc]=x;a[scc]=inf;
				G[x].push_back(scc);
				do{
					k=st[num--];fa[k]=scc;
					G[scc].push_back(k);
					F[scc].Insert(a[k]);
					a[scc]=min(a[scc],a[k]);
				}while(k!=y);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
struct Segment_Tree{
	int t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p]=a[pos[l]];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=min(t[p<<1],t[p<<1|1]);
	}
	void Change(int x,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p]=a[pos[l]];return;}
		int mid=(l+r)>>1;
		Change(x,lson);Change(x,rson);
		t[p]=min(t[p<<1],t[p<<1|1]);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return inf;
		if(x<=l&&r<=y)return t[p];
		int mid=(l+r)>>1;
		return min(Query(x,y,lson),Query(x,y,rson));
	}
}tree;
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(auto y:G[x]){
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(auto y:G[x]){
		if(y!=son[x])DFS2(y,y);
	}
}
void Change(int x,int y){
	if(fa[x]>n){
		F[fa[x]].Delete(a[x]);
		a[x]=y;
		F[fa[x]].Insert(a[x]);
		a[fa[x]]=F[fa[x]].Top();
		tree.Change(id[fa[x]],1,1,scc);
	}
	a[x]=y;
	tree.Change(id[x],1,1,scc);
}
int Query(int x,int y){
	int ans=inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=min(ans,tree.Query(id[top[x]],id[x],1,1,scc));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans=min(ans,tree.Query(id[x],id[y],1,1,scc));
	if(x>n)ans=min(ans,a[fa[x]]);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();scc=n;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	Tarjan(1,0);tot=0;
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,scc);
	while(Q--){
		scanf("%s",s);
		int x=read(),y=read();
		if(s[0]=='C')Change(x,y);
		if(s[0]=='A')printf("%d\n",Query(x,y));
	}
	return 0;
}