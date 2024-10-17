#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
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
int n,m,S,T;
int f[N][N],d[N][N],e[N][N];
int h[N],fa[N],dis[N],vis[N];
bool BFS(){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.front();
		q.pop();
		if(x==T)return true;
		for(int y=1;y<=n;y++){
			if(dis[y]==-1&&d[x][y]){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx){
	int ans=0,dlt=0;
	if(x==T||!maxx)return maxx;
	for(int y=1;y<=n;y++){
		if(d[x][y]&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[x][y]));
			if(!dlt)dis[y]=-1;
			d[x][y]-=dlt;
			d[y][x]+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(){
	int ans=0;
	while(BFS())ans+=DFS(S,inf);
	return ans;
}
void dfs(int x){
	vis[x]=1;
	for(int y=1;y<=n;y++){
		if(d[x][y]&&!vis[y])dfs(y);
	}
}
void Build(){
	memset(f,0x3f,sizeof(f));
	for(int i=2;i<=n;i++)fa[i]=1;
	for(int i=2;i<=n;i++){
		memcpy(d,e,sizeof(e));
		memset(vis,0,sizeof(vis));
		S=fa[i];T=i;
		int ans=Dinic();dfs(S);
		for(int j=i+1;j<=n;j++){
			if(!vis[j]&&fa[j]==fa[i])fa[j]=i;
		}
		for(int j=1;j<i;j++){
			f[i][j]=f[j][i]=min(ans,f[fa[i]][j]);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		memset(d,0,sizeof(d));
		memset(e,0,sizeof(e));
		n=read();m=read();
		for(int i=1;i<=m;i++){
			int x=read(),y=read(),z=read();
			d[x][y]=d[y][x]=d[x][y]+z;
			e[x][y]=e[y][x]=e[x][y]+z;
		}
		Build();
		m=read();
		while(m--){
			int ans=0,maxx=read();
			for(int i=1;i<=n;i++){
				for(int j=i+1;j<=n;j++){
					if(f[i][j]<=maxx)ans++;
				}
			}
			printf("%d\n",ans);
		}
		printf("\n");
	}
	return 0;
}