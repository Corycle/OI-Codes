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
const int N=7505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,Ans,Mod,Phi;
int F[N],G[N],C[N][N],Fac[N],vis[N],prime[N];
int mod(int x){return x>=Phi?x-Phi:x;}
int Pow(int x,int y,int mod){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%mod;x=1ll*x*x%mod;y>>=1;}
	return ans;
}
void Prepare(){
	Fac[0]=1;
	for(int i=1;i<N;i++)Fac[i]=1ll*Fac[i-1]*i%Phi;
	for(int i=0;i<N;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);}
	for(int i=2;i<N;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<N;j++){vis[i*prime[j]]=1;if(i%prime[j]==0)break;}
	}
	for(int i=1;i<=cnt;i++)for(int j=prime[i];j<N;j*=prime[i])G[j]=prime[i];
}
int Solve(int s){
	int num=n/s,ans=0;F[0]=Phi-1;
	for(int i=1;i<=num;i++)F[i]=0;
	for(int i=1;i<=num;i++){
		for(int j=1;j<=i;j++){
			F[i]=mod(F[i]-1ll*F[i-j]*C[i*s-1][j*s-1]%Phi*Fac[j*s-1]%Phi+Phi);
		}
	}
	for(int i=1;i<=num;i++)ans=mod(ans+1ll*F[i]*C[n][i*s]%Phi*Fac[n-i*s]%Phi);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Mod=read();Phi=Mod-1;Prepare();Ans=1;
	for(int i=2;i<=n;i++)if(G[i])Ans=1ll*Ans*Pow(G[i],Solve(i),Mod)%Mod;
	printf("%d\n",Ans);
	return 0;
}
