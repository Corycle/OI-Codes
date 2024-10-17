/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int M=1<<20;
const int N=21;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,Sta,c[N][N],sta[M],num[M];
int A[N][M],B[N][M],C[N][M],F[M],G[M];
inline int lowbit(int x){return x&(-x);}
inline int mod(int x){return x>=Mod?x-Mod:x;}
inline void FMT(int a[],int f){
	for(register int i=1;i<=Sta;i<<=1){
		for(register int j=0;j<=Sta;j+=(i<<1)){
			for(register int k=0;k<i;++k){
				if(f==1)a[j+k+i]=mod(a[j+k+i]+a[j+k]);
				else a[j+k+i]=mod(a[j+k+i]-a[j+k]+Mod);
			}
		}
	}
//	for(register int i=1;i<=Sta;i<<=1){
//		for(register int j=0;j<=Sta;j++){
//			if(i&j)a[j]=(f==1?mod(a[j]+a[j-i]):mod(a[j]-a[j-i]+Mod));
//		}
//	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Sta=(1<<n)-1;
	for(register int i=0;i<n;i++){
		sta[1<<i]=i;
		for(register int j=i+1;j<n;j++){
			c[i][j]=c[j][i]=read();
		}
	}
	A[0][0]=B[0][0]=G[0]=1;
	for(register int S=1;S<=Sta;S++){
		G[S]=G[S-lowbit(S)];
		num[S]=num[S-lowbit(S)]+1;
		for(register int i=0,x=sta[lowbit(S)];i<n;i++){
			if((S>>i)&1)G[S]=1ll*G[S]*(c[i][x]+1)%Mod;
		}
		A[num[S]][S]=G[S];
		B[num[S]][S]=(S&1)?0:G[S];
	}
	for(register int i=0;i<=n;i++){FMT(A[i],1);FMT(B[i],1);}
	for(register int S=0;S<=Sta;S++){
		C[0][S]=1;//C=Inv(B);
		for(register int i=1;i<=n;i++){
			ll t=C[i][S];
			for(register int j=0;j<i;j++){
				t-=1ll*C[j][S]*B[i-j][S];
			}
			C[i][S]=mod(t%Mod+Mod);
		}
	}
	for(register int S=0;S<=Sta;S++){
		for(register int i=0;i<=n;i++){
			F[S]=mod(F[S]+1ll*A[i][S]*C[n-i][S]%Mod);
		}
	}
	FMT(F,-1);
	printf("%d",F[Sta]);
	return 0;
}