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
void Reverse(ll A[],ll n){
	for(ll i=0;i<=n/2;i++){
		swap(A[i],A[n-i]);
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
	NTT(b,len,-1);
	for(ll i=0;i<n;i++)B[i]=b[i];
}
void Division(ll A[],ll B[],ll P[],ll Q[],ll n,ll m){
	Reverse(A,n);Reverse(B,m);
	Inverse(B,P,n-m+1);Prepare(n+n);
	NTT(A,len,1);NTT(P,len,1);
	for(ll i=0;i<len;i++)P[i]=(A[i]*P[i])%Mod;
	NTT(A,len,-1);NTT(P,len,-1);
	Reverse(P,n-m);
	
	Reverse(A,n);Reverse(B,m);Prepare(n+1);
	for(ll i=m+1;i<len;i++)B[i]=0;
	for(ll i=n-m+1;i<len;i++)P[i]=0;
	NTT(B,len,1);NTT(P,len,1);
	for(ll i=0;i<len;i++)Q[i]=(B[i]*P[i])%Mod;
	NTT(B,len,-1);NTT(P,len,-1);NTT(Q,len,-1);
	for(ll i=0;i<=n;i++)Q[i]=(A[i]-Q[i]+Mod)%Mod;
}
ll n,m,A[N],B[N],P[N],Q[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();for(ll i=0;i<=n;i++)A[i]=read();
	m=read();for(ll i=0;i<=m;i++)B[i]=read();
	if(n<m){
		printf("0\n");
		for(ll i=0;i<m;i++)printf("%lld ",A[i]);
		return 0;
	}
	Division(A,B,P,Q,n,m);
	for(ll i=0;i<n-m+1;i++)printf("%lld ",P[i]);
	printf("\n");
	for(ll i=0;i<m;i++)printf("%lld ",Q[i]);
	return 0;
}