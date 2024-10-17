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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,root;
ll c0[2000005],c1[2000005];
ll p[1000005][21],dep[1000005],val[1000005];
struct edge{
	ll to,next;
}d[2000005];
ll h[1000005],cnt,step,l[1000005],r[1000005];
void hqq_add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void dfs(ll x,ll depth){
	l[x]=++step;
	dep[x]=depth;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(l[y])continue;
		dfs(y,depth+1);
		p[y][0]=x;
	}
	r[x]=++step;
}
ll lowbit(ll x){
	return (x&(-x));
}
void Add(ll c[],ll x,ll y){
	for(ll i=x;i<=n*2;i+=lowbit(i)){
		c[i]+=y;
	}
}
ll Ask(ll c[],ll x){
	ll ans=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
void update(int x,int y){
	if(x==-1)return;
	Add(c0,l[x],y);
	Add(c1,l[x],dep[x]*y);
}
void ST(){
	ll k=(ll)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
ll lca(ll x,ll y){
	ll k;
	if(dep[x]<dep[y])swap(x,y);
	k=(ll)(log(dep[x])/log(2));
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
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();root=read();
	for(ll i=1;i<=n;i++){
		val[i]=read();
	}
	for(ll i=1;i<=n-1;i++){
		ll x=read(),y=read();
		hqq_add(x,y);
		hqq_add(y,x);
	}
	memset(p,-1,sizeof(p));
	dfs(root,1);
	ST();
	for(int i=1;i<=n;i++){
		update(i,val[i]);
		update(p[i][0],-val[i]);
	}
	while(m--){
		ll c=read();
		if(c==1){
			ll x=read(),y=read(),data=read();
			ll z=lca(x,y);
			update(x,data);
			update(y,data);
			update(z,-data);
			update(p[z][0],-data);
		}
		if(c==2){
			ll x=read();
			ll ans=Ask(c0,r[x])-Ask(c0,l[x]-1);
			printf("%lld\n",ans);
		}
		if(c==3){
			ll x=read();
			ll ans=Ask(c1,r[x])-Ask(c1,l[x]-1);
			ans-=(dep[x]-1)*(Ask(c0,r[x])-Ask(c0,l[x]-1));
			printf("%lld\n",ans);
		}
	}
	return 0;
}