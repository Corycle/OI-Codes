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
const ll Mod=100003;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,a[N],f[N],dis[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("trennen.in","r",stdin);
//	freopen("trennen.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	ll Ans=0,tot=0;
	for(ll i=n;i>=1;i--){
		if(a[i]){
			for(ll j=1;j*j<=i;j++){
				if(i%j==0){
					ll x=j,y=i/j;
					a[x]^=1;
					if(x!=y)a[y]^=1;
				}
			}
			tot++;
		}
	}
	for(ll i=n;i>=1;i--){
		f[i]=((n-i)*f[i+1]%Mod+n)%Mod*Pow(i,Mod-2)%Mod;
	}
	for(ll i=tot;i>m;i--)Ans=(Ans+f[i])%Mod;
	Ans=(Ans+min(tot,m))%Mod;
	for(ll i=1;i<=n;i++)Ans=Ans*i%Mod;
	printf("%lld",Ans);
	return 0;
}