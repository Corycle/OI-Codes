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
const ll Inv2=5e8+4;
const ll Mod=1e9+7;
const ll M=2505;
const ll N=1505;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,X,Y,cnt,scc;
ll h[N],b[N],fa[N],dis[N],dep[N];
ll p[N][N],f[N][M][2],g[N][M][2];
struct edge{ll to,next,dist;}d[N*2];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
ll Find(ll x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void DFS(ll x,ll prt){
	dep[x]=dep[prt]+1;b[x]=scc;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==prt)continue;
		dis[y]=dis[x]+d[i].dist;
		p[y][0]=x;DFS(y,x);
	}
}
void ST(){
	ll k=(ll)(log(n)/log(2));
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
	return dis[x]+dis[y]-dis[LCA(x,y)]*2;
}
ll Fac(ll x){
	ll fac=1;
	for(ll i=1;i<=x;i++)fac=fac*i%Mod;
	return fac;
}
/*
	g[i][0]：第i棵树的路径数 
	g[i][1]：第i棵树的路径长度和 
	f[i][0]：和为i的方案数 
	f[i][1]：和为i的方案和 
	大于Y的方案全部装进f[y]中 
*/
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	X=read();Y=read();
	for(ll i=1;i<=n;i++)fa[i]=i;
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
		fa[Find(x)]=Find(y);
	}
	for(ll i=1;i<=n;i++){
		if(fa[i]==i){
			scc++;
			DFS(i,0);
		}
	}
	ST();
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			if(b[i]==b[j]&&i!=j){
				ll dist=Dist(i,j);
				g[b[i]][min(dist,Y)][0]=(g[b[i]][min(dist,Y)][0]+1)%Mod;
				g[b[i]][min(dist,Y)][1]=(g[b[i]][min(dist,Y)][1]+dist)%Mod;
			}
		}
	}
	ll st=min(X*scc,Y);
	f[0][st][0]=1;f[0][st][1]=X*scc;
	for(ll i=1;i<=scc;i++){
		for(ll j=0;j<=Y;j++){
			if(!g[i][j][0])continue;
			for(ll k=st;k<=Y;k++){
				f[i][min(j+k,Y)][0]=(f[i][min(j+k,Y)][0]+f[i-1][k][0]*g[i][j][0]%Mod)%Mod;
				f[i][min(j+k,Y)][1]=(f[i][min(j+k,Y)][1]+f[i-1][k][0]*g[i][j][1]%Mod)%Mod;
				f[i][min(j+k,Y)][1]=(f[i][min(j+k,Y)][1]+f[i-1][k][1]*g[i][j][0]%Mod)%Mod;
			}
		}
	}
	printf("%lld",f[scc][Y][1]*Fac(scc-1)%Mod*Inv2%Mod);
	return 0;
}