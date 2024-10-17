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
const int Phi=998244352;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,fac[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
namespace Task1{
	const int M=1e3+5;
	int F[M],G[M];
	void Main(){
		for(int k=1;k<=n;k++)G[k]=1ll*inv[n]*Pow(k,n)%Mod;
		for(int k=0;k<=n;k++)for(int i=0;i<k;i++)F[k]=mod(F[k]+1ll*(i&1?Mod-1:1)*C(n,i)%Mod*G[k-i]%Mod);
		for(int t=0;t<=n-1;t++)Ans=mod(Ans+1ll*mod(F[t+1]-F[t]+Mod)*Pow(t,m)%Mod);
		printf("%d",Ans);
	}
}
namespace Task2{
	int len,L,F[N],G[N],H[N],R[N];
	void NTT(int a[],int n,int f){
		for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
		for(int i=1;i<n;i<<=1){
			int Wn=Pow(3,Phi+f*Phi/(i<<1));
			for(int j=0;j<n;j+=(i<<1)){
				int W=1;
				for(int k=0;k<i;k++){
					int x=a[j+k],y=1ll*a[j+k+i]*W%Mod;
					a[j+k+i]=mod(x-y+Mod);
					a[j+k]=mod(x+y);
					W=1ll*W*Wn%Mod;
				}
			}
		}
		if(f==-1){
			int Inv=Pow(n,Mod-2);
			for(int i=0;i<n;i++)a[i]=1ll*a[i]*Inv%Mod;
		}
	}
	void Main(){
		for(int k=1;k<=n;k++)G[k]=1ll*inv[n]*Pow(k,n)%Mod;
		for(int i=0;i<=n;i++)H[i]=1ll*(i&1?Mod-1:1)*C(n,i)%Mod;
		len=1;L=0;while(len<=n+n){len<<=1;L++;}
		for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
		NTT(G,len,1);NTT(H,len,1);
		for(int i=0;i<len;i++)F[i]=1ll*G[i]*H[i]%Mod;
		NTT(F,len,-1);
		for(int i=n+1;i<len;i++)F[i]=0;
		for(int t=0;t<=n-1;t++)Ans=mod(Ans+1ll*mod(F[t+1]-F[t]+Mod)*Pow(t,m)%Mod);
		printf("%d",Ans);
	}
}
int main(){
//	freopen("expectation.in","r",stdin);
//	freopen("expectation.out","w",stdout);
	n=read();m=read();Prepare();
	if(n<=1000){Task1::Main();return 0;}
	Task2::Main();
	return 0;
}