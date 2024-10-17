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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Mod,cnt,f[N],g[N],h[N],mu[N],vis[N],prime[N];
ll mod(ll x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(int maxn){
	mu[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(1e6);
	int T=read();
	while(T--){
		n=read();Mod=read();
		f[0]=0;f[1]=1;
		for(int i=1;i<=n;i++)h[i]=1;
		for(int i=2;i<=n;i++){
			f[i]=mod(2ll*f[i-1]%Mod+f[i-2]);
			int Inv=Pow(f[i],Mod-2);
			for(int j=i;j<=n;j+=i){
				if(mu[j/i]==1)h[j]=1ll*h[j]*f[i]%Mod;
				if(mu[j/i]==-1)h[j]=1ll*h[j]*Inv%Mod;
			}
		}
		g[0]=1;
		int Ans=0;
		for(int i=1;i<=n;i++){
			g[i]=1ll*g[i-1]*h[i]%Mod;
			Ans=mod(Ans+1ll*g[i]*i%Mod);
		}
		printf("%d\n",Ans);
	}
	return 0;
}