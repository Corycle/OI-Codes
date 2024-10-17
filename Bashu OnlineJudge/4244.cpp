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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt=1;
ll a[N],b[N],h[N],dis[N];
struct edge{ll to,next,flow;}d[N*20];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(ll s,ll t){
	memset(dis,-1,sizeof(dis));
	queue<ll>q;q.push(s);dis[s]=0;
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
	ll ans=0;
	if(x==t||!maxx)return maxx;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			ll dlt=DFS(y,min(maxx,d[i].flow),t);
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
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
bool Check(ll x,ll y){
	if(gcd(x,y)!=1)return false;
	ll z=sqrt(x*x+y*y);
	return (x*x+y*y==z*z);
}
int main(){
//	freopen("number.in","r",stdin);
//	freopen("number.out","w",stdout);
	n=read();
	ll S=n*2+1,T=n*2+2,ans=0;
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++)b[i]=read();
	for(ll i=1;i<=n;i++){
		Add(S,i,b[i]);
		Add(i+n,T,b[i]);
		ans+=b[i];
	}
	for(ll i=1;i<=n;i++){
		for(ll j=i+1;j<=n;j++){
			if(Check(a[i],a[j])){
				Add(i,j+n,inf);
				Add(j,i+n,inf);
			}
		}
	}
	ans-=Dinic(S,T)/2;
	printf("%lld",ans);
	return 0;
}