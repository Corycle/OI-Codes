#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,S,T,Max,Sum,tot,cnt=1;
ll h[N],b[N],dis[N],pre[N],vis[N];
struct edge{
	ll to,next,data;
}d[N];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void dfs(ll x,ll fa){
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa)continue;
		dis[y]=dis[x]+d[i].data;
		dfs(y,x);pre[y]=i;
	}
}
void DFS(ll x,ll fa,ll dist){
	Max=max(Max,dist);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa||vis[y])continue;
		DFS(y,x,dist+d[i].data);
	}
}
void Prepare(){
	dfs(1,0);
	for(ll i=1;i<=n;i++)if(dis[i]>dis[S])S=i;
	memset(dis,0,sizeof(dis));dfs(S,0);
	for(ll i=1;i<=n;i++)if(dis[i]>dis[T])T=i;
	for(ll i=T;i!=S;i=d[pre[i]^1].to)vis[b[++tot]=i]=1;
	vis[b[++tot]=S]=1;Sum=dis[T];
	for(ll i=1;i<=tot/2;i++)swap(b[i],b[tot-i+1]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=2;i<=n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Prepare();
	for(ll i=1;i<=n;i++){
		if(vis[i])DFS(i,0,0);
	}
	ll l=1,r=0,ans=inf;
	while(r<tot){
		r++;
		while(l<r&&dis[b[r]]-dis[b[l]]>m)l++;
		ans=min(ans,max(Max,max(dis[b[l]],Sum-dis[b[r]])));
	}
	printf("%lld",ans);
	return 0;
}