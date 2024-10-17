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
const int N=855;
const int M=N*N;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt=1,S,T;
int h[N],dis[N],vis[N],f[N][N],fa[N],Gap[N],b[M];
struct edge{
	int to,next,flow;
}d[N*40],e[N*40];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
int DFS(int x,int maxx){
	int ans=0;
	if(x==T||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[x]==dis[y]+1){
			int dlt=DFS(y,min(maxx,d[i].flow));
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(dis[S]==n||!maxx)return ans;
		}
	}
	if(!(--Gap[dis[x]]))dis[S]=n;
	Gap[++dis[x]]++;
	return ans;
}
int SAP(){
	Gap[0]=n;
	int ans=0;
	while(dis[S]<n)ans+=DFS(S,inf);
	return ans;
}
void dfs(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&!vis[y])dfs(y);
	}
}
void Build(){
	memset(f,0x3f,sizeof(f));
	for(int i=2;i<=n;i++)fa[i]=1;
	for(int i=2;i<=n;i++){
		memcpy(d,e,sizeof(e));
		memset(vis,0,sizeof(vis));
		memset(dis,0,sizeof(dis));
		memset(Gap,0,sizeof(Gap));
		S=fa[i];T=i;Gap[0]=n;
		int ans=SAP();dfs(S);
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
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);
	}
	memcpy(e,d,sizeof(e));
	Build();
	int tot=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			b[++tot]=f[i][j];
		}
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	printf("%d",tot);
	return 0;
}