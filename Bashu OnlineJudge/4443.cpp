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
const int inf=0x3f3f3f3f;
const int Mod=998244353;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int Phi(ll n){
	ll phi=n;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0){
			phi=phi/i*(i-1);
			while(n%i==0)n/=i;
		}
	}
	if(n!=1)phi=phi/n*(n-1);
	return phi%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll n=read(),m=read();
	printf("%lld",(n%Mod)*(m%Mod)%Mod*Phi(n)%Mod*Phi(m)%Mod);
	return 0;
}