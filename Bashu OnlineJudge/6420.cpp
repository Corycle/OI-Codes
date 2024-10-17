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
const int Mod=998244353;
const int M=2005;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,Sum;
int sum[N],a[N][M],f[N][N*2],g[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			sum[i]=(sum[i]+a[i][j])%Mod;
		}
	}
	/*
	//O(MN^3)
	for(int c=1;c<=m;c++){
		f[0][0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=i;j++){
				for(int k=0;j+k<=i;k++){
					f[i][j][k]=f[i-1][j][k];
					int tot=(sum[i]-a[i][c]+Mod)%Mod;
					if(j)f[i][j][k]=(f[i][j][k]+1ll*f[i-1][j-1][k]*a[i][c]%Mod)%Mod;
					if(k)f[i][j][k]=(f[i][j][k]+1ll*f[i-1][j][k-1]*tot%Mod)%Mod;
				}
			}
		}
		for(int j=0;j<=n;j++){
			for(int k=0;j+k<=n;k++){
				if(j>(j+k)/2)Ans=(Ans+f[n][j][k])%Mod;
			}
		}
	}
	*/
	for(int c=1;c<=m;c++){
		f[0][n]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n*2;j++){
				f[i][j]=f[i-1][j];
				int tot=(sum[i]-a[i][c]+Mod)%Mod;
				f[i][j]=(f[i][j]+1ll*f[i-1][j-1]*a[i][c]%Mod)%Mod;
				f[i][j]=(f[i][j]+1ll*f[i-1][j+1]*tot%Mod)%Mod;
			}
		}
		for(int j=1;j<=n;j++){
			Ans=(Ans+f[n][n+j])%Mod;
		}
	}
	g[0][0]=1;
	for(int i=1;i<=n;i++){
		g[i][0]=1;
		for(int j=1;j<=n;j++){
			g[i][j]=(g[i-1][j]+1ll*g[i-1][j-1]*sum[i]%Mod)%Mod;
		}
	}
	for(int i=1;i<=n;i++)Sum=(Sum+g[n][i])%Mod;
	printf("%d",(Sum-Ans+Mod)%Mod);
	return 0;
}