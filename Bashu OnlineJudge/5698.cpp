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
const int Mod=1e9+7;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,Ans,a[N],f[N],g[N],A[N],B[N],C[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Multi(int A[],int B[]){//Query A * B Mod G
	for(int i=0;i<=K*2;i++)C[i]=0;
	for(int i=0;i<K;i++){
		for(int j=0;j<K;j++){
			C[i+j]=mod(C[i+j]+1ll*A[i]*B[j]%Mod);
		}
	}
	for(int i=2*K-1;i>=K;i--){
		for(int j=K-1;j>=0;j--){
			C[i+j-K]=mod(C[i+j-K]-1ll*C[i]*g[j]%Mod+Mod);
		}
		C[i]=0;
	}
	for(int i=0;i<K;i++)A[i]=C[i];
}
void Solve(int t){//Query Pow(x,n) Mod G
	A[0]=B[1]=1;
	while(t){
		if(t&1)Multi(A,B);
		Multi(B,B);
		t>>=1;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<=K;i++)a[i]=mod(read()+Mod);
	for(int i=0;i<K;i++)f[i]=mod(read()+Mod);
	for(int i=1;i<=K;i++)g[K-i]=mod(Mod-a[i]);g[K]=1;
	Solve(n);
	for(int i=0;i<K;i++)Ans=mod(Ans+1ll*A[i]*f[i]%Mod);
	printf("%d",Ans);
	return 0;
}