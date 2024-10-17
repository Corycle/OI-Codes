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
const int N=2e5+5;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,len,L,R[N],A[N],B[N],fac[N],inv[N],f[2][N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
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
				a[j+k]=mod(x+y);a[j+k+i]=mod(x-y+Mod);W=1ll*W*Wn%Mod;
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
	n=read();m=read();
	int t=0;Prepare(2e5);
	len=1;L=0;while(len<=n+n+2){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	for(int i=0;i<=n;i++)f[t][i]=C(n,i);
	for(int i=m-1;i>=0;i--){
		t^=1;
		for(int j=0;j<len;j++)A[j]=B[j]=0;
		for(int j=0;j<n;j++)A[j]=inv[n-j+2];
		for(int j=0;j<=n;j++)B[j]=1ll*f[t^1][j]*fac[j+2]%Mod;
		NTT(A,len,1);NTT(B,len,1);
		for(int j=0;j<len;j++)A[j]=1ll*A[j]*B[j]%Mod;
		NTT(A,len,-1);
		for(int j=0;j<=n;j++)f[t][j]=mod(1ll*A[n+j]*inv[j]%Mod+1ll*f[t^1][j]*mod(C(j+1,2)+1)%Mod);
	}
	printf("%d",f[t][0]);
	return 0;
}