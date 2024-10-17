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
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=500005;
const ll g=3;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll R[N];
ll Multi(ll x,ll y,ll mod){
	ll ans=0,tot=x;
	while(y){
		if(y&1)ans=(ans+tot)%mod;
		tot=(tot+tot)%mod;
		y>>=1;
	}
	return ans;
}
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
struct Number_Theoretic_Transforms{
	ll A[N],Mod;
	void NTT(ll a[],ll n,ll f){
		for(ll i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
		for(ll i=1;i<n;i<<=1){
			ll Wn=Pow(g,Mod-1+f*(Mod-1)/(i<<1),Mod);
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
			ll inv=Pow(n,Mod-2,Mod);
			for(ll i=0;i<n;i++)a[i]=(a[i]*inv)%Mod;
		}
	}
}ntt[3];
ll n,m,maxn,p=1000000007;
ll a[N],b[N],B[N],Ans[N];
ll P[3]={469762049,998244353,1004535809};
void Merge(){
	ll M=P[0]*P[1];
	ll inv0=Pow(P[0]%P[1],P[1]-2,P[1]);
	ll inv1=Pow(P[1]%P[0],P[0]-2,P[0]);
	ll inv2=Pow(M%P[2],P[2]-2,P[2]);
	for(ll i=0;i<=maxn;i++){
		ll a=ntt[0].A[i],b=ntt[1].A[i],c=ntt[2].A[i];
		ll t=(Multi(a*P[1]%M,inv1,M)+Multi(b*P[0]%M,inv0,M))%M;
		ll k=((c-t%P[2])%P[2]+P[2])%P[2]*inv2%P[2];
		Ans[i]=((k%p)*(M%p)%p+t%p)%p;
	}
}
void Solve(){
	ll len=1,L=0;
	while(len<=n+m){len<<=1;L++;}
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	for(ll k=0;k<=2;k++){
		ntt[k].Mod=P[k];
		ll *A=ntt[k].A;
		for(int i=0;i<=n;i++)A[i]=a[i];
		for(int i=0;i<len;i++)B[i]=b[i];
		ntt[k].NTT(A,len,1);
		ntt[k].NTT(B,len,1);
		for(ll i=0;i<len;i++){
			A[i]=(A[i]*B[i])%P[k];
		}
		ntt[k].NTT(A,len,-1);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=0;i<=n;i++)a[i]=read();
	for(ll i=0;i<=m;i++)b[i]=read();
	maxn=n+m;
	Solve();Merge();
	for(ll i=0;i<=maxn;i++)printf("%lld ",Ans[i]);
	return 0;
}