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
const int N=405;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,A[N],B[N],f[N][N],g[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)A[i]=read();
	for(int i=1;i<=n;i++)B[i]=read();
	for(int j=0;j<=400;j++)for(int i=1;i<=400;i++)g[i][j]=mod(g[i-1][j]+Pow(i,j));
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<=j;k++){
				f[i][j]=mod(f[i][j]+1ll*f[i-1][j-k]*mod(g[B[i]][k]-g[A[i]-1][k]+Mod)%Mod);
			}
		}
	}
	printf("%d\n",f[n][m]);
	return 0;
}
