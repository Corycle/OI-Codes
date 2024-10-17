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
ll n,m,a[N][N];
struct Number{
	ll a,b;
};
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
Number Plus(Number A,Number B){
	A.b=max(A.b,1ll);B.b=max(B.b,1ll);
	if(A.b<B.b)swap(A,B);ll dlt=A.b/B.b;
	Number C=(Number){A.a+B.a*dlt,B.b*dlt};
	ll p=gcd(C.a,C.b);if(p!=0){C.a/=p;C.b/=p;}
	return C;
}
Number f[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=i;j++){
			char s[1];scanf("%s",s);
			a[i][j]=(s[0]=='*');
		}
	}
	f[1][1]=(Number){1,1};
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=i;j++){
			if(a[i][j]){
				Number t=f[i][j];t.b<<=1;
				f[i+1][j]=Plus(f[i+1][j],t);
				f[i+1][j+1]=Plus(f[i+1][j+1],t);
			}
			else f[i+2][j+1]=Plus(f[i+2][j+1],f[i][j]);
		}
	}
	Number ans=f[n+1][m+1];
	printf("%lld/%lld",ans.a,ans.b);
	return 0;
}