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
const int inf=0x3f3f3f3f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll F(ll a,ll b,ll c,ll n){
	if(!c)return 0;
	if(a>=c||b>=c)return F(a%c,b%c,c,n)+(a/c)*n*(n+1)/2+(b/c)*(n+1);
	ll m=(a*n+b)/c;return m*n-F(c,c-b-1,a,m-1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll A=read(),B=read(),C=read();
	printf("%lld\n",F(A,C%A,B,C/A)+(C/A)+1);
	return 0;
}