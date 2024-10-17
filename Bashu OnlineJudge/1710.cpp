#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,p,f[N][N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
ll Inv(ll x,ll mod){
	return Pow(x,mod-2,mod);
}
ll Lagrange(ll k){
	ll ans=0;
	for(ll i=0;i<=n*2;i++){
		ll t1=1,t2=1;
		for(ll j=0;j<=n*2;j++){
			if(i==j)continue;
			t1=t1*(k-j)%p;
			t2=t2*(i-j)%p;
		}
		ans=(ans+t1*f[i][n]%p*Inv(t2,p)%p)%p;
	}
	return (ans+p)%p;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	m=read();n=read();p=read();
	f[0][0]=1;
	for(ll i=1;i<=n*2;i++){
		for(ll j=0;j<=n;j++){
			if(!j)f[i][j]=f[i-1][j];
			else f[i][j]=(f[i-1][j]+f[i-1][j-1]*i%p*j%p)%p;
		}
	}
	if(m<=n*2)printf("%lld",f[m][n]);
	else printf("%lld",Lagrange(m));
	return 0;
}
/*
	参考： 
	https://blog.csdn.net/ez_yww/article/details/77221338
*/