#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll p=1234567891;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll inv[N],g[N],f[N],pre[N],suf[N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
ll Lagrange(ll s[],ll x,ll n){
	ll ans=0,tmp=0;
	pre[0]=suf[n+2]=1;
	for(ll i=1;i<=n+1;i++)pre[i]=pre[i-1]*(x-i+p)%p;
	for(ll i=n+1;i>=1;i--)suf[i]=suf[i+1]*(x-i+p)%p;
	for(ll i=1;i<=n+1;i++){
		tmp=s[i]*pre[i-1]%p*suf[i+1]%p*inv[i-1]%p*inv[n-i+1]%p;
		if(!((n-i)&1))tmp=-tmp+p;ans=(ans+tmp)%p;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll T=read();
	inv[0]=inv[1]=1;
	for(ll i=2;i<=200;i++)inv[i]=(p-p/i)*inv[p%i]%p;
	for(ll i=2;i<=200;i++)inv[i]=inv[i]*inv[i-1]%p;
	while(T--){
		ll k=read(),a=read(),n=read(),d=read();
		for(ll i=0;i<=k+3;i++)g[i]=Pow(i,k,p);//i^k
		for(ll i=1;i<=k+3;i++)g[i]=(g[i-1]+g[i])%p;//f(i)=1^k+2^k+...+i^k
		for(ll i=1;i<=k+3;i++)g[i]=(g[i-1]+g[i])%p;//g(i)=f(1)+f(2)+...+f(i)
		f[0]=Lagrange(g,a,k+2);
		for(ll i=1;i<=k+5;i++){
			f[i]=(f[i-1]+Lagrange(g,(a+i*d)%p,k+2))%p;
		}
		printf("%lld\n",Lagrange(f,n,k+4));
	}
	return 0;
}