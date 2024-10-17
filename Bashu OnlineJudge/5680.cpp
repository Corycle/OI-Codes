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
const int N=2022;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,Mod,C[N][N],Fac[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	Fac[0]=1;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
	}
	for(int i=1;i<=n;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Mod=read();Prepare();
	for(int i=2;i<=n;i++){
		for(int j=1;j<=n-i+1;j++){
			Ans=mod(Ans+1ll*Fac[j]*C[n-i][j-1]%Mod*j%Mod*(n-j)%Mod*Fac[n-j-1]%Mod*i%Mod*(i-1)%Mod);
		}
	}
	printf("%d",Ans);
	return 0;
}