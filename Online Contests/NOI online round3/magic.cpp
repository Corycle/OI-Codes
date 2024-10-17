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
#include<bitset>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=105;
const int M=35;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N];
int n,m,Q;
struct Matrix{
	int a[N][N];
	void Init(){for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=0;}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=1;i<=n;i++){
			for(int k=1;k<=n;k++){
				if(!A.a[i][k])continue;
				for(int j=1;j<=n;j++){
					C.a[i][j]^=(A.a[i][k]&B.a[k][j]);
				}
			}
		}
		return C;
	}
	friend Matrix operator+(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int k=1;k<=n;k++){
			for(int j=1;j<=n;j++){
				C.a[1][j]^=(A.a[1][k]&B.a[k][j]);
			}
		}
		return C;
	}
}A[M];
int main(){
//	freopen("magic.in","r",stdin);
//	freopen("magic.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		A[0].a[x][y]=1;
		A[0].a[y][x]=1;
	}
	for(int i=1;i<=32;i++)A[i]=A[i-1]*A[i-1];
	while(Q--){
		ll num=read(),ans=0;
		if(num==0){printf("%lld\n",a[1]);continue;}
		Matrix Ans;Ans.Init();
		for(int i=1;i<=n;i++)Ans.a[i][i]=1;
		for(int i=0;i<=31;i++)if((num>>i)&1)Ans=Ans+A[i];
		for(int i=1;i<=n;i++)if(Ans.a[1][i])ans^=a[i];
		printf("%lld\n",ans);
	}
	return 0;
}
