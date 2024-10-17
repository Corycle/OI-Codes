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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,Lim;
int mu[N],vis[N],prime[N];
int L[N],R[N],F[N],G[N],F1[N],F2[N],num[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
void Prepare(){
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(!vis[i]){prime[++tot]=i;mu[i]=-1;}
		for(int j=1;j<=tot&&1ll*i*prime[j]<N;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
	for(int i=1;i<N;i++)mu[i]=mod(mu[i]+Mod);
	for(int i=1;i<N;i++)for(int j=i;j<N;j+=i)G[j]=mod(G[j]+1ll*mu[i]*i%Mod);
}
int Sum(int x){return (1ll*x*(x+1)/2)%Mod;}
void Update(int id){
	for(int l=1,r=0;l<=Lim;l=r+1){
		r=min(Lim,min(L[id]>=l?L[id]/(L[id]/l):inf,R[id]/(R[id]/l)));
		int tmp=mod(Sum(R[id]/l)-Sum(L[id]/l)+Mod);
		if(tmp){
			F1[l]=1ll*F1[l]*tmp%Mod;
			F2[r+1]=1ll*F2[r+1]*tmp%Mod;
		}
		else{num[l]++;num[r+1]--;}
	}
}
int main(){
//	freopen("ratio.in","r",stdin);
//	freopen("ratio.out","w",stdout);
	int Case=read();Prepare();
	while(Case--){
		n=read();Lim=inf;
		int ans=0,tmp=1;
		for(int i=1;i<=n;i++){
			L[i]=read()-1;R[i]=read();
			Lim=min(Lim,R[i]);tmp=1ll*tmp*(R[i]-L[i])%Mod;
		}
		if(n==1){puts("1");continue;}
		for(int i=0;i<=Lim;i++){F1[i]=F2[i]=1;num[i]=0;}
		for(int i=1;i<=n;i++)Update(i);
		for(int i=1;i<=Lim;i++)num[i]+=num[i-1];
		for(int i=1;i<=Lim;i++)F1[i]=1ll*F1[i-1]*F1[i]%Mod;
		for(int i=1;i<=Lim;i++)F2[i]=1ll*F2[i-1]*F2[i]%Mod;
		for(int i=1;i<=Lim;i++)F[i]=1ll*F1[i]*Pow(F2[i],Mod-2)%Mod*Pow(i,n-1)%Mod;
		for(int i=1;i<=Lim;i++)if(!num[i])ans=mod(ans+1ll*F[i]*G[i]%Mod);
		ans=1ll*ans*Pow(tmp,Mod-2)%Mod;
		printf("%d\n",ans);
	}
	return 0;
}