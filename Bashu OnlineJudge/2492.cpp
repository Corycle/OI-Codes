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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<pii>F[N];
ll b[N],dis[N],Ans[N];
int n,m,tot,fa[N],Root[N];
struct edge{int to,next;}d[N];
struct Tree{int l,r,num;ll val;};
struct Segment_Tree{
	int tot;
	Tree t[N*20];
	void Insert(int x,int &p,int l,int r){
		if(!p)p=++tot;t[p].num++;t[p].val+=b[x];
		if(l==r)return;int mid=(l+r)>>1;
		x<=mid?Insert(x,lson):Insert(x,rson);
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		t[x].num+=t[y].num;
		t[x].val+=t[y].val;
		t[x].l=Merge(t[x].l,t[y].l);
		t[x].r=Merge(t[x].r,t[y].r);
		return x;
	}
	ll Query(int x,int y,ll dlt,int p,int l,int r){
		if(y<l||x>r||!p)return 0;
		if(x<=l&&r<=y)return t[p].val-t[p].num*dlt;
		int mid=(l+r)>>1;
		return Query(x,y,dlt,lson)+Query(x,y,dlt,rson);
	}
}tree;
int main(){
//	freopen("distance.in","r",stdin);
//	freopen("distance.out","w",stdout);
	n=read();
	for(int i=2;i<=n;i++){fa[i]=read();int w=read();dis[i]=dis[fa[i]]+w;}
	m=read();
	for(int i=1;i<=m;i++){int x=read();F[x].push_back(mp(read(),i));}
	
	for(int i=1;i<=n;i++)b[i]=dis[i];
	sort(b+1,b+n+1);tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)dis[i]=lower_bound(b+1,b+tot+1,dis[i])-b;
	
	for(int i=n;i>=1;i--){
		tree.Insert(dis[i],Root[i],1,tot);
		int num=F[i].size();
		for(int j=0;j<num;j++){
			int pos=lower_bound(b+1,b+tot+1,b[dis[i]]+F[i][j].fst)-b;
			Ans[F[i][j].scd]=tree.Query(pos,tot,b[dis[i]],Root[i],1,tot);
		}
		if(fa[i])Root[fa[i]]=tree.Merge(Root[i],Root[fa[i]]);
	}
	
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}