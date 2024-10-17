#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N],f[N];
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	f[0]=1;
	for(ll i=1;i<=24;i++)f[i]=f[i-1]*3;
	for(ll i=1;i<=24;i++){
		ll a=0,b=0;
		for(ll j=0;j<i;j++)a+=f[gcd(i,j)];
		if(i&1)b=i*f[(i+1)/2];
		else b=(f[i/2]+f[i/2+1])*i/2;
		Ans[i]=(a+b)/(2*i);
	}
	while(1){
		ll n=read();
		if(n==-1)return 0;
		printf("%lld\n",Ans[n]);
	}
	return 0;
}