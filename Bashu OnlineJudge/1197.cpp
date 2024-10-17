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
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,S;
ll t[N],f[N],c[N],q[N];
double Slope(ll x,ll y){
	if(c[x]==c[y])return inf;
	return (double)(f[y]-f[x])/(c[y]-c[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();S=read();
	for(ll i=1;i<=n;i++){
		t[i]=t[i-1]+read();
		c[i]=c[i-1]+read();
	}
	ll l=1,r=1;
	for(ll i=1;i<=n;i++){
		while(l<r&&Slope(q[l],q[l+1])<=t[i]+S)l++;
		f[i]=f[q[l]]+t[i]*(c[i]-c[q[l]])+S*(c[n]-c[q[l]]);
		while(l<r&&Slope(q[r-1],q[r])>=Slope(q[r],i))r--;
		q[++r]=i;
	}
	printf("%lld",f[n]);
	return 0;
}