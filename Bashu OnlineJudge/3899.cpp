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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,Ans;
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read()+1;m=read()+1;
	Ans=(n*m)*(n*m-1)*(n*m-2)/6;
	for(ll i=3;i<=n;i++)Ans-=(i-2)*(n-i+1)*m;
	for(ll i=3;i<=m;i++)Ans-=(i-2)*(m-i+1)*n;
	for(ll i=3;i<=n;i++){
		for(ll j=3;j<=m;j++){
			ll k=gcd(i-1,j-1)+1;
			if(k>=3)Ans-=2*(k-2)*(n-i+1)*(m-j+1);
		}
	}
	printf("%lld",Ans);
	return 0;
}