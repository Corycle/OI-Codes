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
const ll Mod=1e9+7;
const ll M=500005;
const ll N=2005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
		y>>=1;
	}
	return ans;
}
void FWT(ll a[],ll maxn,ll f){
	for(ll i=1;i<maxn;i<<=1){
		for(ll j=0;j<maxn;j++){
			if(i&j){
				ll x=a[j-i],y=a[j];
				a[j-i]=(x+y)%Mod;
				a[j]=(x-y+Mod)%Mod;
			}
		}
	}
	if(f==-1){
		ll Inv=Pow(maxn,Mod-2);
		for(ll i=0;i<maxn;i++)a[i]=a[i]*Inv%Mod;
	}
}
ll n,m,cnt;
ll ans[N],h[N],a[N],b[N],t[N],f[N][N];
struct edge{ll to,next;}d[M];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(ll x,ll fa){
	f[x][a[x]]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		for(ll j=0;j<m;j++)t[j]=f[x][j];
		FWT(f[x],m,1);FWT(f[y],m,1);
		for(ll j=0;j<m;j++)f[x][j]=f[x][j]*f[y][j]%Mod;
		FWT(f[x],m,-1);
		for(ll j=0;j<m;j++)f[x][j]=(f[x][j]+t[j])%Mod;
	}
	for(ll j=0;j<m;j++)ans[j]=(ans[j]+f[x][j])%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		n=read();m=read();
		memset(h,0,sizeof(h));cnt=0;
		for(ll i=1;i<=n;i++)a[i]=read();
		for(ll i=2;i<=n;i++){
			ll x=read(),y=read();
			Add(x,y);Add(y,x);
		}
		memset(f,0,sizeof(f));
		memset(ans,0,sizeof(ans));
		DFS(1,0);
		for(ll i=0;i<m;i++)printf("%lld ",ans[i]);
		printf("\n");
	}
	return 0;
}