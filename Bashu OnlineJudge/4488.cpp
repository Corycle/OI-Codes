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
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll P[N];
ll n,K,num,Mod;
ll Pow(ll x,ll y){
	ll ans=1,tot=x%Mod;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	K=read();n=read();Mod=read();
	// Ans=K^0+...+K^(n-2)
	//P[i]=K^1+...+K^(2^i)
	P[0]=K;
	for(ll i=1;i<=n;i<<=1){
		num++;
		P[num]=(P[num-1]*Pow(K,i)%Mod+P[num-1])%Mod;
	}
	n=n-2;
	ll tot=0,Ans=1;
	for(ll i=0;i<=num;i++){
		if((n>>i)&1){
			Ans=(Ans+P[i]*Pow(K,tot)%Mod)%Mod;
			tot+=(1ll<<i);
		}
	}
	printf("%lld",Ans);
	return 0;
}