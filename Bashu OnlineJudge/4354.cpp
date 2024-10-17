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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,tot,tp;
ll ans1,ans2,ans3,cnt1,cnt2;
ll h1[N],h2[N],f1[N],f2[N],vis[N],usd[N];
ll p[N][25],a[N],st[N],dfn[N],sum[N],dep[N];
struct edge{
	ll to,next,data;
}d[N*2],e[N*2];
queue<ll>q;
void Add1(ll x,ll y){
	d[++cnt1]=(edge){y,h1[x],0};h1[x]=cnt1;
	d[++cnt1]=(edge){x,h1[y],0};h1[y]=cnt1;
}
void Add2(ll x,ll y){
	ll z=abs(dep[x]-dep[y]);
	e[++cnt2]=(edge){y,h2[x],z};h2[x]=cnt2;
	e[++cnt2]=(edge){x,h2[y],z};h2[y]=cnt2;
}
bool cmp(ll x,ll y){
	return dfn[x]<dfn[y];
}
void DFS(ll x,ll depth){
	dfn[x]=++tot;
	dep[x]=depth;
	for(ll i=h1[x];i;i=d[i].next){
		ll y=d[i].to;
		if(dep[y])continue;
		p[y][0]=x;
		DFS(y,depth+1);
	}
}
void ST(){
	ll i,j,k=(ll)(log(n)/log(2));
	for(j=1;j<=k;j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=-1){
				p[i][j]=p[p[i][j-1]][j-1];
			}
		}
	}
}
ll LCA(ll x,ll y){
	if(dep[x]<dep[y])swap(x,y);
	ll k=(ll)(log(dep[x])/log(2));
	for(k;k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	k=(ll)(log(dep[x])/log(2));
	for(k;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];
			y=p[y][k];
		}
	}
	return p[x][0];
}
void SvT(){
	tp=cnt2=0;
	st[++tp]=1;
	for(ll i=1;i<=m;i++){
		ll lca=LCA(st[tp],a[i]);
		if(lca==st[tp]){st[++tp]=a[i];continue;}
		while(1){
			if(dep[st[tp-1]]<=dep[lca]){
				Add2(lca,st[tp--]);
				if(st[tp]!=lca)st[++tp]=lca;
				break;
			}
			Add2(st[tp-1],st[tp]);
			tp--;
		}
		st[++tp]=a[i];
	}
	while(--tp)Add2(st[tp],st[tp+1]);
}
void dfs(ll x){
	vis[x]=1;
	q.push(x);
	sum[x]=usd[x];
	f1[x]=inf;f2[x]=0;
	if(usd[x])f1[x]=0;
	for(ll i=h2[x];i;i=e[i].next){
		ll y=e[i].to;
		if(vis[y])continue;
		dfs(y);
		ans1+=sum[y]*(m-sum[y])*e[i].data;
		if(sum[x]){
			ans2=min(ans2,f1[x]+f1[y]+e[i].data);
			ans3=max(ans3,f2[x]+f2[y]+e[i].data);
		}
		f1[x]=min(f1[x],f1[y]+e[i].data);
		f2[x]=max(f2[x],f2[y]+e[i].data);
		sum[x]+=sum[y];
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(p,-1,sizeof(p));
	n=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add1(x,y);
	}
	DFS(1,1);ST();
	ll Case=read();
	while(Case--){
		m=read();
		ans1=0;ans2=inf;ans3=0;
		for(ll i=1;i<=m;i++){
			a[i]=read();
			usd[a[i]]=1;
		}
		sort(a+1,a+m+1,cmp);
		SvT();dfs(1);
		while(q.size()){
			ll x=q.front();q.pop();
			h2[x]=vis[x]=sum[x]=usd[x]=0;
		}
		printf("%lld %lld %lld\n",ans1,ans2,ans3);
	}
	return 0;
}