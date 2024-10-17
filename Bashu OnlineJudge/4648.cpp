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
const ll Mod=1e9+7;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll inv[N],fac[N],D[N];
void Prepare(ll n){
	inv[0]=inv[1]=fac[0]=fac[1]=1;
	for(ll i=2;i<=n;i++)fac[i]=fac[i-1]*i%Mod;
	for(ll i=2;i<=n;i++)inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=n;i++)inv[i]=inv[i-1]*inv[i]%Mod;
	D[1]=0;D[2]=1;D[3]=2;
	for(ll i=4;i<=n;i++)D[i]=(D[i-1]+D[i-2])%Mod*(i-1)%Mod;
}
ll C(ll n,ll m){
	if(n<m)return 0;
	return fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(1e6);
	ll T=read();
	while(T--){
		ll n=read(),m=read();
		if(n-m==1)printf("0\n");
		else if(n==m)printf("1\n");
		else if(!m)printf("%lld\n",D[n]);
		else printf("%lld\n",C(n,m)*D[n-m]%Mod);
	}
	return 0;
}