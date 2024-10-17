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
const ll Inv2=500000004;
const ll Mod=1000000007;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt,tot,Sqr;
ll w[N],f[N],g[N],h[N];
ll id1[N],id2[N],vis[N],prime[N];
ll Num(ll x){
	return x<=Sqr?id1[x]:id2[n/x];
}
void Prepare(){
	for(ll i=2;i<=Sqr;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			f[cnt]=(f[cnt-1]+i)%Mod;
		}
		for(ll j=1;j<=cnt&&i*prime[j]<=Sqr;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
ll S(ll x,ll y){
	ll k=Num(x);
	if(x<=1||prime[y]>x)return 0;
	ll ans=(g[k]-f[y-1]-h[k]+y-1)%Mod;
	if(y==1)ans+=2;
	for(ll j=y;j<=cnt&&prime[j]*prime[j]<=x;j++){
		ll t1=prime[j],t2=prime[j]*prime[j];
		for(ll e=1;t2<=x;e++){
			ans=(ans+S(x/t1,j+1)*(prime[j]^e)%Mod+(prime[j]^(e+1))%Mod)%Mod;
			t1=t2;t2*=prime[j];
		}
	}
	return ans;
}
ll Solve(){
	Sqr=sqrt(n);Prepare();
	for(ll i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		w[++tot]=n/i;
		if(w[tot]<=Sqr)id1[w[tot]]=tot;
		else id2[n/w[tot]]=tot;
		g[tot]=((w[tot]+2)%Mod)*((w[tot]-1)%Mod)%Mod*Inv2%Mod;
		h[tot]=(w[tot]-1)%Mod;
	}
	for(ll j=1;j<=cnt;j++){
		for(ll i=1;i<=tot&&prime[j]*prime[j]<=w[i];i++){
			ll k=Num(w[i]/prime[j]);
			g[i]=(g[i]-prime[j]*(g[k]-f[j-1])%Mod+Mod)%Mod;
			h[i]=(h[i]-h[k]+j-1)%Mod;
		}
	}
	return S(n,1)+1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	printf("%lld",(Solve()+Mod)%Mod);
	return 0;
}