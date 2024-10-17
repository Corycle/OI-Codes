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
const ll N=2000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,fx,fy,cnt=1,Edge;
ll h[N],a[N],vis[N],f[N][2];
struct edge{ll to,next;}d[N];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Find(ll x,ll pre){
	vis[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(i==(pre^1))continue;
		if(vis[y]){
			fx=x;fy=y;Edge=i;
			continue;
		}
		Find(y,i);
	}
}
void DFS(ll x,ll pre){
	f[x][0]=0;
	f[x][1]=a[x];
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(i==(pre^1))continue;
		if(i==Edge||i==(Edge^1))continue;
		DFS(y,i);
		f[x][0]+=max(f[y][0],f[y][1]);
		f[x][1]+=f[y][0];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		ll x=read(),y=read();
		Add(i,y);Add(y,i);a[i]=x;
	}
	ll ans=0;
	for(ll i=1;i<=n;i++){
		if(!vis[i]){
			Find(i,0);
			DFS(fx,0);
			ll tmp=f[fx][0];
			DFS(fy,0);
			ans+=max(tmp,f[fy][0]);
		}
	}
	printf("%lld",ans);
	return 0;
}