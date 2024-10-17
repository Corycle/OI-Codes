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
const int inf=0x3f3f3f3f;
const int N=1e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N];
vector<int>F[N];
int n,m,cnt,tot;
int h[N],a[N],b[N],fa[N],dis[N],Root[N];
struct edge{int to,next;}d[N];
struct Node{int x,k;}P[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int dist){
	dis[x]=dist;
	for(int i=h[x];i;i=d[i].next)DFS(d[i].to,dist+a[d[i].to]);
}
struct Tree{int l,r,num;ll sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*M];
	void Insert(int x,int &p,int l,int r){
		if(!p)p=++tot;t[p].num++;t[p].sum+=b[x];
		if(l==r)return;int mid=(l+r)>>1;
		x<=mid?Insert(x,lson):Insert(x,rson);
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		t[x].num+=t[y].num;
		t[x].sum+=t[y].sum;
		t[x].l=Merge(t[x].l,t[y].l);
		t[x].r=Merge(t[x].r,t[y].r);
		return x;
	}
	ll Query(int val,int x,int y,int p,int l,int r){
		if(y<l||x>r||!p)return 0;
		if(x<=l&&r<=y)return t[p].sum-1ll*t[p].num*val;
		int mid=(l+r)>>1;
		return Query(val,x,y,lson)+Query(val,x,y,rson);
	}
}tree;
void Solve(int x){
	tree.Insert(dis[x],Root[x],1,tot);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;Solve(y);
		Root[x]=tree.Merge(Root[x],Root[y]);
	}
	int num=F[x].size();
	for(int j=0;j<num;j++){
		int i=F[x][j];
		int pos=lower_bound(b+1,b+tot+1,b[dis[x]]+P[i].k)-b;
		Ans[i]=tree.Query(b[dis[x]],pos,tot,Root[x],1,tot);
	}
}
int main(){
//	freopen("forging.in","r",stdin);
//	freopen("forging.out","w",stdout);
	n=read();
	for(int i=2;i<=n;i++){Add(read(),i);a[i]=read();}
	m=read();
	for(int i=1;i<=m;i++){P[i].x=read();P[i].k=read();F[P[i].x].push_back(i);}
	DFS(1,0);
	for(int i=1;i<=n;i++)b[i]=dis[i];
	sort(b+1,b+n+1);tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)dis[i]=lower_bound(b+1,b+tot+1,dis[i])-b;
	Solve(1);
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}