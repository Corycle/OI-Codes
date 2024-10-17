#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=400005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot;
ll h[N],vis[N],dis[N],pre[N],Line[N];
struct edge{ll to,next,dist;}d[N*2];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct cmp{
	bool operator()(ll x,ll y){
		return dis[x]>dis[y];
	}
};
ll SPFA(ll s){
	memset(pre,0,sizeof(pre));
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	priority_queue<ll,vector<ll>,cmp>q;
	q.push(s);dis[s]=0;
	while(q.size()){
		ll x=q.top();q.pop();vis[x]=0;
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(dis[y]>dis[x]+d[i].dist){
				dis[y]=dis[x]+d[i].dist;pre[y]=x;
				if(!vis[y]){q.push(y);vis[y]=1;}
			}
		}
	}
	ll t=0,Max=0;
	for(ll i=1;i<=n;i++){
		if(dis[i]>Max){Max=dis[i];t=i;}
	}
	return t;
}
void DFS(ll x){
	vis[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(vis[y])continue;
		dis[y]=dis[x]+d[i].dist;
		DFS(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	ll S=SPFA(1);
	ll T=SPFA(S);
	ll sum=dis[T],ans=0;
	for(ll i=T;i!=S;i=pre[i])Line[++tot]=i;Line[++tot]=S;
	for(ll i=1;i<=tot/2;i++)swap(Line[i],Line[tot-i+1]);
	memset(vis,0,sizeof(vis));
	for(ll i=1;i<=tot;i++)vis[Line[i]]=1;
	for(ll i=1;i<=tot;i++){
		dis[Line[i]]=min(dis[Line[i]],sum-dis[Line[i]]);
		DFS(Line[i]);
	}
	for(ll i=1;i<=n;i++){
		ans=max(ans,dis[i]+sum);
	}
	printf("%lld",ans);
	return 0;
}