#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll M=100005;
const ll N=10005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt1,cnt2,cnt=1;
ll h[N],h1[N],h2[N];
ll dis[N],vis[N],val[N];
struct edge{
	ll to,next,data;
}d1[M*2],d2[M*2],e[M*2];
void Add1(ll x,ll y,ll z){
	d1[++cnt1]=(edge){y,h1[x],z};h1[x]=cnt1;
	d2[++cnt2]=(edge){x,h2[y],z};h2[y]=cnt2;
}
void Add2(ll x,ll y,ll z){
	e[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	e[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
struct cmp{
	bool operator()(ll x,ll y){
		return dis[x]>dis[y];
	}
};
void Dijkstra(){
	priority_queue<ll,vector<ll>,cmp>q;
	memset(dis,0x3f,sizeof(dis));
	q.push(1);dis[1]=0;
	while(q.size()){
		ll x=q.top();q.pop();
		vis[x]=0;
		for(ll i=h1[x];i;i=d1[i].next){
			ll y=d1[i].to;
			if(dis[y]>dis[x]+d1[i].data){
				dis[y]=dis[x]+d1[i].data;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
}
void dfs(ll x){
	vis[x]=1;
	for(ll i=h2[x];i;i=d2[i].next){
		ll y=d2[i].to;
		if(dis[x]==dis[y]+d2[i].data){
			Add2(y+n,x,inf);
			if(!vis[y])dfs(y);
		}
	}
}
bool BFS(ll s,ll t){
	memset(dis,-1,sizeof(dis));
	queue<ll>q;q.push(s);
	dis[s]=0;
	while(q.size()){
		ll x=q.front();
		q.pop();
		if(x==t)return true;
		for(ll i=h[x];i;i=e[i].next){
			ll y=e[i].to;
			if(e[i].data&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
ll DFS(ll x,ll maxx,ll t){
	ll ans=0,dlt=0;
	if(x==t||!maxx)return maxx;
	for(ll i=h[x];i;i=e[i].next){
		ll y=e[i].to;
		if(e[i].data&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,e[i].data),t);
			if(!dlt)dis[y]=-1;
			e[i].data-=dlt;
			e[i^1].data+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
ll Dinic(ll s,ll t){
	ll ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		Add1(x,y,z);
		Add1(y,x,z);
	}
	Dijkstra();
	for(ll i=1;i<=n;i++){
		val[i]=read();
		Add2(i,i+n,val[i]);
	}
	dfs(n);
	printf("%lld",Dinic(1+n,n));
	return 0;
}