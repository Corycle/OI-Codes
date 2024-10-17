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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,L,R,len;
ll a[N],b[N],c[N],sum[N];
ll lowbit(ll x){
	return x&(-x);
}
void Add(ll x){
	for(ll i=x;i<=len;i+=lowbit(i)){
		c[i]++;
	}
}
ll Ask(ll x){
	ll ans=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();L=read();R=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
		b[i]=sum[i];
	}
	ll ans=0;
	sort(b+1,b+n+1);
	len=unique(b+1,b+n+1)-b-1;
	for(ll i=n;i>=1;i--){
		sum[i]=lower_bound(b+1,b+len+1,sum[i])-b;
		Add(sum[i]);
		ll l=lower_bound(b+1,b+len+1,sum[i-1]+L)-b;
		ll r=upper_bound(b+1,b+len+1,sum[i-1]+R)-b-1;
		ll sum=Ask(r)-Ask(l-1);
		if(sum>=0)ans+=sum;
	}
	printf("%lld",ans);
	return 0;
}