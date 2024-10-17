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
const ll inf=9e18;
const ll M=200005;
const ll N=50005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,K,cnt,tot,Ans;
struct Edge{ll s,t,c;}e[15];
struct edge{ll to,next,dist;}d[M*2];
ll h[N],id[N],vis[N],dis[26][N],f[N][26][2];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct Node{
	ll x,dis;
	friend bool operator<(Node A,Node B){
		return A.dis>B.dis;
	}
};
void Dijkstra(ll s){
	if(id[s])return;
	id[s]=++tot;
	for(ll i=1;i<=n;i++){
		vis[i]=0;dis[tot][i]=inf;
	}
	priority_queue<Node>q;
	q.push((Node){s,0});
	dis[tot][s]=0;
	while(q.size()){
		ll x=q.top().x;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(dis[tot][y]>dis[tot][x]+d[i].dist){
				dis[tot][y]=dis[tot][x]+d[i].dist;
				q.push((Node){y,dis[tot][y]});
			}
		}
	}
}
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	n=read();m=read();K=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		if(i<=K){e[i]=(Edge){x,y,z};}
		Add(x,y,z);Add(y,x,z);
	}
	Dijkstra(1);
	for(ll i=1;i<=K;i++){
		Dijkstra(e[i].s);
		Dijkstra(e[i].t);
	}
	ll Sta=(1<<K)-1,Ans=inf;
	memset(f,0x3f,sizeof(f));
	for(ll i=1;i<=K;i++){
		ll S=(1<<(i-1));
		f[S][i][0]=dis[1][e[i].t]+e[i].c;
		f[S][i][1]=dis[1][e[i].s]+e[i].c;
	}
	for(ll S=0;S<=Sta;S++){
		for(ll i=1;i<=K;i++){
			if(!((S>>(i-1))&1))continue;
			ll T=S-(1<<(i-1));
			for(ll j=1;j<=K;j++){
				if(!((T>>(j-1))&1))continue;
				ll sx=id[e[j].s],fx=e[i].s;
				ll sy=id[e[j].t],fy=e[i].t;
				f[S][i][0]=min(f[S][i][0],f[T][j][0]+dis[sx][fy]+e[i].c);
				f[S][i][0]=min(f[S][i][0],f[T][j][1]+dis[sy][fy]+e[i].c);
				f[S][i][1]=min(f[S][i][1],f[T][j][0]+dis[sx][fx]+e[i].c);
				f[S][i][1]=min(f[S][i][1],f[T][j][1]+dis[sy][fx]+e[i].c);
			}
		}
	}
	for(ll i=1;i<=K;i++){
		ll x=id[e[i].s],y=id[e[i].t];
		Ans=min(Ans,f[Sta][i][0]+dis[x][1]);
		Ans=min(Ans,f[Sta][i][1]+dis[y][1]);
	}
	printf("%lld\n",Ans);
	return 0;
}