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
ll Inv(ll n,ll p){
	return Pow(n,p-2,p);
}
ll p;
ll C(ll n,ll m){
	if(m>n)return 0;
	ll up=1,down=1;
	for(ll i=n-m+1;i<=n;i++)up=up*i%p;
	for(ll i=1;i<=m;i++)down=down*i%p;
	return up*Inv(down,p)%p;
}
ll Lucas(ll n,ll m){
	if(m>n)return 0;
	ll ans=1;
	while(m){
		ans=ans*C(n%p,m%p)%p;
		n/=p;m/=p;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll Case=read();
	while(Case--){
		ll n=read(),m=read();p=read();
		printf("%lld\n",Lucas(n,m));
	}
	return 0;
}