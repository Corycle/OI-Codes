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
const ll N=10005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
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
void Exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1;y=0;}
	else{
		Exgcd(b,a%b,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
ll Inv(ll n,ll p){//n和 p不一定互质 
	if(!n)return 0;
	ll a=n,b=p,x=0,y=0;
	Exgcd(a,b,x,y);
	x=(x%p+p)%p;
	return x;
}
ll Multi(ll n,ll pi,ll pk){//n! %pk
	if(!n)return 1;
	ll ans=1;
	if(n/pk){//n>=pk
		for(ll i=2;i<=pk;i++){
			if(i%pi)ans=ans*i%pk;
		}
		ans=Pow(ans,n/pk,pk);
	}
	for(ll i=2;i<=n%pk;i++){
		if(i%pi)ans=ans*i%pk;
	}
	return ans*Multi(n/pi,pi,pk)%pk;
}
ll C(ll n,ll m,ll mod,ll pi,ll pk){
	if(m>n)return 0;
	ll k=0;//ans≡C(n,m)(mod pk)
	ll a=Multi(n,pi,pk);
	ll b=Multi(m,pi,pk);
	ll c=Multi(n-m,pi,pk);
	for(ll i=n;i;i/=pi)k+=i/pi;
	for(ll i=m;i;i/=pi)k-=i/pi;
	for(ll i=n-m;i;i/=pi)k-=i/pi;
	ll ans=a*Inv(b,pk)%pk*Inv(c,pk)%pk*Pow(pi,k,pk)%pk;
	return ans*(mod/pk)%mod*Inv(mod/pk,pk)%mod;//中国剩余定理 
}
ll Exlucas(ll n,ll m,ll p){
	ll x=p,ans=0;
	for(ll i=2;i<=p;i++){//中国剩余定理 
		if(x%i==0){
			ll pk=1;
			while(x%i==0){pk*=i;x/=i;}
			ans=(ans+C(n,m,p,i,pk))%p;
			if(x==1)break;
		}
	}
	return ans;
}
ll w[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll n=read(),m=read(),p=read();
	printf("%lld",Exlucas(n,m,p));
	return 0;
}