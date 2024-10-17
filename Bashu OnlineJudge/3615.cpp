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
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	x ≡r[i](mod a[i])
*/
ll m[N],c[N];
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
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll n;
	while(scanf("%lld",&n)!=EOF){
		bool flag=true;
		for(int i=1;i<=n;i++){
			m[i]=read();
			c[i]=read();
		}
		for(int i=2;i<=n;i++){
			ll m1=m[i-1],m2=m[i];
			ll c1=c[i-1],c2=c[i];
			ll t=gcd(m1,m2);
			if((c2-c1)%t){
				flag=false;
				break;
			}
			m[i]=m1*m2/t;
			c[i]=Inv(m1/t,m2/t)*((c2-c1)/t)%(m2/t)*m1+c1;
			c[i]=(c[i]%m[i]+m[i])%m[i];
		}
		if(flag)printf("%lld\n",c[n]);
		else printf("-1\n");
	}
	return 0;
}