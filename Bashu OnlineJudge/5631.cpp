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
const int Mod=201314;
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int h[N],fa[N],id[N],pos[N],dep[N],sum[N],son[N],top[N],Ans[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y!=son[x])DFS2(y,y);
	}
}
struct Tree{int sum,val,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int x){
		t[p].tag=mod(t[p].tag+x);
		t[p].sum=mod(t[p].sum+1ll*t[p].val*x%Mod);
	}
	void Pushdown(int p){
		if(t[p].tag){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=0;
		}
	}
	void Build(int p,int l,int r){
		t[p].val=r-l+1;
		if(l==r)return;
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
	}
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,val,lson);Update(x,y,val,rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p);
		return mod(Query(x,y,lson)+Query(x,y,rson));
	}
}tree;
void Update(int x){
	while(x){
		tree.Update(id[top[x]],id[x],1,1,1,n);
		x=fa[top[x]];
	}
}
int Query(int x){
	int ans=0;
	while(x){
		ans=mod(ans+tree.Query(id[top[x]],id[x],1,1,n));
		x=fa[top[x]];
	}
	return ans;
}
struct Node{int x,id,f;};
vector<Node>Q[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=2;i<=n;i++){
		fa[i]=read()+1;
		Add(fa[i],i);
	}
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	for(int i=1;i<=m;i++){
		int l=read()+1,r=read()+1,x=read()+1;
		Q[r].push_back((Node){x,i,1});
		Q[l-1].push_back((Node){x,i,-1});
	}
	for(int i=0;i<=n;i++){
		Update(i);
		for(auto t:Q[i])Ans[t.id]+=Query(t.x)*t.f;
	}
	for(int i=1;i<=m;i++)printf("%d\n",(Ans[i]%Mod+Mod)%Mod);
	return 0;
}