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
const int N=555;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,c[N],Fac[N],Inv[N],f[N][N],g[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=1;
	for(int i=2;i<=n;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(int i=2;i<=n;i++)Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=n;i++)Inv[i]=1ll*Inv[i-1]*Inv[i]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=1;i<=m;i++){
		c[i]=read();
		if(!c[i]){i--;m--;}
	}
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=j;k++){
				g[j+1][k+1]=mod(g[j][k]+f[j][k]);
				f[j][k]=0;
			}
		}
		for(int j=1;j<=n;j++){
			for(int k=1;k<=j;k++){
				int l=min(c[i],k);
				f[j][0]=mod(f[j][0]+1ll*Inv[k]*mod(g[j][k]-g[j-l][k-l]+Mod)%Mod);
				if(j!=n){
					l=min(c[i]-1,k);
					f[j][k]=mod(f[j][k]-mod(g[j][k]-g[j-l][k-l]+Mod)+Mod);
				}
			}
		}
		Ans=mod(Ans+f[n][0]);
	}
	Ans=1ll*Ans*Fac[n]%Mod;
	printf("%d",Ans);
	return 0;
}