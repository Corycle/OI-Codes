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
int n,m,K,Ans,C[N][N],f[2][N][N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=0;i<N;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j]+C[i-1][j-1]);}
	for(int i=1,t=0;i<=m;i++){
		t^=1;memset(f[t],0,sizeof(f[t]));
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				for(int l=1;l<=K;l++){
					if(!f[t^1][j][k][l])continue;
					for(int p=k;j+p<=n&&1ll*l*C[p-1][k-1]<=K;p++){
						f[t][j+p][p-k][l*C[p-1][k-1]]=mod(f[t][j+p][p-k][l*C[p-1][k-1]]+f[t^1][j][k][l]);
					}
				}
			}
		}
		for(int j=1;j<=n;j++)f[t][j][j][1]=mod(f[t][j][j][1]+1);
		for(int j=1;j<=n;j++){
			for(int k=1;k<=K;k++){
				Ans=mod(Ans+f[t][j][0][k]);
			}
		}
	}
	printf("%d",Ans);
	return 0;
}
