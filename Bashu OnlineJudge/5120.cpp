#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	1.一定要清数组
	2.Tarjan缩点
	3.拓扑序Dp(可加堆优化) 
*/
ll n,m,cnt,scc,tp,tot,cntt;
ll dfn[50005],low[50005],st[50005],dis[50005],p[50005];
ll h[50005],h2[50005],b[50005],num[50005],vis[50005];
struct edge{
	ll to,next,data;
}d[200005],e[200005];
void hqq_add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void hqq_add2(ll x,ll y,ll z){
	e[++cntt]=(edge){y,h2[x],z};
	h2[x]=cntt;
}
void init(){
	cnt=scc=tp=tot=cntt=0;
	memset(p,0,sizeof(p));
	memset(e,0,sizeof(e));
	memset(h,0,sizeof(h));
	memset(b,0,sizeof(b));
	memset(d,0,sizeof(d));
	memset(st,0,sizeof(st));
	memset(h2,0,sizeof(h2));
	memset(num,0,sizeof(num));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
}
void Tarjan(ll x){
	dfn[x]=low[x]=++tot;
	st[++tp]=x;p[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		scc++;
		ll k;
		do{
			k=st[tp--];
			b[k]=scc;
			p[k]=0;
			num[scc]++;
		}while(x!=k);
	}
}
struct node{
	ll x;
};
bool operator<(node x,node y){
	return dis[x.x]>dis[y.x];
}
void topsort(){
	priority_queue<node>q;
	q.push((node){b[1]});
	memset(dis,0x7f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[b[1]]=0;vis[b[1]]=1;
	while(q.size()){
		ll x=q.top().x;
		q.pop();
		vis[x]=0;
		for(ll i=h2[x];i;i=e[i].next){
			ll y=e[i].to;
			if(dis[y]>e[i].data){
				dis[y]=e[i].data;
				if(!vis[y]){
					q.push((node){y});
					vis[y]=1;
				}
			}
		}
	}
}
int main(){
//	freopen("message.in","r",stdin);
//	freopen("message.out","w",stdout);
	while(1){
		init();
		n=read();m=read();
		if(n==0&&m==0)break;
		for(ll i=1;i<=m;i++){
			ll x=read()+1,y=read()+1,z=read();
			hqq_add(x,y,z);
		}
		for(ll i=1;i<=n;i++){
			if(!dfn[i])Tarjan(i);
		}
		for(ll x=1;x<=n;x++){
			for(ll i=h[x];i;i=d[i].next){
				ll y=d[i].to;
				if(b[x]!=b[y]){
					hqq_add2(b[x],b[y],d[i].data);
				}
			}
		}
		topsort();
		ll ans=0;
		for(ll i=1;i<=scc;i++){
			ans+=dis[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
