#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=999911658;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	求：G^ (∑(d|n) C(n,d) ) mod 999911659
	
	999911659-1=999911658
	ans=G^ (∑(d|n) C(n,d) %999911658) mod 999911659
	
	999911658=2*3*4679*35617
	x ≡a1(mod 2)
	x ≡a2(mod 3)
	x ≡a3(mod 4679)
	x ≡a4(mod 35617)
	
*/
ll fact[N];
ll m[10]={0,2,3,4679,35617},a[10];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x%mod;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
ll Inv(ll n,ll p){
	return Pow(n,p-2,p);
}
void Exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1;y=0;}
	else{
		Exgcd(b,a%b,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
void Prepare(ll n,ll p){
	fact[0]=1;
	for(ll i=1;i<=m[4];i++){
		fact[i]=fact[i-1]*i%p;
	}
}
ll C(ll n,ll m,ll p){
	if(m>n)return 0;
	return fact[n]*Inv(fact[m],p)%p*Inv(fact[n-m],p)%p;
}
ll Lucas(ll n,ll m,ll p){
	if(m>n)return 0;
	ll ans=1;
	while(m){
		ans=ans*C(n%p,m%p,p)%p;
		n/=p;m/=p;
	}
	return ans;
}
ll Solve(int n){//中国剩余定理 
	ll Ans=0;
	for(ll i=1;i<=n;i++){
		ll Mi=Mod/m[i];
		ll x=0,y=0;
		Exgcd(Mi,m[i],x,y);
		Ans=(Ans+Mi*x*a[i])%Mod;
	}
	return (Ans+Mod)%Mod;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll n=read(),g=read();
	if(g%(Mod+1)==0){
		printf("0");
		return 0;
	}
	for(ll k=1;k<=4;k++){
		Prepare(n,m[k]);
		for(ll i=1;i*i<=n;i++){
			if(n%i==0){
				a[k]=(a[k]+Lucas(n,i,m[k]))%m[k];
				if(i*i!=n)a[k]=(a[k]+Lucas(n,n/i,m[k]))%m[k];
			}
		}
	}
	ll ans=Pow(g,Solve(4),Mod+1);
	printf("%lld",ans);
	return 0;
}