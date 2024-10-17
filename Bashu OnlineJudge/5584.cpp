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
#define pii pair<ll,ll>
using namespace std;
const ll inf=0x3f3f3f3f3f3f3f3f;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,Ans=-inf,Edge_cnt;
ll num[2],V[2][N],W[N],b[N];
namespace Tree2{
	ll tp,cnt,tot,Num;
	ll a[N],st[N],dep[N],dis[N],f[N][2];
	ll h[N],dfn[N],vis[N],fir[N],p[N][20];
	struct edge{ll to,next,data;}d[N*2];
	void Add(ll x,ll y,ll z){
		if(x==y)return;
		Edge_cnt++;
		d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
		d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
	}
	ll Compare(ll x,ll y){
		return dep[x]<dep[y]?x:y;
	}
	bool cmp(ll x,ll y){
		return dfn[x]<dfn[y];
	}
	/*----------------初始化-----------------*/
	void dfs(ll x,ll fa){
		dfn[x]=++tot;
		dep[x]=dep[fa]+1;
		p[++Num][0]=x;fir[x]=Num;
		for(int i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(y==fa)continue;
			dis[y]=dis[x]+d[i].data;
			dfs(y,x);p[++Num][0]=x;
		}
	}
	void ST(){
		ll k=(ll)(log(Num)/log(2));
		for(int j=1;j<=k;j++){
			for(int i=1;i+(1<<j)-1<=Num;i++){
				p[i][j]=Compare(p[i][j-1],p[i+(1<<(j-1))][j-1]);
			}
		}
	}
	void Prepare(){
		dfs(1,0);ST();
		memset(h,0,sizeof(h));
		memset(vis,0,sizeof(vis));
	}
	/*----------------虚树DP-----------------*/
	ll LCA(ll x,ll y){
		x=fir[x];y=fir[y];
		if(x>y)swap(x,y);
		ll k=(ll)(log(y-x+1)/log(2));
		return Compare(p[x][k],p[y+1-(1<<k)][k]);
	}
	void SvT(){
		ll k=0,tp=0;cnt=0;
		for(int i=1;i<=num[0];i++)a[++k]=V[0][i];
		for(int i=1;i<=num[1];i++)a[++k]=V[1][i];
		for(int i=1;i<=k;i++)vis[a[i]]=1;
		sort(a+1,a+k+1,cmp);st[++tp]=1;
		for(int i=1;i<=k;i++){
			ll lca=LCA(a[i],st[tp]);
			if(lca==st[tp]){st[++tp]=a[i];continue;}
			while(1){
				if(dep[st[tp-1]]<=dep[lca]){
					Add(lca,st[tp--],0);
					if(st[tp]!=lca)st[++tp]=lca;
					break;
				}
				Add(st[tp-1],st[tp],0);tp--;
			}
			if(st[tp]!=a[i])st[++tp]=a[i];
		}
		while(--tp)Add(st[tp],st[tp+1],0);
	}
	void DP(ll x,ll fa,ll pos){
		f[x][0]=f[x][1]=-inf;
		if(vis[x])f[x][b[x]]=W[x];
		for(int i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(y==fa)continue;DP(y,x,pos);
			ll dlt=max(f[x][0]+f[y][1],f[x][1]+f[y][0]);
			Ans=max(Ans,pos+dlt-2*dis[x]);
			f[x][0]=max(f[x][0],f[y][0]);
			f[x][1]=max(f[x][1],f[y][1]);
		}
		h[x]=0;vis[x]=0;
	}
	void Solve(ll x){SvT();DP(1,0,x);}
}

namespace Tree1{
	vector<pii>v[N];
	ll n,id,cnt,Max;
	ll h[N],dis[N],dep[N];
	ll sum[N],vis[N],flag[N];
	struct edge{ll to,next,data;}d[N*2];
	void Add(ll x,ll y,ll z){
		Edge_cnt++;
		d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
		d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
	}
	/*----------------初始化-----------------*/
	void dfs(ll x,ll fa){
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			ll z=d[i].data;
			if(y==fa)continue;
			dep[y]=dep[x]+d[i].data;
			v[x].push_back(make_pair(y,z));
			dfs(y,x);
		}
	}
	void Rebuild(ll x){
		ll len=v[x].size();
		if(len<=2){
			for(ll i=0;i<len;i++){
				ll y=v[x][i].first;
				ll z=v[x][i].second;
				Add(x,y,z);
			}
		}
		else{
			ll L=++n,R=++n;
			Add(x,L,0);Add(x,R,0);
			for(ll i=0;i<len;i++){
				ll y=v[x][i].first;
				ll z=v[x][i].second;
				if(i&1)v[L].push_back(make_pair(y,z));
				else v[R].push_back(make_pair(y,z));
			}
		}
	}
	void Prepare(){
		dfs(1,0);cnt=1;
		memset(h,0,sizeof(h));
		for(int i=1;i<=n;i++)flag[i]=1;
		for(int i=1;i<=n;i++)Rebuild(i);
	}
	/*----------------边分治-----------------*/
	void Find(ll x,ll fa,ll Sum){
		sum[x]=1;
		for(int i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(vis[i>>1]||y==fa)continue;
			Find(y,x,Sum);sum[x]+=sum[y];
			if(Max>max(sum[y],Sum-sum[y])){
				Max=max(sum[y],Sum-sum[y]);id=i;
			}
		}
	}
	void DFS(ll x,ll fa,ll pos){
		if(flag[x]){
			b[x]=pos;
			V[pos][++num[pos]]=x;
		}
		for(int i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(vis[i>>1]||y==fa)continue;
			dis[y]=dis[x]+d[i].data;
			DFS(y,x,pos);
		}
	}
	void Divide(ll x,ll Sum){
		Max=inf;
		if(Edge_cnt>=6e6)return;
		Find(x,0,Sum);vis[id>>1]=1;
		if(Max==inf||Sum==1)return;
		ll S=d[id].to,T=d[id^1].to;
		ll Num=Sum-sum[d[id].to];
		num[0]=dis[S]=0;DFS(S,0,0);
		num[1]=dis[T]=0;DFS(T,0,1);
		if(!num[0]||!num[1])return;
		for(int i=1;i<=num[0];i++)W[V[0][i]]+=dis[V[0][i]]+dep[V[0][i]];
		for(int i=1;i<=num[1];i++)W[V[1][i]]+=dis[V[1][i]]+dep[V[1][i]];
		Tree2::Solve(d[id].data);
		for(int i=1;i<=num[0];i++)W[V[0][i]]-=dis[V[0][i]]+dep[V[0][i]];
		for(int i=1;i<=num[1];i++)W[V[1][i]]-=dis[V[1][i]]+dep[V[1][i]];
		ll p=sum[d[id].to];
		Divide(S,p);Divide(T,Sum-p);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Tree1::n=n;
	for(int i=2;i<=n;i++){
		ll x=read(),y=read(),z=read();
		Tree1::Add(x,y,z);
	}
	for(int i=2;i<=n;i++){
		ll x=read(),y=read(),z=read();
		Tree2::Add(x,y,z);
	}
	Tree1::Prepare();
	Tree2::Prepare();
	Tree1::Divide(1,Tree1::n);
	Ans/=2;
	for(int i=1;i<=n;i++){
		Ans=max(Ans,Tree1::dep[i]-Tree2::dis[i]);
	}
	printf("%lld",Ans);
	return 0;
}