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
const int Phi=1e9+6;
const int N=61;
const int M=5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n;
int f1,f2,f3,c,Ans;
int mod(int x){return x>=Phi?x-Phi:x;}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
struct Matrix{
	int n,m,a[M][M];
	void Clear(int A,int B){n=A;m=B;for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[i][j]=0;}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Clear(A.n,B.m);
		for(int i=0;i<C.n;i++){
			for(int j=0;j<C.m;j++){
				for(int k=0;k<A.m;k++){
					C.a[i][j]=mod(C.a[i][j]+1ll*A.a[i][k]*B.a[k][j]%Phi);
				}
			}
		}
		return C;
	}
}P[N],A,B,C,D;
void Solve1(ll m){
	P[0].Clear(5,5);
	P[0].a[0][0]=1;P[0].a[0][1]=1;P[0].a[0][2]=1;P[0].a[0][3]=1;P[0].a[0][4]=0;
	P[0].a[1][0]=1;P[0].a[1][1]=0;P[0].a[1][2]=0;P[0].a[1][3]=0;P[0].a[1][4]=0;
	P[0].a[2][0]=0;P[0].a[2][1]=1;P[0].a[2][2]=0;P[0].a[2][3]=0;P[0].a[2][4]=0;
	P[0].a[3][0]=0;P[0].a[3][1]=0;P[0].a[3][2]=0;P[0].a[3][3]=1;P[0].a[3][4]=1;
	P[0].a[4][0]=0;P[0].a[4][1]=0;P[0].a[4][2]=0;P[0].a[4][3]=0;P[0].a[4][4]=1;
	for(int i=1;i<N;i++)P[i]=P[i-1]*P[i-1];
	A.Clear(5,1);A.a[3][0]=A.a[4][0]=2;
	for(int i=0;i<N;i++)if((m>>i)&1)A=P[i]*A;
	Ans=1ll*Ans*Pow(c,A.a[0][0])%Mod;
}
void Solve2(ll m){
	P[0].Clear(3,3);
	P[0].a[0][0]=1;P[0].a[0][1]=1;P[0].a[0][2]=1;
	P[0].a[1][0]=1;P[0].a[1][1]=0;P[0].a[1][2]=0;
	P[0].a[2][0]=0;P[0].a[2][1]=1;P[0].a[2][2]=0;
	for(int i=1;i<N;i++)P[i]=P[i-1]*P[i-1];
	B.Clear(3,1);B.a[2][0]=1;
	C.Clear(3,1);C.a[1][0]=1;
	D.Clear(3,1);D.a[0][0]=1;
	for(int i=0;i<N;i++)if((m>>i)&1){B=P[i]*B;C=P[i]*C;D=P[i]*D;}
	Ans=1ll*Ans*Pow(f1,B.a[0][0])%Mod*Pow(f2,C.a[0][0])%Mod*Pow(f3,D.a[0][0])%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();f1=read();f2=read();f3=read();c=read();
	Ans=1;Solve1(n-3);Solve2(n-3);printf("%d\n",Ans);
	return 0;
}
