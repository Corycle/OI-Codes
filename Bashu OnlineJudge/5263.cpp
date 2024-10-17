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
ll a[1000005],c[2000005];
struct edge{
	ll to,next;
}d[2000005];
ll h[1000005],cnt,step,l[1000005],r[1000005];
void hqq_add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void dfs(ll x){
	l[x]=++step;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(l[y])continue;
		dfs(y);
	}
	r[x]=++step;
}
ll lowbit(ll x){
	return (x&(-x));
}
void Add(ll x,ll y){
	for(ll i=x;i<=n*2;i+=lowbit(i)){
		c[i]+=y;
	}
}
ll Ask(ll x){
	ll ans=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();root=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
	}
	for(ll i=1;i<=n-1;i++){
		ll x=read(),y=read();
		hqq_add(x,y);
		hqq_add(y,x);
	}
	dfs(root);
	for(ll i=1;i<=n;i++){
		Add(l[i],a[i]);
	}
	while(m--){
		ll p=read();
		if(p==1){
			ll x=read(),y=read();
			Add(l[x],y);
		}
		if(p==2){
			ll x=read();
			printf("%lld\n",Ask(r[x])-Ask(l[x]-1));
		}
	}
	return 0;
}