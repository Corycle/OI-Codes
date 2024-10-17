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
const ll N=5000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,ll>F;
ll p,cnt,Inv2,Inv6;
ll phi[N],vis[N],prime[N];
ll Sum1(ll n){n%=p;return n*(n+1)%p*Inv2%p;}
ll Sum2(ll n){n%=p;return n*(n+1)%p*Inv6%p*(n+n+1)%p;}
ll Pow(ll x,ll y){
	ll ans=1,tot=x%p;
	while(y){
		if(y&1)ans=(ans*tot)%p;
		tot=(tot*tot)%p;
		y>>=1;
	}
	return ans;
}
void Prepare(ll maxn){
	phi[1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){
			phi[i]=i-1;
			prime[++cnt]=i;
		}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]){
				phi[i*prime[j]]=phi[i]*phi[prime[j]];
			}
			else{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
		}
	}
	for(ll i=1;i<=maxn;i++){
		phi[i]=(phi[i-1]+phi[i]*i%p*i%p)%p;
	}
}
int DFS(ll n){
	if(n<=5e6)return phi[n];
	if(F[n])return F[n];
	ll ans=Sum1(n)*Sum1(n)%p;
	for(ll i=2,j;i<=n;i=j+1){
		j=n/(n/i);
		ll sum=(Sum2(j)-Sum2(i-1))%p;
		ans-=sum*DFS(n/i)%p;
	}
	return F[n]=(ans+p)%p;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	p=read();
	Inv2=Pow(2,p-2);
	Inv6=Pow(6,p-2);
	ll n=read(),ans=0;
	Prepare(5e6);
	for(ll i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		ll sum1=Sum1(n/i)*Sum1(n/i)%p;
		ll sum2=(DFS(j)-DFS(i-1)+p)%p;
		ans=(ans+sum1*sum2)%p;
	}
	printf("%lld",ans);
	return 0;
}