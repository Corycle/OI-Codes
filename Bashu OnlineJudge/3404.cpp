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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[N],fact[N],inv[N],maxbit[N];
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
ll C(ll n,ll m,ll p){
	if(m>n)return 0;
	return fact[n]*inv[m]%p*inv[n-m]%p;
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
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll n=read(),p=read();
	fact[0]=1;maxbit[0]=-1;
	for(ll i=1;i<=n;i++){
		fact[i]=fact[i-1]*i%p;
		maxbit[i]=maxbit[i>>1]+1;
	}
	inv[n]=Inv(fact[n],p);
	for(int i=n-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%p;
	}
	ll l=1,r=1;
	f[1]=f[2]=1;f[3]=2;
	for(ll i=4;i<=n;i++){
		if(i-(1<<maxbit[i])+1<=(1<<(maxbit[i]-1)))l++;
		else r++;
		f[i]=C(i-1,l,p)*f[l]%p*f[r]%p;
	}
	printf("%lld\n",f[n]);
	return 0;
}