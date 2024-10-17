#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const ll P=998244353;
const ll N=7000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll cnt,f[N],F[N],sum[N],vis[N],prime[N];
ll Sum(ll n){
	return (1+n)*n/2%P;
}
ll G(ll n,ll m){
	return (Sum(n)*Sum(m)%P*2%P+sum[n]*m%P+sum[m]*n%P)%P;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	f[1]=1;
	ll maxn=7000000;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			f[i]=i*i%P*(i-1)%P;
		}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])f[i*prime[j]]=f[i]*f[prime[j]]%P;
			else{
				int x=i,num=1,p=prime[j];
				while(num<=2&&x%prime[j]==0){x/=prime[j];num++;}
				if(num<=2)f[i*p]=-f[x]*p%P*p%P*p%P*p%P*p%P;
				else f[i*p]=0;
				break;
			}
		}
	}
	for(ll i=1;i<=maxn;i++){
		F[i]=(F[i-1]+f[i])%P;
		sum[i]=(sum[i-1]+i*i%P)%P;
	}
	int T=read();
	while(T--){
		int n=read(),m=read();
		ll Min=min(n,m),lst=0,ans=0;
		for(int i=1;i<=Min;i=lst+1){
			lst=min(n/(n/i),m/(m/i));
			ans=(ans+G(n/i,m/i)*(F[lst]-F[i-1])%P)%P;
		}
		printf("%lld\n",(ans%P+P)%P);
	}
	return 0;
}