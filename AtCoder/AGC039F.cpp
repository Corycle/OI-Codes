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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,Mod;
int C[N][N],P[N][N],f[2][N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	for(int i=0;i<N;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);}
	for(int i=0;i<N;i++){P[i][0]=1;for(int j=1;j<N;j++)P[i][j]=1ll*P[i][j-1]*i%Mod;}
}
void Clear(int t){for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)f[t][i][j]=0;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();Mod=read();Prepare();
	int t=0;f[t][0][0]=1;
	for(int T=1;T<=K;T++){
		Clear(t^=1);
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				if(!f[t^1][i][j])continue;
				int tmp=f[t^1][i][j],mul=1ll*P[T][m-j]*P[K-T+1][j]%Mod;
				for(int a=0;i+a<=n;a++,tmp=1ll*tmp*mul%Mod){
					f[t][i+a][j]=mod(f[t][i+a][j]+1ll*C[n-i][a]*tmp%Mod);
				}
			}
		}
		Clear(t^=1);
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				if(!f[t^1][i][j])continue;
				int tmp=f[t^1][i][j],mul=1ll*P[T][n-i]*P[K-T+1][i]%Mod;
				for(int b=0;j+b<=m;b++,tmp=1ll*tmp*mul%Mod){
					f[t][i][j+b]=mod(f[t][i][j+b]+1ll*C[m-j][b]*tmp%Mod);
				}
			}
		}
		Clear(t^=1);
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				if(!f[t^1][i][j])continue;
				int tmp=f[t^1][i][j],mul=1ll*P[T][m-j]*(Mod-P[K-T][j])%Mod;
				for(int c=0;i+c<=n;c++,tmp=1ll*tmp*mul%Mod){
					f[t][i+c][j]=mod(f[t][i+c][j]+1ll*C[n-i][c]*tmp%Mod);
				}
			}
		}
		Clear(t^=1);
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				if(!f[t^1][i][j])continue;
				int tmp=f[t^1][i][j],mul=1ll*P[T][n-i]*(Mod-P[K-T][i])%Mod;
				for(int d=0;j+d<=m;d++,tmp=1ll*tmp*mul%Mod){
					f[t][i][j+d]=mod(f[t][i][j+d]+1ll*C[m-j][d]*tmp%Mod);
				}
			}
		}
	}
	printf("%d",f[t][n][m]);
	return 0;
}
