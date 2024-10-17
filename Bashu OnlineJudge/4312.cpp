#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const ll Mod=1e9+9;
const ll N=2005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,k,ans;
ll A[N],B[N],C[N][N],f[N][N],Lim[N],Fac[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();k=(n+read())/2;
	for(ll i=1;i<=n;i++)A[i]=read();
	for(ll i=1;i<=n;i++)B[i]=read();
	sort(A+1,A+n+1);sort(B+1,B+n+1);
	for(ll i=1;i<=n;i++){
		Lim[i]=Lim[i-1];
		while(Lim[i]<n&&A[i]>B[Lim[i]+1])Lim[i]++;
	}
	C[0][0]=1;
	for(ll i=1;i<=2e3;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
		}
	}
	Fac[0]=1;
	for(ll i=1;i<=2e3;i++)Fac[i]=Fac[i-1]*i%Mod;
	/*
		f[i][j]=(Lim[i]-j+1)*f[i-1][j-1]+f[i-1][j]
		ans=∑(i=k~n) (-1)^(i-k) C[i][k]*f[n][i]*(n-i)!
	*/
	f[0][0]=1;
	for(ll i=1;i<=n;i++){
		f[i][0]=1;
		for(ll j=1;j<=i;j++){
			f[i][j]=(max(Lim[i]-j+1,0ll)*f[i-1][j-1]%Mod+f[i-1][j])%Mod;
		}
	}
	for(ll i=k;i<=n;i++){
		ll c=(i-k)&1?-1:1;
		ans=(ans+Mod+c*C[i][k]*f[n][i]%Mod*Fac[n-i]%Mod)%Mod;
	}
	printf("%lld",ans);
	return 0;
}