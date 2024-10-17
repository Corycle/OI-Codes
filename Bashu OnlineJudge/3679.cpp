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
const ll N=20005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[N];
ll Pow(ll x,ll y,ll p){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%p;
		tot=(tot*tot)%p;
		y>>=1;
	}
	return ans;
}
void Exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1;y=0;}
	else{
		Exgcd(b,a%b,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
ll Inv(ll n,ll p){//n和 p不一定互质 
	if(!n)return 0;
	ll a=n,b=p,x=0,y=0;
	Exgcd(a,b,x,y);
	x=(x%p+p)%p;
	return x;
}
ll Multi(ll n,ll pi,ll pk){//n! %pk
	if(!n)return 1;
	ll ans=1;
	if(n/pk){
		ans=Pow(f[pk],n/pk,pk);
	}
	ans=ans*f[n%pk]%pk;
	return ans*Multi(n/pi,pi,pk)%pk;
}
ll C(ll n,ll m,ll p,ll pi,ll pk){
	if(n<m)return 0;
	f[0]=1;
	for(ll i=1;i<=pk;i++){
		if(i%pi)f[i]=f[i-1]*i%pk;
		else f[i]=f[i-1];
	}
	ll a=Multi(n,pi,pk);
	ll b=Multi(m,pi,pk);
	ll c=Multi(n-m,pi,pk);
	ll k=0;//ans≡C(n,m)(p pk)
	for(ll i=n;i;i/=pi)k+=i/pi;
	for(ll i=m;i;i/=pi)k-=i/pi;
	for(ll i=n-m;i;i/=pi)k-=i/pi;
	ll ans=a*Inv(b,pk)%pk*Inv(c,pk)%pk*Pow(pi,k,pk)%pk;
	return ans*(p/pk)%p*Inv(p/pk,pk)%p;
}
ll cnt,Prime[N],Index[N];
ll Exlucas(ll n,ll m,ll p){
	if(n<m)return 0;
	ll ans=0;
	for(ll i=1;i<=cnt;i++){
		ans=(ans+C(n,m,p,Prime[i],Index[i]))%p;
	}
	return ans;
}
ll n,n1,n2,m,a[N];
//用一共的答案-大于a[i]的答案+两两重复部分-三三重复部分......
ll DFS(ll pos,ll sum,ll f,ll p){
	if(pos==n1+1){
		return Exlucas(sum-1,n-1,p)*f;
	}
	ll ans=DFS(pos+1,sum,f,p);
	if(sum>=a[pos]){
		ans=(ans+DFS(pos+1,sum-a[pos],-f,p))%p;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll Case=read(),p=read();
	if(p==10007){
		cnt=1;
		Prime[1]=10007;
		Index[1]=10007;
	}
	if(p==262203414){
		cnt=5;
		Prime[1]=2;Prime[2]=3;Prime[3]=11;Prime[4]=397;Prime[5]=10007;
		Index[1]=2;Index[2]=3;Index[3]=11;Index[4]=397;Index[5]=10007;
	}
	if(p==437367875){
		cnt=3;
		Prime[1]=5;Prime[2]=7;Prime[3]=101;
		Index[1]=125;Index[2]=343;Index[3]=10201;
	}
	while(Case--){
		n=read();n1=read();n2=read();m=read();
		for(ll i=1;i<=n1;i++)a[i]=read();
		for(ll i=1;i<=n2;i++){
			ll x=read();
			if(x)m-=x-1;
		}
		if(m<n1){
			printf("0\n");
			continue;
		}
		printf("%lld\n",(DFS(1,m,1,p)+p)%p);
	}
	return 0;
}