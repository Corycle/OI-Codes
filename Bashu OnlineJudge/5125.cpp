/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=1e9+7;
const ll N=100005;
const ll M=20;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt,Sum;
ll h[N],fa[N],d1[N],d2[N],len[N],Ans[N];
ll Cut[N],dep[N],dis[N],val[N],p[N][M];
ll Find(ll x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
struct edge{ll to,next;}d[N*2];
struct Edge{ll s,t;}e[N];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(ll x,ll depth){
	dep[x]=depth;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		dis[y]=dis[x]+val[y];
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
ll Dist(ll x,ll y){
	ll z=LCA(x,y);
	return dis[x]+dis[y]-2*dis[z]+val[z];
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Link(ll x,ll y){
	x=Find(x);y=Find(y);fa[x]=y;
	Sum=Sum*Pow(len[x],Mod-2)%Mod;
	Sum=Sum*Pow(len[y],Mod-2)%Mod;
	ll sx=d1[x],tx=d2[x],sy=d1[y],ty=d2[y],Max=-inf,Dis=0;
	Dis=Dist(sx,sy);if(Dis>Max){Max=Dis;d1[y]=sx;d2[y]=sy;}
	Dis=Dist(sx,ty);if(Dis>Max){Max=Dis;d1[y]=sx;d2[y]=ty;}
	Dis=Dist(tx,sy);if(Dis>Max){Max=Dis;d1[y]=tx;d2[y]=sy;}
	Dis=Dist(tx,ty);if(Dis>Max){Max=Dis;d1[y]=tx;d2[y]=ty;}
	Dis=len[x];if(Dis>Max){Max=Dis;d1[y]=sx;d2[y]=tx;}
	Dis=len[y];if(Dis>Max){Max=Dis;d1[y]=sy;d2[y]=ty;}
	len[y]=Max;Sum=Sum*len[y]%Mod;
}
int main(){
//	freopen("forest.in","r",stdin);
//	freopen("forest.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)val[i]=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
		e[i].s=x;e[i].t=y;
	}
	dis[1]=val[1];DFS(1,1);ST();Sum=1;
	for(ll i=1;i<n;i++)Cut[i]=read();
	for(ll i=1;i<=n;i++){
		fa[i]=d1[i]=d2[i]=i;
		Sum=Sum*val[i]%Mod;
		len[i]=val[i];
	}
	Ans[n]=Sum;
	for(ll i=n-1;i>=1;i--){
		Link(e[Cut[i]].s,e[Cut[i]].t);
		Ans[i]=Sum;
	}
	for(ll i=1;i<=n;i++)printf("%lld\n",Ans[i]);
	return 0;
}