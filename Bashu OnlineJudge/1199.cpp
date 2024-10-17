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
const int N=1e4+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Max,Root;
int h[N],fa[N],dis[N],pre[N],vis[N],Ans[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void DFS(int x,int fa,int dist){
	dis[x]=dist;pre[x]=fa;if(dist>Max){Max=dist;Root=x;}
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y==fa)continue;DFS(y,x,dist+d[i].dist);}
}
void dfs(int x,int dist){
	Ans[x]=dist;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(vis[y])continue;dfs(y,dist+d[i].dist);}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=2;i<=n;i++){fa[i]=read();int dist=read();Add(i,fa[i],dist);Add(fa[i],i,dist);}
	Max=0;DFS(1,0,0);Max=0;DFS(Root,0,0);
	int Len=dis[Root];
	for(int x=Root;x;x=pre[x]){vis[x]=1;Ans[x]=max(dis[x],Len-dis[x]);}
	for(int x=Root;x;x=pre[x])dfs(x,Ans[x]);
	for(int i=1;i<=n;i++)printf("%d\n",Ans[i]);
	return 0;
}
