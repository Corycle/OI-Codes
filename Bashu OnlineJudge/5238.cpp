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
const ll Mod=1e9+7;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Inv;
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
		y/=2;
	}
	return ans;
}
void FMT1(ll a[],ll n,ll f){
	for(ll i=1;i<(1<<n);i<<=1){
		for(ll j=0;j<(1<<n);j++){
			if(i&j)a[j]=(a[j]+f*a[j-i]%Mod)%Mod;
		}
	}
}
void FMT2(ll a[],ll n,ll f){
	for(ll i=1;i<(1<<n);i<<=1){
		for(ll j=0;j<(1<<n);j++){
			if(i&j)a[j-i]=(a[j-i]+f*a[j]%Mod)%Mod;
		}
	}
}
void FWT(ll a[],ll n,ll f){
	for(ll i=1;i<(1<<n);i<<=1){
		for(ll j=0;j<(1<<n);j++){
			if(i&j){
				ll x=a[j-i],y=a[j];
				a[j-i]=(x+y)%Mod;
				a[j]=(x-y+Mod)%Mod;
			}
		}
	}
	if(f==-1)for(ll i=0;i<(1<<n);i++)a[i]=(a[i]*Inv)%Mod;
}
ll n,a[N],b[N];
ll Ans1[N],Ans2[N],Ans3[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Inv=Pow(1<<n,Mod-2);
	for(ll i=0;i<(1<<n);i++)a[i]=read();
	for(ll i=0;i<(1<<n);i++)b[i]=read();
	
	FMT1(a,n,1);FMT1(b,n,1);
	for(ll i=0;i<(1<<n);i++)Ans1[i]=(a[i]*b[i])%Mod;
	FMT1(a,n,-1);FMT1(b,n,-1);FMT1(Ans1,n,-1);
	
	FMT2(a,n,1);FMT2(b,n,1);
	for(ll i=0;i<(1<<n);i++)Ans2[i]=(a[i]*b[i])%Mod;
	FMT2(a,n,-1);FMT2(b,n,-1);FMT2(Ans2,n,-1);
	
	FWT(a,n,1);FWT(b,n,1);
	for(ll i=0;i<(1<<n);i++)Ans3[i]=(a[i]*b[i])%Mod;
	FWT(a,n,-1);FWT(b,n,-1);FWT(Ans3,n,-1);
	
	for(ll i=0;i<(1<<n);i++)printf("%lld ",(Ans1[i]%Mod+Mod)%Mod);printf("\n");
	for(ll i=0;i<(1<<n);i++)printf("%lld ",(Ans2[i]%Mod+Mod)%Mod);printf("\n");
	for(ll i=0;i<(1<<n);i++)printf("%lld ",(Ans3[i]%Mod+Mod)%Mod);printf("\n");
	return 0;
}