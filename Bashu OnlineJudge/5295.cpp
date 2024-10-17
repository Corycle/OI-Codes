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
		ll Inv=Pow(n,Mod-2);
		for(ll i=0;i<n;i++)a[i]=(a[i]*Inv)%Mod;
	}
}
ll n,G[N],F[N],a[N],b[N];
ll Num(ll x){
	int ans=0;
	while(x){
		if(x&1)ans++;
		x>>=1;
	}
	return ans;
}
void Solve(ll l,ll r,ll L){
	if(L<=0||l>n)return;
	ll mid=(l+r)>>1;
	Solve(l,mid,L-1);//Left
	
	ll len=r-l+1;
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	memset(a+len/2,0,sizeof(ll)*len/2);
	memcpy(a,F+l,sizeof(ll)*len/2);
	memcpy(b,F,sizeof(ll)*len);
	
	NTT(a,1<<L,1);NTT(b,1<<L,1);
	for(ll i=0;i<len;i++)a[i]=(a[i]*b[i])%Mod;
	NTT(a,1<<L,-1);
	
	for(ll i=len/2;i<len;i++){
		G[i+l]=(G[i+l]+a[i])%Mod;
		if(l!=1)G[i+l]=(G[i+l]+a[i])%Mod;
	}
	F[mid+1]=Num(G[mid+1]);
	Solve(mid+1,r,L-1);//Right
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();F[1]=read();
	ll len=1,L=0;
	while(len<=n){len<<=1;L++;}
	Solve(1,len,L);
	for(ll i=2;i<=n;i++)printf("%lld ",G[i]);
	return 0;
}