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
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,T,cnt,Ans;
ll h[N],c[N],dis[N],vis[N],pre[N],sum[N];
struct edge{ll to,next,dist;}d[N*10];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct Node{ll x,Dis;};
bool operator<(Node A,Node B){
	return A.Dis>B.Dis;
}
void Dijkstra(){
	memset(dis,0x7f,sizeof(dis));dis[1]=0;
	priority_queue<Node>q;q.push((Node){1,0});
	while(q.size()){
		ll x=q.top().x;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(dis[y]>dis[x]+d[i].dist){
				dis[y]=dis[x]+d[i].dist;
				q.push((Node){y,dis[y]});
			}
		}
	}
}
void DFS(ll x){
	sum[x]=c[x];
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(pre[y]==x){
			DFS(y);
			sum[x]+=sum[y];
			c[y]=0;
		}
	}
	Ans=max(Ans,(dis[x]-T)*sum[x]);
}
int main(){
//	freopen("shortcut.in","r",stdin);
//	freopen("shortcut.out","w",stdout);
	n=read();m=read();T=read();
	for(ll i=1;i<=n;i++)c[i]=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Dijkstra();
	memset(pre,0x7f,sizeof(pre));
	for(ll x=1;x<=n;x++){
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(dis[x]==dis[y]+d[i].dist){
				pre[x]=min(pre[x],y);
			}
		}
	}
	pre[1]=0;DFS(1);
	printf("%lld",Ans);
	return 0;
}