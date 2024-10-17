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
const ll P=998244353;
const ll N=30005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,tot;
ll f[N],fac[N],inv[N];
ll C(ll n,ll m){
	if(n<m)return 0;
	return fac[n]*inv[m]%P*inv[n-m]%P;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(ll i=2;i<=3e4;i++)fac[i]=fac[i-1]*i%P;
	for(ll i=2;i<=3e4;i++)inv[i]=inv[P%i]*(P-P/i)%P;
	for(ll i=2;i<=3e4;i++)inv[i]=inv[i-1]*inv[i]%P;
	n=read();f[0]=1;
	for(ll i=1;i<=n;i++){
		ll a=read(),b=read();
		tot+=3;
		for(ll j=tot;j>=2;j--){
			f[j]=((f[j]+f[j-2]*(a-b+1)%P)%P+f[j-1]*(a+b-2)%P+P)%P;
		}
		f[1]=(f[1]+f[0]*(a+b-2)%P+P)%P;
	}
	ll T=read();
	while(T--){
		m=read();ll ans=0;
		for(ll j=0;j<=m;j++){
			ans=(ans+C(3*n+j-1,j)*f[m-j]%P+P)%P;
		}
		printf("%lld\n",ans);
	}
	return 0;
}