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
const ll N=2005;
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
ll n,m,F[N],C[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	C[0][0]=1;
	for(ll i=1;i<=2000;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
		}
	}
	n=read();m=read();
	ll tmp=Pow(m,n+1),Inv=Pow(m-1+Mod,Mod-2);
	F[0]=(Pow(m,n)-1+Mod)%Mod*Inv%Mod*m%Mod;
	for(ll k=1;k<=m;k++){
		ll t=0;
		for(ll j=0;j<k;j++){
			t=(t+Pow(Mod-1,(k-j)&1)%Mod*C[k][j]%Mod*((F[j]-m)%Mod))%Mod;
		}
		F[k]=((tmp*Pow(n,k)%Mod-m+Mod)%Mod+t)%Mod*Inv%Mod;
	}
	printf("%lld",(F[m]%Mod+Mod)%Mod);
	return 0;
}