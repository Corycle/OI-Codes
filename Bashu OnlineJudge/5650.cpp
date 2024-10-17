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
ll n,K,R;
ll F[N],C[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	C[0][0]=1;
	for(ll i=1;i<=2000;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
		}
	}
	while(T--){
		n=read();K=read();R=read()%Mod;
		ll tmp=Pow(R,n+1),Inv=Pow(R-1+Mod,Mod-2);
		F[0]=(Pow(R,n)-1+Mod)%Mod*Inv%Mod*R%Mod;
		for(ll k=1;k<=K;k++){
			ll t=0;
			for(ll j=0;j<k;j++){
				t=(t+Pow(Mod-1,(k-j)&1)%Mod*C[k][j]%Mod*((F[j]-R)%Mod))%Mod;
			}
			F[k]=((tmp*Pow(n,k)%Mod-R+Mod)%Mod+t)%Mod*Inv%Mod;
		}
		printf("%lld\n",(F[K]%Mod+Mod)%Mod);
	}
	return 0;
}