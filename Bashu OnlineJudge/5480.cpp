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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N][N];
int n,m,tot,a[N][N],b[N*N];
int id(int x,int y){return (x<1||x>n||y<1||y>m)?n*m+1:(x-1)*m+y;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void DFS(int i,int j,int belong){
	b[id(i,j)]=belong;
	if(!b[id(i+1,j)]&&s[i+1][j]=='U')DFS(i+1,j,belong);
	if(!b[id(i-1,j)]&&s[i-1][j]=='D')DFS(i-1,j,belong);
	if(!b[id(i,j+1)]&&s[i][j+1]=='L')DFS(i,j+1,belong);
	if(!b[id(i,j-1)]&&s[i][j-1]=='R')DFS(i,j-1,belong);
}
void Prepare(){
	for(int i=1;i<=n;i++)if(s[i][1]=='L')DFS(i,1,1);
	for(int i=1;i<=n;i++)if(s[i][m]=='R')DFS(i,m,1);
	for(int i=1;i<=m;i++)if(s[1][i]=='U')DFS(1,i,1);
	for(int i=1;i<=m;i++)if(s[n][i]=='D')DFS(n,i,1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(s[i][j]=='.')b[id(i,j)]=++tot;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(b[id(i,j)])continue;
			if(s[i][j]=='U'&&s[i-1][j]=='.')DFS(i,j,b[id(i-1,j)]);
			if(s[i][j]=='D'&&s[i+1][j]=='.')DFS(i,j,b[id(i+1,j)]);
			if(s[i][j]=='L'&&s[i][j-1]=='.')DFS(i,j,b[id(i,j-1)]);
			if(s[i][j]=='R'&&s[i][j+1]=='.')DFS(i,j,b[id(i,j+1)]);
		}
	}
	for(int i=1;i<=tot;i++)for(int j=1;j<=tot;j++)a[i][j]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=b[id(i,j)];
			if((s[i][j]=='U'&&s[i-1][j]=='.')||s[i][j]=='.'){a[x][x]++;a[x][b[id(i-1,j)]]--;}
			if((s[i][j]=='D'&&s[i+1][j]=='.')||s[i][j]=='.'){a[x][x]++;a[x][b[id(i+1,j)]]--;}
			if((s[i][j]=='L'&&s[i][j-1]=='.')||s[i][j]=='.'){a[x][x]++;a[x][b[id(i,j-1)]]--;}
			if((s[i][j]=='R'&&s[i][j+1]=='.')||s[i][j]=='.'){a[x][x]++;a[x][b[id(i,j+1)]]--;}
		}
	}
}
int Kirchhoff(){
	int Ans=1,k=0;Prepare();
	for(int i=1;i<=n*m;i++)if(!b[i])return 0;
	for(int i=2;i<=tot;i++){
		for(int j=i;j<=tot;j++)if(a[j][i]){k=j;break;}
		if(k!=i){swap(a[i],a[k]);Ans=Mod-Ans;}
		int Inv=Pow(a[i][i],Mod-2);
		for(int j=i+1;j<=tot;j++){
			int dlt=1ll*a[j][i]*Inv%Mod;
			for(int k=i;k<=tot;k++){
				a[j][k]=(a[j][k]-1ll*a[i][k]*dlt%Mod+Mod)%Mod;
			}
		}
		Ans=1ll*Ans*a[i][i]%Mod;
	}
	return (Ans%Mod+Mod)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		tot=0;
		for(int i=1;i<=n*m+1;i++)b[i]=0;
		n=read();m=read();b[n*m+1]=++tot;
		for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
		printf("%d\n",Kirchhoff());
	}
	return 0;
}