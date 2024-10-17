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
const ll N=100005;
const ll g=3;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll R[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
		y>>=1;
	}
	return ans;
}
void NTT(ll a[],ll n,ll f){
	for(ll i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(ll i=1;i<n;i<<=1){
		ll Wn=Pow(g,Mod-1+f*(Mod-1)/(i<<1));
		for(ll j=0;j<n;j+=(i<<1)){
			ll W=1;
			for(ll k=0;k<i;k++){
				ll x=a[j+k],y=W*a[j+k+i]%Mod;
				a[j+k]=(x+y)%Mod;a[j+k+i]=(x-y+Mod)%Mod;
				W=W*Wn%Mod;
			}
		}
	}
	if(f==-1){
		ll inv=Pow(n,Mod-2);
		for(ll i=0;i<n;i++)a[i]=(a[i]*inv)%Mod;
	}
}
ll n,m,X;
ll A[N],B[N],F[N],G[N],D[N],fac[N],inv[N];
ll C(ll n,ll m){
	if(!m)return 1;
	return D[m]*inv[m]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();X=read();
	fac[0]=inv[0]=fac[1]=inv[1]=1;
	for(ll i=0;i<=m;i++)F[i]=read();
	for(ll i=2;i<=m;i++)fac[i]=fac[i-1]*i%Mod;
	for(ll i=2;i<=m;i++)inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=m;i++)inv[i]=inv[i-1]*inv[i]%Mod;
	ll len=1,L=0;
	while(len<=m+m){len<<=1;L++;}
	for(ll i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	for(ll i=0;i<=m;i++)A[i]=inv[i]*Pow(Mod-1,i)%Mod;
	for(ll i=0;i<=m;i++)B[i]=F[i]*inv[i]%Mod;
	NTT(A,len,1);NTT(B,len,1);
	for(ll i=0;i<len;i++)A[i]=A[i]*B[i]%Mod;
	NTT(A,len,-1);
	for(ll i=0;i<=m;i++)G[i]=A[i]*fac[i]%Mod;
	ll ans=0;D[1]=n;
	for(ll i=2;i<=m;i++)D[i]=D[i-1]*(n-i+1)%Mod;
	for(ll i=0;i<=m;i++)ans=(ans+G[i]*Pow(X,i)%Mod*C(n,i)%Mod)%Mod;
	printf("%lld",ans);
	return 0;
}