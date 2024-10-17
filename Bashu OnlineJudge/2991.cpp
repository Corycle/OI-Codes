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
const ll Mod=100003;
const ll maxn=2000;
const ll N=2005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a,b,c,d,K,Ans;
ll C[N][N],Fac[N];
ll Sum(ll x,ll y,ll k){
	if(x<k||y<k)return 0;
	return C[x][k]*C[y][k]%Mod*Fac[k]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	a=read();b=read();c=read();d=read();K=read();
	C[0][0]=1;Fac[0]=1;
	for(ll i=1;i<=maxn;i++){
		C[i][0]=1;
		Fac[i]=Fac[i-1]*i%Mod;
		for(ll j=1;j<=maxn;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
		}
	}
	for(ll i=0;i<=K;i++){
		Ans=(Ans+Sum(a,b,i)*Sum(c+a-i,d,K-i)%Mod)%Mod;
	}
	printf("%lld",Ans);
	return 0;
}