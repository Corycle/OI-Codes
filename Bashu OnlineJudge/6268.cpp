/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const double eps=1e-12;
const double dlt=0.5772156655606;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
int main(){
//	freopen("book.in","r",stdin);
//	freopen("book.out","w",stdout);
	n=read();m=read();
	if(n<=1e7){
		double Ans=0;
		for(ll i=1;i<=n;i++){
			Ans+=(double)m/i;
		}
		Ans/=2;
		printf("%lld\n",(ll)(floor(Ans-eps)));
	}
	else{
		printf("%lld\n",(ll)(floor((log(n)+dlt)*m/2-eps)));
	}
	return 0;
}