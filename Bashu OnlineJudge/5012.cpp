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
const int Mod=1e9+7;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,f[N],g[N],Fac[N],Inv[N];
int C(int n,int m){return n<m?0:1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;}
int Sum(int n){return n*(n-1)/2;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=1;
	for(int i=2;i<=n;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(int i=2;i<=n;i++)Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=n;i++)Inv[i]=1ll*Inv[i-1]*Inv[i]%Mod;
	for(int i=1;i<=n;i++){
		f[i]=g[i]=Pow(2,Sum(i-1));
		for(int j=1;j<=i-1;j++){
			f[i]=(f[i]-1ll*f[j]*g[i-j]%Mod*C(i-1,j-1)%Mod+Mod)%Mod;
		}
	}
	printf("%lld",1ll*f[n]*C(n,2)%Mod);
	return 0;
}