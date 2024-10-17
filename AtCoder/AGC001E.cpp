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
const int Inv2=5e8+4;
const int Mod=1e9+7;
const int N=2e5+5;
const int M=4005;
const int P=2001;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int a[N],b[N],fac[N],inv[N],f[M][M];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int i=1;i<=n;i++){a[i]=read();b[i]=read();f[P-a[i]][P-b[i]]++;}
	for(int i=1;i<M;i++)for(int j=1;j<M;j++)f[i][j]=mod(f[i][j]+mod(f[i-1][j]+f[i][j-1]));
	for(int i=1;i<=n;i++){Ans=mod(Ans+f[P+a[i]][P+b[i]]);Ans=mod(Ans-C(a[i]*2+b[i]*2,b[i]*2)+Mod);}
	Ans=1ll*Ans*Inv2%Mod;
	printf("%d\n",Ans);
	return 0;
}
