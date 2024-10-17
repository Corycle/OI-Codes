#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=1e9+7;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Pow(ll x,ll y){
	x=x%Mod;
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
		y>>=1;
	}
	return ans;
}
ll n,k;
ll F[N],C[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();k=read();
	C[0][0]=1;
	for(ll i=1;i<=k;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
		}
	}
	ll Inv2=Pow(2,Mod-2);
	F[0]=(1-Pow(Inv2,n)+Mod)%Mod;
	for(ll i=1;i<=k;i++){
		F[i]=(1-Pow(n,i)*Pow(Inv2,n)%Mod+Mod)%Mod;
		for(ll j=1;j<=i;j++){
			F[i]=(F[i]+C[i][j]*(F[i-j]-Pow(n,i-j)*Pow(Inv2,n)%Mod+Mod)%Mod)%Mod;
		}
	}
	ll Sum1=F[k]*Pow(2,n)%Mod;
	
	n--;
	F[0]=(1-Pow(Inv2,n)+Mod)%Mod;
	for(ll i=1;i<=k;i++){
		F[i]=(1-Pow(n,i)*Pow(Inv2,n)%Mod+Mod)%Mod;
		for(ll j=1;j<=i;j++){
			F[i]=(F[i]+C[i][j]*(F[i-j]-Pow(n,i-j)*Pow(Inv2,n)%Mod+Mod)%Mod)%Mod;
		}
	}
	ll Sum2=F[k]*Pow(2,n)%Mod;
	printf("%lld",(Sum1-Sum2+Mod)%Mod);
	return 0;
}