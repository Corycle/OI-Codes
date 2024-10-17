/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
const ll N=1000005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll cnt;
ll Fib[N],Inv[N],F[N];
ll mu[N],vis[N],prime[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(ll maxn){
	F[0]=F[1]=1;
	mu[1]=Fib[1]=Inv[1]=1;
	for(ll i=2;i<=maxn;i++){
		Fib[i]=(Fib[i-1]+Fib[i-2])%Mod;
		Inv[i]=Pow(Fib[i],Mod-2);F[i]=1;
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
	for(ll i=1;i<=maxn;i++){
		if(!mu[i])continue;
		for(ll j=i;j<=maxn;j+=i){
			if(mu[i]==1)F[j]=F[j]*Fib[j/i]%Mod;
			else F[j]=F[j]*Inv[j/i]%Mod;
		}
	}
	for(ll i=1;i<=maxn;i++)F[i]=F[i]*F[i-1]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(1e6);
	ll T=read();
	while(T--){
		ll n=read(),m=read();
		ll maxn=min(n,m),ans=1;
		for(ll i=1,j=0;i<=maxn;i=j+1){
			j=min(n/(n/i),m/(m/i));
			ll sum=F[j]*Pow(F[i-1],Mod-2)%Mod;
			ans=ans*Pow(sum,(n/i)*(m/i))%Mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}