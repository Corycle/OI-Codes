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
const ll Mod=1004535809;
const ll N=500005;
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
void Derivatives(ll a[],ll n){
	for(ll i=0;i<n-1;i++){
		a[i]=a[i+1]*(i+1)%Mod;
	}
	a[n-1]=0;
}
void Integral(ll a[],ll n){
	for(ll i=n-1;i>=1;i--){
		a[i]=a[i-1]*Pow(i,Mod-2)%Mod;
	}
	a[0]=0;
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
		for(ll i=0;i<n;i++)a[i]=a[i]*inv%Mod;
	}
}
ll c[N];
void Inv(ll n,ll a[],ll b[]){
	if(n==1){b[0]=Pow(a[0],Mod-2);return;}
	Inv((1+n)>>1,a,b);
	ll len=1,L=0;
	while(len<n+n){len<<=1;L++;}
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	for(ll i=0;i<n;i++)c[i]=a[i];
	for(ll i=n;i<len;i++)c[i]=0;
	NTT(b,len,1);NTT(c,len,1);
	for(ll i=0;i<len;i++){
		b[i]=(2-b[i]*c[i]%Mod+Mod)%Mod*b[i]%Mod;
	}
	NTT(b,len,-1);
	for(ll i=n;i<len;i++)b[i]=0;
}
ll tmp[N];
void Ln(ll n,ll a[],ll b[]){
	memcpy(tmp,a,sizeof(tmp));
	Derivatives(a,n);
	Inv(n,tmp,b);
	int len=1,L=0;
	while(len<n+n){len<<=1;L++;}
	for(int i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	NTT(a,len,1);
	NTT(b,len,1);
	for(ll i=0;i<len;i++){
		a[i]=a[i]*b[i]%Mod;
	}
	NTT(a,len,-1);
	Integral(a,n);
}
ll n,a[N],b[N],F[N],G[N],fac[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	fac[0]=1;
	for(ll i=1;i<=n;i++)fac[i]=fac[i-1]*i%Mod;
	for(ll i=0;i<=n;i++)F[i]=Pow(2,i*(i-1)/2)*Pow(fac[i],Mod-2)%Mod;
	Ln(n+1,F,G);
	printf("%lld",F[n]*fac[n]%Mod);
	return 0;
}