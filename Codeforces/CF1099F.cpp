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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll m,Ans[N];
int n,cnt,tot;
int a[N],b[N],c[N],h[N],fa[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
struct Tree{ll num,sum;};
struct Segment_Tree{
	Tree t[N*4];
	void Update(int x,int y,int p,int l,int r){
		t[p].num+=y;t[p].sum+=1ll*c[x]*y;
		if(l==r)return;int mid=(l+r)>>1;
		x<=mid?Update(x,y,lson):Update(x,y,rson);
	}
	ll Query(ll K,int p,int l,int r){
		if(l==r)return min(t[p].num,K/c[l]);
		int mid=(l+r)>>1;
		if(K<t[p<<1].sum)return Query(K,lson);
		return t[p<<1].num+Query(K-t[p<<1].sum,rson);
	}
}tree;
void DFS(int x,ll dist){
	if(dist>=m)return;
	tree.Update(b[x],a[x],1,1,tot);
	Ans[x]=tree.Query(m-dist,1,1,tot);
	int Max=0,tmp=0;
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;DFS(y,dist+d[i].dist);if(Ans[y]>Max){Max=Ans[y];tmp=y;}}
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y==tmp)continue;Ans[x]=max(Ans[x],Ans[y]);}
	tree.Update(b[x],-a[x],1,1,tot);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=c[i]=read();
	sort(c+1,c+n+1);tot=unique(c+1,c+n+1)-c-1;
	for(int i=1;i<=n;i++)b[i]=lower_bound(c+1,c+tot+1,b[i])-c;
	for(int i=2;i<=n;i++){fa[i]=read();Add(fa[i],i,read()*2);}
	DFS(1,0);
	ll ans=min((ll)a[1],m/c[b[1]]);
	for(int i=h[1];i;i=d[i].next){int x=d[i].to;ans=max(ans,Ans[x]);}
	printf("%lld\n",ans);
	return 0;
}
