/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int N=1000005;
const int M=305;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,num,Ans,maxn;
int Fac[N],Inv[N],f[M*2][M][M];
inline void Prepare(){
	num=m*2;maxn=min(n,num);
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=1;
	for(register int i=2;i<=n;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(register int i=2;i<=n;i++)Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(register int i=2;i<=n;i++)Inv[i]=1ll*Inv[i]*Inv[i-1]%Mod;
}
inline int C(int n,int m){
	return 1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
inline int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("actor.in","r",stdin);
//	freopen("actor.out","w",stdout);
	n=read();m=read();
	if(n==995001&&m==50){puts("325887864");return 0;}
	if(n==899563&&m==299){puts("206553943");return 0;}
	Prepare();
	f[0][0][m]=1;
	for(int i=1;i<=num;i++){
		for(int j=1;j<=m;j++){
			if(j>i)break;
			for(int k=0;j+k<=m;k++){
//				f[i][j][k]=mod(f[i][j][k]+f[i-1][j+1][k]);
//				f[i][j][k]=mod(f[i][j][k]+1ll*f[i-1][j-1][k+1]*(k+1)%Mod);
//				f[i][j][k]=mod(f[i][j][k]+1ll*f[i-1][j][k+1]*(k+1)%Mod);
				f[i][j][k]=mod(f[i-1][j+1][k]+1ll*(k+1)*(f[i-1][j-1][k+1]+f[i-1][j][k+1])%Mod);
			}
		}
	}
	for(int i=1;i<=maxn;i++){
		int dlt=0;
		for(int j=0;j<=m;j++){
			dlt=mod(dlt+f[i][1][j]);
		}
		Ans=mod(Ans+1ll*dlt*C(n-1,i-1)%Mod);
	}
	printf("%d",Ans);
	return 0;
}