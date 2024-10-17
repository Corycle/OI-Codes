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
const ll N=500005;
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
void Derivation(ll A[],ll n){
	for(ll i=0;i<n-1;i++){
		A[i]=A[i+1]*(i+1)%Mod;
	}
	A[n-1]=0;
}
void Integral(ll A[],ll n){
	for(ll i=n-1;i>=1;i--){
		A[i]=A[i-1]*Pow(i,Mod-2)%Mod;
	}
	A[0]=0;
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
ll c[N];
void Logarithm(ll A[],ll B[],ll n){
	memcpy(c,A,sizeof(c));
	Inverse(c,B,n+1);
	Derivation(A,n);
	Prepare(n+n+2);
	NTT(A,len,1);NTT(B,len,1);
	for(ll i=0;i<len;i++)B[i]=(A[i]*B[i])%Mod;
	NTT(A,len,-1);NTT(B,len,-1);
	Integral(B,n);
}
ll F[N],G[N],H[N];
void Exp(ll A[],ll B[],ll n){
	if(n==1){B[0]=1;return;}
	Exp(A,B,(1+n)>>1);
	memset(F,0,sizeof(F));
	memset(G,0,sizeof(G));
	memset(H,0,sizeof(G));
	for(ll i=0;i<n;i++)F[i]=B[i];
	Logarithm(F,H,n);
	Prepare(n+n);
	F[0]=(1-H[0]+A[0]+Mod)%Mod;
	for(ll i=1;i<n;i++)F[i]=(A[i]-H[i]+Mod)%Mod;
	for(ll i=0;i<n;i++)G[i]=B[i];
	for(ll i=n;i<len;i++)F[i]=0;
	for(ll i=n;i<len;i++)G[i]=0;
	NTT(F,len,1);NTT(G,len,1);
	for(ll i=0;i<len;i++)F[i]=(F[i]*G[i])%Mod;
	NTT(F,len,-1);
	for(ll i=0;i<len;i++)B[i]=F[i];
}
ll n,m,A[N],B[N];
ll sum[N],inv[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)sum[read()]++;
	inv[0]=inv[1]=1;
	for(ll i=2;i<=1e5;i++)inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=1;i<=1e5;i++){
		if(sum[i]){
			for(ll j=1;j<=1e5;j++){
				if(i*j>m)break;
				A[i*j]=(A[i*j]+sum[i]*inv[j]%Mod)%Mod;
			}
		}
	}
	Exp(A,B,m+1);
	for(ll i=1;i<=m;i++)printf("%lld\n",B[i]);
	return 0;
}