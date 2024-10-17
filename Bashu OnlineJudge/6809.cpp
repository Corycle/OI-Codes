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
#define pii pair<ll,int>
#define fst first
#define scd second
#define mp make_pair
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const ll inf=1e18;
const int M=100005;
const int N=M*10;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll dis[N];
int n,m,S,cnt,tot;
int h[N],vis[N],pos1[N],pos2[N];
struct edge{int to,next,dist;}d[M*30];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
struct Segment_Tree{
	int id1[M*4],id2[M*4];
	void Build(int p,int l,int r){
		id1[p]=++tot;id2[p]=++tot;Add(id2[p],id1[p],0);
		if(l==r){pos1[l]=id1[p];pos2[l]=id2[p];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
		if(id1[p<<1]){
			Add(id1[p<<1],id1[p],0);
			Add(id2[p],id2[p<<1],0);
		}
		if(id1[p<<1|1]){
			Add(id1[p<<1|1],id1[p],0);
			Add(id2[p],id2[p<<1|1],0);
		}
	}
	void Update(int x,int y,int op,int P,int w,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			if(op==2)Add(pos1[P],id2[p],w);
			if(op==3)Add(id1[p],pos2[P],w);
			return;
		}
		int mid=(l+r)>>1;
		Update(x,y,op,P,w,lson);
		Update(x,y,op,P,w,rson);
	}
}tree;
void Dijkstra(){
	for(int i=1;i<=tot;i++)dis[i]=inf;
	priority_queue<pii,vector<pii>,greater<pii> >q;
	q.push(mp(0,pos1[S]));dis[pos1[S]]=dis[pos2[S]]=0;
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].dist){
				dis[y]=dis[x]+d[i].dist;
				q.push(mp(dis[y],y));
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();S=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read();
		if(op==1){
			int x=read(),y=read(),z=read();
			Add(pos1[x],pos2[y],z);
		}
		else{
			int x=read(),l=read(),r=read(),w=read();
			tree.Update(l,r,op,x,w,1,1,n);
		}
	}
	Dijkstra();
	for(int i=1;i<=n;i++)printf("%lld ",(dis[pos2[i]]==inf?-1:dis[pos2[i]]));
	return 0;
}