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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,cnt;
int h[N],dis[N],vis[N];
int id[20][20],a[305][305],key[15][305],knum[15],Have[15];
struct edge{int to,next,data;}d[N*2];
void edge_add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void Build(){
	for(int k=0;k<(1<<p);k++){
		int S=k*n*m;
		for(int i=1;i<=p;i++){
			if(k&(1<<(i-1)))Have[i]=1;
			else Have[i]=0;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int x=id[i][j],y;
				y=id[i][j+1];
				if(y!=0&&(a[x][y]==-1||Have[a[x][y]])){
					edge_add(x+S,y+S,1);edge_add(y+S,x+S,1);
				}
				y=id[i+1][j];
				if(y!=0&&(a[x][y]==-1||Have[a[x][y]])){
					edge_add(x+S,y+S,1);edge_add(y+S,x+S,1);
				}
			}
		}
		for(int i=1;i<=p;i++){
			if(Have[i])continue;
			for(int j=1;j<=knum[i];j++){
				int T=(k+(1<<(i-1)))*n*m;
				int x=key[i][j]+S,y=key[i][j]+T;
				edge_add(x,y,0);
			}
		}
	}
}
void SPFA(){
	queue<int>q;
	memset(dis,0x3f,sizeof(dis));
	q.push(1);dis[1]=0;
	while(q.size()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[x]+d[i].data<dis[y]){
				dis[y]=dis[x]+d[i].data;
				if(!vis[y]){q.push(y);vis[y]=1;}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(a,-1,sizeof(a));
	n=read();m=read();p=read();
	int num=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			id[i][j]=++num;
		}
	}
	int T=read();
	while(T--){
		int sx=read(),sy=read();
		int fx=read(),fy=read();
		int x=id[sx][sy],y=id[fx][fy];
		a[x][y]=a[y][x]=read();
	}
	T=read();
	while(T--){
		int sx=read(),sy=read(),y=read();
		key[y][++knum[y]]=id[sx][sy];
	}
	Build();
	SPFA();
	int ans=inf;
	for(int i=1;i<=(1<<p);i++){
		ans=min(ans,dis[i*n*m]);
	}
	if(ans==inf)printf("-1");
	else printf("%d",ans);
	return 0;
}