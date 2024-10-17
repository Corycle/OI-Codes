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
ll n,tot[N],dis[N],p[N],c[N],s[N],f[N],q[N];
double G(ll k,ll j){
	return (double)(f[j]-f[k]-tot[j+1]+tot[k+1]+s[j+1]*dis[j+1]-s[k+1]*dis[k+1])/(s[j+1]-s[k+1]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		dis[i]=read();
		p[i]=read();
		c[i]=read();
		s[i+1]=s[i]+p[i];
		tot[i]=s[i]*(dis[i]-dis[i-1])+tot[i-1];
	}
	ll l=1,r=1;
	for(ll i=1;i<=n;i++){
		while(l<r&&G(q[l],q[l+1])<dis[i])l++;
		ll j=q[l];
		f[i]=f[j]+tot[i]-tot[j+1]-s[j+1]*(dis[i]-dis[j+1])+c[i];
		while(l<r&&G(q[r-1],q[r])>=G(q[r],i))r--;
		q[++r]=i;
	}
	printf("%lld",f[n]);
	return 0;
}