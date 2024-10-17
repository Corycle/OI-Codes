#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot,root=1;
ll h[N],fa[N],val[N],dep[N],a[N];
ll son[N],sum[N],top[N],id[N];
struct Tree{
	ll sum,bj;
}t[N*4];
struct edge{
	ll to,next;
}d[N];
void edge_add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void dfs1(ll x,ll depth){
	sum[x]=1;
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		dfs1(y,depth+1);
		sum[x]+=sum[y];
		if(sum[y]>sum[son[x]])son[x]=y;
	}
}
void dfs2(ll x,ll tp){
	top[x]=tp;
	id[x]=++tot;
	val[id[x]]=a[x];
	if(son[x])dfs2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		dfs2(y,y);
	}
}
void update(ll x,ll num,ll l,ll r){
	t[num].bj+=x;
	t[num].sum+=(r-l+1)*x;
}
void Pushup(ll num){
	t[num].sum=t[num<<1].sum+t[num<<1|1].sum;
}
void Pushdown(ll num,ll l,ll r){
	if(!t[num].bj)return;
	ll mid=(l+r)>>1;
	update(t[num].bj,lson);
	update(t[num].bj,rson);
	t[num].bj=0;
}
void Build(ll num,ll l,ll r){
	if(l==r){
		t[num].sum=val[l];
		return;
	}
	ll mid=(l+r)>>1;
	Build(lson);
	Build(rson);
	Pushup(num);
}
void Add(ll x,ll y,ll z,ll num,ll l,ll r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		t[num].bj+=z;
		t[num].sum+=(r-l+1)*z;
		return;
	}
	Pushdown(num,l,r);
	ll mid=(l+r)>>1;
	Add(x,y,z,lson);
	Add(x,y,z,rson);
	Pushup(num);
}
ll Ask(ll x,ll y,ll num,ll l,ll r){
	if(y<l||x>r)return 0;
	if(x<=l&&r<=y){
		return t[num].sum;
	}
	Pushdown(num,l,r);
	ll mid=(l+r)>>1;
	return Ask(x,y,lson)+Ask(x,y,rson);
}
ll lca(ll x,ll y){//return LCA(x,y)'s son
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		if(fa[top[x]]==y)return top[x];
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return son[x];
}
void Update1(ll x,ll y,ll z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Add(id[top[x]],id[x],z,1,1,n);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	Add(id[x],id[y],z,1,1,n);
}
void Update2(ll x,ll y){
	ll fy=lca(x,root);
	ll fx=fa[fy];
	if(x==root)Add(1,sum[1],y,1,1,n);
	else if(fx!=x)Add(id[x],id[x]+sum[x]-1,y,1,1,n);
	else{
		Add(1,sum[1],y,1,1,n);
		Add(id[fy],id[fy]+sum[fy]-1,-y,1,1,n);
	}
}
ll Query1(ll x,ll y){
	ll ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=Ask(id[top[x]],id[x],1,1,n);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans+=Ask(id[x],id[y],1,1,n);
	return ans;
}
ll Query2(ll x){
	ll fy=lca(x,root);
	ll fx=fa[fy];
	if(x==root)return Ask(1,sum[1],1,1,n);
	if(fx!=x)return Ask(id[x],id[x]+sum[x]-1,1,1,n);
	return Ask(1,sum[1],1,1,n)-Ask(id[fy],id[fy]+sum[fy]-1,1,1,n);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++){
		ll x=read();
		edge_add(x,i);
	}
	dfs1(1,1);
	dfs2(1,1);
	Build(1,1,n);
	m=read();
	while(m--){
		ll op=read();
		if(op==1)root=read();
		if(op==2){
			ll x=read(),y=read(),z=read();
			Update1(x,y,z);
		}
		if(op==3){
			ll x=read(),y=read();
			Update2(x,y);
		}
		if(op==4){
			ll x=read(),y=read();
			printf("%lld\n",Query1(x,y));
		}
		if(op==5){
			ll x=read();
			printf("%lld\n",Query2(x));
		}
	}
	return 0;
}