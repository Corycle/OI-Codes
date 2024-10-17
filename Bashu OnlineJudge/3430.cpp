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
const ll N=10000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll prime[N],mu[N],vis[N],cnt,sum[N]; 
void Prepare(){
	mu[1]=1;
	ll n=10000000;
	for(ll i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			mu[i]=-1;
		}
		for(ll j=1;j<=cnt;j++){
			if(i*prime[j]>n)break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			else mu[i*prime[j]]=-mu[i];
		}
	}
	for(ll j=1;j<=cnt;j++){
		for(ll i=1;i*prime[j]<=n;i++){
			sum[i*prime[j]]+=mu[i];
		}
	}
	for(ll i=1;i<=n;i++){
		sum[i]+=sum[i-1];
	}
}
ll Ask(ll n,ll m){
	if(n>m)swap(n,m);
	ll ans=0,lst=0;
	for(ll i=1;i<=n;i=lst+1){
		lst=min(n/(n/i),m/(m/i));
		ans+=(n/i)*(m/i)*(sum[lst]-sum[i-1]);
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	Prepare();
	int T=read();
	while(T--){
		ll n=read(),m=read();
		printf("%lld\n",Ask(n,m));
	}
	return 0;
}