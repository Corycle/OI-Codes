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
const ll N=5005;
const ll L=12;
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
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
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
ll phi(ll n){
	ll ans=n;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0)ans=ans/i*(i-1);
		while(n%i==0)n/=i;
	}
	if(n>1)ans=ans/n*(n-1);
	return ans;
}
ll ans[N],tot[N];
void Multi(ll A[],ll B[]){
	for(ll i=0;i<(1<<L);i++){
		A[i]=A[i]*B[i]%Mod;
	}
}
void Solve(ll x[],ll y){
	memset(ans,0,sizeof(ans));
	memcpy(tot,x,sizeof(tot));
	ans[0]=1;
	FWT(ans,L,1);FWT(tot,L,1);
	while(y){
		if(y&1)Multi(ans,tot);
		Multi(tot,tot);
		y>>=1;
	}
	FWT(ans,L,-1);
}
ll n,m,Ans,a[N];
int main(){
//	freopen("fire.in","r",stdin);
//	freopen("fire.out","w",stdout);
	n=read();m=read();
	Inv=Pow(1<<L,Mod-2);
	for(ll i=1;i<=m;i++)a[read()]=1;
	for(ll i=1;i*i<=n;i++){
		if(n%i==0){
			ll x=i,y=n/i;
			if(y&1)Solve(a,x);
			else ans[0]=Pow(m,x);
			Ans=(Ans+ans[0]*phi(y)%Mod)%Mod;
			if(x!=y){
				if(x&1)Solve(a,y);
				else ans[0]=Pow(m,y);
				Ans=(Ans+ans[0]*phi(x)%Mod)%Mod;
			}
		}
	}
	printf("%lld",Ans*Pow(n,Mod-2)%Mod);
	return 0;
}