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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll c[500005],n,m;
ll a[500005],b[500005];
ll lowbit(ll x){
	return (x&(-x));
}
void Add(ll x,ll y){
	for(ll i=x;i<=m;i+=lowbit(i)){
		c[i]+=y;
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
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		ll n=read();
		if(n==0)break;
		memset(c,0,sizeof(c));
		for(ll i=1;i<=n;i++)a[i]=b[i]=read();
		sort(b+1,b+n+1);
		m=unique(b+1,b+n+1)-b-1;
		for(ll i=1;i<=n;i++)a[i]=lower_bound(b+1,b+m+1,a[i])-b;
		ll ans=0;
		for(ll i=1;i<=n;i++){
//			cout<<a[i]<<" ";
			Add(a[i],1);
			ans+=i-Ask(a[i]);
		}
//		cout<<endl;
		printf("%lld\n",ans);
	}
	return 0;
}