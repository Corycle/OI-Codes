/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=1005;
const ll M=N*N;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,tot,cnt=1;
ll id1[N][N],id2[N];
ll h[M],H[M],dis[M];
struct edge{ll to,next,flow;}d[M*5];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(ll s,ll t){
	for(ll i=1;i<=tot;i++)dis[i]=-1;
	queue<ll>q;q.push(s);dis[s]=0;
	while(q.size()){
		ll x=q.front();q.pop();
		if(x==t)return true;
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return false;
}
ll DFS(ll x,ll maxx,ll t){
	ll ans=0;
	if(x==t||!maxx)return maxx;
	for(ll &i=H[x];i;i=d[i].next){
		ll y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			ll dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
ll Dinic(ll s,ll t){
	ll ans=0;
	while(BFS(s,t)){
		for(ll i=1;i<=tot;i++)H[i]=h[i];
		ans+=DFS(s,inf,t);
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	ll S=++tot,T=++tot,sum=0;
	for(ll i=1;i<=n;i++)id2[i]=++tot;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			id1[i][j]=++tot;
			ll x=read();sum+=x;
			Add(S,id1[i][j],x);
			Add(id1[i][j],id2[i],inf);
			Add(id1[i][j],id2[j],inf);
		}
	}
	for(ll i=1;i<=n;i++){
		Add(id2[i],T,read());
	}
	printf("%lld",sum-Dinic(S,T));
	return 0;
}