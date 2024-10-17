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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,Ans;
ll mu[N],vis[N],prime[N];
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
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=sqrt(n);Prepare(m);
	for(ll i=1;i*i<=n;i++){
		ll t=n/(i*i),sum=0;
		for(ll l=1,r=0;l<=t;l=r+1){
			r=t/(t/l);
			sum=(sum+(r-l+1)*(t/l)%Mod)%Mod;
		}
		Ans=(Ans+sum*mu[i]%Mod+Mod)%Mod;
	}
	printf("%lld",Ans);
	return 0;
}