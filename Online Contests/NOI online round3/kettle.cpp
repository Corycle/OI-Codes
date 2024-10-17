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
const ll N=1e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,K,Ans,a[N],sum[N];
int main(){
//	freopen("kettle.in","r",stdin);
//	freopen("kettle.out","w",stdout);
	n=read();K=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	for(ll i=1;i+K<=n;i++){
		Ans=max(Ans,sum[i+K]-sum[i-1]);
	}
	printf("%lld",Ans);
	return 0;
}
