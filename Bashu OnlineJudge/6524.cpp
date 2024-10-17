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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int f[N][N],g[N],h[N][N],p[N*N],C[N][N];
int Sum(int x){return x*(x-1)/2;}
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(int n){
	p[0]=1;
	for(int i=1;i<=n*n;i++)p[i]=mod(p[i-1]<<1);
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
		}
	}
	for(int i=1;i<=n;i++){
		g[i]=p[Sum(i)];
		for(int j=1;j<=i-1;j++){
			g[i]=mod(g[i]-1ll*g[j]*p[Sum(i-j)]%Mod*C[i-1][j-1]%Mod+Mod);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			h[i][j]=1ll*g[j]*Pow(p[j]-1,i)%Mod*p[Sum(i)]%Mod;
		}
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		f[i][0]=p[Sum(i)];
		for(int j=1;j<=i;j++){
			for(int k=1;k<=j;k++){
				f[i][j]=(f[i][j]+1ll*f[i-k][j-k]*C[j-1][k-1])%Mod;
			}
			for(int x=1;x<=j;x++){//white points
				for(int y=1;y<=i-j;y++){//black points
					f[i][j]=mod(f[i][j]+1ll*f[i-x-y][j-x]*h[x][y]%Mod*C[j-1][x-1]%Mod*C[i-j][y]%Mod);
				}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(100);
	int T=read();
	while(T--){
		int n=read(),m=read();
		printf("%d\n",f[n][m]);
	}
	return 0;
}