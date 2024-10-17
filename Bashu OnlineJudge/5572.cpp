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
const ll Mod=924844033;
const ll N=4005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,tot;
ll fac[N],vis[N],f[N][N][2];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();fac[0]=1;
	for(ll i=1;i<=n;i++)fac[i]=fac[i-1]*i%Mod;
	for(ll i=1;i<=m;i++){
		for(ll t=2;t>=1;t--){
			for(ll j=i;j<=n;j+=m){
				tot++;
				if(j!=i)vis[tot]=1;
			}
		}
	}
	ll ans=0;
	f[0][0][0]=1;
	for(ll i=0;i<n*2;i++){
		for(ll j=0;j<=n;j++){
			f[i+1][j][0]=(f[i][j][0]+f[i][j][1])%Mod;
			if(vis[i+1])f[i+1][j+1][1]=f[i][j][0];
		}
	}
	for(ll i=0;i<=n;i++){
		ll t=i&1?-1:1;
		f[2*n][i][0]=(f[2*n][i][0]+f[2*n][i][1])%Mod*fac[n-i]%Mod;
		ans=(ans+f[2*n][i][0]*t+Mod)%Mod;
	}
	printf("%lld",ans);
	return 0;
}