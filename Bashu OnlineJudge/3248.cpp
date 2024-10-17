/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
const ll M=10005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt,Ans;
ll sum[M],tim[M],pos[N],vis[N],prime[N];
void Prepare(ll maxn){
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;pos[i]=cnt;}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
void Divide(ll x,ll num,ll Tim){
	for(ll i=2;i*i<=x;i++){
		if(x%i==0){
			ll tot=0;
			while(x%i==0){
				x/=i;tot++;
			}
			sum[pos[i]]+=tot*num;
			tim[pos[i]]=min(tim[pos[i]],Tim+1);
		}
	}
	if(x!=1){
		sum[pos[x]]+=num;
		tim[pos[x]]=min(tim[pos[x]],Tim+1);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	Prepare(1e5);
	while(T--){
		n=read();Ans=0;
		memset(sum,0,sizeof(sum));
		memset(tim,0x3f,sizeof(tim));
		for(ll i=1;i<=n;i++){
			ll p=read(),q=read();
			sum[pos[p]]+=q;
			tim[pos[p]]=0;
		}
		for(ll i=cnt;i>=1;i--){
			if(sum[i]){
				Ans=max(Ans,sum[i]+tim[i]);
				Divide(prime[i]-1,sum[i],tim[i]);
			}
		}
		printf("%lld\n",Ans);
	}
	return 0;
}