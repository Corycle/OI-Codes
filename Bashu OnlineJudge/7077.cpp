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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=3e5+5;
const int M=19;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,cnt,h[N],fa[N],p[N][M],dep[N],dis[N],vis[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int depth){
	dep[x]=depth;p[x][0]=fa[x];
	for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(int i=h[x];i;i=d[i].next)if(d[i].to!=fa[x])DFS(d[i].to,depth+1);
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	return p[x][0];
}
int Dist(int x,int y){return dep[x]+dep[y]-dep[LCA(x,y)]*2;}
int Climb(int x,int depth){
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(dep[x]-(1<<k)>=depth)x=p[x][k];
	return x;
}
priority_queue<pii,vector<pii>,greater<pii> >q;
void Insert(int x,int dist){dis[x]=min(dis[x],dist);q.push(mp(dist,x));}
void Update(int x,int y,int dist){
	int z=LCA(x,y),mid=(dist+1)/2;
	if(dep[x]>dep[y])swap(x,y);
	int pos=Climb(y,dep[z]+mid-(dep[x]-dep[z]));
	Insert(pos,mid);if(dist&1)Insert(fa[pos],mid);
}
void Solve(){
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+1){
				dis[y]=dis[x]+1;
				q.push(mp(dis[y],y));
			}
		}
	}
}
int main(){
//	freopen("stone.in","r",stdin);
//	freopen("stone.out","w",stdout);
	n=read();
	for(int i=2;i<=n;i++){fa[i]=read();Add(fa[i],i);Add(i,fa[i]);}
	for(int i=1;i<=n;i++)dis[i]=inf;
	DFS(1,1);
	int T=read();
	while(T--){
		int num=read(),s=0,t=0,tmp=0,dist=0;
		for(int i=1;i<=num;i++){
			int x=read();
			if(i==1){s=t=x;continue;}
			int fx=s,fy=t;
			tmp=Dist(fx,x);if(tmp>dist){dist=tmp;s=fx;t=x;}
			tmp=Dist(fy,x);if(tmp>dist){dist=tmp;s=fy;t=x;}
		}
		Update(s,t,dist);
	}
	Solve();
	for(int i=1;i<=n;i++)printf("%d\n",dis[i]);
	return 0;
}