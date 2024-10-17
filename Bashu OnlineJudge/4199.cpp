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
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
ll q[N],f[N],g[N],sum[N];
ll Sqr(ll x){return x*x;}
double Slope(ll x,ll y){
	if(sum[x]==sum[y])return inf;
	return (double)((Sqr(sum[x])-f[x])-(Sqr(sum[y])-f[y]))/(double)(sum[x]-sum[y]);
}
ll Check(ll cost){
	ll l=1,r=1;q[l]=1;f[1]=g[1]=0;
	for(ll i=2;i<=n;i++){
		while(l<r&&Slope(q[l],q[l+1])<sum[i])l++;
		f[i]=f[q[l]]+sum[q[l]]*(sum[i]-sum[q[l]])-cost;
		g[i]=g[q[l]]+1;if(f[i]<0)f[i]=g[i]=0;
		while(l<r&&Slope(q[r-1],q[r])>Slope(q[r],i))r--;
		q[++r]=i;
	}
	return g[n];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		sum[i]=sum[i-1]+read();
	}
	ll l=0,r=inf,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(Check(mid)<=m){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	Check(ans);
	printf("%lld",f[n]+m*ans);
	return 0;
}