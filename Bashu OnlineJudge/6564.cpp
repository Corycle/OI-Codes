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
const int N=45;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,A,B;
int a[N][N],f[N][N],g[N][N];
int F[N][N],G[N][N][3],fac[N],inv[N];
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
void Prepare(int maxn){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int Kirchhoff(int n){
	int ans=1;
	for(int i=1;i<n;i++){
		int t=i;
		for(int j=i;j<n;j++)if(a[j][i])t=j;
		if(i!=t){swap(a[i],a[t]);ans=mod(Mod-ans);}
		if(!a[i][i])return 0;
		ans=1ll*ans*a[i][i]%Mod;
		int inv=Pow(a[i][i],Mod-2);
		for(int j=i+1;j<n;j++){
			int dlt=1ll*a[j][i]*inv%Mod;
			for(int k=i;k<n;k++){
				a[j][k]=mod(a[j][k]-1ll*a[i][k]*dlt%Mod+Mod);
			}
		}
	}
	return ans;
}
int Solve(int x,int y){
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int val=mod(G[i][j][0]+mod(1ll*G[i][j][1]*x%Mod+1ll*G[i][j][2]*y%Mod));
			a[i][i]=mod(a[i][i]+val);
			a[j][j]=mod(a[j][j]+val);
			a[i][j]=mod(a[i][j]-val+Mod);
			a[j][i]=mod(a[j][i]-val+Mod);
		}
	}
	return Kirchhoff(n);
}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();m=read();A=read();B=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),c=read()-1;
		G[x][y][c]++;G[y][x][c]++;
	}
	Prepare(n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=Solve(i,j);
		}
	}
	for(int i=1;i<=n;i++){
		g[i][0]=1;
		int tmp=1;
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			tmp=1ll*tmp*mod(i-j+Mod)%Mod;
			//g(i)*(x-j)
			for(int k=n;k>=0;k--){
				g[i][k]=1ll*g[i][k]*mod(Mod-j)%Mod;
				if(k)g[i][k]=mod(g[i][k]+g[i][k-1]);
			}
		}
		int Inv=Pow(tmp,Mod-2);
		for(int j=0;j<=n;j++)g[i][j]=1ll*g[i][j]*Inv%Mod;
	}
	int Ans=0;
	for(int i=0;i<=A;i++){
		for(int j=0;j<=B;j++){
			for(int x=1;x<=n;x++){
				for(int y=1;y<=n;y++){
					F[i][j]=mod(F[i][j]+1ll*f[x][y]*g[x][i]%Mod*g[y][j]%Mod);
				}
			}
			Ans=mod(Ans+F[i][j]);
		}
	}
	printf("%d",Ans);
	return 0;
}