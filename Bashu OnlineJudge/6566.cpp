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
const int N=(1<<20)+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,tot;
int h[N],fa[N],id[N],pos[N],dep[N],sum[N],son[N],top[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
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
struct Tree{ll sum,val,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int x){
		t[p].tag+=x;
		t[p].sum+=t[p].val*x;
	}
	void Pushdown(int p){
		if(t[p].tag){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=0;
		}
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].val=2*dep[pos[l]]-1;return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p].val=t[p<<1].val+t[p<<1|1].val;
	}
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,val,lson);Update(x,y,val,rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	ll Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree;
void Update(int x){
	while(x){tree.Update(id[top[x]],id[x],1,1,1,n);x=fa[top[x]];}
}
ll Query(int x){
	ll ans=0;
	while(x){ans+=tree.Query(id[top[x]],id[x],1,1,n);x=fa[top[x]];}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=2;i<=n;i++){
		fa[i]=read();
		Add(fa[i],i);
	}
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	for(int i=1;i<=n;i++){
		Update(i);
		printf("%lld\n",Query(read()));
	}
	return 0;
}