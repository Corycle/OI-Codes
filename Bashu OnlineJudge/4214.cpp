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
const int N=505;
const int M=N*N;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt=1;
int h[M],id[N][N],dis[M];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
struct edge{
	int to,next,flow;
}d[M*10];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0,dlt=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
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
	n=read();m=read();
	int dlt=n*m,ans=0;
	int S=0,T=dlt*3+1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			id[i][j]=++tot;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();ans+=x;
			Add(S,id[i][j],x);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();ans+=x;
			Add(id[i][j],T,x);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();ans+=x;
			Add(S,id[i][j]+dlt,x);
			for(int k=0;k<4;k++){
				int fx=i+dx[k],fy=j+dy[k];
				if(fx<1||fy<1||fx>n||fy>m)continue;
				Add(id[i][j]+dlt,id[fx][fy],inf);
			}
			Add(id[i][j]+dlt,id[i][j],inf);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();ans+=x;
			Add(id[i][j]+dlt*2,T,x);
			for(int k=0;k<4;k++){
				int fx=i+dx[k],fy=j+dy[k];
				if(fx<1||fy<1||fx>n||fy>m)continue;
				Add(id[fx][fy],id[i][j]+dlt*2,inf);
			}
			Add(id[i][j],id[i][j]+dlt*2,inf);
		}
	}
	ans-=Dinic(S,T);
	printf("%d",ans);
	return 0;
}
