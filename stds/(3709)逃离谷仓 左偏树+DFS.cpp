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
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,h[N],ans[N],prt[N];
struct edge{
	ll to,next,data;
}d[N];
struct tree{
	ll l,r,fa;
	ll dis,dep;
}t[N];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
ll Merge(ll x,ll y){
	if(!x||!y)return x+y;
	if(t[x].dep<t[y].dep)swap(x,y);
	t[x].r=Merge(t[x].r,y);
	if(t[t[x].l].dis<t[t[x].r].dis)swap(t[x].l,t[x].r);
	if(!t[x].r)t[x].dis=0;
	else t[x].dis=t[t[x].r].dis+1;
	return x;
}
void dfs(ll x){
	ans[x]=1;
	t[x].fa=x;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==prt[x])continue;
		t[y].dep=t[x].dep+d[i].data;
		dfs(y);
		ans[x]+=ans[y];
		t[x].fa=Merge(t[x].fa,t[y].fa);
		while(t[t[x].fa].dep>t[x].dep+m){
			ans[x]--;
			t[x].fa=Merge(t[t[x].fa].l,t[t[x].fa].r);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=2;i<=n;i++){
		ll x=read(),y=read();
		Add(x,i,y);
		prt[i]=x;
	}
	dfs(1);
	for(ll i=1;i<=n;i++)printf("%lld\n",ans[i]);
	return 0;
}
