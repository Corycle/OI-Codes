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
const ll Inv9=229582513;
const ll Mod=258280327;
const ll N=5e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,ll>F;
ll n,cnt;
int f[N],vis[N],prime[N];
ll mod(ll x){return x>=Mod?x-Mod:x;}
ll Sum(ll x){x%=Mod;return 1ll*x*(x+1)/2%Mod;}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(ll maxn){
	f[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;f[i]=Mod-i;}
		for(ll j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			f[i*prime[j]]=1ll*f[i]*f[prime[j]]%Mod;
			if(i%prime[j]==0){f[i*prime[j]]=0;break;}
		}
	}
	for(ll i=1;i<=maxn;i++)f[i]=mod(f[i-1]+f[i]);
}
ll SumF(ll n){
	if(n<=5e6)return f[n];
	if(F[n])return F[n];
	ll ans=1;
	for(ll i=2,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans=(ans-1ll*(Sum(j)-Sum(i-1)+Mod)%Mod*SumF(n/i)%Mod+Mod)%Mod;
	}
	return F[n]=ans;
}
ll GetG(ll n){
	ll tmp=Pow(10,n+1);
	return (1ll*n%Mod*tmp%Mod-1ll*(tmp-10+Mod)*Inv9%Mod+Mod)%Mod*Inv9%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare(5e6);
	ll Ans=0;
	for(ll i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		Ans=(Ans+1ll*(SumF(j)-SumF(i-1)+Mod)%Mod*GetG(n/i)%Mod)%Mod;
	}
	printf("%lld",(Ans%Mod+Mod)%Mod);
	return 0;
}