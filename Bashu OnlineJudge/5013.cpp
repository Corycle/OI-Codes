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
#define pii pair<ll,ll>
#define mp make_pair
#define fst first
#define scd second
using namespace std;
const ll inf=9e18;
const ll N=1000005;
const ll M=505;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot;
ll a[M][M],b[M][M],c[M][M],id[M][M][4];
ll h[N],t[N],dis[N],vis[N],pre[N],flag[N];
ll vis1[M][M],vis2[M][M],vis3[M][M],vis4[M][M];
struct edge{ll to,next,dist;}d[N*5];
void Add(ll x,ll y,ll z){
	if(t[x]||t[y])return;
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
void Dijkstra(ll s){
	priority_queue<pii,vector<pii>,greater<pii> >q;
	for(ll i=1;i<=tot;i++){dis[i]=inf;vis[i]=pre[i]=0;}
	q.push(mp(0,s));dis[s]=0;
	while(q.size()){
		ll x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(dis[y]>dis[x]+d[i].dist){
				dis[y]=dis[x]+d[i].dist;
				q.push(mp(dis[y],y));
				pre[y]=x;
			}
		}
	}
}
void DFS(ll x){
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(pre[y]==x){
			DFS(y);
			flag[x]|=flag[y];
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)for(ll j=1;j<=m;j++)a[i][j]=read();
	for(ll i=1;i<=n;i++)for(ll j=1;j<=m+1;j++)b[i][j]=read();
	for(ll i=1;i<=n+1;i++)for(ll j=1;j<=m;j++)c[i][j]=read();
	for(ll i=1;i<=n+1;i++){
		for(ll j=1;j<=m+1;j++){
			for(ll k=0;k<4;k++)id[i][j][k]=++tot;
		}
	}
	for(ll i=1;i<=n+1;i++){
		for(ll j=1;j<=m+1;j++){
			if(i!=n+1)Add(id[i][j][0],id[i+1][j][0],b[i][j]);
			if(j!=m+1)Add(id[i][j][0],id[i][j+1][0],c[i][j]);
		}
	}
	Dijkstra(id[1][1][0]);
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			if(a[i][j]){
				flag[id[i][j][0]]=1;flag[id[i+1][j+1][0]]=1;
				flag[id[i][j+1][0]]=1;flag[id[i+1][j][0]]=1;
				t[id[i][j][2]]=1;t[id[i+1][j+1][0]]=1;
				t[id[i][j+1][3]]=1;t[id[i+1][j][1]]=1;
			}
		}
	}
	DFS(id[1][1][0]);
	vis1[1][1]=vis4[1][1]=1;
	for(ll i=1;i<=n+1;i++){
		for(ll j=1;j<=m+1;j++){
			if(i!=n+1){
				ll x=id[i][j][0],y=id[i+1][j][0];
				if(flag[x]&&flag[y]&&(pre[x]==y||pre[y]==x)){
					vis3[i][j]=1;vis1[i+1][j]=1;
				}
			}
			if(j!=m+1){
				ll x=id[i][j][0],y=id[i][j+1][0];
				if(flag[x]&&flag[y]&&(pre[x]==y||pre[y]==x)){
					vis2[i][j]=1;vis4[i][j+1]=1;
				}
			}
		}
	}
	cnt=0;
	for(ll i=1;i<=tot;i++)h[i]=0;
	for(ll i=1;i<=n+1;i++){
		for(ll j=1;j<=m+1;j++){
			if(i!=n+1){
				Add(id[i][j][2],id[i+1][j][1],b[i][j]);
				Add(id[i][j][3],id[i+1][j][0],b[i][j]);
			}
			if(j!=m+1){
				Add(id[i][j][1],id[i][j+1][0],c[i][j]);
				Add(id[i][j][2],id[i][j+1][3],c[i][j]);
			}
			if(!vis1[i][j])Add(id[i][j][0],id[i][j][1],0);
			if(!vis2[i][j])Add(id[i][j][1],id[i][j][2],0);
			if(!vis3[i][j])Add(id[i][j][2],id[i][j][3],0);
			if(!vis4[i][j])Add(id[i][j][3],id[i][j][0],0);
		}
	}
	Dijkstra(id[1][1][1]);
	printf("%lld",dis[id[1][1][3]]);
	return 0;
}