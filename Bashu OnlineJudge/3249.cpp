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
#define mp make_pair
#define pii pair<int,int>
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
vector<pii>G[N];
int h[N],rd[N],vis[N],dis[N],num1[N],num2[N],Ans[N];
struct edge{int to,next,dist,id;}d[N];
void Add(int x,int y,int z,int id){
	d[++cnt]=(edge){y,h[x],z,id};
	h[x]=cnt;
}
void Dijkstra(int x){
	for(int i=1;i<=n;i++){dis[i]=inf;vis[i]=num1[i]=0;}
	priority_queue<pii,vector<pii>,greater<pii> >q;
	q.push(mp(0,x));dis[x]=0;num1[x]=1;
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to,dlt=dis[x]+d[i].dist;
			if(dis[y]==dlt)num1[y]=(num1[y]+num1[x])%Mod;
			if(dis[y]>dlt){dis[y]=dlt;num1[y]=num1[x];q.push(mp(dis[y],y));}
		}
	}
}
void Solve(){
	for(int i=1;i<=n;i++)G[i].clear();
	for(int x=1;x<=n;x++){
		num2[x]=(dis[x]!=inf);
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]==dis[x]+d[i].dist){
				G[y].push_back(mp(x,d[i].id));
				rd[x]++;
			}
		}
	}
	queue<int>q;
	for(int i=1;i<=n;i++)if(!rd[i])q.push(i);
	while(q.size()){
		int x=q.front();q.pop();
		for(auto e:G[x]){
			int y=e.fst,id=e.scd;
			rd[y]--;if(!rd[y])q.push(y);
			num2[y]=(num2[x]+num2[y])%Mod;
			Ans[id]=(Ans[id]+1ll*num1[y]*num2[x]%Mod)%Mod;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z,i);
	}
	for(int i=1;i<=n;i++){Dijkstra(i);Solve();}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}