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
const ll Mod=998244353;
const ll N=1000005;
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
ll n,P,cnt,Ans,Dlt,Inv;
ll h[N],f[N],g[N],fa[N],sum[N];
struct edge{ll to,next;}d[N*2];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
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
void DFS1(ll x){
	sum[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y);
		sum[x]+=sum[y];
	}
	f[x]=(P-1+sum[x])%Mod*Pow(sum[x],Mod-2)%Mod;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		f[x]=f[x]*f[y]%Mod;
	}
}
void DFS2(ll x){
	if(fa[x]){
		ll dlt1=Dlt;sum[fa[x]]=n-sum[x];
		ll dlt2=(P-1+sum[fa[x]])%Mod*Pow(sum[fa[x]],Mod-2)%Mod;
		f[fa[x]]=g[fa[x]]*Inv%Mod*dlt2%Mod*Pow(f[x],Mod-2)%Mod;
	}
	f[x]=Dlt;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		f[x]=f[x]*f[y]%Mod;
	}
	g[x]=f[x];
	Ans=(Ans+f[x])%Mod;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		DFS2(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();P=read();
	Dlt=(P-1+n)%Mod*Pow(n,Mod-2)%Mod;
	Inv=Pow(Dlt,Mod-2);
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1);DFS2(1);
	printf("%lld",Ans*Pow(n,Mod-2)%Mod);
	return 0;
}