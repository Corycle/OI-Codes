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
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,Mod,f[N][N],C[N][N],sum[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();Mod=read();
	for(int i=0;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<N;j++){
			C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
		}
	}
	for(int i=0;i<=K;i++){f[1][i]=1;sum[1][i]=K-i+1;}
	for(int i=2;i<=n+1;i++){
		for(int j=0;j<=K;j++){
			for(int k=1;k<i;k++){
				f[i][j]=mod(f[i][j]+1ll*C[i-2][k-1]*f[i-k][j]%Mod*sum[k][j+1]%Mod);
			}
		}
		for(int j=K;j>=0;j--)sum[i][j]=mod(sum[i][j+1]+f[i][j]);
	}
	printf("%d",f[n+1][0]);
	return 0;
}
