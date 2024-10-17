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
ll g[N],f[N],id1[N],id2[N];
ll Num(ll x){
	return x<=Sqr?id1[x]:id2[n/x];
}
void Prepare(ll maxn){
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			f[cnt]=f[cnt-1]+i;
		}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	Lim=cnt;
}
ll Solve(ll maxn){
	ll ans=0;tot=0;n=maxn;Sqr=sqrt(n);
	cnt=upper_bound(prime+1,prime+Lim+1,Sqr)-prime-1;
	for(ll i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		w[++tot]=n/i;
		if(w[tot]<=Sqr)id1[w[tot]]=tot;
		else id2[n/w[tot]]=tot;
		g[tot]=(w[tot]+2)*(w[tot]-1)/2;
	}
	for(ll j=1;j<=cnt;j++){
		for(ll i=1;i<=tot&&prime[j]*prime[j]<=w[i];i++){
			ll k=Num(w[i]/prime[j]);
			ll dlt=g[k]-f[j-1];
			g[i]-=prime[j]*dlt;
			if(i==1)ans+=dlt;
		}
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(1e6);
	ll l=read(),r=read();
	ll ans=Solve(r)-Solve(l-1);
	printf ("%lld\n",ans);
	return 0;
}