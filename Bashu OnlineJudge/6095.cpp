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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e6+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,tot;
int h[N],fa[N],val[N],prt[N],dis[N],vis[N],p[N][M];
struct Edge{int x,y,l,a;}E[N];
struct edge{int to,next,dist;}d[N];
bool cmp(Edge A,Edge B){return A.a>B.a;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void Dijkstra(){
	for(int i=1;i<=n*2;i++){dis[i]=2e9;vis[i]=0;}
	priority_queue<pii,vector<pii>,greater<pii> >q;
	q.push(mp(0,1));dis[1]=0;
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].dist){
				dis[y]=dis[x]+d[i].dist;
				q.push(mp(dis[y],y));
			}
		}
	}
}
void Kruskal(){
	sort(E+1,E+m+1,cmp);tot=n;
	for(int i=1;i<=n*2;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=Find(E[i].x),y=Find(E[i].y);
		if(Find(x)==Find(y))continue;
		tot++;val[tot]=E[i].a;
		fa[Find(x)]=Find(tot);
		fa[Find(y)]=Find(tot);
		prt[x]=tot;prt[y]=tot;
		G[tot].push_back(x);
		G[tot].push_back(y);
	}
}
void DFS(int x){
	p[x][0]=prt[x];
	for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(auto y:G[x]){DFS(y);dis[x]=min(dis[x],dis[y]);}
}
int Query(int x,int H){
	for(int i=M-1;i>=0;i--)if(val[p[x][i]]>H)x=p[x][i];
	return dis[x];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();m=read();cnt=0;
		for(int i=1;i<=n;i++)h[i]=0;
		for(int i=1;i<=m;i++){
			E[i].x=read();E[i].y=read();
			E[i].l=read();E[i].a=read();
			Add(E[i].x,E[i].y,E[i].l);
			Add(E[i].y,E[i].x,E[i].l);
		}
		Dijkstra();Kruskal();DFS(tot);
		int Q=read(),K=read(),S=read(),Ans=0;
		while(Q--){
			int x=(read()+1ll*K*Ans-1)%n+1;
			int H=(read()+1ll*K*Ans)%(S+1);
			printf("%d\n",Ans=Query(x,H));
		}
		for(int i=1;i<=tot;i++){
			prt[i]=0;G[i].clear();
			for(int j=0;j<M;j++)p[i][j]=0;
		}
	}
	return 0;
}