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
const int M=4005;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,L,f[M][N][2],fac[M],inv[M];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<M;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<M;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<M;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();L=read();Prepare();
	f[0][0][0]=1;
	for(int i=0;i<n*2+1;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<2;k++){
				f[i+1][j+1][k]=mod(f[i+1][j+1][k]+f[i][j][k]);
				if(j)f[i+1][j-1][k]=mod(f[i+1][j-1][k]+1ll*f[i][j][k]*j%Mod);
			}
			if(j>=m)f[i+1][j][1]=mod(f[i+1][j][1]+f[i][j][0]);
		}
	}
	int Ans=1ll*f[n*2+1][0][1]*Pow(2,n)%Mod*fac[n]%Mod*inv[n*2+1]%Mod*L%Mod;
	printf("%d\n",Ans);
	return 0;
}
