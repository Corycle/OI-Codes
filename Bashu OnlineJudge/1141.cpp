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
const ll M=2000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,top,tot,num,Sum,Max,cnt=1;
ll h[N],a[M],vis[N],f[N][2],Circle[M];
ll q[M],dfn[N],low[N],st[N],dis[M],vst[M];
struct edge{ll to,next,data;}d[M];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void Tarjan(ll x,ll pre){
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
		}
		else{
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		ll k=0;
		if(st[top]==x){
			top--;
			return;
		}
		do{
			k=st[top--];
			Circle[++num]=k;
			vis[k]=1;
		}while(k!=x);
	}
}
void DFS(ll x,ll fa){
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(vis[y]||y==fa)continue;
		DFS(y,x);
		ll dlt=f[y][0]+d[i].data;
		if(f[x][0]<dlt){
			f[x][1]=f[x][0];
			f[x][0]=dlt;
		}
		else f[x][1]=max(f[x][1],dlt);
	}
	Max=max(Max,f[x][0]+f[x][1]);
}
ll Dist(ll x,ll y){
	for(ll i=h[x];i;i=d[i].next){
		if(y==d[i].to&&!vst[i]){
			vst[i]=vst[i^1]=1;
			return d[i].data;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		int x=read(),y=read();
		Add(i,x,y);Add(x,i,y);
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
		if(!dfn[i]){
			Max=num=Sum=0;
			Tarjan(i,0);
			for(ll j=1;j<=num;j++){
				Circle[j+num]=Circle[j];
				DFS(Circle[j],0);
			}
			dis[1]=0;
			for(ll j=2;j<=num+1;j++){
				dis[j]=dis[j-1]+Dist(Circle[j-1],Circle[j]);
			}
			for(ll j=num+2;j<=num*2;j++){
				dis[j]=dis[j-1]+dis[j-num]-dis[j-1-num];
			}
			Sum=dis[num+1];
			ll L=1,R=1;q[1]=1;
			for(ll j=1;j<=num*2;j++)a[j]=f[Circle[j]][0];
			for(ll j=2;j<=num*2;j++){
				while(L<=R&&dis[j]-dis[q[L]]>=Sum)L++;
				if(L<=R){
					ll dist=max(dis[j]-dis[q[L]],Sum-(dis[j]-dis[q[L]]));
					Max=max(Max,dist+a[j]+a[q[L]]);
				}
				while(L<=R&&a[j]-dis[j]>a[q[R]]-dis[q[R]])R--;
				q[++R]=j;
			}
			ans+=Max;
		}
	}
	printf("%lld",ans);
	return 0;
}