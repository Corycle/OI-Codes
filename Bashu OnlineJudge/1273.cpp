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
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=300005;
inline char getch(){
    static char buf[500],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,500,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll n,m,cnt,tot,step;
ll h[N],L[N],R[N],fa[N];
ll dep[N],sum[N],pos[N],rt[N];
struct edge{
	ll to,next;
}d[N*2];
struct Tree{
	ll l,r,sum;
}t[N*50];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(ll x,ll depth){
	sum[x]=1;
	dep[x]=depth;
	L[x]=++step;
	pos[step]=x;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		DFS(y,depth+1);
		sum[x]+=sum[y];
	}
	R[x]=step;
}
ll Insert(ll x,ll p,ll addv,ll l,ll r){
	ll y=++tot;
	t[y]=t[x];
	t[y].sum+=addv;
	if(l==r)return y;
	ll mid=(l+r)>>1;
	if(p<=mid)t[y].l=Insert(t[x].l,p,addv,l,mid);
	else t[y].r=Insert(t[x].r,p,addv,mid+1,r);
	return y;
}
ll Ask(ll x,ll y,ll sx,ll sy,ll l,ll r){
	if(sy<l||r<sx)return 0;
	if(sx<=l&&r<=sy)return t[y].sum-t[x].sum;
	ll mid=(l+r)>>1;
	ll sum=0;
	sum+=Ask(t[x].l,t[y].l,sx,sy,l,mid);
	sum+=Ask(t[x].r,t[y].r,sx,sy,mid+1,r);
	return sum;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);
	for(ll i=1;i<=n;i++){
		ll p=pos[i];
		rt[i]=Insert(rt[i-1],dep[p],sum[p]-1,1,n);
	}
	while(m--){
		ll x=read(),k=read();
		ll ans=Ask(rt[L[x]],rt[R[x]],dep[x]+1,dep[x]+k,1,n);
		ans+=min(k,dep[x]-1)*(sum[x]-1);
		printf("%lld\n",ans);
	}
	return 0;
}