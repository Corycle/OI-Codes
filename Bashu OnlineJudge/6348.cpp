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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt,Ans;
ll h[N],a[N],f[N],fa[N],Inv[N];
struct edge{ll to,next;}d[N*2];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Prepare(){
	Inv[0]=Inv[1]=1;
	for(ll i=2;i<=n;i++)Inv[i]=Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=n;i++)Inv[i]=Inv[i-1]*Inv[i]%Mod;
}
void DFS(ll x,ll depth){
	f[x]=Inv[depth];
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
		f[x]=(f[x]+f[y])%Mod;
	}
}
int main(){
//	freopen("treasure.in","r",stdin);
//	freopen("treasure.out","w",stdout);
	n=read();Prepare();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		if(a[i]!=-1)Add(a[i],i);
	}
	ll Ans=0;
	for(ll i=1;i<=n;i++){
		if(a[i]==-1){
			DFS(i,1);
			Ans=(Ans+f[i])%Mod;
		}
	}
	printf("%lld",Ans);
	return 0;
}