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
const ll Mod=1000000007;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,ans=1;
ll a[N],inv[N],f[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		ans=ans*a[i]%Mod;
	}
	f[0]=1;
	for(ll i=1;i<=n;i++){
		for(ll j=i;j>=1;j--){
			f[j]=(f[j]*a[i]%Mod-f[j-1]+Mod)%Mod;
		}
		f[0]=f[0]*a[i]%Mod;
	}
	inv[0]=inv[1]=1;
	for(ll i=2;i<=n;i++)inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
	ll t=1,tmp=1;
	for(ll i=0;i<=min(n,m);i++){
		ans=(ans-f[i]*t%Mod*tmp%Mod)%Mod;
		t=t*inv[n]%Mod;tmp=tmp*(m-i)%Mod;
	}
	printf("%lld",(ans%Mod+Mod)%Mod);
	return 0;
}