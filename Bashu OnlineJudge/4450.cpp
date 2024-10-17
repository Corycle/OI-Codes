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
const ll Mod=950009857;
const ll N=300005;
const ll g=7;
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
				W=(W*Wn)%Mod;
			}
		}
	}
	if(f==-1){
		ll inv=Pow(n,Mod-2);
		for(ll i=0;i<n;i++)a[i]=(a[i]*inv)%Mod;
	}
}
ll n,m,p,len=1;
ll f[N],c[N],sum[N];
void Multi(ll A[],ll B[],ll type){
	NTT(A,len,1);
	if(type==1)NTT(B,len,1);
	for(ll i=0;i<len;i++)A[i]=(A[i]*B[i])%Mod;
	if(type==1)NTT(B,len,-1);
	NTT(A,len,-1);
	for(int i=n;i<len;i++)A[i]=B[i]=0;
}
void Solve(){
	while(p){
		if(p&1)Multi(f,sum,1);
		Multi(sum,sum,0);
		p>>=1;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(ll i=0;i<n;i++)f[i]=read();
	for(ll i=0;i<m;i++)c[i]=read();
	for(ll i=0;i<m;i++)sum[c[i]]++;
	ll L=0;
	while(len<n+n){len<<=1;L++;}
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	Solve();
	for(ll i=0;i<n;i++)printf("%lld ",f[i]);
	return 0;
}