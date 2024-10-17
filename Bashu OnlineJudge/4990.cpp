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
const int Mod=258280327;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,p,f[N][N],g[N];
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
	f[1][0]=1;g[0]=1;
	int x=read(),y=read();
	p=1ll*x*Pow(y,Mod-2)%Mod;
	for(int i=1;i<=n;i++)g[i]=1ll*g[i-1]*(1-p+Mod)%Mod;
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			f[i][j]=(1ll*f[i-1][j-1]*g[j-1]%Mod+1ll*f[i-1][j]*(1-g[j]+Mod)%Mod)%Mod;
		}
	}
	int Inv=Pow(n,Mod-2);
	for(int k=0;k<n;k++){
		int ans=0;
		for(int i=1;i<=n;i++){
			ans=(ans+1ll*f[i][k]*g[k]%Mod)%Mod;
		}
		printf("%lld ",1ll*ans*Inv%Mod);
	}
	return 0;
}