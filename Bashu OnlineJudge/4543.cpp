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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	1000003 = Prime
	1019663265 = 3 x 5 x 6793 x 10007
*/
ll n,m,T,P,f[N];
struct Point{ll x,y;}p[N];
ll prime[5]={0,3,5,6793,10007};
bool cmp(Point A,Point B){
	if(A.x!=B.x)return A.x<B.x;
	return A.y<B.y;
}
struct Prime1{
	ll fac[N],inv[N];
	void Init(){
		fac[0]=inv[0]=inv[1]=1;
		for(ll i=1;i<=P;i++)fac[i]=fac[i-1]*i%P;
		for(ll i=2;i<=P;i++)inv[i]=(P-P/i)*inv[P%i]%P;
		for(ll i=1;i<=P;i++)inv[i]=inv[i]*inv[i-1]%P;
	}
	ll C(ll n,ll m){
		if(n<m)return 0;
		if(n<P&&m<P)return fac[n]*inv[m]%P*inv[n-m]%P;
		return C(n/P,m/P)*C(n%P,m%P)%P;
	}
}P1;
struct Prime2{
	ll fac[5][N],inv[5][N];
	void Init(){
		for(ll k=1;k<=4;k++){
			ll mod=prime[k];
			fac[k][0]=inv[k][0]=inv[k][1]=1;
			for(ll i=1;i<=mod;i++)fac[k][i]=fac[k][i-1]*i%mod;
			for(ll i=2;i<=mod;i++)inv[k][i]=(mod-mod/i)*inv[k][mod%i]%mod;
			for(ll i=1;i<=mod;i++)inv[k][i]=inv[k][i]*inv[k][i-1]%mod;
		}
	}
	ll C(ll k,ll n,ll m,ll mod){
		if(n<m)return 0;
		if(n<mod&&m<mod)return fac[k][n]*inv[k][m]%mod*inv[k][n-m]%mod;
		return C(k,n/mod,m/mod,mod)*C(k,n%mod,m%mod,mod)%mod;
	}
	void Exgcd(ll a,ll b,ll &x,ll &y){
		if(b==0){
			x=1,y=0;
			return;
		}
		else{
			Exgcd(b,a%b,x,y);
			ll t=x;x=y;y=t-a/b*y;
		}
	}
	ll CRT(ll n,ll m){
		ll x,y,ans=0,M=P;
		for(ll k=1;k<=4;k++){
			ll t=M/prime[k];
			Exgcd(t,prime[k],x,y);
			ans=(ans+t*x*C(k,n,m,prime[k])%M)%M;
		}
		return (ans+M)%M;
	}
}P2;
ll C(ll n,ll m){
	if(P==1000003)return P1.C(n,m);
	return P2.CRT(n,m);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	T=read();P=read();
	for(ll i=1;i<=T;i++){
		p[i].x=read();
		p[i].y=read();
	}
	p[++T]=(Point){n,m};
	sort(p+1,p+T+1,cmp);
	if(P==1000003)P1.Init();
	else P2.Init();
	for(ll i=1;i<=T;i++){
		f[i]=C(p[i].x+p[i].y,p[i].x);
		for(ll j=1;j<i;j++){
			if(p[j].x<=p[i].x&&p[j].y<=p[i].y){
				f[i]=(f[i]+P-C(p[i].x-p[j].x+p[i].y-p[j].y,p[i].x-p[j].x)*f[j]%P)%P;
			}
		}
	}
	printf("%lld",f[T]);
	return 0;
}