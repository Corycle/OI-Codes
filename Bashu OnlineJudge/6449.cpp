/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
#define uint unsigned int
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool vis[N];
uint Ans,f[N],g[N],pk[N];
int n,m,K,cnt,tot,w[N],id1[N],id2[N],prime[N];
inline int ID(int x){return x<=m?id1[x]:id2[n/x];}
inline uint Sqr(uint x){return x*x;}
inline uint Pow(uint x,int y){
	uint ans=1;
	while(y){if(y&1)ans=ans*x;x=x*x;y>>=1;}
	return ans;
}
inline void Prepare(){
	for(int i=2;i<=m;i++){
		if(!vis[i]){prime[++cnt]=i;pk[cnt]=Pow(i,K);}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=m;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	for(int i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);w[++tot]=n/i;g[tot]=w[tot]-1;
		w[tot]<=m?id1[w[tot]]=tot:id2[n/w[tot]]=tot;
	}
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=tot&&1ll*prime[i]*prime[i]<=w[j];j++){
			g[j]=g[j]-(g[ID(w[j]/prime[i])]-(i-1));
		}
	}
}
uint S(int n,int x){//Min_25
	if(n<=1||n<prime[x])return 0;
	uint ans=0;
	for(int i=x+1;i<=cnt&&1ll*prime[i]*prime[i]<=n;i++){
		for(int Pe=prime[i];Pe<=n/prime[i];Pe=Pe*prime[i]){
			ans+=S(n/Pe,i)+pk[i]*(g[ID(n/Pe)]-(i-1));
		}
	}
	return ans;
}
inline uint F(int n){//Du Jiao
	if(f[ID(n)])return f[ID(n)];
	uint ans=S(n,0)+g[ID(n)];
	for(int i=2,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans=ans-F(n/i)*(j-i+1);
	}
	return f[ID(n)]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();m=sqrt(n);Prepare();
	uint lst=0;
	for(int i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		uint now=F(j);
		Ans=(Ans+Sqr(n/i)*(now-lst));
		lst=now;
	}
	printf("%u",Ans);
	return 0;
}