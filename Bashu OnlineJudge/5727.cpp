/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=30005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n=23333,mod;
ll f[N],g[N],s[N];
inline ll Mod(ll x){return x>=mod?x-mod:x;}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%mod;
		tot=tot*tot%mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();mod=read();
	f[0]=f[1]=1;
	for(ll i=1;i<=n;i++)s[i]=1;
	for(ll i=2;i<=n;i++){
		__int128 tmp=0;
		for(ll j=0;j<i;j++)tmp+=f[j]*s[i-j];tmp%=mod;
		g[i]=tmp*Pow(i,mod-2)%mod;f[i]=Mod(g[i]*2);
		for(ll j=i;j<=n;j+=i)s[j]=Mod(s[j]+tmp);
	}
	while(T--)printf("%lld\n",f[read()]);
	return 0;
}