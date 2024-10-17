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
const ll Mod=1e9+7;
const ll N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,ll>Sum;
ll cnt,inv2,inv6;
ll g[N],vis[N],phi[N],prime[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(ll maxn){
	phi[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])phi[i*prime[j]]=phi[i]*phi[prime[j]]%Mod;
			else{phi[i*prime[j]]=phi[i]*prime[j]%Mod;break;}
		}
	}
	for(ll i=1;i<=maxn;i++)g[i]=(g[i-1]+i*phi[i]%Mod)%Mod;
	inv2=Pow(2,Mod-2);inv6=Pow(6,Mod-2);
}
ll G(ll n){
	if(n<=1e5)return g[n];
	if(Sum[n])return Sum[n];
	ll ans=n*(n+1)%Mod*(2*n+1)%Mod*inv6%Mod;
	for(ll i=2,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans=(ans-(i+j)*(j-i+1)%Mod*inv2%Mod*G(n/i)%Mod+Mod)%Mod;
	}
	return Sum[n]=ans;
}
ll F(ll n){
	ll ans=n;
	for(ll i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans=(ans+(j-i+1)*G(n/i)%Mod)%Mod;
	}
	return ans*inv2%Mod;
}
int main(){
//	freopen("gcd.in","r",stdin);
//	freopen("gcd.out","w",stdout);
	Prepare(1e5);
	ll l=read(),r=read();
	printf("%lld",(F(r)-F(l-1)+Mod)%Mod);
	return 0;
}