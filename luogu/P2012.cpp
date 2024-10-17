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
const int Mod=1e9;
const int Phi=4e8;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n;
ll Pow(ll x,ll y){
	ll ans=1;x%=Mod;y=(y<Phi?y:y%Phi+Phi);
	while(y){if(y&1)ans=ans*x%Mod;x=x*x%Mod;y>>=1;}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(1){
		n=read();
		if(!n)break;
		if(n<=3){puts("0");continue;}
		if(n==4){puts("24");continue;}
		printf("%lld\n",((81*Pow(12,n-4)-Pow(8,n-2)+6*Pow(4,n-4)+Pow(Mod-4,n-4))%Mod+Mod)%Mod);
	}
	return 0;
}
