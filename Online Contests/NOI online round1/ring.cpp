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
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
ll a[N],b[N],Ans[N];
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
ll Calc(ll l,ll r){
	ll len=(r-l+1),ans=0;
	if(len&1){
		ll tot=0;
		for(ll i=1;i<=len;i+=2)b[++tot]=a[l+i-1];
		for(ll i=len-1;i>=2;i-=2)b[++tot]=a[l+i-1];
	}
	else{
		ll tot=0;
		for(ll i=2;i<=len;i+=2)b[++tot]=a[l+i-1];
		for(ll i=len-1;i>=1;i-=2)b[++tot]=a[l+i-1];
	}
	if(len==2)ans=b[1]*b[2];
	else{
		b[len+1]=b[1];
		for(ll i=1;i<=len;i++)ans+=b[i]*b[i+1];
	}
	return ans;
}
ll Solve(ll k){
	if(k==0){
		ll ans=0;
		for(ll i=1;i<=n;i++)ans+=a[i]*a[i];
		return ans;
	}
	ll t=gcd(k,n);
	ll len=n/t,ans=0;
	for(ll i=1;i<=n;i+=len){
		ans+=Calc(i,i+len-1);
	}
	return ans;
}
int main(){
	freopen("ring.in","r",stdin);
	freopen("ring.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	while(m--){
		ll k=read();
		if(Ans[k])printf("%lld\n",Ans[k]);
		else printf("%lld\n",Ans[k]=Solve(k));
	}
	return 0;
}
