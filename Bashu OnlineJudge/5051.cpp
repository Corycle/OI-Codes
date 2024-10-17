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
const ll Mod=1e9+7;
const ll M=3e5+5;
const ll N=20;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,Sta;
ll g[N][N],f[M],p[M],c[M],way[M],sum[M];
ll lowbit(ll x){
	return x&(-x);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read();
		g[x-1][y-1]=1;
	}
	Sta=(1<<n)-1;
	p[0]=1;
	for(ll i=1;i<=m;i++){
		p[i]=(p[i-1]<<1)%Mod;
	}
	c[0]=-1;
	for(ll i=1;i<=Sta;i++){
		c[i]=c[i>>1];
		if(i&1)c[i]=-c[i];
	}
	f[0]=1;
	for(ll S=0;S<Sta;S++){
		for(ll i=0;i<n;i++)way[1<<i]=0;
		for(ll i=0;i<n;i++){
			if((S>>i)&1){
				for(ll j=0;j<n;j++){
					way[1<<j]+=g[i][j];
				}
			}
		}
		ll sta=Sta^S;sum[0]=0;
		for(ll T=(sta-1)&sta;;T=(T-1)&sta){
			ll k=sta^T;
			sum[k]=sum[k-lowbit(k)]+way[lowbit(k)];
			f[S^k]=(f[S^k]+f[S]*p[sum[k]]%Mod*c[k]%Mod+Mod)%Mod;
			if(!T)break;
		}
	}
	printf("%lld",f[Sta]);
	return 0;
}