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
const int N=400005;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int fac[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
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
int c(int n,int m){
	return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
int A[N],B[N],C[N],L,R[N];
void NTT(int a[],int n,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		int Wn=Pow(G,Phi+f*Phi/(i<<1));
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
void S(int n){
	if(n==0){A[0]=1;return;}
	if(n==1){A[0]=0;A[1]=1;return;}
	if(n&1){
		S(n-1);
		for(int i=n;i>=0;i--){
			A[i]=1ll*A[i]*(n-1)%Mod;
			A[i]=mod(A[i]+A[i-1]);
		}
		return;
	}
	S(n>>1);int m=n>>1;
	int len=1;L=0;while(len<=m+m){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	
	for(int i=0;i<=m;i++)B[i]=1ll*Pow(m,i)*inv[i]%Mod;
	for(int i=0;i<=m;i++)C[i]=1ll*A[m-i]*fac[m-i]%Mod;
	for(int i=m+1;i<len;i++)B[i]=C[i]=0;
	NTT(B,len,1);NTT(C,len,1);
	for(int i=0;i<len;i++)C[i]=1ll*B[i]*C[i]%Mod;
	NTT(C,len,-1);
	
	for(int i=0;i<=m;i++)B[i]=1ll*C[m-i]*inv[i]%Mod;
	for(int i=m+1;i<len;i++)B[i]=0;
	NTT(A,len,1);NTT(B,len,1);
	for(int i=0;i<len;i++)A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,len,-1);
	for(int i=n+1;i<len;i++)A[i]=0;
}
int n,a,b;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();a=read();b=read();
	Prepare(max(n,a+b));S(n-1);
	printf("%lld\n",1ll*c(a+b-2,a-1)*A[a+b-2]%Mod);
	return 0;
}