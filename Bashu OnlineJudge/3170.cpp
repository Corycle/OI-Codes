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
const ll N=500005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
ll q[N],f[N],sum[N];
ll Sqr(ll x){return x*x;}
double Slope(ll x,ll y){
	if(sum[x]==sum[y])return inf;
	return (double)((f[x]+Sqr(sum[x]))-(f[y]+Sqr(sum[y])))/(sum[x]-sum[y]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(scanf("%lld%lld",&n,&m)!=EOF){
		ll l=1,r=1;q[1]=f[0]=sum[0]=0;
		for(ll i=1;i<=n;i++)sum[i]=sum[i-1]+read();
		for(ll i=1;i<=n;i++){
			while(l<r&&Slope(q[l],q[l+1])<sum[i]*2)l++;
			f[i]=f[q[l]]+Sqr(sum[i]-sum[q[l]])+m;
			while(l<r&&Slope(q[r-1],q[r])>Slope(q[r],i))r--;
			q[++r]=i;
		}
		printf("%lld\n",f[n]);
	}
	return 0;
}