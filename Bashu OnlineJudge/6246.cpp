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
const ll N=1000005;
const ll g=3;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll len,L,R[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(ll n){
	len=1;L=0;
	while(len<n){len<<=1;L++;}
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
}
void NTT(ll a[],ll n,ll f){
	for(ll i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(ll i=1;i<n;i<<=1){
		ll Wn=Pow(g,Mod-1+f*(Mod-1)/(i<<1));
		for(ll j=0;j<n;j+=(i<<1)){
			ll W=1;
			for(ll k=0;k<i;k++){
				ll x=a[j+k],y=(W*a[j+k+i])%Mod;
				a[j+k]=(x+y)%Mod;a[j+k+i]=(x-y+Mod)%Mod;
				W=(W*Wn)%Mod;
			}
		}
	}
	if(f==-1){
		ll Inv=Pow(n,Mod-2);
		for(ll i=0;i<n;i++)a[i]=(a[i]*Inv)%Mod;
	}
}
ll a[N],b[N];
void Inverse(ll A[],ll B[],ll n){
	if(n==1){B[0]=Pow(A[0],Mod-2);return;}
	Inverse(A,B,(1+n)>>1);Prepare(n+n);
	for(ll i=0;i<n;i++)a[i]=A[i];
	for(ll i=0;i<n;i++)b[i]=B[i];
	for(ll i=n;i<len;i++)a[i]=0;
	for(ll i=n;i<len;i++)b[i]=0;
	NTT(a,len,1);NTT(b,len,1);
	for(ll i=0;i<len;i++){
		b[i]=(b[i]*2%Mod-b[i]*b[i]%Mod*a[i]%Mod+Mod)%Mod;
	}
	NTT(a,len,-1);NTT(b,len,-1);
	for(ll i=0;i<n;i++)B[i]=b[i];
	for(ll i=n;i<len;i++)B[i]=0;
}
ll n,fac[N],inv[N];
ll Ans[N],F1[N],F2[N];
int main(){
//	freopen("giligili.in","r",stdin);
//	freopen("giligili.out","w",stdout);
	n=read();
	ll Inv2=Pow(2,Mod-2),ans=0;
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(ll i=2;i<=n;i++)fac[i]=fac[i-1]*i%Mod;
	for(ll i=2;i<=n;i++)inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=n;i++)inv[i]=inv[i-1]*inv[i]%Mod;
	for(ll i=0;i<=n;i++)F1[i]=Pow(2,i*(i-1)/2)*inv[i]%Mod;
	Inverse(F1,F2,n+1);
	for(ll i=0;i<=n;i++)F1[i]=F1[i]*fac[i]%Mod;
	for(ll i=0;i<=n;i++)F2[i]=F2[i]*fac[i]%Mod;
	for(ll i=0;i<=n;i++){
		Ans[i]=(F1[i]+F2[i])%Mod*Inv2%Mod;
		ans=ans^(i*Ans[i]);
	}
	printf("%lld",ans);
	return 0;
}