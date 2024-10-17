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
const int inf=0x3f3f3f3f;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,X,tot,cnt1,cnt2,num[N],p1[N],p2[N];
ll Multi(ll x,ll y,ll mod){return ((ull)x*y-(ull)((ld)x/mod*y)*mod+mod)%mod;}
ll Pow(ll x,ll y,ll mod){ll ans=1;x%=mod;while(y){if(y&1)ans=Multi(ans,x,mod);x=Multi(x,x,mod);y>>=1;}return ans;}
void Divide(ll n){for(ll i=1;i*i<=n;i++)if(n%i==0){num[++tot]=i;if(i*i!=n)num[++tot]=n/i;};sort(num+1,num+tot+1);}
void GetPrime(ll n,ll p[],ll &tot){for(ll i=2;i*i<=n;i++)if(n%i==0){p[++tot]=i;while(n%i==0)n/=i;}if(n!=1)p[++tot]=n;}
ll Phi(ll n){ll phi=n;for(int i=1;i<=cnt1;i++)if(n%p1[i]==0)phi=phi/p1[i]*(p1[i]-1);return phi;}
ll Solve(ll n){
	ll phi=Phi(n),ans=0;
	if(phi!=1)GetPrime(phi,p2,cnt2);
	for(int i=1;i<=tot;i++){
		ll F=Phi(num[i]),L=F;
		for(int j=1;j<=cnt2;j++){
			while(L%p2[j]==0&&Pow(X,L/p2[j],num[i])==1)L/=p2[j];
		}
		ans+=F/L;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();X=read();Divide(n);GetPrime(n,p1,cnt1);printf("%lld",Solve(n));
	return 0;
}
/* "https://blog.csdn.net/qq_34454069/article/details/82963027" */
