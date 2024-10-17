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
#define inf 0x7f7f7f7f7f7f7f7f
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,a[200005],f[200005],cnt,h[200005],dfn[200005],low[200005];
ll p[200005],st[200005],tp,tot,scc,b[200005],sum[200005];
ll h2[200005],cntt,rd[200005],ans[200005];
struct edge{
	int to,next;
}d[200005],e[200005];
void hqq_add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void hqq_add2(ll x,ll y){
	e[++cntt]=(edge){y,h2[x]};
	h2[x]=cntt;
}
void tarjan(ll x){
	ll i,j,k;
	dfn[x]=low[x]=++tot;
	st[++tp]=x;
	p[x]=1;
	for(i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		scc++;
		do{
			k=st[tp--];
			p[k]=0;
			b[k]=scc;
			sum[scc]+=a[k];
		}while(k!=x);
	}
}
queue<ll>q;
void topsort(){
	ll i,j,k;
	for(i=1;i<=scc;i++){
		if(rd[i]==0){
			q.push(i);
			ans[i]=sum[i];
		}
	}
	while(q.size()){
		ll x=q.front();
		q.pop();
		for(i=h2[x];i;i=e[i].next){
			ll y=e[i].to;
			rd[y]--;
			if(rd[y]==0)q.push(y);
			ans[y]=max(ans[y],ans[x]+sum[y]);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll i,j,k;
	n=read();
	for(i=1;i<=n;i++)a[i]=read();
	for(i=1;i<=n;i++)hqq_add(i,read());
	for(i=1;i<=n;i++){
		if(!dfn[i])tarjan(i);
	}
	for(i=1;i<=cnt;i++){
		if(b[i]!=b[d[i].to]){
			hqq_add2(b[d[i].to],b[i]);
			rd[b[i]]++;
		}
	}
	topsort();
	for(i=1;i<=n;i++){
		printf("%lld\n",ans[b[i]]);
	}
	return 0;
}