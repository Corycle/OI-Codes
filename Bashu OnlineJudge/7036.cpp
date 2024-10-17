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
const int N=5e4+5;
const int M=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,Ans,a[N],t0[N],t1[N],f[N][M],g[N][M],sum[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS(int x,int fa){
	f[x][1]=1;sum[x]=1;
	for(auto y:G[x]){
		if(y==fa)continue;
		DFS(y,x);
		for(int i=0;i<=m;i++)t0[i]=t1[i]=0;
		for(int i=1;i<=min(m,sum[x]);i++){
			for(int j=0;j<=min(m-i,sum[y]);j++){
				t0[i+j]=mod(t0[i+j]+1ll*f[x][i]*f[y][j]%Mod);
				t1[i+j]=mod(t1[i+j]+1ll*f[x][i]*g[y][j]%Mod);
				t1[i+j]=mod(t1[i+j]+1ll*g[x][i]*f[y][j]%Mod);
			}
		}
		for(int i=0;i<=m;i++){f[x][i]=t0[i];g[x][i]=t1[i];}
		sum[x]+=sum[y];
	}
	sum[x]=1;
	for(int i=0;i<=m;i++)t0[i]=0;t0[1]=1;
	for(auto y:G[x]){
		if(y==fa)continue;
		for(int i=0;i<=m;i++)t1[i]=0;
		for(int i=1;i<=min(m,sum[x]);i++){
			for(int j=0;j<=min(min(m-i,m/2),sum[y]);j++){
				if(j*2==m&&y<x)continue;
				t1[i+j]=mod(t1[i+j]+1ll*t0[i]*f[y][j]%Mod);
			}
		}
		for(int i=0;i<=m;i++)t0[i]=t1[i];
		sum[x]+=sum[y];
	}
	for(int i=(m+1)/2;i<=m;i++){
		if(i*2==m&&fa<x)continue;
		g[x][i]=mod(g[x][i]+1ll*t0[i]*a[x]%Mod);
	}
	Ans=mod(Ans+g[x][m]);
	f[x][0]=1;
}
int main(){
//	freopen("centroid.in","r",stdin);
//	freopen("centroid.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	DFS(1,0);
	printf("%d\n",Ans);
	return 0;
}