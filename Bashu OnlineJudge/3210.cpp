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
const ll Mod=1e9+7;
const ll N=100005;
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
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
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
ll n,m,cnt;
ll a[N],vis[N],prime[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll maxn=5e4;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	while(scanf("%lld%lld",&n,&m)!=EOF){
		memset(a,0,sizeof(a));
		for(ll i=1;i<=cnt&&prime[i]<=m;i++)a[prime[i]]=1;
		ll len=1,L=0;
		while(len<=m){len<<=1;L++;}
		Inv=Pow(len,Mod-2);
		FWT(a,L,1);
		for(ll i=0;i<len;i++)a[i]=Pow(a[i],n);
		FWT(a,L,-1);
		printf("%lld\n",a[0]);
	}
	return 0;
}