#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#define ll long long
using namespace std;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,mod,h[100005],cnt;
ll dfn[100005],low[100005],st[100005],p[100005],tp,tot;
ll scc,b[100005],sum[100005],ans1,ans2,maxx[100005];
ll cntt,h2[100005],num[100005],rd[100005];
struct edge{
	ll to,next,fr;
}d[2000005],e[2000005];
void hqq_add(ll x,ll y){
	d[++cnt]=(edge){y,h[x],x};
	h[x]=cnt;
}
void hqq_add2(ll x,ll y){
	e[++cntt]=(edge){y,h2[x],x};
	h2[x]=cntt;
}
void tarjan(ll x){
	dfn[x]=low[x]=++tot;
	st[++tp]=x;
	p[x]=1;
	for(ll i=h[x];i;i=d[i].next){
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
		ll k;
		do{
			k=st[tp--];
			p[k]=0;
			b[k]=scc;
			sum[scc]++;
		}while(k!=x);
	}
}
void topsort(){
	queue<ll>q;
	for(ll i=1;i<=scc;i++){
		if(!rd[i]){
			q.push(i);
		}
		maxx[i]=sum[i];
		num[i]=1;
	}
	while(q.size()){
		ll x=q.front();
		q.pop();
		ans1=max(maxx[x],ans1);
		for(ll i=h2[x];i;i=e[i].next){
			ll y=e[i].to;
			rd[y]--;
			if(!rd[y])q.push(y);
			if(maxx[x]+sum[y]>maxx[y]){
				maxx[y]=maxx[x]+sum[y];
				num[y]=num[x];
			}
			else if(maxx[x]+sum[y]==maxx[y]){
				num[y]=(num[y]+num[x])%mod;
			}
		}
	}
}
ll qvq[100005],qwq[100005];
int main(){
//	freopen("semi.in","r",stdin);
//	freopen("semi.out","w",stdout);
	n=read();m=read();mod=read();
	while(m--){
		ll x=read(),y=read();
		hqq_add(x,y);
	}
	for(ll i=1;i<=n;i++){
		if(!dfn[i])tarjan(i);
	}
	for(ll i=1;i<=cnt;i++){
		if(b[d[i].fr]!=b[d[i].to]){
			hqq_add2(b[d[i].fr],b[d[i].to]);
			rd[b[d[i].to]]++;
		}
	}
	memset(qvq,0,sizeof(qvq));
	for(ll i=1;i<=scc;i++){
		ll lst=h2[i];
		qwq[0]=0;
		for(ll j=h2[i];j;j=e[j].next){
			ll y=e[j].to;
			if(!qvq[y]){
				lst=j;
				qvq[y]++;
				qwq[++qwq[0]]=y;
			}
			else{//删掉重边 
				e[lst].next=e[j].next;
				rd[y]--;
			}
		}
		for(ll j=1;j<=qwq[0];j++)qvq[qwq[j]]=0;//用memset要超时 
	}
	topsort();
	for(ll i=1;i<=scc;i++){
		if(maxx[i]==ans1){
			ans2=(ans2+num[i])%mod;
		}
	}
	printf("%lld\n%lld",ans1,ans2);
	return 0;
}