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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll cnt,phi[N],sum[N],vis[N],prime[N];
void Prepare(ll maxn){
	phi[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])phi[i*prime[j]]=phi[i]*phi[prime[j]];
			else{phi[i*prime[j]]=phi[i]*prime[j];break;}
		}
	}
	for(ll i=1;i<=maxn;i++)sum[i]=sum[i-1]+phi[i];
}
ll Sum(ll n){
	return n*(n+1)/2;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(1e6);
	ll T=read();
	while(T--){
		ll n=read(),ans=0;
		for(ll i=1,j=0;i<=n;i=j+1){
			j=n/(n/i);
			ans+=(n/i)*(n/i)*(sum[j]-sum[i-1]);
		}
		printf("%lld\n",(ans-Sum(n))/2);
	}
	return 0;
}