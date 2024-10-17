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
const int Inv2=5e8+4;
const int Mod=1e9+7;
const int N=50005;
const int M=21;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,Sum[N][M],Inv[N][M];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Matrix{
	int a[M][M];
	void Init(){memset(a,0,sizeof(a));}
	friend Matrix Multi1(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=0;i<=K;i++){
			for(int k=i;k<=K;k++){
				if(!A.a[i][k])continue;
				for(int j=k;j<=K;j++){
					C.a[i][j]=mod(C.a[i][j]+1ll*A.a[i][k]*B.a[k][j]%Mod);
				}
			}
		}
		return C;
	}
	friend Matrix Multi2(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int k=0;k<=K;k++){
			for(int j=k;j<=K;j++){
				if(!B.a[k][j])continue;
				for(int i=0;i<=k;i++){
					C.a[i][j]=mod(C.a[i][j]+1ll*A.a[i][k]*B.a[k][j]%Mod);
				}
			}
		}
		return C;
	}
}I,A,B,tmp;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=0;i<=K;i++)I.a[i][i]=1;
	for(int i=0;i<=K;i++)Sum[0][i]=1;
	A=B=I;Inv[0][0]=1;
	for(int t=1;t<=n;t++){
		int x=read();
		tmp=I;
		for(int i=0;i<x;i++)tmp.a[i][x]=1;
		tmp.a[x][x]=2;
		A=Multi1(A,tmp);
		tmp=I;
		for(int i=0;i<x;i++)tmp.a[i][x]=Mod-Inv2;
		tmp.a[x][x]=Inv2;
		B=Multi2(tmp,B);
		for(int i=0;i<=K;i++)Inv[t][i]=B.a[0][i];
		for(int i=0;i<=K;i++){
			for(int j=i;j<=K;j++){
				Sum[t][i]=mod(Sum[t][i]+A.a[i][j]);
			}
		}
	}
	m=read();
	while(m--){
		int l=read()-1,r=read();
		int Ans=0;
		for(int i=0;i<=K;i++){
			Ans=mod(Ans+1ll*Inv[l][i]*Sum[r][i]%Mod);
		}
		printf("%d\n",Ans);
	}
	return 0;
}