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
#define pii pair<ll,int>
using namespace std;
const int inf=0x3f3f3f3f;
const ll INF=9e18;
const int N=1e5+5;
const int M=30;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,cnt,Sta;
ll Ans,f[M][N],dis[M][N];
int h[N],a[N],b[N],p[N],vis[N];
struct edge{int to,next,dist;}d[N*4];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void Dijkstra(int sx,ll dis[]){
	priority_queue<pii,vector<pii>,greater<pii> >q;
	for(int i=1;i<=n;i++){dis[i]=INF;vis[i]=0;}
	q.push(mp(0,sx));dis[sx]=0;
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(a[x]&&x!=sx)continue;
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
int main(){
//	freopen("escape.in","r",stdin);
//	freopen("escape.out","w",stdout);
	n=read();m=read();K=read();Sta=(1<<K)-1;p[0]=1;p[1]=n;Ans=INF;
	for(int i=1;i<=m;i++){int x=read(),y=read(),z=read();Add(x,y,z);Add(y,x,z);}
	for(int i=1;i<=K;i++){p[i*2]=read();int x=p[i*2+1]=read();a[x]=1;b[i*2]=(1<<(i-1));}
	for(int i=0;i<=K*2+1;i++){
		Dijkstra(p[i],dis[i]);
		for(int S=0;S<=Sta;S++)f[i][S]=INF;
	}
	f[0][0]=0;
	for(int S=0;S<=Sta;S++){
		priority_queue<pii,vector<pii>,greater<pii> >q;
		for(int i=0;i<=K*2+1;i++){
			vis[i]=0;
			if(f[i][S]!=INF)q.push(mp(f[i][S],i));
		}
		while(q.size()){
			int x=q.top().scd;q.pop();
			if(vis[x])continue;vis[x]=1;
			for(int y=0;y<=K*2+1;y++){
				if(dis[x][p[y]]==INF)continue;
				if(a[p[y]]&&!((S>>(y/2-1))&1))continue;
				if(f[y][S]>f[x][S]+dis[x][p[y]]){
					f[y][S]=f[x][S]+dis[x][p[y]];
					q.push(mp(f[y][S],y));
				}
			}
		}
		for(int i=0;i<=2*K+1;i++)f[i][S|b[i]]=min(f[i][S|b[i]],f[i][S]);
	}
	for(int S=0;S<=Sta;S++)Ans=min(Ans,f[1][S]);
	printf("%lld\n",(Ans==INF?-1:Ans));
	return 0;
}