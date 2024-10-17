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
const int M=(1<<17)+5;
const int N=72;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,A,B,cnt,tot,Sta;
struct edge{int to,next,dist;}d[M];
int h[N],fa[N],id[N],sum[N],sta[N],vis[N][M],dis[N][M];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void Union(int x,int y){x=Find(x);y=Find(y);if(x!=y){fa[x]=y;sum[y]+=sum[x];}}
bool Belong(int S,int T){return (S|T)==T;}
struct Node{
	int x,t,dis;
	friend bool operator<(Node A,Node B){return A.dis>B.dis;}
};
void Dijkstra(){
	priority_queue<Node>q;
	for(int i=1;i<=n;i++)for(int S=0;S<=Sta;S++)dis[i][S]=inf;
	dis[1][sta[1]]=0;q.push((Node){1,sta[1],dis[1][sta[1]]});
	while(q.size()){
		int x=q.top().x,t=q.top().t;q.pop();
		if(vis[x][t])continue;vis[x][t]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to,p=t|sta[y];
			if(d[i].dist==B&&Find(x)==Find(y))continue;
			if(d[i].dist==B&&sta[y]&&Belong(sta[y],t))continue;
			if(dis[y][p]>dis[x][t]+d[i].dist){
				dis[y][p]=dis[x][t]+d[i].dist;
				q.push((Node){y,p,dis[y][p]});
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();A=read();B=read();
	for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}
	for(int i=1;i<=m;i++){int x=read(),y=read(),z=read();Add(x,y,z);Add(y,x,z);if(z==A)Union(x,y);}
	for(int i=1;i<=n;i++)if(!id[Find(i)]&&sum[Find(i)]>=4)id[Find(i)]=++tot;
	for(int i=1;i<=n;i++)if(id[Find(i)])sta[i]=(1<<(id[Find(i)]-1));
	Sta=(1<<tot)-1;
	Dijkstra();
	for(int i=1;i<=n;i++){
		int ans=inf;
		for(int S=0;S<=Sta;S++)ans=min(ans,dis[i][S]);
		printf("%d ",ans);
	}
	return 0;
}
