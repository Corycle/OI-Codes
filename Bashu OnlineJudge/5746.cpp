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
const int Sta=1<<8;
const int N=55;
const int M=10;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Power[2*N*M],C[N][N];
int f[N][M],g[N][N][M],p[N][N][M][Sta];
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
void Prepare(){
	Power[0]=1;
	for(int i=1;i<=2*n*m;i++)Power[i]=mod(Power[i-1]<<1);
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
		}
	}
}
int P(int S,int T,int m,int k){
	if(S>T)swap(S,T);
	if(k>=Power[m])return 0;
	if(S==0||k<=0)return Power[(S+T)*m];
	if(p[S][T][m][k]!=-1)return p[S][T][m][k];
	int ans=0;
	for(int i=0;i<=S;i++){
		for(int j=0;j<=T;j++){
			if((i==S&&j==0)||(i==0&&j==T))ans=mod(ans+P(S,T,m-1,k-Power[m-1]));
			else ans=mod(ans+1ll*C[S][i]*C[T][j]%Mod*P(i,j,m-1,k)%Mod*P(S-i,T-j,m-1,k)%Mod);
		}
	}
	return p[S][T][m][k]=ans;
}
int G(int S,int T,int m){
	if(g[S][T][m]!=-1)return g[S][T][m];
	int ans=0;
	for(int k=1;k<Power[m];k++){
		ans=mod(ans+P(S,T,m,k));
	}
	return g[S][T][m]=ans;
}
int F(int n,int m){
	if(m==0||n==1)return 0;
	if(f[n][m]!=-1)return f[n][m];
	int ans=mod(F(n,m-1)<<1);
	for(int i=1;i<n;i++){
		int tmp=mod(G(i,n-i,m-1)+Power[(m-1)*(n+1)]);
		tmp=mod(tmp+1ll*Power[(m-1)*(n-i)]*F(i,m-1)%Mod);
		tmp=mod(tmp+1ll*Power[(m-1)*(i)]*F(n-i,m-1)%Mod);
		ans=mod(ans+1ll*C[n][i]*tmp%Mod);
	}
	return f[n][m]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	memset(f,-1,sizeof(f));
	memset(g,-1,sizeof(g));
	memset(p,-1,sizeof(p));
	n=read();m=read();Prepare();
	int Ans=1ll*F(n,m)*Pow(Power[n*m],Mod-2)%Mod;
	printf("%d",Ans);
	return 0;
}