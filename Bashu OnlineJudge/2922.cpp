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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,T;
int deg[N],G[N][N];
double f[N][N],g[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();T=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		G[x][y]=1;deg[x]++;
	}
	deg[0]=G[0][1]=g[1][0]=1;
	for(int t=1;t<=T;t++){
		for(int x=0;x<=n;x++){
			for(int y=0;y<=n;y++){
				if(x==y||!G[y][x])continue;
				int num=deg[x]+1-G[x][y];
				if(num)f[x][y]+=g[x][y]/num;
				for(int z=0;z<=n;z++){
					if(z==x||z==y||!G[z][y])continue;
					num=deg[y]+1-G[y][z];
					if(num)f[x][y]+=g[y][z]/num;
				}
			}
		}
		for(int x=0;x<=n;x++){
			for(int y=0;y<=n;y++){
				g[x][y]=f[x][y];
				f[x][y]=0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		double ans=0;
		for(int j=0;j<=n;j++)ans+=g[i][j];
		printf("%.3lf\n",ans*100);
	}
	return 0;
}