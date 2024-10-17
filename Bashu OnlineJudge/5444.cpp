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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt,tot,Sqr,Lim;
ll w[N],vis[N],prime[N];
ll id1[N],id2[N],g[N],h[N];
ll Num(ll x){
	return x<=Sqr?id1[x]:id2[n/x];
}
void Prepare(ll maxn){
	for(ll i=2;i<=maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	Lim=cnt;
}
ll S(ll x,ll y){
	ll k=Num(x);
	if(x<=1||prime[y]>x)return 0;
	ll ans=g[k]+h[k]-(y-1)*4;
	for(ll j=y;j<=cnt&&prime[j]*prime[j]<=x;j++){
		ll tmp=prime[j];
		for(ll e=1;tmp*prime[j]<=x;e++){
			ans+=S(x/tmp,j+1)*(e*3+1)+(e+1)*3+1;
			tmp*=prime[j];
		}
	}
	return ans;
}
ll Solve(){
	Sqr=sqrt(n);tot=0;
	cnt=upper_bound(prime+1,prime+Lim+1,Sqr)-prime-1;
	for(ll i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		w[++tot]=n/i;
		if(w[tot]<=Sqr)id1[w[tot]]=tot;
		else id2[n/w[tot]]=tot;
		g[tot]=(w[tot]-1)*3;
		h[tot]=(w[tot]-1);
	}
	for(ll j=1;j<=cnt;j++){
		for(ll i=1;i<=tot&&prime[j]*prime[j]<=w[i];i++){
			ll k=Num(w[i]/prime[j]);
			g[i]-=g[k]-(j-1)*3;
			h[i]-=h[k]-(j-1);
		}
	}
	return S(n,1)+1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(1e6);
	ll T=read();
	while(T--){
		n=read();
		printf("%lld\n",Solve());
	}
	return 0;
}