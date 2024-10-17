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
#define Lson t[x].l,t[y].l,l,mid
#define Rson t[x].r,t[y].r,mid+1,r
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
int n,m,cnt,num,tot,top,Ans,type,Case;
int a[N],b[N],c[N],h[N],st[N],dfn[N],dep[N],Root[N],p[N][M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
bool cmp(int x,int y){return dfn[x]<dfn[y];}
struct Tree{int l,r,num;};
struct Segment_Tree{
	int tot;
	Tree t[N*M];
	void Insert(int x,int &p,int l,int r){
		t[++tot]=t[p];p=tot;
		if(l==r){t[p].num=1;return;}
		int mid=(l+r)>>1;x<=mid?Insert(x,lson):Insert(x,rson);
		t[p].num=t[t[p].l].num+t[t[p].r].num;
	}
	int Query1(int pos,int x,int y,int l,int r){
		if(!(t[y].num-t[x].num))return -inf;
		if(l==r)return b[l];int mid=(l+r)>>1;
		if(pos<=mid)return Query1(pos,Lson);
		int tmp=Query1(pos,Rson);
		if(tmp!=-inf)return tmp;
		return Query1(pos,Lson);
	}
	int Query2(int pos,int x,int y,int l,int r){
		if(!(t[y].num-t[x].num))return inf;
		if(l==r)return b[l];int mid=(l+r)>>1;
		if(pos>mid)return Query2(pos,Rson);
		int tmp=Query2(pos,Lson);
		if(tmp!=inf)return tmp;
		return Query2(pos,Rson);
	}
}tree;
void DFS(int x,int fa,int depth){
	Root[x]=Root[fa];tree.Insert(a[x],Root[x],1,num);dfn[x]=++tot;
	dep[x]=depth;p[x][0]=fa;for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y==fa)continue;DFS(y,x,depth+1);}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	return p[x][0];
}
void Query(int val,int pos,int x,int y){
	if(pos-1>=1)Ans=min(Ans,val-tree.Query1(pos-1,Root[p[x][0]],Root[y],1,num));
	if(pos<=num)Ans=min(Ans,tree.Query2(pos,Root[p[x][0]],Root[y],1,num)-val);
}
void Solve(int val){
	st[top=1]=c[1];Ans=inf;
	int pos=lower_bound(b+1,b+num+1,val)-b;
	for(int i=2;i<=m;i++){
		int lca=LCA(st[top],c[i]);
		while(top>1&&dep[st[top-1]]>=dep[lca]){Query(val,pos,st[top-1],st[top]);top--;}
		if(st[top]!=lca){Query(val,pos,lca,st[top]);st[top]=lca;}
		st[++top]=c[i];
	}
	while(top>1){Query(val,pos,st[top-1],st[top]);top--;}
	Ans=min(Ans,abs(val-b[a[st[1]]]));
}
int main(){
//	freopen("network.in","r",stdin);
//	freopen("network.out","w",stdout);
	n=read();Case=read();type=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);num=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+num+1,a[i])-b;
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	DFS(1,0,1);
	while(Case--){
		int x=read();m=read();
		for(int i=1;i<=m;i++)c[i]=(read()-1+Ans*type)%n+1;
		sort(c+1,c+m+1,cmp);Solve(x);
		printf("%d\n",Ans);
	}
	return 0;
}