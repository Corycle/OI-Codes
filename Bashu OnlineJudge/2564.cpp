#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2005;
const int M=40005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int g[N*10][N/4],p[M],vis[M],id[N][N],num[5],map[N][N];
int n,m,x,y,flag=1,t,all;
bool dfs(int x){
	for(int i=1;i<=g[x][0];i++){
		if(!vis[g[x][i]]){
			vis[g[x][i]]=1;
			if(p[g[x][i]]==0||dfs(p[g[x][i]])){
				p[g[x][i]]=x;
				return 1;
			}
		}
	}
	return 0;
}
int Hungary(){
	int tot=0;
	memset(p,0,sizeof(p));
	for(int i=1;i<=num[0];i++){
		memset(vis,0,sizeof(vis));
		if(dfs(i))tot++;
	}
	return tot;
}
void Build(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!map[i][j]&&(i+j)%2==0){
				if(!map[i+2][j+1]&&map[i+2][j+1]!=-1)g[id[i][j]][++g[id[i][j]][0]]=id[i+2][j+1];
				if(!map[i+2][j-1]&&j-1>0&&i+2<n+1)g[id[i][j]][++g[id[i][j]][0]]=id[i+2][j-1];
				if(!map[i-2][j+1]&&j+1<n+1&&i-2>0)g[id[i][j]][++g[id[i][j]][0]]=id[i-2][j+1];
				if(!map[i-2][j-1]&&j-1>0&&i-2>0)g[id[i][j]][++g[id[i][j]][0]]=id[i-2][j-1];
				if(!map[i+1][j-2]&&j-2>0&&i+1<n+1)g[id[i][j]][++g[id[i][j]][0]]=id[i+1][j-2];
				if(!map[i+1][j+2]&&j+2<n+1&&i+1<n+1)g[id[i][j]][++g[id[i][j]][0]]=id[i+1][j+2];
				if(!map[i-1][j-2]&&j-2>0&&i-1>0)g[id[i][j]][++g[id[i][j]][0]]=id[i-1][j-2];
				if(!map[i-1][j+2]&&j+2<n+1&&i-1>0)g[id[i][j]][++g[id[i][j]][0]]=id[i-1][j+2];
			}
		}
	}
}
int main(){
	n=read();m=read();
	memset(map,-1,sizeof(map));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			map[i][j]=0;
			id[i][j]=++num[(i+j)%2];
		}
	}
	for(int i=1;i<=m;i++){
		x=read(),y=read();
		map[x][y]=1; 
	}
	Build();
	int t=Hungary();
	printf("%d",n*n-m-t);
	return 0;
}