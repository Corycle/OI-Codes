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
const ll inf=1e18;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,F[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(1){
		n++;F[n]=n;
		for(ll i=2;i<=10;i++){
			if(n-i-1<=0)break;
			F[n]=max(F[n],F[n-i-1]*i);
		}
		if(F[n]>=inf)break;
	}
	ll T=read();
	while(T--){
		ll k=read();
		ll p=lower_bound(F+1,F+n+1,k)-F;
		printf("%lld\n",p*2+2);
	}
	return 0;
}