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
#define pii pair<ll,ll>
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=200005;
const ll M=20;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<pii,ll>mp;
ll n,m,cnt,Ans;
ll h[N],fa[N],dep[N],sum[N],mark[N],p[N][M];
struct edge{ll to,next;}d[N*2];
struct Edge{ll s,t,lca;}e[N];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(ll x,ll depth){
	dep[x]=depth;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
}
void ST(){
	ll k=(ll)(log(n)/log(2));
	for(ll i=1;i<=n;i++)p[i][0]=fa[i];
	for(ll j=1;j<=k;j++){
		for(ll i=1;i<=n;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
ll LCA(ll x,ll y){
	if(dep[x]<dep[y])swap(x,y);
	for(ll k=(ll)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(ll k=(ll)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
ll Son(ll x,ll pre){
	if(x==pre)return -1;
	for(ll k=(ll)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>dep[pre])x=p[x][k];
	}
	return x;
}
ll Dist(ll x,ll y){
	return sum[x]+sum[y]-sum[LCA(x,y)]*2;
}
void dfs(ll x,ll Sum){
	sum[x]=(Sum+=mark[x]);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		dfs(y,Sum);
	}
}
int main(){
//	freopen("route.in","r",stdin);
//	freopen("route.out","w",stdout);
	n=read();m=read()-n+1;
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);ST();
	for(ll i=1;i<=m;i++){
		e[i].s=read();e[i].t=read();
		e[i].lca=LCA(e[i].s,e[i].t);
		ll fx=Son(e[i].s,e[i].lca);
		ll fy=Son(e[i].t,e[i].lca);
		if(fx!=-1)Ans-=(++mark[fx]);
		if(fy!=-1)Ans-=(++mark[fy]);
		if(fx!=-1&&fy!=-1){
			if(fx>fy)swap(fx,fy);
			Ans-=(mp[make_pair(fx,fy)]++);
		}
	}
	dfs(1,0);
	for(ll i=1;i<=m;i++){
		Ans+=Dist(e[i].s,e[i].t);
	}
	printf("%lld",Ans);
	return 0;
}