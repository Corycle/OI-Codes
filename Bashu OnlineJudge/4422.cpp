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
const ll Mod=1e9+9;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt;
ll m[N],mu[N],sum[N],vis[N],prime[N];
void Prepare(ll maxn){
	mu[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=Mod-1;}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=mu[i]*mu[prime[j]]%Mod;
			else{mu[i*prime[j]]=0;break;}
		}
	}
	for(ll i=1;i<=maxn;i++){
		sum[i]=(sum[i-1]+mu[i])%Mod;
		if(!(i&1))sum[i]=(sum[i]+mu[i/2])%Mod;
	}
}
int main(){
//	freopen("point.in","r",stdin);
//	freopen("point.out","w",stdout);
	Prepare(1e6);
	ll T=read();
	while(T--){
		ll p=inf,ans=0;n=read();
		for(ll i=1;i<=n;i++){
			m[i]=read();
			p=min(p,m[i]);
		}
		for(ll i=1,j=0;i<=p;i=j+1){
			j=p/(p/i);
			ll dlt=1;
			for(ll k=1;k<=n;k++)j=min(j,m[k]/(m[k]/i));
			for(ll k=1;k<=n;k++)dlt=(dlt*(m[k]/i))%Mod;
			ans=(ans+dlt*(sum[j]-sum[i-1]+Mod)%Mod)%Mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}