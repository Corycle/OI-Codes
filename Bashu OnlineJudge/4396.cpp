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
const ll N=500005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt=1;
ll h[N],dis[N];
struct edge{
	ll to,next,flow;
}d[N*10];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(ll s,ll t){
	queue<ll>q;
	memset(dis,-1,sizeof(dis));
	q.push(s);dis[s]=0;
	while(q.size()){
		ll x=q.front();q.pop();
		if(x==t)return true;
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
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
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
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
	ll S=0,T=n+m*2+1,ans=0;
	for(ll i=1;i<=n;i++){
		ll x=read(),y=read();
		Add(S,i,x);
		Add(i,T,y);
		ans+=x+y;
	}
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read();
		ll a=read(),b=read(),c=read();
		Add(x,n+i,inf);
		Add(y,n+i,inf);
		Add(n+i,T,a+c);
		Add(n+m+i,x,inf);
		Add(n+m+i,y,inf);
		Add(S,n+m+i,b+c);
		ans+=a+b+c;
	}
	ans-=Dinic(S,T);
	printf("%lld",ans);
	return 0;
}
