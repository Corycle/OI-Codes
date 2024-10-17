#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt,tot;
ll h[N],fa[N],dis[N];
struct edge{ll to,next,data;}d[N*2];
struct Trie{ll ch[2],flag;}t[N*10];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS(ll x){
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;
		dis[y]=dis[x]^d[i].data;
		fa[y]=x;DFS(y);
	}
}
void Insert(ll num){
	ll p=0;
	for(ll i=31;i>=0;i--){
		ll x=(num>>i)&1;
		if(!t[p].ch[x])t[p].ch[x]=++tot;
		p=t[p].ch[x];
	}
	t[p].flag=1;
}
ll Ask(ll num){
	ll p=0,ans=0;
	for(ll i=31;i>=0;i--){
		ll x=(num>>i)&1;
		if(t[p].ch[x^1]){
			ans+=(1ll<<i);
			p=t[p].ch[x^1];
		}
		else p=t[p].ch[x];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	ll ans=0;DFS(1);
	for(ll i=1;i<=n;i++)Insert(dis[i]);
	for(ll i=1;i<=n;i++)ans=max(ans,Ask(dis[i]));
	printf("%lld",ans);
	return 0;
}