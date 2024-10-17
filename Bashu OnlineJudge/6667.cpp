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
const int Mul=19260817;
const int N=3e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a,Ans;
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
namespace Task1{
	int F[N],Sum[N];
	void Main(){
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				if(j<=i)F[j]=Pow(a,j);
				else F[j]=1ll*(a-1)*mod(Sum[j-1]-Sum[j-i-1]+Mod)%Mod;
				Sum[j]=mod(Sum[j-1]+F[j]);
			}
			Ans=mod(Ans+1ll*F[n]*Pow(Mul,i)%Mod);
		}
		printf("%d\n",Ans);
	}
}
namespace Task2{
	int A[N],B[N],C[N],D[N],L;
	void Multi(int a[],int b[],int c[]){
		for(int i=0;i<=(L+1)*(L+1);i++)D[i]=0;
		for(int i=0;i<=L;i++){
			for(int j=0;j<=L;j++){
				D[i+j]=mod(D[i+j]+1ll*a[i]*b[j]%Mod);
			}
		}
		for(int i=2*L+1;i>L;i--){
			if(!D[i])continue;
			int dlt=D[i];
			for(int j=0;j<=L;j++)D[i-j]=mod(D[i-j]-1ll*C[L-j]*dlt%Mod+Mod);
		}
		for(int i=0;i<=L;i++)c[i]=D[i];
	}
	void Solve(int t){
		for(int i=0;i<=L;i++)A[i]=B[i]=0;A[0]=B[1]=1;
		while(t){if(t&1)Multi(A,B,A);Multi(B,B,B);t>>=1;}
	}
	void Main(){
		for(int k=1;k<=m;k++){
			int ans=0;L=k;
			for(int i=1;i<=k;i++)C[k-i]=mod(1-a+Mod);C[k]=1;
			Solve(n);
			for(int i=1;i<=k;i++)ans=mod(ans+1ll*Pow(a,i)*A[i]%Mod);
			Ans=mod(Ans+1ll*ans*Pow(Mul,k)%Mod);
		}
		printf("%d\n",Ans);
	}
}
namespace Task3{
	int Ans,fac[N],inv[N],P1[N],P2[N];
	void Prepare(){
		fac[0]=fac[1]=inv[0]=inv[1]=1;
		for(int i=2;i<=n;i++)fac[i]=1ll*fac[i-1]*i%Mod;
		for(int i=2;i<=n;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
		for(int i=2;i<=n;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
		P1[0]=P2[0]=1;
		for(int i=1;i<=n;i++)P1[i]=1ll*P1[i-1]*a%Mod;
		for(int i=1;i<=n;i++)P2[i]=1ll*P2[i-1]*(1-a+Mod)%Mod;
	}
	int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
	void Main(){
		Prepare();
		if(m>=n){Ans=1ll*Pow(a,n)*mod(Pow(Mul,m+1)-Pow(Mul,n)+Mod)%Mod*Pow(Mul-1,Mod-2)%Mod;m=n-1;}
		int t0=1ll*a*Pow(a-1,Mod-2)%Mod,t1=a;
		for(int k=1;k<=m;k++){
			int ans=0;
			for(int i=1;i*(k+1)<=n;i++)ans=mod(ans+1ll*C(i-1+n-i*(k+1),i-1)*P1[n-i*(k+1)]%Mod*P2[i]%Mod*t0%Mod);
			for(int i=0;i*(k+1)<n;i++) ans=mod(ans+1ll*C(i-1+n-i*(k+1),i)*P1[n-1-i*(k+1)]%Mod*P2[i]%Mod*t1%Mod);
			Ans=mod(Ans+1ll*ans*Pow(Mul,k)%Mod);
		}
		printf("%d\n",Ans);
	}
}
int main(){
//	freopen("array.in","r",stdin);
//	freopen("array.out","w",stdout);
	m=read();a=read();n=read();
	if(m<=10&&n<=1e5){Task1::Main();return 0;}
	if(m<=200){Task2::Main();return 0;}
	Task3::Main();
	return 0;
}