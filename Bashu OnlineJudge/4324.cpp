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
const ll mod=1e9+7;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	考虑将上下界都除以K，问题就转化为了求L/K---->R/K中选N个数，其gcd为1的方案数
	f[i]表示gcd=i的方案数
*/
ll f[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x%mod;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y/=2;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll n=read(),m=read();
	ll l=read(),r=read();
	ll flag=(l<=m&&m<=r);
	l=(l-1)/m;r=r/m;
	ll maxx=r-l;
	for(ll i=maxx;i>=1;i--){
		ll a=l/i,b=r/i;
		ll t=b-a;
		f[i]=(Pow(t,n)-t+mod)%mod;
		for(ll j=i*2;j<=maxx;j+=i){
			f[i]=(f[i]-f[j]+mod)%mod;
		}
	}
	printf("%lld",(f[1]+flag)%mod);
	return 0;
}