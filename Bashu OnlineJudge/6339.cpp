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
#include<set>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,q,cnt,tot,top1,top2;
struct Line{ll x,y;}P[N];
struct Ques{ll l,r,id;}Q[N];
struct edge{ll to,next;}d[N*2];
struct Node{ll l,r,c;}st1[N],st2[N];
ll h[N],fa[N],dep[N],sum[N],son[N];
ll a[N],id[N],pos[N],Ans[N],top[N],Sum[N];
void Add(ll x,ll y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
bool operator<(Node A,Node B){return A.r<B.r;}
bool cmp(Ques A,Ques B){return A.r<B.r;}
set<Node>F;
set<Node>::iterator it;
struct BIT{
	ll c[N];
	ll lowbit(ll x){return x&(-x);}
	void Add(ll x,ll y){for(;x<=m;x+=lowbit(x))c[x]+=y;}
	ll Ask(ll x){ll sum=0;for(;x>=1;x-=lowbit(x))sum+=c[x];return sum;}
	ll Query(ll l,ll r){return Ask(r)-Ask(l-1);}
}tree;
void DFS1(ll x,ll depth){
	dep[x]=depth;sum[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(ll x,ll tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
void Cover(ll l,ll r,ll c){
	st1[++top1]=(Node){l,r,c};
	it=F.lower_bound((Node){l,l,c});
	for(;it!=F.end()&&(*it).l<=r;it++){
		Node t=*it;st2[++top2]=t;
		if(t.l<l)st1[++top1]=(Node){t.l,l-1,t.c};
		if(t.r>r)st1[++top1]=(Node){r+1,t.r,t.c};
	}
	while(top2){
		Node t=st2[top2--];F.erase(t);
		tree.Add(t.c,-(Sum[t.r]-Sum[t.l-1]));
	}
	while(top1){
		Node t=st1[top1--];F.insert(t);
		tree.Add(t.c,(Sum[t.r]-Sum[t.l-1]));
	}
}
void Update(ll num){
	ll x=P[num].x,y=P[num].y;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Cover(id[top[x]],id[x],num);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	Cover(id[x],id[y],num);
}
int main(){
//	freopen("D:\\star.in","r",stdin);
//	freopen("D:\\star.out","w",stdout);
	n=read();m=read();q=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<n;i++){ll x=read(),y=read();Add(x,y);Add(y,x);}
	for(ll i=1;i<=m;i++){P[i].x=read();P[i].y=read();}
	for(ll i=1;i<=q;i++){Q[i].l=read();Q[i].r=read();Q[i].id=i;}
	DFS1(1,1);DFS2(1,1);sort(Q+1,Q+q+1,cmp);
	for(ll i=1;i<=n;i++)Sum[i]=Sum[i-1]+a[pos[i]];
	ll p=0;
	for(ll i=1;i<=q;i++){
		while(p<Q[i].r)Update(++p);
		Ans[Q[i].id]=tree.Query(Q[i].l,Q[i].r);
	}
	for(ll i=1;i<=q;i++)printf("%lld\n",Ans[i]);
	return 0;
}