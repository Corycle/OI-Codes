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
const ll inf=0x3f3f3f3f;
const ll N=3005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,p,q,cnt,Sump,Sumq;
struct edge{ll to,next;}d[N*2];
ll h[N],f[N][N],fa[N],fp[N],fq[N],dep[N];
ll prt[N],sump[N],vis[N],sumq[N],lca[N][N];
ll Find(ll x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(ll x,ll y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS1(ll x,ll depth){
	dep[x]=depth;
	f[x][0]=1;vis[x]=1;
	for(ll i=1;i<=n;i++){
		if(vis[i])lca[x][i]=lca[i][x]=Find(i);
	}
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==prt[x])continue;
		prt[y]=x;DFS1(y,depth+1);
		for(ll j=0;j<p;j++)fp[x]+=f[x][j]*f[y][p-j-1];
		for(ll j=0;j<q;j++)fq[x]+=f[x][j]*f[y][q-j-1];
		for(ll j=0;j<max(p,q);j++)f[x][j+1]+=f[y][j];
	}
	fa[x]=Find(prt[x]);
	Sump+=fp[x];Sumq+=fq[x];
}
void DFS2(ll x){
	sump[x]=sump[prt[x]]+fp[x];
	sumq[x]=sumq[prt[x]]+fq[x];
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==prt[x])continue;
		DFS2(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();p=read();q=read();
	for(ll i=1;i<=n;i++)fa[i]=i;
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1);
	ll Ans=(p==q?Sump*(Sump-1)/2:Sump*Sumq);
	for(ll i=1;i<=n;i++){
		for(ll j=i+1;j<=n;j++){
			ll k=lca[i][j];
			ll len=dep[i]+dep[j]-dep[k]*2;
			if(len==p&&len==q)Ans-=sumq[i]+sumq[j]-sumq[k]-sumq[prt[k]]-1;
			else if(len==p)Ans-=sumq[i]+sumq[j]-sumq[k]-sumq[prt[k]];
			else if(len==q)Ans-=sump[i]+sump[j]-sump[k]-sump[prt[k]];
		}
	}
	for(ll i=1;i<=n;i++){
		if(p!=q)Ans+=fp[i]*fq[i];
		else Ans+=(fp[i]-1)*fp[i]/2;
	}
	printf("%lld",p==q?Ans<<3:Ans<<2);
	return 0;
}