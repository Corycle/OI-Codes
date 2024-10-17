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
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,d[N],fa[N],g[N],f[N][N],dis[N][N];
void DFS(int x){
	g[x]=inf;
	for(auto y:G[x]){
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
	}
	//f[x][i]表示距离x最近的物流中心为i时，x子树上所有点的费用和 
	for(int i=1;i<=n;i++){
		f[x][i]=d[dis[x][i]];
		for(auto y:G[x]){
			if(y==fa[x])continue;
			f[x][i]+=min(f[y][i],g[y]);
			//y子树到i的费用和，或重新建一个物流中心让y子树到它的费用和最小 
		}
		g[x]=min(g[x],f[x][i]+m);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;i++)dis[i][i]=0;
	for(int i=1;i<n;i++)d[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		dis[x][y]=dis[y][x]=1;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	DFS(1);
	printf("%d",g[1]);
	return 0;
}