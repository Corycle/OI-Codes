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
const ll N=100005;
const ll g=3;
ll read(){
	ll s=0,F=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')F=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*F;
}
ll R[N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
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
ll f[N];
ll GetRoot(ll n){
	ll tot=0,phi=n-1;
	for(ll i=2;i*i<=n;i++){
		if(phi%i==0){
			f[++tot]=i;
			while(phi%i==0)phi/=i;
		}
	}
	if(phi>1)f[++tot]=phi;
	phi=n-1;
	for(ll i=2;i<=phi;i++){
		ll flag=1;
		for(ll j=1;j<=tot;j++){
			if(Pow(i,phi/f[j],n)==1){
				flag=0;break;
			}
		}
		if(flag)return i;
	}
	return -1;
}
ll n,m,p,S,len;
ll num[N],F[N],H[N];
void Multi(ll A[],ll B[],ll type){
	NTT(A,len,1);
	if(type==1)NTT(B,len,1);
	for(ll i=0;i<len;i++)A[i]=(A[i]*B[i])%Mod;
	if(type==1)NTT(B,len,-1);
	NTT(A,len,-1);
	for(ll i=0;i<m-1;i++)A[i]=(A[i]+A[i+m-1])%Mod;
	for(ll i=m-1;i<len;i++)A[i]=0;
}
void Solve(){
	while(n){
		if(n&1)Multi(H,F,1);
		Multi(F,F,0);
		n>>=1;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	p=read();S=read();
	ll G=GetRoot(m);
	for(ll i=0;i<m-1;i++)num[Pow(G,i,m)]=i;
	for(ll i=1;i<=S;i++){
		ll x=read()%m;
		if(x)F[num[x]]++;
	}
	H[num[1]]=1;
	ll L=0;len=1;
	while(len<m*2){len<<=1;L++;}
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	Solve();
	printf("%lld",H[num[p]]);
	return 0;
}