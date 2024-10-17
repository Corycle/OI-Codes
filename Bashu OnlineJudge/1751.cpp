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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Mod,a[N],b[N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
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
ll C(ll n,ll m){
	if(m>n)return 0;
	return a[n]*b[m]%Mod*b[n-m]%Mod;
}
ll Lucas(ll n,ll m){
	if(m>n)return 0;
	ll ans=1;
	while(m){
		ans=ans*C(n%Mod,m%Mod)%Mod;
		n/=Mod;m/=Mod;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	a[0]=1;
	ll sx,sy,fx,fy;
	while(scanf("%lld%lld%lld%lld%lld",&sx,&sy,&fx,&fy,&Mod)!=EOF){
		ll ans=0,num=max(fx,fy)+1;
		b[0]=Inv(a[0],Mod);
		for(ll i=1;i<=num;i++){
			a[i]=a[i-1]*i%Mod;
			b[i]=Inv(a[i],Mod);
		}
		for(ll i=sy;i<=fy;i++){
			ans+=Lucas(fx+1,i+1);
			ans-=Lucas(sx,i+1);
			ans=(ans%Mod+Mod)%Mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}