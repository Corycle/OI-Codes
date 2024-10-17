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
#define ld long double
#define ull unsigned ll
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=105;
const ll M=10;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll P[N];
ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
ll Rand(ll maxn){return (1ll*rand()*rand()+rand())%maxn+1;}
ll Multi(ll x,ll y,ll mod){return ((ull)x*y-(ull)((ld)x/mod*y)*mod+mod)%mod;}
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=Multi(ans,tot,mod);
		tot=Multi(tot,tot,mod);
		y>>=1;
	}
	return ans;
}
bool Miller_Rabin(ll n){
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	ll m=n-1,k=0;while(!(m&1)){k++;m>>=1;}
	for(ll i=1;i<=M;i++){
		ll a=Rand(n-1),x=Pow(a,m,n),y=0;
		for(ll j=1;j<=k;j++){
			y=x;x=Multi(x,x,n);
			if(x==1&&y!=1&&y!=n-1)return false;
		}
		if(x!=1)return false;
	}
	return true;
}
ll Pollard_rho(ll n,ll c){
	ll x=Rand(n-1),y=x,z=1,i=1,k=2;
	while(1){
		i++;
		x=(Multi(x,x,n)+c)%n;
		z=Multi(z,abs(y-x),n);
		if(x==y||!z)return n;
		if(i%127==0||i==k){
			ll d=gcd(z,n);
			if(d>1)return d;
			if(i==k){y=x;k<<=1;}
		}
	}
}
void Solve(ll n,ll c){
	if(n==1)return;
	if(Miller_Rabin(n)){P[++P[0]]=n;return;}
	ll p=n;while(p==n)p=Pollard_rho(n,c--);
	Solve(p,c);Solve(n/p,c);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	srand(time(NULL));
	while(T--){
		ll n=read();
		if(Miller_Rabin(n))puts("Prime");
		else{
			P[0]=0;
			Solve(n,10000007);
			sort(P+1,P+P[0]+1);
			printf("%lld\n",P[1]);
		}
	}
	return 0;
}
