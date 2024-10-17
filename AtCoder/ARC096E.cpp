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
const int N=3005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Mod,Phi,Ans,C[N][N],S[N][N],p1[N],p2[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	for(int i=0;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
	}
	S[0][0]=1;
	for(int i=1;i<N;i++){
		for(int j=1;j<=i;j++)S[i][j]=mod(S[i-1][j-1]+1ll*j*S[i-1][j]%Mod);
	}
	p1[0]=1;for(int i=1;i<N;i++)p1[i]=(p1[i-1]<<1)%Mod;
	p2[0]=1;for(int i=1;i<N;i++)p2[i]=(p2[i-1]<<1)%Phi;
}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Mod=read();Phi=Mod-1;Prepare();
	for(int k=0;k<=n;k++){
		int ans=0;
		for(int j=0;j<=k;j++)ans=mod(ans+1ll*S[k+1][j+1]*Pow(p1[n-k],j)%Mod);
		Ans=mod(Ans+1ll*ans*Pow(2,p2[n-k])%Mod*C[n][k]%Mod*(k&1?Mod-1:1)%Mod);
	}
	printf("%d",Ans);
	return 0;
}
