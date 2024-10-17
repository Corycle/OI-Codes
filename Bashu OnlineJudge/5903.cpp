/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
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
ll n,m,Max;
ll a[N],b[N];
bool Check(ll maxn){
	ll sum=0;
	for(ll i=1;i<=n;i++){
		if(b[i]<=maxn){
			sum+=a[i];
			if(sum>=m)return true;
		}
		else sum=0;
	}
	return false;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
		Max=max(Max,b[i]);
	}
	ll l=1,r=Max,ans=inf;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(Check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}