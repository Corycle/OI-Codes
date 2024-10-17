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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Mod,f[N],fac[N],inv[N];
int C(int n,int m){
	return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
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
	n=read();m=read();Mod=read();
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
	for(int i=2;i<=n;i++)f[i]=(1ll*Pow(i,i-2)*C(n,i)%Mod+f[i-1])%Mod;
	while(m--){
		int l=read(),r=read();
		printf("%d\n",(f[r]-f[l-1]+Mod)%Mod);
	}
	return 0;
}