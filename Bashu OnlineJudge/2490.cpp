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
const int N=10005;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M][M];
vector<int>G[N];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int n,m,top,a[N],p[N],st[N],vis[N];
int id(int x,int y){return m*(x-1)+y;}
bool DFS(int x){
	for(int i=G[x].size()-1;i>=0;i--){
		int y=G[x][i];
		if(vis[y])continue;vis[y]=1;st[++top]=y;
		if(!p[y]||DFS(p[y])){p[y]=x;return true;}
	}
	return false;
}
void dfs(int x){
	vis[x]=1;a[x]=0;
	for(int i=G[x].size()-1;i>=0;i--){
		int y=G[x][i];
		if(p[y]&&!vis[p[y]])dfs(p[y]);
	}
}
int main(){
//	freopen("maze.in","r",stdin);
//	freopen("maze.out","w",stdout);
	while(1){
		n=read();m=read();
		if(!n&&!m)return 0;
		for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(s[i][j]=='X')continue;
				for(int k=0;k<4;k++){
					int x=i+dx[k],y=j+dy[k];
					if(x<1||x>n||y<1||y>m||s[x][y]=='X')continue;
					G[id(i,j)].push_back(id(x,y));
					G[id(x,y)].push_back(id(i,j));
				}
			}
		}
		
		for(int i=1;i<=n*m;i++)a[i]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if((i+j)&1){
					top=0;DFS(id(i,j));
					while(top)vis[st[top--]]=0;
				}
			}
		}
		for(int i=1;i<=n*m;i++)if(p[i])p[p[i]]=i;
		for(int i=1;i<=n*m;i++)vis[i]=0;
		for(int i=1;i<=n*m;i++)if(!p[i]&&!vis[i])dfs(i);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)printf("%c",(s[i][j]=='X'?'X':(a[id(i,j)]?'A':'B')));
			printf("\n");
		}
		printf("\n");
		for(int i=1;i<=n*m;i++){p[i]=vis[i]=0;G[i].clear();}
	}
	return 0;
}