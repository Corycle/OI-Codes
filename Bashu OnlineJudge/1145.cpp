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
const ll N=500005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,L,s[N],f[N],q[N];
double G(ll j,ll k){
	return (double)((f[j]+s[j]*s[j])-(f[k]+s[k]*s[k]))/(2*(s[j]-s[k]));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();L=read();
	int l=1,r=1;
	for(ll i=1;i<=n;i++){
		s[i]=s[i-1]+1+read();
		s[i]-=L+1;
		while(l<r&&G(q[l],q[l+1])<s[i])l++;
		ll j=q[l];
		f[i]=f[j]+(s[i]-s[j])*(s[i]-s[j]);
		s[i]+=L+1;
		while(l<r&&G(q[r-1],q[r])>=G(q[r],i))r--;
		q[++r]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}