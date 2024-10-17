#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,a[N];
ll Check(ll x){
	ll ans=0;
	for(ll i=1;i<=n;i++){
		ans+=(a[i]>=x)*(a[i]-x);
	}
	return ans>=m;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	ll l=0,r=1e9,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(Check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%lld",ans);
	return 0;
}