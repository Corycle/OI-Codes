#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
const ll Mod=1e9+1;
const ll M=1e5+5;
const ll N=20;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,ans=1;
ll a[N][N],b[N],p[N],vis[M],f[N][M];
ll Ask(ll x){
	a[1][1]=x;
	for(ll i=2;i<=18;i++){
		if(a[i-1][1]*2<=n)a[i][1]=a[i-1][1]*2;
		else a[i][1]=n+1;
	}
	for(ll i=1;i<=18;i++){
		for(ll j=2;j<=11;j++){
			if(a[i][j-1]*3<=n)a[i][j]=a[i][j-1]*3;
			else a[i][j]=n+1;
		}
	}
	memset(b,0,sizeof(b));
	for(ll i=1;i<=18;i++){
		for(ll j=1;j<=11;j++){
			if(a[i][j]<=n){
				b[i]+=p[j-1];
				vis[a[i][j]]=1;
			}
		}
	}
	for(ll i=0;i<=18;i++){
		for(ll j=0;j<=b[i];j++){
			f[i][j]=0;
		}
	}
	f[0][0]=1;
	for(ll i=0;i<18;i++){
		for(ll x=0;x<=b[i];x++){
			if(f[i][x]){
				for(ll y=0;y<=b[i+1];y++){
					if(!(x&y)&&!(y&(y>>1))){
						f[i+1][y]=(f[i][x]+f[i+1][y])%Mod;
					}
				}
			}
		}
	}
	return f[18][0];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();p[0]=1;
	for(ll i=1;i<=19;i++)p[i]=p[i-1]<<1;
	for(ll i=1;i<=n;i++){
		if(!vis[i])ans=(ans*Ask(i))%Mod;
	}
	printf("%lld",ans);
	return 0;
}