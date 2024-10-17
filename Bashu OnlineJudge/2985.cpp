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
const ll Mod=1000000007;
const ll N=5000005;
const ll M=500005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int K,cnt;
ll f[N],g[M];
int vis[N],prime[M];
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
	f[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;g[cnt]=Pow(i,K);f[i]=g[cnt]-1;}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])f[i*prime[j]]=f[i]*f[prime[j]]%Mod;
			else{f[i*prime[j]]=f[i]*g[j]%Mod;break;}
		}
	}
	for(ll i=1;i<=maxn;i++)f[i]=(f[i]+f[i-1])%Mod;
}
ll Solve(ll n,ll m){
	ll ans=0,maxn=min(n,m);
	for(ll i=1,j;i<=maxn;i=j+1){
		j=min(n/(n/i),m/(m/i));
		ans=(ans+(f[j]-f[i-1])*(n/i)%Mod*(m/i)%Mod)%Mod;
	}
	return (ans+Mod)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();K=read();Prepare(5e6);
	while(T--){
		ll l=read(),r=read();
		printf("%lld\n",Solve(l,r));
	}
	return 0;
}