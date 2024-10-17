/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=50005;
const ll M=20;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,G,R,tot,root,len[N],dis[N];
struct Tree{ll Min,l,r;};
struct Segment_Tree{
	Tree t[N*M];
	void Insert(ll pos,ll x,ll &p,ll l,ll r){
		if(!p)t[p=++tot].Min=inf;
		t[p].Min=min(t[p].Min,x);
		if(l==r)return;ll mid=(l+r)>>1;
		if(pos<=mid)Insert(pos,x,lson);
		if(pos>mid) Insert(pos,x,rson);
	}
	ll Query(ll x,ll y,ll p,ll l,ll r){
		if(y<l||x>r||!p)return inf;
		if(x<=l&&r<=y)return t[p].Min;
		ll mid=(l+r)>>1;
		return min(Query(x,y,lson),Query(x,y,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();G=read();R=read();
	for(ll i=1;i<=n+1;i++)len[i]=len[i-1]+read();
	for(ll i=n;i>=1;i--){
		ll l=(G+len[i])%(G+R),r=(G+R-1+len[i])%(G+R),tmp=inf;
		if(l<=r)tmp=tree.Query(l+1,r+1,root,1,G+R);
		else tmp=min(tree.Query(1,r+1,root,1,G+R),tree.Query(l+1,G+R,root,1,G+R));
		if(tmp==inf)dis[i]=len[n+1]-len[i];
		else dis[i]=len[tmp]-len[i]+dis[tmp]+(G+R)-(len[tmp]-len[i])%(G+R);
		tree.Insert(len[i]%(G+R)+1,i,root,1,G+R);
	}
	ll T=read();
	while(T--){
		ll x=read(),tmp=inf;
		ll l=(G-x%(G+R)+G+R)%(G+R),r=(G+R-1-x%(G+R)+G+R)%(G+R);
		if(l<=r)tmp=tree.Query(l+1,r+1,root,1,G+R);
		else tmp=min(tree.Query(1,r+1,root,1,G+R),tree.Query(l+1,G+R,root,1,G+R));
		if(tmp==inf)printf("%lld\n",x+len[n+1]);
		else printf("%lld\n",x+len[tmp]+dis[tmp]+(G+R)-(len[tmp]+x)%(G+R));
	}
	return 0;
}