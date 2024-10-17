#include<map>
#include<stack>
#include<queue>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll M=200005;
const ll N=15;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt;
ll vis[N],h[N],w[N];
ll g[N][N],f[M][N],ans;
struct edge{
	ll to,next,data;
}d[M];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
inline void DFS(ll x,ll tot,ll depth,ll s){
	if(tot>ans)return;
	if(f[s][x]<=tot)return;
	f[s][x]=tot;
	if(depth==n){
		ans=min(ans,tot);
		return;
	}
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(vis[y]<=1&&d[i].data!=inf){
			vis[y]++;
			DFS(y,tot+d[i].data,depth+(vis[y]==1),s+w[y-1]);
			vis[y]--;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	w[0]=1;
	for(ll i=1;i<=10;i++)w[i]=w[i-1]*3;
	while(scanf("%lld%lld",&n,&m)!=EOF){
		ans=inf;cnt=0;
		memset(h,0,sizeof(h));
		memset(f,0x7f,sizeof(f));
		memset(g,0x7f,sizeof(g));
		for(ll i=1;i<=m;i++){
			ll x=read(),y=read(),z=read();
			g[x][y]=g[y][x]=min(g[x][y],z);
		}
		for(ll i=1;i<=n;i++){
			for(ll j=1;j<=n;j++){
				if(g[i][j]!=inf)Add(i,j,g[i][j]);
			}
		}
		for(ll i=1;i<=n;i++){
			memset(vis,0,sizeof(vis));
			vis[i]=1;
			DFS(i,0,1,w[i-1]);
		}
		if(ans!=inf)printf("%lld\n",ans);
		else printf("-1\n");
	}
	return 0;
}