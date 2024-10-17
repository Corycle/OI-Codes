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
const int N=1505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,K;
int a[N][N],P[N],Inv[N],Ans[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x%Mod;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Special_Gauss(int n){
	for(int i=n;i>1;i--){
		int dlt=1ll*a[i-1][i]*Pow(a[i][i],Mod-2)%Mod;
		for(int j=1;j<=i;j++){
			a[i-1][j]=mod(a[i-1][j]-1ll*a[i][j]*dlt%Mod+Mod);
		}
		a[i-1][n+1]=mod(a[i-1][n+1]-1ll*a[i][n+1]*dlt%Mod+Mod);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			a[i][n+1]=mod(a[i][n+1]-1ll*a[i][j]*Ans[j]%Mod+Mod);
		}
		Ans[i]=1ll*a[i][n+1]*Pow(a[i][i],Mod-2)%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Inv[1]=1;
	for(int i=2;i<N;i++){
		Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
	}
	int T=read();
	while(T--){
		n=read();p=read();m=read();K=read();
		if(!K||(!m&&K==1)){printf("-1\n");continue;}
		else if(!m){
			int cnt=0;
			while(p>0){
				if(p<n)p++;
				p-=K;cnt++;
			}
			printf("%d\n",cnt);
			continue;
		}
		int Inv1=Pow(m,Mod-2),Inv2=Pow(m+1,Mod-2);
		P[0]=1ll*Pow(m,K)*Pow(Inv2,K)%Mod;
		for(int i=1;i<=n;i++){
			P[i]=1ll*P[i-1]*((K-i+1)%Mod)%Mod*Inv[i]%Mod*Inv1%Mod;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i+1;j++){
				if(j==n+1)a[i][j]=0;
				else if(i==n)a[i][j]=P[i-j];
				else if(j==i+1)a[i][j]=1ll*P[0]*Inv2%Mod;
				else a[i][j]=mod(1ll*P[i-j]*m%Mod*Inv2%Mod+1ll*P[i-j+1]*Inv2%Mod);
				a[i][j]=Mod-a[i][j];
			}
			a[i][i]=mod(a[i][i]+1);
			a[i][n+1]=1;
		}
		Special_Gauss(n);
		printf("%d\n",Ans[p]);
	}
	return 0;
}