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
const int N=200005;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int len,L,R[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	L=0;len=1;while(len<=maxn){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
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

int n,K,Ans;
int a[N],f[N],g[N],g1[N],g2[N],A[N],B[N],t1[N],t2[N];
void GetInv(int A[],int B[],int n){//Query 1 / A
	if(n==1){B[0]=Pow(A[0],Mod-2);return;}
	GetInv(A,B,(1+n)>>1);Prepare(n+n);
	for(int i=0;i<n;i++)t1[i]=A[i];
	for(int i=0;i<n;i++)t2[i]=B[i];
	for(int i=n;i<=len;i++)t1[i]=0;
	for(int i=n;i<=len;i++)t2[i]=0;
	NTT(t1,len,1);NTT(t2,len,1);
	for(int i=0;i<len;i++){
		t1[i]=mod(t2[i]*2ll%Mod-1ll*t2[i]*t2[i]%Mod*t1[i]%Mod+Mod);
	}
	NTT(t1,len,-1);
	for(int i=0;i<n;i++)B[i]=t1[i];
	for(int i=n;i<len;i++)B[i]=0;
}
void Multi(int A[],int B[]){//Query A * B
	Prepare(K+K);
	for(int i=0;i<len;i++)t1[i]=A[i];
	for(int i=0;i<len;i++)t2[i]=B[i];
	NTT(t1,len,1);NTT(t2,len,1);
	for(int i=0;i<len;i++)t1[i]=1ll*t1[i]*t2[i]%Mod;
	NTT(t1,len,-1);
	for(int i=0;i<len;i++)A[i]=t1[i];
}
void GetMod(int A[]){//Query A Mod G
	Prepare(K+K);
	for(int i=0;i<len;i++)t1[i]=A[i];
	int tmp=len-1;while(tmp&&!t1[tmp])tmp--;
	if(tmp<K)return;reverse(t1,t1+tmp+1);
	for(int i=tmp-K+1;i<len;i++)t1[i]=0;
	NTT(t1,len,1);for(int i=0;i<len;i++)t1[i]=1ll*t1[i]*g2[i]%Mod;NTT(t1,len,-1);
	for(int i=tmp-K+1;i<len;i++)t1[i]=0;reverse(t1,t1+tmp-K+1);
	NTT(t1,len,1);for(int i=0;i<len;i++)t1[i]=1ll*t1[i]*g1[i]%Mod;NTT(t1,len,-1);
	for(int i=0;i<K;i++)A[i]=mod(A[i]-t1[i]+Mod);//A - (A / G Mod x^(tmp-K+1)) * G
	for(int i=K;i<len;i++)A[i]=0;
}
void Solve(int t){//Query Pow(x,n) Mod G
	A[0]=B[1]=1;
	while(t){
		if(t&1){Multi(A,B);GetMod(A);}
		Multi(B,B);GetMod(B);
		t>>=1;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();Prepare(K);
	for(int i=1;i<=K;i++)a[i]=mod(read()+Mod);
	for(int i=0;i<K;i++)f[i]=mod(read()+Mod);
	for(int i=1;i<=K;i++)g1[K-i]=mod(Mod-a[i]);g1[K]=1;
	for(int i=0;i<=K;i++)g[i]=g1[i];
	reverse(g,g+K+1);GetInv(g,g2,len);
	Prepare(K+K);NTT(g1,len,1);NTT(g2,len,1);Solve(n);
	for(int i=0;i<K;i++)Ans=mod(Ans+1ll*A[i]*f[i]%Mod);
	printf("%d",Ans);
	return 0;
}
