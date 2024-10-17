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
const int N=167;
const int M=63;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Matrix{
	int n,m,a[N][N];
	void Init(int x,int y){n=x;m=y;memset(a,0,sizeof(a));}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init(A.n,B.m);
		for(int i=0;i<C.n;i++){
			for(int j=0;j<C.m;j++){
				__int128 tmp=0;
				for(int k=0;k<A.m;k++){
					tmp+=1ll*A.a[i][k]*B.a[k][j];
				}
				C.a[i][j]=tmp%Mod;
			}
		}
		return C;
	}
}P[M],A;
int m,K,tot,id[9][9][9],inv[M];
void Prepare2(){
	for(int i=0;i<=K;i++){
		for(int j=0;i+j<=K;j++){
			id[i][j][0]=tot++;
		}
	}
	for(int i=0;i<=K;i++){
		for(int j=0;i+j<=K;j++){
			int x=id[i][j][0];
			if(i)P[0].a[x][id[i-1][j][0]]=1ll*i*inv[i+j+1]%Mod;
			if(j){
				if(i+j<K)P[0].a[x][id[i+1][j][0]]=1ll*j*inv[i+j+1]%Mod;
				else P[0].a[x][id[i+1][j-1][0]]=1ll*j*inv[i+j+1]%Mod;
			}
			P[0].a[x][tot]=P[0].a[x][x]=inv[i+j+1];
		}
	}
	P[0].a[tot][tot]=1;
	P[0].n=P[0].m=tot+1;
}
void Prepare3(){
	for(int i=0;i<=K;i++){
		for(int j=0;i+j<=K;j++){
			for(int k=0;i+j+k<=K;k++){
				id[i][j][k]=tot++;
			}
		}
	}
	for(int i=0;i<=K;i++){
		for(int j=0;i+j<=K;j++){
			for(int k=0;i+j+k<=K;k++){
				int x=id[i][j][k];
				if(i)P[0].a[x][id[i-1][j][k]]=1ll*i*inv[i+j+k+1]%Mod;
				if(j){
					if(i+j+k<K)P[0].a[x][id[i+1][j-1][k+1]]=1ll*j*inv[i+j+k+1]%Mod;
					else P[0].a[x][id[i+1][j-1][k]]=1ll*j*inv[i+j+k+1]%Mod;
				}
				if(k){
					if(i+j+k<K)P[0].a[x][id[i][j+1][k]]=1ll*k*inv[i+j+k+1]%Mod;
					else P[0].a[x][id[i][j+1][k-1]]=1ll*k*inv[i+j+k+1]%Mod;
				}
				P[0].a[x][tot]=P[0].a[x][x]=inv[i+j+k+1];
			}
		}
	}
	P[0].a[tot][tot]=1;
	P[0].n=P[0].m=tot+1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();m=read();K=read();inv[1]=1;
	for(int i=2;i<M;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	if(m==3)Prepare3();else Prepare2();
	for(int i=1;i<M;i++)P[i]=P[i-1]*P[i-1];
	while(T--){
		ll n=read();A.Init(1,tot+1);
		if(m==1)A.a[0][id[1][0][0]]=1;
		if(m==2)A.a[0][id[0][1][0]]=1;
		if(m==3)A.a[0][id[0][0][1]]=1;
		for(int i=0;i<M;i++){
			if((n>>i)&1)A=A*P[i];
		}
		printf("%d\n",A.a[0][A.m-1]);
	}
	return 0;
}