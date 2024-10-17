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
using namespace std;
const ll inf=9e18;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot,Ans;
ll h[N],c[N],sum[N],pre[N];
ll fa[N],f1[N],f2[N],F1[N],F2[N];
struct edge{ll to,next,dist;}d[N*2];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
ll Sqr(ll x){return x*x;}
void DFS1(ll x){
	sum[x]=c[x];
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y);
		sum[x]+=sum[y];pre[y]=d[i].dist;
		f1[x]=f1[x]+f1[y]+sum[y]*d[i].dist;
		f2[x]=f2[x]+f2[y]+sum[y]*Sqr(d[i].dist)+2*f1[y]*d[i].dist;
	}
}
void DFS2(ll x){
	if(fa[x]){
		sum[fa[x]]=tot-sum[x];
		f1[fa[x]]=F1[fa[x]]-f1[x]-sum[x]*pre[x];
		f2[fa[x]]=F2[fa[x]]-f2[x]-sum[x]*Sqr(pre[x])-2*f1[x]*pre[x];
	}
	f1[x]=0;f2[x]=0;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		f1[x]=f1[x]+f1[y]+sum[y]*d[i].dist;
		f2[x]=f2[x]+f2[y]+sum[y]*Sqr(d[i].dist)+2*f1[y]*d[i].dist;
	}
	Ans=min(Ans,f2[x]);
	F1[x]=f1[x];F2[x]=f2[x];
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y!=fa[x])DFS2(y);
	}
}
int main(){
//	freopen("nirvana.in","r",stdin);
//	freopen("nirvana.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)c[i]=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS1(1);Ans=inf;tot=sum[1];DFS2(1);
	printf("%lld",Ans);
	return 0;
}