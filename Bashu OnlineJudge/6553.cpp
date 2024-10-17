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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int Sum(int x){return x*(x+1)/2;}
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
namespace Task1{//Gauss
	const int M=520;
	int Sta,P,num[M],g[M],a[M][M],f[M];
	int lowbit(int x){return x&(-x);}
	void Gauss(int n){
		for(int i=0;i<=n;i++){
			int t=i;
			for(int j=i;j<=n;j++)if(a[j][i])t=j;
			if(t!=i)swap(a[t],a[i]);
			int inv=Pow(a[i][i],Mod-2);
			for(int j=i+1;j<=n;j++){
				int dlt=1ll*a[j][i]*inv%Mod;
				for(int k=i;k<=n+1;k++){
					a[j][k]=mod(a[j][k]-1ll*a[i][k]*dlt%Mod+Mod);
				}
			}
		}
		for(int i=n;i>=0;i--){
			for(int j=i+1;j<=n;j++)a[i][n+1]=mod(a[i][n+1]-1ll*a[i][j]*f[j]%Mod+Mod);
			f[i]=1ll*a[i][n+1]*Pow(a[i][i],Mod-2)%Mod;
		}
	}
	void Main(){
		Sta=(1<<n)-1;
		P=Pow(Sum(n),Mod-2);
		for(int S=1;S<=Sta;S++)num[S]=num[S^lowbit(S)]+1;
		for(int S=0;S<=Sta;S++){
			a[S][S]=1;
			if(num[S]>=m)continue;
			for(int i=1;i<=n;i++){
				for(int j=i;j<=n;j++){
					int T=S;
					for(int k=i;k<=j;k++)T|=(1<<(k-1));
					a[S][T]=mod(a[S][T]-P+Mod);
				}
			}
			a[S][Sta+1]=1;
		}
		Gauss(Sta);
		printf("%d",f[0]);
	}
}
namespace Task2{//Min-Max
	int f[2][N][N*N/2];
	void Main(){
		int Maxn=Sum(n),t=0;
		f[t][1][1]=1;f[t][0][0]=Mod-1;
		for(int i=2;i<=n;i++){
			t^=1;
			memset(f[t],0,sizeof(f[t]));
			for(int j=0;j<=n;j++){
				for(int k=0;k<=Maxn;k++){
					f[t][0][k]=mod(f[t][0][k]-f[t^1][j][k]+Mod);
					f[t][j+1][j+k+1]=mod(f[t][j+1][j+k+1]+f[t^1][j][k]);
				}
			}
		}
		int Ans=0;
		for(int i=0;i<=n;i++){
			for(int j=0;j<=Maxn;j++){
				Ans=mod(Ans-1ll*f[t][i][j]*Pow(Maxn-j,Mod-2)%Mod+Mod);
			}
		}
		Ans=1ll*Ans*Maxn%Mod;
		printf("%d",Ans);
	}
}
namespace Task3{//Kth_Min-Max
	int C[N][N],f[2][N][N*N/2];
	void Main(){
		m=n-m+1;
		int Maxn=Sum(n);
		for(int i=0;i<N;i++){
			C[i][0]=1;
			for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
		}
		int t=0;
		for(int p=1;p<=m;p++){
			t^=1;
			memset(f[t],0,sizeof(f[t]));
			for(int i=1;i<=n;i++){
				f[t][i][Sum(i-1)]=Mod-C[0][p-1];
				for(int j=0;j<i;j++){
					for(int k=0;k<=Sum(j-1);k++){
						f[t][i][k+Sum(i-j-1)]=mod(f[t][i][k+Sum(i-j-1)]-mod(f[t][j][k]+f[t^1][j][k])+Mod);
					}
				}
			}
		}
		int Ans=0;
		for(int k=0;k<=Maxn;k++){
			int ans=0;
			for(int i=1;i<=n;i++){
				if(k-Sum(n-i)>=0)ans=mod(ans+f[t][i][k-Sum(n-i)]);
			}
			ans=1ll*ans*(m&1?Mod-1:1)%Mod;
			Ans=mod(Ans+1ll*ans*Pow(Maxn-k,Mod-2)%Mod);
		}
		Ans=1ll*Ans*Maxn%Mod;
		printf("%d",Ans);
	}
}
int main(){
//	freopen("paint.in","r",stdin);
//	freopen("paint.out","w",stdout);
	n=read();m=read();
//	if(n<=9){Task1::Main();return 0;}//Gauss
//	if(n==m){Task2::Main();return 0;}//Min-Max
	Task3::Main();//Kth_Min-Max
	return 0;
}