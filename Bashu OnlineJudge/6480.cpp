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
ll a,b,k;
ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}
int main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	ll T=read();
	while(T--){
		a=read();b=read();k=read();
		ll d=gcd(a,b);a/=d;b/=d;
		if(a>b)swap(a,b);
		if(k==1)puts("NO");
		else{
			if(a*(k-1)+1>=b)puts("YES");
			else puts("NO");
		}
	}
	return 0;
}