/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=1953130;
const ll Mod=1e9;
const ll p5=1953125;
const ll p2=512;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a,b;
ll f2[N],f5[N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%mod;
		tot=1ll*tot*tot%mod;
		y>>=1;
	}
	return ans;
}
void Exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1;y=0;}
	else{
		Exgcd(b,a%b,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
ll Inv(ll n,ll p){
	if(!n)return 0;
	ll x=0,y=0;
	Exgcd(n,p,x,y);
	return (x%p+p)%p;
}
ll Multi(ll n,ll pi,ll pk){//n! mod pk
	if(!n)return 1;
	if(pi==2)return 1ll*Multi(n/pi,pi,pk)*f2[n%pk]%pk*Pow(f2[pk],n/pk,pk)%pk;
	if(pi==5)return 1ll*Multi(n/pi,pi,pk)*f5[n%pk]%pk*Pow(f5[pk],n/pk,pk)%pk;
	return -1;
}
ll C(ll n,ll m,ll pi,ll pk){//C(n,m) mod pk
	if(n<m)return 0;
	ll k=0;
	for(ll i=n;i;i/=pi)k+=i/pi;
	for(ll i=m;i;i/=pi)k-=i/pi;
	for(ll i=n-m;i;i/=pi)k-=i/pi;
	if(k>=9)return 0;
	ll a=Multi(n,pi,pk);
	ll b=Multi(m,pi,pk);
	ll c=Multi(n-m,pi,pk);
	return 1ll*a*Inv(b,pk)%pk*Inv(c,pk)%pk*Pow(pi,k,pk)%pk;
}
int p,Ans2,Ans5,c[105];
void Exlucas(ll n,ll m){//CRT Merge Lucas
	Ans2=(Ans2+C(n,m,2,p2))%p2;
	Ans5=(Ans5+C(n,m,5,p5))%p5;
}
void Print(ll Ans,ll p){
	for(ll i=0;i<=p;i++){c[i]=Ans%10;Ans/=10;}
	for(ll i=p-1;i>=0;i--)printf("%d",c[i]);
	printf("\n");
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	f2[0]=f5[0]=1;
	for(ll i=1;i<=p2;i++){f2[i]=f2[i-1];if(i%2)f2[i]=1ll*f2[i]*i%p2;}
	for(ll i=1;i<=p5;i++){f5[i]=f5[i-1];if(i%5)f5[i]=1ll*f5[i]*i%p5;}
	while(scanf("%lld%lld%d",&a,&b,&p)!=EOF){
		Ans2=Ans5=0;
		if(a==b){
			Exlucas(2*a-1,a);
			Ans2=1ll*Ans2*(Mod/p2)%Mod*Inv(Mod/p2,p2)%Mod;
			Ans5=1ll*Ans5*(Mod/p5)%Mod*Inv(Mod/p5,p5)%Mod;
			ll Ans=(Pow(2,a+b-1,Mod)-(Ans2+Ans5)%Mod)%Mod;
			Ans=(Ans%Mod+Mod)%Mod;
			Print(Ans,p);
		}
		else{
			ll num=a-b-1;
			for(ll i=1;i<=num/2;i++)Exlucas(a+b,b+i);
			if(num&1)Exlucas(a+b-1,b+num/2);
			Ans2=1ll*Ans2*(Mod/p2)%Mod*Inv(Mod/p2,p2)%Mod;
			Ans5=1ll*Ans5*(Mod/p5)%Mod*Inv(Mod/p5,p5)%Mod;
			ll Ans=(Pow(2,a+b-1,Mod)+(Ans2+Ans5)%Mod)%Mod;
			Print(Ans,p);
		}
	}
	return 0;
}