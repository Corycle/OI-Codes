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
const int N=66000;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,len,L,R[N],P[N];
int A[N],B[N],fac[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void NTT(int a[],int n,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		int Wn=Pow(G,Phi+f*Phi/(i<<1));
		for(int j=0;j<n;j+=(i<<1)){
			int W=1;
			for(int k=0;k<i;k++){
				int x=a[j+k],y=1ll*W*a[j+k+i]%Mod;
				a[j+k+i]=mod(x-y+Mod);
				a[j+k]=mod(x+y);
				W=1ll*W*Wn%Mod;
			}
		}
	}
	if(f==-1){
		int Inv=Pow(n,Mod-2);
		for(int i=0;i<len;i++)a[i]=1ll*a[i]*Inv%Mod;
	}
}
void Prepare(int maxn){
	P[0]=fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=1;i<=maxn;i++)P[i]=mod(P[i-1]<<1);
	for(int i=2;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){
	return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
void Solve(int n){
	if(n==1){
		for(int i=1;i<=K;i++)A[i]=inv[i];
		return;
	}
	if(n&1){
		Solve(n-1);
		for(int i=0;i<len;i++)A[i]=1ll*A[i]*P[i]%Mod;
		for(int i=1;i<len;i++)B[i]=inv[i];B[0]=0;
		NTT(A,len,1);NTT(B,len,1);
		for(int i=0;i<len;i++)A[i]=1ll*A[i]*B[i]%Mod;
		NTT(A,len,-1);
		for(int i=K+1;i<len;i++)A[i]=0;
		return;
	}
	Solve(n/2);m=n/2;
	for(int i=0;i<len;i++)B[i]=1ll*A[i]*Pow(P[m],i)%Mod;
	NTT(A,len,1);NTT(B,len,1);
	for(int i=0;i<len;i++)A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,len,-1);
	for(int i=K+1;i<len;i++)A[i]=0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();Prepare(K);
	len=1;L=0;while(len<=K+K){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	Solve(n);
	int Ans=0;
	for(int i=0;i<=K;i++)A[i]=1ll*A[i]*fac[i]%Mod;
	for(int i=0;i<=K;i++)Ans=mod(Ans+1ll*A[i]*C(K,i)%Mod);
	printf("%d",Ans);
	return 0;
}