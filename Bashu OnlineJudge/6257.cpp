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
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=2005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,tot,W,Flow,Cost,cnt=1;
ll h[N],H[N],A[N],B[N],a[N],vis[N],dis[N];
struct edge{ll to,next,flow,cost;}d[N*N];
void Add(ll x,ll y,ll f,ll c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(ll s,ll t){
	for(ll i=1;i<=tot;i++){
		vis[i]=0;dis[i]=inf;
	}
	queue<ll>q;q.push(s);dis[s]=0;
	while(q.size()){
		ll x=q.front();q.pop();vis[x]=0;
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return dis[t]!=inf;
}
ll DFS(ll x,ll maxx,ll t){
	ll ans=0;
	if(x==t||!maxx)return maxx;
	vis[x]=1;
	for(ll &i=H[x];i;i=d[i].next){
		ll y=d[i].to;
		if(d[i].flow&&!vis[y]&&dis[y]==dis[x]+d[i].cost){
			ll dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-inf;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
void ZKW(ll s,ll t){
	Flow=Cost=0;
	while(SPFA(s,t)){
		for(ll i=1;i<=tot;i++){
			H[i]=h[i];vis[i]=0;
		}
		ll dlt=DFS(s,inf,t);
		Flow+=dlt;
		Cost+=dlt*dis[t];
	}
}
int main(){
//	freopen("commu.in","r",stdin);
//	freopen("commu.out","w",stdout);
	n=read();W=read();
	ll S=++tot,T=++tot,D=++tot;
	Add(D,T,inf,0);
	for(ll i=1;i<=n;i++){
		a[i]=read();
		Add(S,A[i]=++tot,1,0);
		Add(B[i]=++tot,T,1,0);
		ll Min=-inf,Max=inf;
		for(ll j=i-1;j>=1;j--){
			if(a[j]<=Min||a[j]>=Max)continue;
			Add(A[i],B[j],inf,abs(a[i]-a[j]));
			if(a[j]<=a[i]){
				Add(A[i],A[j],inf,a[i]-a[j]);
				Min=a[j];
			}
			else{
				Add(A[i],A[j],inf,a[j]-a[i]);
				Max=a[j];
			}
		}
		Add(A[i],D,1,W);
	}
	ZKW(S,T);
	printf("%lld",Cost);
	return 0;
}