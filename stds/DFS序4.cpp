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
const ll inf=0x3f3f3f3f;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,root,cnt,step;
struct edge{
	ll to,next;
}d[N*2];
ll l[N],r[N],h[N],fa[N],val[N],sum[N],son[N],dep[N],top[N];
ll c1[N*2],c2[N*2];
void hqq_add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void dfs1(ll x,ll depth){
	ll maxx=-1,s=0;
	dep[x]=depth;
	l[x]=++step;
	sum[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(dep[y])continue;
		fa[y]=x;
		dfs1(y,depth+1);
		sum[x]+=sum[y];
		if(maxx<sum[y]){
			maxx=sum[y];
			s=y;
		}
	}
	son[x]=s;
	r[x]=step;
}
void dfs2(ll x,ll tp){
	top[x]=tp;
	if(son[x])dfs2(son[x],tp);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		dfs2(y,y);
	}
}
ll lowbit(ll x){
	return (x&(-x));
}
void Add(ll c[],ll x,ll y){
	for(ll i=x;i<=step;i+=lowbit(i)){
		c[i]+=y;
	}
}
ll Ask(ll c[],ll x){
	ll ans=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
ll Sum(ll x){
	return dep[x]*Ask(c2,l[x])+Ask(c1,l[x]);
}
ll lca(ll x,ll y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();root=read();
	for(ll i=1;i<=n;i++){
		val[i]=read();
	}
	for(ll i=1;i<=n-1;i++){
		ll x=read(),y=read();
		hqq_add(x,y);
		hqq_add(y,x);
	}
	dfs1(root,1);
	dfs2(root,root);
	for(ll i=1;i<=n;i++){
		Add(c1,l[i],val[i]);
		Add(c1,r[i]+1,-val[i]);
	}
	while(m--){
		ll p=read();
		if(p==1){
			ll x=read(),y=read();
			Add(c1,l[x],y);
			Add(c1,r[x]+1,-y);
		}
		if(p==2){
			ll x=read(),y=read();
			Add(c2,l[x],y);
			Add(c2,r[x]+1,-y);
			Add(c1,l[x],-y*(dep[x]-1));
			Add(c1,r[x]+1,y*(dep[x]-1));
		}
		if(p==3){
			ll x=read(),y=read();
			ll z=lca(x,y);
			ll ans=Sum(x)+Sum(y)-Sum(z)-Sum(fa[z]);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
/*
　　这是一道模板题。
　　给一棵有根树，这棵树由编号为1…N的N个结点组成。根结点的编号为R。每个结点都有一个权值，结点i的权值为vi。
　　接下来有M组操作，操作分为三类：
　　1 a x，表示将结点a的权值增加x；
　　2 a x，表示将a的子树上所有结点的权值增加x；
　　3 a b，表示求「结点a到结点b的简单路径」上所有结点的权值之和。
*/
