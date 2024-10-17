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
const ll Mod=998244353;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,Ans;
ll mod(ll x){return x>=Mod?x-Mod:x;}
ll SumH(ll n){
	ll ans=n%Mod,t=2;
	while(t<=n){
		ans=mod(ans+(t/2)*(n/t)%Mod);
		t<<=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	ll lst=0;
	for(ll i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ll now=SumH(j);
		Ans=mod(Ans+(n/i)%Mod*mod(now-lst+Mod)%Mod);
		lst=now;
	}
	printf("%lld",Ans);
	return 0;
}
