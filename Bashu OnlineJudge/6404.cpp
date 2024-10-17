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
const ll Mod=998244353;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,top;
ll h[N],f1[N],f2[N],F1[N],F2[N],st[N];
ll A[N],D[N],F[N],fa[N],pre[N],Ans[N];
struct edge{ll to,next,p;}d[N*2];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
ll Sqr(ll x){return x*x%Mod;}
void Prepare(ll x){
	ll p=st[max(top-D[x],0ll)];
	F[p]=(F[p]-A[x]+Mod)%Mod;
	F[x]=(F[x]+A[x])%Mod;
	st[++top]=x;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;Prepare(y);
		F[x]=(F[x]+F[y])%Mod;
	}
	F[x]=(F[x]%Mod+Mod)%Mod;
	top--;
}
void DFS1(ll x){
	f1[x]=F[x];f2[x]=Sqr(F[x]);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		DFS1(y);pre[y]=d[i].p;
		f2[x]=(f2[x]+d[i].p*((2*f1[x]%Mod*f1[y]%Mod+f2[y])%Mod)%Mod)%Mod;
		f1[x]=(f1[x]+d[i].p*f1[y]%Mod)%Mod;
	}
}
void DFS2(ll x){
	if(fa[x]){
		f1[fa[x]]=(F1[fa[x]]-pre[x]*f1[x]%Mod+Mod)%Mod;
		f2[fa[x]]=(F2[fa[x]]-pre[x]*((2*f1[fa[x]]%Mod*f1[x]%Mod+f2[x])%Mod)%Mod+Mod)%Mod;
	}
	f1[x]=F[x];f2[x]=Sqr(F[x]);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		f2[x]=(f2[x]+d[i].p*((2*f1[x]%Mod*f1[y]%Mod+f2[y])%Mod)%Mod)%Mod;
		f1[x]=(f1[x]+d[i].p*f1[y]%Mod);
	}
	Ans[x]=f2[x];
	F1[x]=f1[x];F2[x]=f2[x];
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y!=fa[x])DFS2(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		A[i]=read();D[i]=read();
	}
	for(ll i=1;i<n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Prepare(1);DFS1(1);DFS2(1);m=read();
	while(m--)printf("%lld\n",Ans[read()]);
	return 0;
}