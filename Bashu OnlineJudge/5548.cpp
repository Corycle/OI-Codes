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
const int N=200005;
const int M=450;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,f[2][N],g[N],Fac[N],Inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=1;
	for(int i=2;i<=maxn;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)Inv[i]=1ll*Inv[i-1]*Inv[i]%Mod;
}
int C(int n,int m){
	return n<m?0:1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();Prepare(2e5);
	int t=0;f[t][0]=1;g[0]=1;
	for(int i=1;i<M;i++){
		t^=1;
		memset(f[t],0,sizeof(f[t]));
		for(int j=i;j<=K;j++){
			f[t][j]=mod(f[t][j]+mod(f[t][j-i]+f[t^1][j-i]));
			if(j>n)f[t][j]=mod(f[t][j]-f[t^1][j-n-1]+Mod);
		}
		for(int j=i;j<=K;j++){
			if(i&1)g[j]=mod(g[j]-f[t][j]+Mod);
			else g[j]=mod(g[j]+f[t][j]);
		}
	}
	int Ans=0;
	for(int i=0;i<=K;i++){
		Ans=mod(Ans+1ll*g[i]*C(n+K-i-1,n-1)%Mod);
	}
	printf("%d",Ans);
	return 0;
}