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
const ll mod=20101009;
const ll N=10000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt;
ll prime[N],vis[N],mu[N],g[N],sum[N];
void Prepare(){
	mu[1]=g[1]=1;
	n=10000000;
	for(ll i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			mu[i]=-1;
			g[i]=1-i;
		}
		for(ll j=1;j<=cnt;j++){
			if(i*prime[j]>n)break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				g[i*prime[j]]=g[i];
				break;
			}
			else{
				mu[i*prime[j]]=-mu[i];
				g[i*prime[j]]=g[i]*g[prime[j]]%mod;
			}
		}
	}
	for(ll i=1;i<=n;i++){
		sum[i]=(sum[i-1]+(g[i]*i)%mod)%mod;
	}
}
ll Sum(ll x){
	return ((1+x)*x/2)%mod;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	Prepare();
	n=read();m=read();
	ll ans=0,lst=0;
	for(ll i=1;i<=n;i=lst+1){
		lst=min(n/(n/i),m/(m/i));
		ans=(ans+(Sum(n/i)*Sum(m/i)%mod)*(sum[lst]-sum[i-1])%mod+mod)%mod;
	}
	printf("%d",ans);
	return 0;
}