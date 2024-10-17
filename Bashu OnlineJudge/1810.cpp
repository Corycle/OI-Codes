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
#define ll unsigned long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Inv2=500000004;
const ll Inv6=166666668;
const ll Mod=1e9+7;
const ll maxn=1e6;
const ll N=1e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,ll>G;
ll cnt,Ans,g[N],mu[N],vis[N],prime[N];
ll Sum(ll n){n%=Mod;return n*(n+1)%Mod*Inv2%Mod;}
ll Sum2(ll n){n%=Mod;return n*(n+1)%Mod*(2*n+1)%Mod*Inv6%Mod;}
void Prepare(){
	mu[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=Mod-1;}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=Mod-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
	for(ll i=1;i<=maxn;i++){
		for(ll j=i;j<=maxn;j+=i){
			g[j]=(g[j]+i*mu[i]%Mod*j%Mod+Mod)%Mod;
		}
	}
	for(ll i=2;i<=maxn;i++)g[i]=(g[i]+g[i-1])%Mod;
}
ll Gsum(ll n){
	if(n<=maxn)return g[n];
	if(G[n])return G[n];
	ll ans=Sum(n);
	for(ll i=2,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans=(Mod+ans-(Mod+Sum2(j)-Sum2(i-1))%Mod*Gsum(n/i)%Mod)%Mod;
	}
	return G[n]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll n=read();Prepare();
	for(ll i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ll F=1ll*Sum(n/i)*Sum(n/i)%Mod;
		Ans=(Ans+1ll*F*(Gsum(j)-Gsum(i-1)+Mod)%Mod)%Mod;
	}
	printf("%lld",Ans);
	return 0;
}