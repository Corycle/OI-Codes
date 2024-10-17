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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,F[N][N*N],C[N][N],Fac[N],Max[N];
int Sqr(int x){return 1ll*x*x%Mod;}
void Prepare(){
	n=500;
	for(int i=1;i<=n;i++){
		F[i][0]=1;
		Max[i]=Max[i-1]+i-1;
		for(int j=1;j<=Max[i];j++){
			F[i][j]=(F[i][j-1]+F[i-1][j])%Mod;
			if(j>=i)F[i][j]=(F[i][j]-F[i-1][j-i]+Mod)%Mod;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=Max[i];j++){
			F[i][j]=(F[i][j]+F[i][j-1])%Mod;
		}
	}
	C[0][0]=Fac[0]=1;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		Fac[i]=1ll*Fac[i-1]*i%Mod;
		for(int j=1;j<=i;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();Prepare();
	while(T--){
		n=read();m=read();Ans=0;
		for(int i=1;i<=n;i++){
			Ans=(Ans+1ll*(n-i+1)*F[i][min(m,Max[i])]%Mod*Sqr(1ll*C[n][i]*Fac[n-i]%Mod)%Mod)%Mod;
		}
		printf("%d\n",Ans);
	}
	return 0;
}