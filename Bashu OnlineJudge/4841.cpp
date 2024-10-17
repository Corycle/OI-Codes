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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Number{ll a,b;}Ans;
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
Number Add(Number A,Number B){
	Number C=(Number){A.a*B.b+A.b*B.a,A.b*B.b};
	ll p=gcd(C.a,C.b);C.a/=p;C.b/=p;
	return C;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll n=read();
	Ans.a=Ans.b=1;
	for(ll i=2;i<=n;i++){
		Number dlt=(Number){1,i};
		Ans=Add(Ans,dlt);
	}
	Ans.a*=n;
	ll p=gcd(Ans.a,Ans.b);Ans.a/=p;Ans.b/=p;
	if(Ans.a%Ans.b==0)printf("%lld",Ans.a/Ans.b);
	else if(Ans.a<Ans.b)printf("(%lld/%lld)",Ans.a,Ans.b);
	else printf("%lld(%lld/%lld)",Ans.a/Ans.b,Ans.a%Ans.b,Ans.b);
	return 0;
}