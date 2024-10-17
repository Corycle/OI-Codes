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
const int N=100005;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],sum[N],f[N][M][2][2],g[M][2][2];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS(int x,int fa){
	sum[x]=1;
	f[x][0][0][0]=f[x][1][1][0]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		for(int j=0;j<=sum[x]&&j<=m;j++){
			for(int k=0;k<=sum[y]&&j+k<=m;k++){
				g[j+k][0][0]=mod(g[j+k][0][0]+1ll*f[x][j][0][0]*f[y][k][0][1]%Mod);
				
				g[j+k][1][0]=mod(g[j+k][1][0]+1ll*f[x][j][1][0]*mod(f[y][k][0][0]+f[y][k][0][1])%Mod);
				
				g[j+k][0][1]=mod(g[j+k][0][1]+1ll*f[x][j][0][0]*f[y][k][1][1]%Mod);
				g[j+k][0][1]=mod(g[j+k][0][1]+1ll*f[x][j][0][1]*mod(f[y][k][0][1]+f[y][k][1][1])%Mod);
				
				g[j+k][1][1]=mod(g[j+k][1][1]+1ll*f[x][j][1][0]*mod(f[y][k][1][0]+f[y][k][1][1])%Mod);
				g[j+k][1][1]=mod(g[j+k][1][1]+1ll*f[x][j][1][1]*mod(f[y][k][0][0]+f[y][k][0][1])%Mod);
				g[j+k][1][1]=mod(g[j+k][1][1]+1ll*f[x][j][1][1]*mod(f[y][k][1][0]+f[y][k][1][1])%Mod);
			}
		}
		sum[x]+=sum[y];
		for(int j=0;j<=sum[x]&&j<=m;j++){
			f[x][j][0][0]=g[j][0][0];g[j][0][0]=0;
			f[x][j][1][0]=g[j][1][0];g[j][1][0]=0;
			f[x][j][0][1]=g[j][0][1];g[j][0][1]=0;
			f[x][j][1][1]=g[j][1][1];g[j][1][1]=0;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,0);
	printf("%d",mod(f[1][m][0][1]+f[1][m][1][1]));
	return 0;
}