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
#include<unordered_map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Inv2=5e8+4;
const int Mod=1e9+7;
const int maxn=1e6;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
//g[n]=\sum_{i=1}^{n} i*\mu[i]
int n,cnt,Ans;
unordered_map<int,int>G,F;
int Fac[N],Inv[N],sum1[N],sum2[N];
int low[N],g[N],f[N],vis[N],prime[N];
int Sum(int x){return 1ll*(1+x)*x%Mod*Inv2%Mod;}
int mod(int x){return x>=Mod?x-Mod:x;}
int Sqr(int x){return 1ll*x*x%Mod;}
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
	f[1]=g[1]=Inv[0]=Inv[1]=Fac[0]=Fac[1]=1;
	for(int i=2;i<=maxn;i++){
		Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
		if(!vis[i]){prime[++cnt]=i;f[i]=mod(i+1);g[i]=mod(Mod-i);low[i]=1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				g[i*prime[j]]=0;
				low[i*prime[j]]=low[i];
				if(low[i]==1)f[i*prime[j]]=mod(1ll*f[i]*prime[j]%Mod+1);
				else f[i*prime[j]]=1ll*f[i*prime[j]/low[i*prime[j]]]*f[low[i*prime[j]]]%Mod;
				break;
			}
			low[i*prime[j]]=i;
			f[i*prime[j]]=1ll*f[i]*f[prime[j]]%Mod;
			g[i*prime[j]]=1ll*g[i]*g[prime[j]]%Mod;
		}
	}
	for(int i=2;i<=maxn;i++){
		f[i]=mod(f[i-1]+f[i]);
		g[i]=mod(g[i-1]+g[i]);
		Fac[i]=1ll*Fac[i-1]*i%Mod;
		Inv[i]=1ll*Inv[i-1]*Inv[i]%Mod;
	}
}
int SumG(int n){
	if(n<=maxn)return g[n];
	if(G[n])return G[n];
	int ans=1;
	for(int i=2,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans=mod(ans-1ll*mod(Sum(j)-Sum(i-1)+Mod)*SumG(n/i)%Mod+Mod);
	}
	return G[n]=(ans%Mod+Mod)%Mod;
}
int GetF(int n){
	if(n<=maxn)return f[n];
	if(F[n])return F[n];
	int ans=0;
	for(int i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans=mod(ans+1ll*mod(Sum(j)-Sum(i-1)+Mod)*(n/i)%Mod);
	}
	return F[n]=(ans%Mod+Mod)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		Ans=mod(Ans+1ll*mod(SumG(j)-SumG(i-1)+Mod)*Sqr(GetF(n/i))%Mod);
	}
	printf("%d",Ans);
	return 0;
}