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
const int N=524300;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,len,L,R[N],P[N],a[N],b[N],f[N],g[N],fac[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
void Init(){
	P[0]=fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=1;i<N;i++)P[i]=mod(P[i-1]<<1);
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
void Prepare(int maxn){
	len=1;L=0;while(len<=maxn){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
}
void NTT(int a[],int n,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		int Wn=Pow(G,Phi+f*Phi/(i<<1));
		for(int j=0;j<n;j+=(i<<1)){
			int W=1;
			for(int k=0;k<i;k++){
				int x=a[j+k],y=1ll*a[j+k+i]*W%Mod;
				a[j+k]=mod(x+y);a[j+k+i]=mod(x-y+Mod);W=1ll*W*Wn%Mod;
			}
		}
	}
	if(f==-1){int Inv=Pow(n,Mod-2);for(int i=0;i<n;i++)a[i]=1ll*a[i]*Inv%Mod;}
}
int main(){
//	freopen("fight.in","r",stdin);
//	freopen("fight.out","w",stdout);
	n=read();m=read();Init();Prepare(n+n);
	
	for(int i=1;i<n;i++)a[i]=1ll*P[i]*inv[i]%Mod*inv[i-1]%Mod;
	for(int i=0;i<n;i++)b[i]=1ll*fac[n-i-1]*inv[i]%Mod*(i&1?Mod-1:1)%Mod;
	NTT(a,len,1);NTT(b,len,1);
	for(int i=0;i<len;i++)a[i]=1ll*a[i]*b[i]%Mod;
	NTT(a,len,-1);
	for(int i=0;i<n;i++)g[i]=1ll*a[i]*fac[i]%Mod*fac[i]%Mod*inv[n-i]%Mod;
//	for(int i=0;i<n;i++)cout<<g[i]<<" ";cout<<endl;
	
	for(int i=0;i<len;i++)a[i]=b[i]=0;
	for(int i=0;i<n;i++)a[i]=1ll*g[i]%Mod*fac[n-i]%Mod;
	for(int i=0;i<n;i++)b[i]=1ll*inv[i]*(i&1?Mod-1:1)%Mod;
	NTT(a,len,1);NTT(b,len,1);
	for(int i=0;i<len;i++)a[i]=1ll*a[i]*b[i]%Mod;
	NTT(a,len,-1);
	for(int i=0;i<n;i++)f[i]=1ll*a[i]*inv[n-i]%Mod;
//	for(int i=0;i<n;i++)cout<<f[i]<<" ";cout<<endl;
	
	for(int i=1;i<=m+1;i++)Ans=mod(Ans+f[i]);
	printf("%d\n",Ans);
	return 0;
}