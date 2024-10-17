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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll cnt,tot,a[N],b[N],c[N];
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
ll Phi(ll n){
	ll phi=n;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0){
			phi=phi/i*(i-1);
			while(n%i==0)n/=i;
		}
	}
	if(n!=1)phi=phi/n*(n-1);
	return phi;
}
void Divide(ll n){
	for(ll i=2;i*i<=n;i++){
		if(n%i==0){
			a[++cnt]=i;b[cnt]=0;
			while(n%i==0){n/=i;b[cnt]++;}
		}
	}
	if(n!=1){a[++cnt]=n;b[cnt]=1;}
}
void DFS(ll x,ll sum){
	if(x==cnt+1){c[++tot]=sum;return;}
	ll tmp=1;
	for(ll i=0;i<=b[x];i++){
		DFS(x+1,sum*tmp);
		tmp*=a[x];
	}
}
ll Multi(ll x,ll y,ll Mod){
	ll ans=0,tot=x;
	while(y){
		if(y&1)ans=(ans+tot)%Mod;
		tot=(tot+tot)%Mod;
		y>>=1;
	}
	return ans;
}
ll Pow(ll x,ll y,ll Mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=Multi(ans,tot,Mod);
		tot=Multi(tot,tot,Mod);
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(1){
		ll L=read();
		if(!L)return 0;
		ll P=L/gcd(L,8)*9;
		if(gcd(10,P)!=1)puts("0");
		else{
			cnt=tot=0;
			ll phi=Phi(P);
			Divide(phi);
			DFS(1,1);
			sort(c+1,c+tot+1);
			for(ll i=1;i<=tot;i++){
				if(Pow(10,c[i],P)==1){
					printf("%lld\n",c[i]);
					break;
				}
			}
		}
	}
	return 0;
}