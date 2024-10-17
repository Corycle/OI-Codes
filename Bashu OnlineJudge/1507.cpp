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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,Sum1,Sum2,a[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=2;i<=n;i++){
		if(a[i]>a[i-1])Sum1+=a[i]-a[i-1];
		if(a[i]<a[i-1])Sum2+=a[i-1]-a[i];
	}
	printf("%lld\n%lld",max(Sum1,Sum2),abs(Sum1-Sum2)+1);
	return 0;
}