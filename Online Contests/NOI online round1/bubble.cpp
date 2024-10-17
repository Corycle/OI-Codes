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
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
ll a[N],sum[N];
int main(){
	freopen("bubble.in","r",stdin);
	freopen("bubble.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++){
		for(ll j=i+1;j<=n;j++){
			if(a[i]>a[j])sum[j-i]++;
		}
	}
	while(m--){
		ll op=read(),x=read();
		if(op==1){
			ll y=x+1;
			for(ll i=1;i<=x-1;i++){
				if(a[i]>a[x])sum[x-i]--;
				if(a[i]>a[y])sum[y-i]--;
			}
			for(ll i=y+1;i<=n;i++){
				if(a[x]>a[i])sum[i-x]--;
				if(a[y]>a[i])sum[i-y]--;
			}
			if(a[x]>a[y])sum[1]--;
			swap(a[x],a[y]);
			for(ll i=1;i<=x-1;i++){
				if(a[i]>a[x])sum[x-i]++;
				if(a[i]>a[y])sum[y-i]++;
			}
			for(ll i=y+1;i<=n;i++){
				if(a[x]>a[i])sum[i-x]++;
				if(a[y]>a[i])sum[i-y]++;
			}
			if(a[x]>a[y])sum[1]++;
		}
		if(op==2){
			ll Ans=0;
			for(ll i=x+1;i<=n;i++)Ans+=sum[i];
			printf("%lld\n",Ans);
		}
	}
	return 0;
}
