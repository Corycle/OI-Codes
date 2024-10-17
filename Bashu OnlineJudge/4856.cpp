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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],P[N][30],dep[N],son[N];
int Ans[N],prt[N],Top[N],sum[N];
struct node{int a,b;};
struct edge{int to,next;}d[N*2];
vector<node>v[N*4];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x,int depth){
	sum[x]=1;
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==prt[x])continue;
		P[y][0]=prt[y]=x;
		DFS1(y,depth+1);
		sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int top){
	Top[x]=top;
	if(son[x])DFS2(son[x],top);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==prt[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
int lca(int x,int y){
	while(Top[x]!=Top[y]){
		if(dep[Top[x]]<dep[Top[y]])swap(x,y);
		x=prt[Top[x]];
	}
	if(dep[x]<dep[y])return x;
	return y;
}
int Dist(int x,int y){
	int z=lca(x,y);
	if(z==-1)return 0;
	return dep[x]+dep[y]-dep[z]*2;
}
struct Union_Find_set{
	int top,fa[N],sum[N],dis[N];
	struct Stack{
		int x,y,a,b,dis,ans;
	}st[N];
	node pos[N];
	void Init(){
		for(int i=1;i<=n;i++){
			fa[i]=i;sum[i]=1;
			pos[i].a=pos[i].b=i;
			dis[i]=0;
		}
	}
	int Find(int x){
		return x==fa[x]?x:Find(fa[x]);
	}
	void Union(int x,int y){
		x=Find(x);y=Find(y);
		if(x==y)return;
		if(sum[x]<sum[y])swap(x,y);
		sum[x]+=sum[y];fa[y]=x;
		int sx=pos[x].a,sy=pos[x].b;
		int tx=pos[y].a,ty=pos[y].b;
		int tmp=0,dist=0,fx=0,fy=0;
		dist=dis[x];if(dist>tmp){tmp=dist;fx=sx,fy=sy;}
		dist=dis[y];if(dist>tmp){tmp=dist;fx=tx,fy=ty;}
		dist=Dist(sx,tx);if(dist>tmp){tmp=dist;fx=sx,fy=tx;}
		dist=Dist(sx,ty);if(dist>tmp){tmp=dist;fx=sx,fy=ty;}
		dist=Dist(sy,tx);if(dist>tmp){tmp=dist;fx=sy,fy=tx;}
		dist=Dist(sy,ty);if(dist>tmp){tmp=dist;fx=sy,fy=ty;}
		st[++top]=(Stack){x,y,sx,sy,dis[x],0};
		st[top].ans=max(st[top-1].ans,tmp);
		pos[x].a=fx;pos[x].b=fy;dis[x]=tmp;
	}
	void Undo(int tp){
		while(top>tp){
			int x=st[top].x;
			int y=st[top].y;
			sum[x]-=sum[y];
			pos[x].a=st[top].a;
			pos[x].b=st[top].b;
			dis[x]=st[top].dis;
			fa[y]=y;top--;
		}
	}
}F;
void Update(int x,int y,int a,int b,int p,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		v[p].push_back((node){a,b});
		return;
	}
	ll mid=(l+r)>>1;
	Update(x,y,a,b,lson);
	Update(x,y,a,b,rson);
}
void Solve(int p,int l,int r){
	int num=v[p].size(),tp=F.top;
	for(int i=0;i<num;i++){
		F.Union(v[p][i].a,v[p][i].b);
	}
	if(l==r)Ans[l]=F.st[F.top].ans;
	else{
		int mid=(l+r)>>1;
		Solve(lson);
		Solve(rson);
	}
	F.Undo(tp);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(P,-1,sizeof(P));
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		int l=read(),r=read();
		Update(l,r,x,y,1,1,n);
		Add(x,y);Add(y,x);
	}
	F.Init();
	DFS1(1,1);
	DFS2(1,1);
	Solve(1,1,n);
	for(int i=1;i<=m;i++){
		printf("%d\n",Ans[read()]);
	}
	return 0;
}