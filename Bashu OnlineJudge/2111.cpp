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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N][N],G[N][N],F[N],Ans[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int mod(int x){return x>=Mod?x-Mod:x;}
void Gauss(int n){
	for(int i=1;i<=n;i++){
		int t=i;
		for(int j=i;j<=n;j++)if(a[j][i])t=j;
		if(i!=t)swap(a[i],a[t]);
		if(!a[i][i])continue;
		int inv=Pow(a[i][i],Mod-2);
		for(int j=i+1;j<=n;j++){
			int dlt=1ll*a[j][i]*inv%Mod;
			for(int k=i;k<=n+1;k++){
				a[j][k]=mod(a[j][k]-1ll*a[i][k]*dlt%Mod+Mod);
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++){
			a[i][n+1]=mod(a[i][n+1]-1ll*a[i][j]*Ans[j-1]%Mod+Mod);
		}
		Ans[i-1]=1ll*a[i][n+1]*Pow(a[i][i],Mod-2)%Mod;
	}
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
int Solve(int x){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int v=G[i][j]?x:1;
			a[i][i]=mod(a[i][i]+v);
			a[j][j]=mod(a[j][j]+v);
			a[i][j]=mod(a[i][j]-v+Mod);
			a[j][i]=mod(a[j][i]-v+Mod);
		}
	}
	return Kirchhoff(n);
}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x][y]++;G[y][x]++;
	}
	for(int i=1;i<=n;i++)F[i]=Solve(i);
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++){
		int tmp=1;
		for(int j=1;j<=n;j++){
			a[i][j]=tmp;
			tmp=1ll*tmp*i%Mod;
		}
		a[i][n+1]=F[i];
	}
	Gauss(n);
	for(int i=0;i<n;i++)printf("%d ",Ans[i]);
	return 0;
}