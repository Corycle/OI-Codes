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
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll prime[N],vis[N],mu[N],sum[N],cnt;
void Prepare(){
	ll n=100000;
	mu[1]=1;
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
	for(ll i=1;i<=n;i++){
		for(ll j=i;j<=n;j+=i){
			sum[j]+=i*mu[j/i];
		}
	}
	for(int i=1;i<=n;i++)sum[i]+=sum[i-1];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	Prepare();
	ll n=read(),m=read();
	ll lst=0,ans=0;
	for(ll i=1;i<=min(n,m);i=lst+1){
		lst=min(n/(n/i),m/(m/i));
		ans+=(ll)(n/i)*(ll)(m/i)*(sum[lst]-sum[i-1]);
	}
	ans=2*ans-n*m;
	printf("%lld",ans);
	return 0;
}
