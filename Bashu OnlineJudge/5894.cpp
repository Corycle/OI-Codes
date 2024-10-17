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
const ll inf=9e18;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,a[N],f[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	f[1]=a[1];
	for(ll i=2;i<=n+1;i++){
		f[i]=-inf;
		if(i>=2)f[i]=max(f[i],f[i-2]+a[i]);
		if(i>=3)f[i]=max(f[i],f[i-3]+a[i]);
	}
	printf("%lld",max(f[n],f[n+1]));
	return 0;
}