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
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,a[N],g[N],ans;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%lld",&n)!=EOF){
		ans=0;
		g[n+1]=0;
		for(ll i=1;i<=n;i++){
			a[i]=read();
			g[i]=0;
		}
		sort(a+1,a+n+1);
		for(ll i=n;i>=1;i--)g[i]=g[i+1]+a[i];
		for(ll i=1;i<=n;i++){
			ans+=g[i+1]-a[i]*(n-i);
		}
		ans*=2;
		printf("%lld\n",ans);
	}
	return 0;
}
