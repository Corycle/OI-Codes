#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=1e9+7;
const ll N=5e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,ll>Sum;
ll cnt,mu[N],sum[N],vis[N],fac[N],inv[N],prime[N];
void Prepare(ll maxn){
	mu[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(ll i=2;i<=maxn;i++)fac[i]=fac[i-1]*i%Mod;
	for(ll i=2;i<=maxn;i++)inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=maxn;i++)inv[i]=inv[i-1]*inv[i]%Mod;
	for(ll i=1;i<=maxn;i++)sum[i]=sum[i-1]+mu[i];
}
ll Sum_Mu(ll n){
	if(n<=5e6)return sum[n];
	if(Sum[n])return Sum[n];
	ll ans=1;
	for(ll i=2,j;i<=n;i=j+1){
		j=n/(n/i);
		ans=(ans-(j-i+1)*Sum_Mu(n/i)%Mod+Mod)%Mod;
	}
	return Sum[n]=ans;
}
ll C(ll n,ll m){
	if(n<m)return 0;
	if(n<=5e6&&m<=5e6){
		return fac[n]*inv[m]%Mod*inv[n-m]%Mod;
	}
	ll ans=1;
	for(ll i=1;i<=m;i++){
		ans=ans*(n-i+1)%Mod;
	}
	return ans*inv[m]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(5e6);
	ll T=read();
	while(T--){
		ll n=read(),K=read(),Ans=0;
		for(ll i=1,j;i<=n;i=j+1){
			j=n/(n/i);
			Ans=(Ans+(Sum_Mu(j)-Sum_Mu(i-1)+Mod)%Mod*C(n/i+K-1,K)%Mod)%Mod;
		}
		printf("%lld\n",Ans);
	}
	return 0;
}