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
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Ans[N],fac[N],C[N][N],E[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=0;i<N;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);}
	for(int i=0;i<N;i++){E[i][0]=1;for(int j=1;j<=i;j++)E[i][j]=mod(1ll*(j+1)*E[i-1][j]%Mod+1ll*(i-j)*E[i-1][j-1]%Mod);}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int k=1;k<=n;k++){
		for(int i=max(k-1,1);i<=n;i++)Ans[k]=mod(Ans[k]+1ll*E[i][k-1]*C[n][i]%Mod*fac[n-i]%Mod);
		printf("%d ",Ans[k]);
	}
	puts("");
	return 0;
}