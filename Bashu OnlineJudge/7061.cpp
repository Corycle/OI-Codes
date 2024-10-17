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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a,b;
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
namespace Task1{
	const int N=1e6+5;
	const int M=75;
	int f[N][M];
	void Main(){
		f[1][m/2]=1;
		for(int i=2;i<n;i++){
			for(int j=1;j<=m;j++){
				f[i][j]=mod(f[i-1][j]+mod(f[i-1][j-1]+f[i-1][j+1]));
			}
		}
		int Ans=0;
		for(int i=2;i<n;i++){
			for(int j=a+1;j<b;j++){
				Ans=mod(Ans+1ll*f[i][j]*f[n-i+1][j]%Mod);
			}
		}
		Ans=1ll*Ans*Pow(n-2,Mod-2)%Mod;
		printf("%d\n",Ans);
	}
}
namespace Task2{
	const int M=261;
	struct Matrix{
		int n,m,a[M][M];
		void Clear(int A,int B){n=A;m=B;for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=0;}
		friend Matrix operator*(Matrix A,Matrix B){
			Matrix C;C.Clear(A.n,B.m);
			for(int i=1;i<=C.n;i++){
				for(int j=1;j<=C.m;j++){
					for(int k=1;k<=A.m;k++){
						C.a[i][j]=mod(C.a[i][j]+1ll*A.a[i][k]*B.a[k][j]%Mod);
					}
				}
			}
			return C;
		}
	}A,B;
	void Solve(int t){while(t){if(t&1)B=A*B;A=A*A;t>>=1;}}
	void Main(){
		A.Clear(m*2,m*2);
		for(int i=1;i<=m;i++){
			A.a[i][i]=A.a[i+m][i+m]=1;
			A.a[i][i-1]=A.a[i+m][i+m-1]=(i!=1);
			A.a[i][i+1]=A.a[i+m][i+m+1]=(i!=m);
			if(a<i&&i<b){A.a[i+m][i]=1;A.a[i+m][i-1]=(i!=1);A.a[i+m][i+1]=(i!=m);}
		}
		B.Clear(m*2,1);B.a[m/2][1]=1;Solve(n-2);
		int Ans=(m==2?B.a[m+m/2][1]:mod(B.a[m+m/2][1]+mod(B.a[m+m/2-1][1]+B.a[m+m/2+1][1])));
		Ans=1ll*Ans*Pow(n-2,Mod-2)%Mod;
		printf("%d\n",Ans);
	}
}
int main(){
//	freopen("expect.in","r",stdin);
//	freopen("expect.out","w",stdout);
	n=read();m=read();a=read();b=read();
//	if(n<=1000000&&m<=70){Task1::Main();return 0;}
	Task2::Main();
	return 0;
}