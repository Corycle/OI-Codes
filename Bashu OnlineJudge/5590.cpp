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
const int Mod=1e9+7;
const int maxn=1e7;
const int N=1e7+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
//l[n]=\sum_{i=1}^{n} i^K
//g[n]=\sum_{i=1}^{n} i^K*\mu[i]
ll n;
int K,cnt,Ans;
unordered_map<ll,int>L,G,F;
int Fac[N],Inv[N],sum1[N],sum2[N];
int l[N],f[N],g[N],low[N],vis[N],prime[N];
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
	l[1]=f[1]=g[1]=Inv[0]=Inv[1]=Fac[0]=Fac[1]=1;
	for(int i=2;i<=maxn;i++){
		Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
		if(!vis[i]){
			prime[++cnt]=i;
			l[i]=Pow(i,K);
			f[i]=mod(l[i]+1);
			g[i]=mod(Mod-l[i]);
			low[i]=i;
		}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			l[i*prime[j]]=1ll*l[i]*l[prime[j]]%Mod;
			if(i%prime[j]==0){
				g[i*prime[j]]=0;
				low[i*prime[j]]=low[i]*prime[j];
				if(low[i*prime[j]]==i*prime[j])f[i*prime[j]]=mod(1ll*f[i]*l[prime[j]]%Mod+1);
				else f[i*prime[j]]=1ll*f[i/low[i]]*f[low[i]*prime[j]]%Mod;
				break;
			}
			low[i*prime[j]]=prime[j];
			f[i*prime[j]]=1ll*f[i]*f[prime[j]]%Mod;
			g[i*prime[j]]=1ll*g[i]*g[prime[j]]%Mod;
		}
	}
	for(int i=2;i<=maxn;i++){
		l[i]=mod(l[i-1]+l[i]);
		f[i]=mod(f[i-1]+f[i]);
		g[i]=mod(g[i-1]+g[i]);
		Fac[i]=1ll*Fac[i-1]*i%Mod;
		Inv[i]=1ll*Inv[i-1]*Inv[i]%Mod;
	}
}
int Lagrange(ll n){
	if(n<=maxn)return l[n];
	if(L[n])return L[n];
	int ans=0,x=n%Mod;sum1[0]=sum2[K+3]=1;
	for(int i=1;i<=K+2;i++)sum1[i]=1ll*sum1[i-1]*mod(x-i+Mod)%Mod;
	for(int i=K+2;i>=1;i--)sum2[i]=1ll*sum2[i+1]*mod(x-i+Mod)%Mod;
	for(int i=1;i<=K+2;i++){
		int t=((K-i+2)&1)?Mod-1:1;
		int t1=1ll*sum1[i-1]*sum2[i+1]%Mod;
		int t2=1ll*Inv[i-1]*Inv[K-i+2]%Mod;
		ans=mod(ans+1ll*t1*t2%Mod*t%Mod*l[i]%Mod);
	}
	return L[n]=ans;
}
int SumG(ll n){
	if(n<=maxn)return g[n];
	if(G[n])return G[n];
	int ans=1;
	for(ll i=2,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans=mod(ans-1ll*mod(Lagrange(j)-Lagrange(i-1)+Mod)*SumG(n/i)%Mod+Mod);
	}
	return G[n]=ans;
}
int GetF(ll n){
	if(n<=maxn)return f[n];
	if(F[n])return F[n];
	int ans=0;
	for(ll i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans=mod(ans+1ll*mod(Lagrange(j)-Lagrange(i-1)+Mod)*(n/i)%Mod);
	}
	return F[n]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();Prepare();
	for(ll i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		Ans=mod(Ans+1ll*mod(SumG(j)-SumG(i-1)+Mod)*Sqr(GetF(n/i))%Mod);
	}
	printf("%d",Ans);
	return 0;
}