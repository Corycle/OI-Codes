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
const ll mod=100000009;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt;
ll prime[N],vis[N],mu[N],phi[N],sum[N],ans[N];
void Prepare(){
	n=1000000;
	mu[1]=phi[1]=1;
	for(ll i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			mu[i]=-1;
			phi[i]=i-1;
		}
		for(ll j=1;j<=cnt;j++){
			if(i*prime[j]>n)break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else{
				mu[i*prime[j]]=-mu[i];
				phi[i*prime[j]]=phi[i]*phi[prime[j]];
			}
		}
	}
	for(ll i=2;i<=n;i++){
		for(ll j=i;j<=n;j+=i){
			ans[j]+=phi[i]*i/2;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	Prepare();
	ll T=read();
	while(T--){
		n=read();
		printf("%lld\n",ans[n]*n+n);
	}
	return 0;
}