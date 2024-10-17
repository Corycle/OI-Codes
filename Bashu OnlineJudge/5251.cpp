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
const ll Mod=998244353;
const ll N=2005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
ll X[N],Y[N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
ll Inv(ll x,ll p){
	return Pow(x,p-2,p);
}
ll Lagrange(ll k){
	ll ans=0;
	for(ll i=1;i<=n;i++){
		ll t1=1,t2=1;
		for(ll j=1;j<=n;j++){
			if(i==j)continue;
			t1=t1*(k-X[j])%Mod;
			t2=t2*(X[i]-X[j])%Mod;
		}
		ans=(ans+t1*Y[i]%Mod*Inv(t2,Mod)%Mod)%Mod;
	}
	return (ans+Mod)%Mod;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		X[i]=read();
		Y[i]=read();
	}
	printf("%lld",Lagrange(m));
	return 0;
}