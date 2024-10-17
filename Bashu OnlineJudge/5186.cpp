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
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot,top,scc,Ans;
struct edge{ll to,next;}e1[N],e2[N];
ll h1[N],h2[N],b[N],st[N],rd[N],val[N],vis[N],sum[N],dfn[N],low[N];
void Add1(ll x,ll y){e1[++cnt]=(edge){y,h1[x]};h1[x]=cnt;}
void Add2(ll x,ll y){e2[++cnt]=(edge){y,h2[x]};h2[x]=cnt;}
void Tarjan(ll x){
	dfn[x]=low[x]=++tot;
	st[++top]=x;vis[x]=1;
	for(ll i=h1[x];i;i=e1[i].next){
		ll y=e1[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		ll k=0;scc++;
		do{
			k=st[top--];
			sum[scc]+=val[k];
			vis[k]=0;b[k]=scc;
		}while(x!=k);
	}
}
void Solve(){
	queue<ll>q;
	for(ll i=1;i<=scc;i++){
		if(!rd[i])q.push(i);
	}
	while(q.size()){
		ll x=q.front();q.pop();
		for(ll i=h2[x];i;i=e2[i].next){
			ll y=e2[i].to;
			rd[y]--;sum[y]+=sum[x];
			if(!rd[y])q.push(y);
		}
	}
}
int main(){
//	freopen("meaning.in","r",stdin);
//	freopen("meaning.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)Add1(i,read());
	for(ll i=1;i<=n;i++)val[i]=read();
	for(ll i=1;i<=n;i++)if(!dfn[i])Tarjan(i);
	cnt=0;
	for(ll x=1;x<=n;x++){
		for(ll i=h1[x];i;i=e1[i].next){
			ll y=e1[i].to;
			if(b[x]!=b[y]){
				Add2(b[y],b[x]);
				rd[b[x]]++;
			}
		}
	}
	Solve();
	for(ll i=1;i<=n;i++)Ans+=sum[b[i]];
	printf("%.6lf",(double)(Ans)/(double)(n));
	return 0;
}
