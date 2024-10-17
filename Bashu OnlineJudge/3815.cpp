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
ll n,Sqr,cnt,tot;
ll w[N],id1[N],id2[N];
ll g[N],vis[N],prime[N];
ll Num(ll x){
	return x<=Sqr?id1[x]:id2[n/x];
}
void Prepare(){
	for(ll i=2;i<=Sqr;i++){
		if(!vis[i])prime[++cnt]=i;
		for(ll j=1;j<=cnt&&i*prime[j]<=Sqr;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
ll Solve(){
	Sqr=sqrt(n);Prepare();
	for(ll i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		w[++tot]=n/i;
		if(w[tot]<=Sqr)id1[w[tot]]=tot;
		else id2[n/w[tot]]=tot;
		g[tot]=w[tot]-1;
	}
	for(ll j=1;j<=cnt;j++){
		for(ll i=1;i<=tot&&prime[j]*prime[j]<=w[i];i++){
			int k=Num(w[i]/prime[j]);
			g[i]=g[i]-g[k]+j-1;
		}
	}
	return g[1];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	printf("%lld",Solve());
	return 0;
}