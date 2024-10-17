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
int g[N][N],dis[N],vis[N];
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[s]=0;vis[s]=1;
	queue<int>q;
	q.push(s);
	while(q.size()){
		int x=q.front();
		q.pop();
		if(x==t)return true;
		for(int y=1;y<=n;y++){
			if(g[x][y]&&!vis[y]){
				dis[y]=dis[x]+1;
				vis[y]=1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0,dlt=0;
	if(x==t)return maxx;
	for(int y=1;y<=n;y++){
		if(g[x][y]&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,g[x][y]),t);
			g[x][y]-=dlt;
			g[y][x]+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	m=read();n=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		g[x][y]+=z;
	}
	S=1;T=n;
	printf("%d",Dinic(S,T));
	return 0;
}