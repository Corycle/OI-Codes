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
const int N=405;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K;
int P[N],F[2][N][N],G[2][N][N];
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
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	if(n>m){printf("0");return 0;}
	for(int i=0;i<=n;i++)P[i]=Pow(i,K);
	int t=0;G[t][0][0]=1;
	for(int k=1;k<=m;k++){
		t^=1;
		for(int i=0;i<=min(k,n);i++){
			for(int j=0;j<=i;j++){
				G[t][i][j]=G[t^1][i][j];
				F[t][i][j]=F[t^1][i][j];
				if(i){
					G[t][i][j]=mod(G[t][i][j]+G[t^1][i-1][j]);
					F[t][i][j]=mod(F[t][i][j]+F[t^1][i-1][j]);
				}
				if(j){
					G[t][i][j]=mod(G[t][i][j]+G[t^1][i][j-1]);
					F[t][i][j]=mod(F[t][i][j]+F[t^1][i][j-1]);
				}
				if(i&&j){
					G[t][i][j]=mod(G[t][i][j]+G[t^1][i-1][j-1]);
					F[t][i][j]=mod(F[t][i][j]+F[t^1][i-1][j-1]);
				}
				F[t][i][j]=mod(F[t][i][j]+1ll*P[i-j]*G[t][i][j]%Mod);
			}
		}
	}
	printf("%d",F[t][n][n]);
	return 0;
}