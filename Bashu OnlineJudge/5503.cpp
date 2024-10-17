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
ll n,m,q;
ll f[N],fa[N],dis[N];
ll Find(ll x){
	if(x==fa[x])return x;
	ll Fa=fa[x];fa[x]=Find(fa[x]);
	dis[x]=(dis[x]+dis[Fa])%m;
	return fa[x];
}
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
void Exgcd(ll a,ll b,ll &d,ll &x,ll &y){
	if(b==0){d=a;x=1;}
	else{
		Exgcd(b,a%b,d,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();q=read();
	for(ll i=1;i<=n;i++)f[i]=m;
	for(ll i=1;i<=n;i++)fa[i]=i;
	while(q--){
		ll op=read(),x=read(),y=read();
		ll fx=Find(x),fy=Find(y);
		if(op==1){
			ll w=read();
			if(fx==fy)f[fx]=gcd(f[fx],gcd(w*2%m,(w+dis[x]+dis[y])%m));
			else{
				fa[fx]=fy;dis[fx]=(w-dis[x]+dis[y]+m)%m;
				f[fy]=gcd(dis[fx]*2%m,gcd(f[fx],f[fy]));
			}
		}
		else{
			ll a=read(),b=read(),c=read();
			if(fx!=fy)printf("0\n");
			else{
				ll len=(dis[x]+dis[y])%m;
				ll t=f[fx],d=0,A=0,B=0;
				ll tmp=((len-a)%t+t)%t;
				Exgcd(b%t,t,d,A,B);
				if(tmp%d){printf("0\n");continue;}
				A=((A*(tmp/d))%(t/d)+(t/d))%(t/d);
				if(A>=c)printf("0\n");
				else printf("%lld\n",(c-1-A)/(t/d)+1);
			}
		}
	}
	return 0;
}