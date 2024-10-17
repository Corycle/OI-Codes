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
ll prime[N],cnt;
void Prepare(ll n){
	cnt=0;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0){
			while(n%i==0)n/=i;
			prime[++cnt]=i;
		}
	}
	if(n!=1)prime[++cnt]=n;
}
ll Solve(ll n){
	ll num=(1<<cnt),ans=0;
	for(ll i=1;i<num;i++){
		ll tmp=1,tot=0;
		for(ll j=1;j<=cnt;j++){
			if((i>>(j-1))&1){
				tmp*=prime[j];
				tot++;
			}
		}
		if(tot&1)ans+=n/tmp;
		else ans-=n/tmp;
	}
	return n-ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		ll a=read(),b=read(),n=read();
		Prepare(n);
		ll ans=Solve(b)-Solve(a-1);
		printf("%lld\n",ans);
	}
	return 0;
}