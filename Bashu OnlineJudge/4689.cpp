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
const ll Mod=998244353;
const ll N=300005;
const ll g=3;
ll read(){
	ll s=0,F=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')F=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*F;
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
		y>>=1;
	}
	return ans;
}
ll R[N];
void NTT(ll a[],ll n,ll f){
	for(ll i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(ll i=1;i<n;i<<=1){
		ll Wn=Pow(g,Mod-1+f*(Mod-1)/(i<<1));
		for(ll j=0;j<n;j+=(i<<1)){
			ll W=1;
			for(ll k=0;k<i;k++){
				ll x=a[j+k],y=W*a[j+k+i]%Mod;
				a[j+k]=(x+y)%Mod;a[j+k+i]=(x-y+Mod)%Mod;
				W=(W*Wn)%Mod;
			}
		}
	}
	if(f==-1){
		ll inv=Pow(n,Mod-2);
		for(ll i=0;i<n;i++)a[i]=(a[i]*inv)%Mod;
	}
}
ll fac[N],inv[N],F[N],G[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll n=read(),len=1,L=0;
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(ll i=2;i<=n;i++)fac[i]=fac[i-1]*i%Mod;
	for(ll i=2;i<=n;i++)inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=n;i++)inv[i]=inv[i-1]*inv[i]%Mod;
	while(len<n+n+2){len<<=1;L++;}
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	for(ll i=0;i<=n;i++){
		F[i]=(inv[i]*(i&1?-1:1)+Mod)%Mod;
		G[i]=(Pow(i,n+1)-1+Mod)%Mod*Pow((i-1+Mod)%Mod,Mod-2)%Mod*inv[i]%Mod;
	}
	G[1]=n+1;
    NTT(F,len,1);NTT(G,len,1);
	for(ll i=0;i<len;i++)F[i]=(F[i]*G[i])%Mod;
	NTT(F,len,-1);
	ll ans=0,dlt=1;
	for(ll j=0;j<=n;j++){
		ans=(ans+dlt*fac[j]%Mod*F[j])%Mod;
		dlt=(dlt<<1)%Mod;
	}
	printf("%lld",ans);
	return 0;
}