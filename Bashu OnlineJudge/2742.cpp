#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,a,b,c;
ll s[N],f[N],q[N];
ll F(ll i){
	return f[i]+a*s[i]*s[i]-b*s[i];
}
double G(ll k,ll j){
	return (double)(F(j)-F(k))/(2*a*(s[j]-s[k]));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	a=read();b=read();c=read();
	for(ll i=1;i<=n;i++){
		s[i]=s[i-1]+read();
	}
	ll l=1,r=1;
	for(ll i=1;i<=n;i++){
		while(l<r&&G(q[l],q[l+1])<s[i])l++;
		ll j=q[l],x=s[i]-s[j];
		f[i]=f[j]+a*x*x+b*x+c;
		while(l<r&&G(q[r-1],q[r])>=G(q[r],i))r--;
		q[++r]=i;
	}
	printf("%lld",f[n]);
	return 0;
}