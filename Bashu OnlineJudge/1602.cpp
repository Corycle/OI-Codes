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
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,p;
struct Point{
	ll x,y;
}a[N];
ll Solve(){
	ll num=1<<p,ans=0;
	for(ll i=1;i<=num;i++){
		ll cnt=0;
		ll sx=0,sy=0,fx=0,fy=0;
		for(ll j=1;j<=p;j++){
			if((i>>(j-1))&1){
				if(!cnt){
					sx=fx=a[j].x;
					sy=fy=a[j].y;
				}
				else{
					sx=min(sx,a[j].x);
					sy=min(sy,a[j].y);
					fx=max(fx,a[j].x);
					fy=max(fy,a[j].y);
				}
				cnt++;
			}
		}
		ll t=sx*sy*(n-fx+1)*(m-fy+1);
		if(cnt&1)ans+=t;
		else ans-=t;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		n=read();m=read();p=read();
		for(ll i=1;i<=p;i++){
			a[i].x=read();
			a[i].y=read();
		}
		ll ans=Solve();
		printf("%lld\n",(n+1)*n/2*(m+1)*m/2-ans);
	}
	return 0;
}