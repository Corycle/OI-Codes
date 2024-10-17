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
const ll M=2e9;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll prime[N],mu[N],vis[N],cnt; 
void Prepare(){
	mu[1]=1;
	for(ll i=2;i<=100000;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			mu[i]=-1;
		}
		for(ll j=1;j<=cnt;j++){
			if(i*prime[j]>100000)break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			else mu[i*prime[j]]=-mu[i];
		}
	}
}
ll Ask(ll x){
	ll ans=0;
	for(ll i=1;i<=sqrt(x);i++){
		ans+=mu[i]*(x/(i*i));
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	Prepare();
	int T=read();
	while(T--){
		ll x=read();
		ll l=1,r=M,ans=0;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(Ask(mid)>=x){
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		printf("%lld\n",ans);
	} 
	return 0;
}