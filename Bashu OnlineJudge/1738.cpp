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
ll n;
ll a[N],m[N];
void Exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1;y=0;}
	else{
		Exgcd(b,a%b,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
ll Solve(){
	ll M=1,Ans=0;
	for(ll i=1;i<=n;i++)M*=m[i];
	for(ll i=1;i<=n;i++){
		ll Mi=M/m[i];
		ll x=0,y=0;
		Exgcd(Mi,m[i],x,y);
		Ans=(Ans+Mi*x*a[i])%M;
	}
	return (Ans+M)%M;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		m[i]=read();
		a[i]=read();
	}
	printf("%lld",Solve());
	return 0;
}