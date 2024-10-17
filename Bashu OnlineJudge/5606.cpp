#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=9e18;
const ll N=100005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll n,m,cnt,tot,Min,root;
ll h[N],Fa[N],rt[N],prt[N],dep[N];
ll sum[N],son[N],top[N],vis[N],dis[N];
struct edge{
	ll to,next,dist;
}d[N*2];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
/*==========以下为树剖求LCA==========*/
void DFS1(ll x,ll depth){
	dep[x]=depth;sum[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==Fa[x])continue;
		Fa[y]=x;
		dis[y]=dis[x]+d[i].dist;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(ll x,ll tp){
	top[x]=tp;
	if(son[x])DFS2(son[x],tp);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==Fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
ll LCA(ll x,ll y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=Fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
ll Dist(ll x,ll y){
	return dis[x]+dis[y]-2*dis[LCA(x,y)];
}
/*==========以下为点分树==========*/
void GetRoot(ll x,ll Fa,ll num){
	ll S=0;sum[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==Fa||vis[y])continue;
		GetRoot(y,x,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<Min){Min=S;root=x;}
}
void DFS(ll x,ll fa,ll num){
	Min=inf;GetRoot(x,0,num);
	x=root;prt[x]=fa;vis[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(vis[y])continue;
		DFS(y,x,sum[y]);
	}
}
/*==========以下为线段树==========*/
struct Segment_Tree{
	struct Tree{ll l,r,Min;}t[N*100];
	void Insert(ll &x,ll l,ll r,ll pos,ll val){
		if(!x){x=++tot;t[x].Min=inf;}
		t[x].Min=min(t[x].Min,val);
		if(l==r)return;
		ll mid=(l+r)>>1;
		if(pos<=mid)Insert(t[x].l,l,mid,pos,val);
		else Insert(t[x].r,mid+1,r,pos,val);
	}
	ll Ask(ll x,ll l,ll r,ll fx,ll fy){
		if(!x||fy<l||fx>r)return inf;
		if(fx<=l&&r<=fy)return t[x].Min;
		ll mid=(l+r)>>1;
		ll ansl=Ask(t[x].l,l,mid,fx,fy);
		ll ansr=Ask(t[x].r,mid+1,r,fx,fy);
		return min(ansl,ansr);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=2;i<=n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS1(1,1);
	DFS2(1,1);
	DFS(1,0,n);
	for(ll i=1;i<=n;i++){
		for(ll x=i;x;x=prt[x]){
			tree.Insert(rt[x],1,n,i,Dist(x,i));
		}
	}
	m=read();
	while(m--){
		ll l=read(),r=read(),x=read();
		ll y=x,ans=inf;
		while(x){
			ans=min(ans,tree.Ask(rt[x],1,n,l,r)+Dist(x,y));
			x=prt[x];
		}
		printf("%lld\n",ans);
	}
	return 0;
}