#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
ll n,top;
ll a[N],L[N],R[N],st[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(scanf("%lld",&n)!=EOF){
		ll ans=0;
		for(ll i=1;i<=n;i++)a[i]=read();
		a[st[top=0]=0]=0;
		for(ll i=1;i<=n;i++){
			while(top&&a[st[top]]>=a[i])top--;
			L[i]=st[top]+1;
			st[++top]=i;
		}
		a[st[top=0]=n+1]=0;
		for(ll i=n;i>=1;i--){
			while(top&&a[st[top]]>=a[i])top--;
			R[i]=st[top]-1;
			st[++top]=i;
		}
		for(ll i=1;i<=n;i++){
			ans=max(ans,a[i]*(R[i]-L[i]+1));
		}
		printf("%lld\n",ans);
	}
	return 0;
}