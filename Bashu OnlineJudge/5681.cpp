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
const int Mod=1004535809;
const int Phi=1004535808;
const int N=10000005;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,len,lim,L,R[N],F[N],A[N],B[N],W[N],Ans[N],fac[N],inv[N];
void Prepare(){
	lim=min(m,n/S);
	int maxn=max(n,m);
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){
	return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
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
				W=1ll*W*Wn%Mod;
				a[j+k]=(x+y)%Mod;
				a[j+k+i]=(x-y+Mod)%Mod;
			}
		}
	}
	if(f==-1){
		int Inv=Pow(n,Mod-2);
		for(int i=0;i<n;i++)a[i]=1ll*a[i]*Inv%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();S=read();Prepare();
	for(int i=0;i<=m;i++)W[i]=read();
	for(int i=0;i<=lim;i++)F[i]=1ll*C(m,i)*C(n,i*S)%Mod*fac[i*S]%Mod*Pow(inv[S],i)%Mod*Pow(m-i,n-i*S)%Mod;
	for(int i=0;i<=lim;i++)A[i]=1ll*Pow(Mod-1,i)*inv[i]%Mod;
	for(int i=0;i<=lim;i++)B[i]=1ll*F[i]*fac[i]%Mod;
	len=1;L=0;while(len<=lim*2){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	/*
	Ans[i]*fac[i]=\sum_{j=i}^{lim}A[j-i]*B[j]
	             =\sum_{j=0}^{lim-i+1}A[lim-i+1-j]*B[lim-j+1];
	             =\sum_{j=0}^{lim-i+1}A[lim-i+1-j]*B'[j];
	*/
	int Answer=0;
	reverse(B,B+lim+1);
	NTT(A,len,1);NTT(B,len,1);
	for(int i=0;i<len;i++)Ans[i]=1ll*A[i]*B[i]%Mod;
	NTT(Ans,len,-1);
	reverse(Ans,Ans+lim+1);
	for(int i=0;i<len;i++)Ans[i]=1ll*Ans[i]*inv[i]%Mod;
	for(int i=0;i<=lim;i++)Answer=(Answer+1ll*Ans[i]*W[i]%Mod)%Mod;
	printf("%d",Answer);
	return 0;
}