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
const int N=525000;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,len,L,R[N],a[N],b[N],v[N],f[N],g[N],t1[N],t2[N],t3[N],t4[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
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
vector<int> Multi(const vector<int>&A,const vector<int>&B){
	int n=A.size(),m=B.size();Prepare(n+m-2);
	for(int i=0;i<n;i++)t1[i]=A[i];
	for(int i=0;i<m;i++)t2[i]=B[i];
	for(int i=n;i<len;i++)t1[i]=0;
	for(int i=m;i<len;i++)t2[i]=0;
	NTT(t1,len,1);NTT(t2,len,1);
	for(int i=0;i<len;i++)t1[i]=1ll*t1[i]*t2[i]%Mod;
	NTT(t1,len,-1);
	vector<int>C;C.resize(n+m-1);
	for(int i=0;i<n+m-1;i++)C[i]=t1[i];
	return C;
}
vector<int> Solve(int l,int r){
	if(l==r){
		vector<int>F;F.resize(2);
		F[0]=1;F[1]=mod(Mod-v[l]);
		return F;
	}
	int mid=(l+r)>>1;
	return Multi(Solve(l,mid),Solve(mid+1,r));
}
void Derivation(int A[],int B[],int n){for(int i=1;i<n;++i)B[i-1]=1ll*A[i]*i%Mod;B[n-1]=0;}
void Integral(int A[],int B[],int n){for(int i=1;i<n;++i)B[i]=1ll*A[i-1]*inv[i]%Mod;B[0]=0;}
void Inverse(int A[],int B[],int n){
	if(n==1){B[0]=Pow(A[0],Mod-2);return;}
	Inverse(A,B,(1+n)>>1);Prepare(n+n);
	for(int i=0;i<n;i++)t3[i]=A[i];
	for(int i=0;i<n;i++)t4[i]=B[i];
	for(int i=n;i<len;i++)t3[i]=0;
	for(int i=n;i<len;i++)t4[i]=0;
	NTT(t3,len,1);NTT(t4,len,1);
	for(int i=0;i<len;i++)t3[i]=mod(2ll*t4[i]%Mod-1ll*t3[i]*t4[i]%Mod*t4[i]%Mod+Mod);
	NTT(t3,len,-1);
	for(int i=0;i<n;i++)B[i]=t3[i];
	for(int i=n;i<len;i++)B[i]=0;
}
void Logarithm(int A[],int B[],int n){
	Derivation(A,t1,n);Inverse(A,t2,n);Prepare(n+n);
	for(int i=n;i<len;i++)t1[i]=0;
	for(int i=n;i<len;i++)t2[i]=0;
	NTT(t1,len,1);NTT(t2,len,1);
	for(int i=0;i<len;i++)t1[i]=1ll*t1[i]*t2[i]%Mod;
	NTT(t1,len,-1);Integral(t1,B,n);
	for(int i=n;i<len;i++)B[i]=0;
}
int F[N],F1[N],F2[N],Fac[N],Inv[N];
void GetF(int a[],int F[],int n,int K){
	for(int i=1;i<=n;i++)v[i]=a[i];
	vector<int>tmp=Solve(1,n);
	for(int i=0;i<=min(n,K);i++)f[i]=tmp[i];
	for(int i=min(n,K)+1;i<=K+1;i++)f[i]=0;
	Logarithm(f,g,K+1);Derivation(g,f,K+1);
	for(int i=K;i>=1;i--)F[i]=1ll*mod(Mod-f[i-1])*Inv[i]%Mod;
	F[0]=n;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)Inv[i]=1ll*Inv[i-1]*inv[i]%Mod;
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	int K=read();GetF(a,F1,n,K);GetF(b,F2,m,K);
	Prepare(K+K);
	for(int i=K+1;i<len;i++)F1[i]=F2[i]=0;
	NTT(F1,len,1);NTT(F2,len,1);
	for(int i=0;i<len;i++)F[i]=1ll*F1[i]*F2[i]%Mod;
	NTT(F,len,-1);
	for(int i=0;i<len;i++)F[i]=1ll*F[i]*Fac[i]%Mod*Pow(n,Mod-2)%Mod*Pow(m,Mod-2)%Mod;
	for(int i=1;i<=K;i++)printf("%d\n",F[i]);
	return 0;
}