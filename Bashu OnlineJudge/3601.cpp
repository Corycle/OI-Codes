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
const ll p=1000000007;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N],f[N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
ll Lagrange(ll k,ll m){
	ll ans=0;
	if(k<=m+2)f[k];
	for(ll i=1;i<=m+2;i++){
		ll t1=1,t2=1;
		for(ll j=0;j<=m+2;j++){
			if(i==j)continue;
			t1=t1*(k-j)%p;
			t2=t2*(i-j)%p;
		}
		ans=(ans+t1*f[i]%p*Pow(t2,p-2,p)%p)%p;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		ll n=read(),m=read(),ans=0;
		for(ll i=1;i<=m;i++)a[i]=read();
		sort(a+1,a+m+1);
		for(ll i=1;i<=m+2;i++)f[i]=(f[i-1]+Pow(i,m+1,p))%p;
		for(ll i=1;i<=m+1;i++){
			ans=(ans+Lagrange(n-a[i-1],m))%p;
			for(ll j=i;j<=m;j++){
				ans=(ans-Pow(a[j]-a[i-1],m+1,p)+p)%p;
			}
		}
		printf("%lld\n",(ans+p)%p);
	}
	return 0;
}