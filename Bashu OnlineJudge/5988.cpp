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
const ll N=2e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,fac[N],inv[N];
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(ll i=2;i<=2e6;i++)fac[i]=fac[i-1]*i%Mod;
	for(ll i=2;i<=2e6;i++)inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=2e6;i++)inv[i]=inv[i-1]*inv[i]%Mod;
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
ll C(ll n,ll m){
	if(n<m)return 0;
	return fac[n]*inv[n-m]%Mod*inv[m]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll ans=0;
	n=read();m=read();Prepare();
	for(ll k=0;k<=m;k++){
		ll Mul=Pow(m-k,n);
		if(!(k&1))ans=(ans+Mul*C(m+1,k+1)%Mod)%Mod;
		else ans=(ans+Mod-Mul*C(m+1,k+1)%Mod)%Mod;
	}
	printf("%lld",ans);
	return 0;
}