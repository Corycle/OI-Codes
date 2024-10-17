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
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int S[N],F[N],G[N],C[N][N];
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
	for(int i=0;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=0;i<N;i++)F[i]=Pow(2,i*(i-1)/2);
	for(int i=1;i<m;i++){
		S[i]=F[i];
		for(int j=1;j<i;j++){
			S[i]=mod(S[i]-1ll*C[i][j]*S[j]%Mod*F[i-j]%Mod+Mod);
		}
	}
	G[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<m&&j<=i;j++){
			G[i]=mod(G[i]+1ll*C[i][j]*S[j]%Mod*G[i-j]%Mod);
		}
	}
	printf("%d",(F[n]-G[n]+Mod)%Mod);
	return 0;
}