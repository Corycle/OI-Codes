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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
ll Ans,Sum,dis[N];
int h[N],fa[N],son[N],top[N];
int a[N],id[N],pos[N],dep[N],sum[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;a[y]=d[i].dist;
		dis[y]=dis[x]+d[i].dist;
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
struct Segment_Tree{
	struct Tree{ll sum,tot,tag;}t[N*4];
	void update(int p,int x){
		t[p].tag+=x;
		t[p].tot+=x*t[p].sum;
	}
	void Pushdown(int p){
		if(t[p].tag){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=0;
		}
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].sum=a[pos[l]];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	void Update(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,1);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,lson);Update(x,y,rson);
		t[p].tot=t[p<<1].tot+t[p<<1|1].tot;
	}
	ll Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].tot;
		int mid=(l+r)>>1;Pushdown(p);
		return Ask(x,y,lson)+Ask(x,y,rson);
	}
}tree;
void Update(int x){
	while(x){
		tree.Update(id[top[x]],id[x],1,1,n);
		x=fa[top[x]];
	}
}
ll Ask(int x){
	ll ans=0;
	while(x){
		ans+=tree.Ask(id[top[x]],id[x],1,1,n);
		x=fa[top[x]];
	}
	return ans;
}
int main(){
//	freopen("express.in","r",stdin);
//	freopen("express.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	while(m--){
		int op=read(),x=read();
		if(op==1){Sum++;Ans+=dis[x];Update(x);}
		else printf("%lld\n",dis[x]*Sum+Ans-Ask(x)*2);
	}
	return 0;
}