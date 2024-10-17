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
const int N=3e4+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<pii>G[N];
int n,m,K,cnt,Root,Min,Max;
int h[N],vis[N],dis[N],sum[N];
struct Node{
	int ans,num;
	void Init(){ans=-inf;num=0;}
	friend Node operator*(Node A,Node B){return (Node){A.ans+B.ans,A.num*B.num};}
	friend Node operator+(Node A,Node B){return A.ans==B.ans?(Node){A.ans,A.num+B.num}:(A.ans>B.ans?A:B);}
}F[N],tmp[N],Answer;
struct edge{int to,next,dist;}d[N*4];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
}
void Rebuild(int x){
	vis[x]=1;vector<pii>son;
	for(int i=h[x];i;i=d[i].next){
		if(dis[d[i].to]==dis[x]+d[i].dist)son.push_back(mp(d[i].to,d[i].dist));
	}
	sort(son.begin(),son.end());
	for(auto e:son){
		int y=e.fst,w=e.scd;
		if(!vis[y]){Rebuild(y);G[x].push_back(mp(y,w));G[y].push_back(mp(x,w));}
	}
}
void Dijkstra(){
	priority_queue<pii,vector<pii>,greater<pii> >q;
	for(int i=1;i<=n;i++)dis[i]=inf;
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
	memset(vis,0,sizeof(vis));
	Rebuild(1);
	memset(vis,0,sizeof(vis));
}
void Find(int x,int fa,int num){
	int S=0;sum[x]=1;
	for(auto e:G[x]){
		int y=e.fst;
		if(vis[y]||y==fa)continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void dfs(int x,int fa,int dist,int depth){
	sum[x]=1;Max=max(Max,depth);
	for(auto e:G[x]){
		int y=e.fst;
		if(vis[y]||y==fa)continue;
		dfs(y,x,dist+e.scd,depth+1);
		sum[x]+=sum[y];
	}
}
void Update(int x,int fa,int dist,int depth){
	Max=max(Max,depth);
	tmp[depth]=tmp[depth]+(Node){dist,1};
	if(depth==K-1){Answer=Answer+(Node){dist,1};return;}
	for(auto e:G[x]){
		int y=e.fst;
		if(vis[y]||y==fa)continue;
		Update(y,x,dist+e.scd,depth+1);
	}
}
void Calc(int x){
	Max=0;dfs(x,0,0,1);
	int t=min(Max,K);if(t*2<K)return;
	for(int i=0;i<=K;i++)F[i].Init();
	for(int i=0;i<=K;i++)tmp[i].Init();
	for(auto e:G[x]){
		int y=e.fst;if(vis[y])continue;
		Max=0;Update(y,x,e.scd,1);Max=min(Max,K-1);
		for(int i=1;i<=Max;i++)Answer=Answer+(tmp[i]*F[K-i-1]);
		for(int i=1;i<=Max;i++){F[i]=F[i]+tmp[i];tmp[i].Init();}
	}
}
void Divide(int x,int num){
	if(num<K)return;
	Root=0;Min=inf;Find(x,0,num);x=Root;vis[x]=1;Calc(x);
	for(auto e:G[x])if(!vis[e.fst])Divide(e.fst,sum[e.fst]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Dijkstra();Divide(1,n);
	printf("%d %d\n",Answer.ans,Answer.num);
	return 0;
}