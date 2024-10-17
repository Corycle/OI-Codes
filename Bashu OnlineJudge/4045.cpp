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
const ll N=5000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,ll>F1,F2;
ll cnt,mu[N],phi[N],vis[N],prime[N];
void Prepare(ll maxn){
	mu[1]=phi[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){
			mu[i]=-1;
			phi[i]=i-1;
			prime[++cnt]=i;
		}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]){
				mu[i*prime[j]]=-mu[i];
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
			}
			else{
				mu[i*prime[j]]=0;
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
		}
	}
	for(ll i=1;i<=maxn;i++){
		mu[i]+=mu[i-1];
		phi[i]+=phi[i-1];
	}
}
void DFS(ll n,ll &p,ll &m){
	if(n<=5e6){
		p=phi[n];m=mu[n];
		return;
	}
	if(F1[n]||F2[n]){
		p=F1[n];m=F2[n];
		return;
	}
	p=(1+n)*n/2;m=1;
	for(ll i=2,j;i<=n;i=j+1){
		ll ans1=0,ans2=0;
		j=n/(n/i);
		DFS(n/i,ans1,ans2);
		p-=(j-i+1)*ans1;
		m-=(j-i+1)*ans2;
	}
	F1[n]=p;F2[n]=m;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	Prepare(5e6);
	while(T--){
		ll n=read();
		ll ans1=0,ans2=0;
		DFS(n,ans1,ans2);
		printf("%lld %lld\n",ans1,ans2);
	}
	return 0;
}