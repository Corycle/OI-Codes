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
const ll N=10005;
ll read(){
	ll s=0,f=1;char b=getchar();
	while(b<'0'||b>'9'){if(b=='-')f=-1;b=getchar();}
	while(b>='0'&&b<='9'){s=s*10+b-'0';b=getchar();}
	return s*f;
}
/*
	x ≡b[i] (mod a[i])
*/
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
void Exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1;y=0;}
	else{
		Exgcd(b,a%b,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
ll Inv(ll n,ll p){
	ll x=0,y=0;
	Exgcd(n,p,x,y);
	x=(x%p+p)%p;
	return x;
}
ll n,m,a[N],b[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		bool flag=true;
		n=read();m=read();
		for(ll i=1;i<=m;i++)a[i]=read();
		for(ll i=1;i<=m;i++)b[i]=read();
		for(ll i=2;i<=m;i++){
			ll a1=a[i-1],a2=a[i];
			ll b1=b[i-1],b2=b[i];
			ll t=gcd(a1,a2);
			if((b2-b1)%t){
				flag=false;
				break;
			}
			a[i]=a1*a2/t;
			b[i]=Inv(a1/t,a2/t)*((b2-b1)/t)%(a2/t)*a1+b1;
			b[i]=(b[i]%a[i]+a[i])%a[i];
		}
		if(!flag)printf("0\n");
		else{
			ll ans=max(0ll,(n-b[m]+a[m])/a[m]-(b[m]==0));
			printf("%lld\n",ans);
		}
	}
	return 0;
}