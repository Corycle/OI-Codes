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
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=20005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,p[N],s[N],a[N],dis[N];
ll ans=inf,tot;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();p[i]=read();
		s[i]=s[i-1]+a[i];
	}
	for(ll i=n;i>=1;i--){
		dis[i]=dis[i+1]+p[i];
		tot+=dis[i]*a[i];
	}
	for(ll i=1;i<=n;i++){
		for(ll j=i+1;j<=n;j++){
			ans=min(ans,tot-s[i]*dis[i]-(s[j]-s[i])*dis[j]);
		}
	}
	printf("%lld",ans);
	return 0;
}