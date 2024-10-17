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
const ll Mod=998244353;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,S,cnt;
ll h[N],vis[N],dis1[N];double dis2[N];
struct edge{ll to,next,dist1;double dist2;}d[N*10];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z,log(z)};h[x]=cnt;
}
struct Node{ll x;double dist;};
bool operator<(Node A,Node B){
	return A.dist>B.dist;
}
void Dijkstra(){
	priority_queue<Node>q;
	for(ll i=1;i<=n;i++)dis1[i]=dis2[i]=inf;
	q.push((Node){S,0});dis1[S]=1;dis2[S]=0;
	while(q.size()){
		ll x=q.top().x;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(dis2[y]>dis2[x]+d[i].dist2){
				dis2[y]=dis2[x]+d[i].dist2;
				dis1[y]=dis1[x]*d[i].dist1%Mod;
				q.push((Node){y,dis2[y]});
			}
		}
	}
}
int main(){
//	freopen("duliu.in","r",stdin);
//	freopen("duliu.out","w",stdout);
	n=read();m=read();S=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Dijkstra();
	ll T=read();
	while(T--){
		int x=read();
		printf("%lld\n",dis1[x]);
	}
	return 0;
}