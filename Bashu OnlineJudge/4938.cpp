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
const ll Mod=1e9+7;
const ll N=2005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,B[N],C[N][N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(){
	C[0][0]=1;
	for(ll i=1;i<N;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
		}
	}
	B[0]=1;
	for(ll i=1;i<N-1;i++){
		B[i]=0;
		for(ll j=0;j<i;j++){
			B[i]=(B[i]+C[i+1][j]*B[j]%Mod)%Mod;
		}
		B[i]=B[i]*Pow(Mod-C[i+1][i],Mod-2)%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare();
	ll T=read();
	while(T--){
		ll n=read()%Mod+1,m=read();
		ll ans=0;
		for(ll i=0;i<=m;i++){
			ans=(ans+C[m+1][i]*B[i]%Mod*Pow(n,m-i+1)%Mod)%Mod;
		}
		ans=ans*Pow(m+1,Mod-2)%Mod;
		printf("%lld\n",ans);
	}
	return 0;
}