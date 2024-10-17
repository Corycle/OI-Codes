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
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=250005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
queue<ll>q;
ll n,m,num,cnt1,cnt2;
ll p[N][25],g[N][25],f[N];
ll h1[N],h2[N],fa[N],dep[N];
ll dfn[N],a[N],vis[N],st[N],usd[N];
struct edge{
	ll to,next,data;
}e1[N*10],e2[N*10];
void Add1(ll x,ll y,ll z){
	e1[++cnt1]=(edge){y,h1[x],z};h1[x]=cnt1;
	e1[++cnt1]=(edge){x,h1[y],z};h1[y]=cnt1;
}
bool cmp(ll x,ll y){
	return dfn[x]<dfn[y];
}
void DFS(ll x,ll depth){
	dfn[x]=++num;
	dep[x]=depth;
	for(ll i=h1[x];i;i=e1[i].next){
		ll y=e1[i].to;
		if(y==fa[x])continue;
		fa[y]=p[y][0]=x;
		g[y][0]=e1[i].data;
		DFS(y,depth+1);
	}
}
void ST(){
	ll i,j,k=(ll)(log(n)/log(2));
	for(j=1;j<=k;j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=-1){
				p[i][j]=p[p[i][j-1]][j-1];
				g[i][j]=min(g[i][j-1],g[p[i][j-1]][j-1]);
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
ll Ask(ll x,ll y){
	ll ans=inf;
	ll k=(ll)(log(dep[x])/log(2));
	for(k;k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y]){
			ans=min(ans,g[x][k]);
			x=p[x][k];
		}
	}
	return ans;
}
void Add2(ll x,ll y){
	if(dep[x]<dep[y])swap(x,y);
	if(x==y)return;
	ll z=Ask(x,y);
	e2[++cnt2]=(edge){y,h2[x],z};h2[x]=cnt2;
	e2[++cnt2]=(edge){x,h2[y],z};h2[y]=cnt2;
}
void SvT(){
	cnt2=0;
	ll k=read();
	for(ll i=1;i<=k;i++)a[i]=read();
	sort(a+1,a+k+1,cmp);
	ll tp=0,tot=1;
	for(ll i=2;i<=k;i++){
		if(LCA(a[tot],a[i])!=a[tot]){
			a[++tot]=a[i];
			usd[a[i]]=1;
		}
	}
	st[++tp]=1;
	for(ll i=1;i<=tot;i++){
		ll lca=LCA(a[i],st[tp]);
		while(1){
			if(dep[st[tp-1]]<=dep[lca]){
				Add2(lca,st[tp--]);
				if(st[tp]!=lca)st[++tp]=lca;
				break;
			}
			Add2(st[tp-1],st[tp]);
			tp--;
		}
		if(st[tp]!=a[i])st[++tp]=a[i];
	}
	while(--tp)Add2(st[tp],st[tp+1]);
}
void dfs(ll x){
	vis[x]=1;
	q.push(x);
	ll sum=0,flag=0;
	for(ll i=h2[x];i;i=e2[i].next){
		ll y=e2[i].to;
		if(vis[y])continue;
		f[y]=e2[i].data;
		dfs(y);
		flag=1;
		sum+=f[y];
	}
	if(flag&&!usd[x])f[x]=min(f[x],sum);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(p,-1,sizeof(p));
	memset(g,0x7f,sizeof(g));
	memset(f,0x7f,sizeof(f));
	n=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read(),z=read();
		Add1(x,y,z);
	}
	DFS(1,1);
	ST();
	ll Case=read();
	while(Case--){
		SvT();
		dfs(1);
		printf("%lld\n",f[1]);
		while(q.size()){
			ll x=q.front();
			q.pop();
			f[x]=inf;
			h2[x]=usd[x]=vis[x]=0;
		}
	}
	return 0;
}