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
const ll P=998244353;
const ll N=500005;
const ll M=55;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll maxn,maxk,q,cnt;
ll f[N][M],prime[N],vis[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%P;
		tot=(tot*tot)%P;
		y>>=1;
	}
	return ans;
}
void Multi(ll a[],ll b[],ll c[]){
	c[0]=a[0]+b[0]-1;
	for(ll i=1;i<=a[0];i++){
		for(ll j=1;j<=b[0];j++){
			c[i+j-1]=(c[i+j-1]+a[i]*b[j]%P)%P;
		}
	}
}
void Add(ll a[],ll b[]){
	a[0]=max(a[0],b[0]);
	for(ll i=1;i<=a[0];i++){
		a[i]=(a[i]+b[i])%P;
	}
}
ll Ask(ll a[],ll b[],ll k){
	ll tmp=1,ans=0;
	for(ll i=1;i<=b[0];i++){
		ans=(ans+(b[i]-a[i])*tmp%P)%P;
		tmp=tmp*k%P;
	}
	return (ans+P)%P;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	maxn=read();maxk=read();q=read();
	f[1][0]=f[1][1]=1;
	for(ll i=2;i<=maxn;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			f[i][0]=2;f[i][1]=f[i][2]=1;
		}
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])Multi(f[i],f[prime[j]],f[i*prime[j]]);
			else{
				ll x=i,x1=prime[j],x2=1;
				while(x%prime[j]==0){
					x/=prime[j];
					x1*=prime[j];
					x2++;
				}
				if(x==1){
					ll e[M]={2,x2,1};
					ll dlt=Pow(x2,P-2);
					Multi(f[i],e,f[i*prime[j]]);
					for(ll k=1;k<=f[i*prime[j]][0];k++){
						f[i*prime[j]][k]=(f[i*prime[j]][k]*dlt)%P;
					}
				}
				else Multi(f[x],f[x1],f[i*prime[j]]);
				break;
			}
		}
	}
	for(ll i=2;i<=maxn;i++)Add(f[i],f[i-1]);
	for(ll i=1;i<=q;i++){
		ll l=read(),r=read(),k=read();
		printf("%lld\n",Ask(f[l-1],f[r],k));
	}
	return 0;
}