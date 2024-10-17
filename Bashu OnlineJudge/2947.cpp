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
ll a,b,c,A,B;
ll Sqr(ll x){return x*x;}
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	a=read();b=read();c=read();
	B=Sqr(b-a);A=B-Sqr(b-a-c);
	ll Gcd=gcd(A,B);
	A/=Gcd;B/=Gcd;
	if(B==1)printf("%lld",A);
	else printf("%lld/%lld",A,B);
	return 0;
}