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
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot;
ll a[N],h[N],fa[N],id[N],pos[N],dep[N],top[N],son[N],sum[N];
struct edge{ll to,next;}d[N*2];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(ll x,ll depth){
	dep[x]=depth;sum[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(ll x,ll tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
struct Tree{ll sum,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(ll p,ll l,ll r,ll x){
		t[p].tag+=x;
		t[p].sum+=x*(r-l+1);
	}
	void Pushdown(ll p,ll l,ll r){
		if(t[p].tag){
			ll mid=(l+r)>>1;
			update(lson,t[p].tag);
			update(rson,t[p].tag);
			t[p].tag=0;
		}
	}
	void Build(ll p,ll l,ll r){
		if(l==r){t[p].sum=a[pos[l]];return;}
		ll mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	void Update(ll x,ll y,ll z,ll p,ll l,ll r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,l,r,z);return;}
		ll mid=(l+r)>>1;Pushdown(p,l,r);
		Update(x,y,z,lson);Update(x,y,z,rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	ll Query(ll x,ll y,ll p,ll l,ll r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		ll mid=(l+r)>>1;Pushdown(p,l,r);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree;
ll Query(ll x){
	ll ans=0;
	while(x){
		ans+=tree.Query(id[top[x]],id[x],1,1,n);
		x=fa[top[x]];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	while(m--){
		ll op=read(),x=read();
		if(op==1)tree.Update(id[x],id[x],read(),1,1,n);
		if(op==2)tree.Update(id[x],id[x]+sum[x]-1,read(),1,1,n);
		if(op==3)printf("%lld\n",Query(x));
	}
	return 0;
}