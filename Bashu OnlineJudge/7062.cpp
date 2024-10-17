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
const int N=2e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,num,Sum,Ans;
int h[N],L[N],R[N],val[N],dep[N],p[N][M];
struct edge{int to,next;}d[N*2];
struct Node{int y,l,r,v;}P[N*20];
bool cmp(Node A,Node B){return A.y<B.y;}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int fa){
	L[x]=++tot;dep[x]=dep[fa]+1;p[x][0]=fa;
	for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa)DFS(y,x);}
	R[x]=tot;
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	return p[x][0];
}
int Pre(int x,int y){
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(dep[x]-(1<<k)>dep[y])x=p[x][k];
	return x;
}
void GetMatrix(int sx,int tx,int sy,int ty,int v){
	P[++num]=(Node){sy,sx,tx,v};
	P[++num]=(Node){ty+1,sx,tx,-v};
}
void Update(int x,int y,int v){
	int lca=LCA(x,y);
	if(x==y){val[x]+=v;return;}
	if(x!=lca&&y!=lca)GetMatrix(L[x],R[x],L[y],R[y],v);
	else if(x==lca){int p=Pre(y,x);GetMatrix(1,L[p]-1,L[y],R[y],v);GetMatrix(R[p]+1,tot,L[y],R[y],v);}
	else if(y==lca){int p=Pre(x,y);GetMatrix(L[x],R[x],1,L[p]-1,v);GetMatrix(L[x],R[x],R[p]+1,tot,v);}
}
struct Tree{int Max,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int v){t[p].tag+=v;t[p].Max+=v;}
	void Pushup(int p){t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);Pushup(p);
	}
}tree;
int main(){
//	freopen("score.in","r",stdin);
//	freopen("score.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	DFS(1,0);
	for(int i=1;i<=m;i++){int x=read(),y=read(),v=read();Update(x,y,v);}
	for(int x=1;x<=n;x++){
		if(!val[x])continue;
		Sum+=val[x];
		if(p[x][0]){
			GetMatrix(1,L[x]-1,1,L[x]-1,-val[x]);
			GetMatrix(1,L[x]-1,R[x]+1,tot,-val[x]);
			GetMatrix(R[x]+1,tot,1,L[x]-1,-val[x]);
			GetMatrix(R[x]+1,tot,R[x]+1,tot,-val[x]);
		}
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;if(y==p[x][0])continue;
			GetMatrix(L[y],R[y],L[y],R[y],-val[x]);
		}
	}
	Ans=-inf;
	sort(P+1,P+num+1,cmp);
	for(int y=1,i=1;y<=tot;y++){
		while(i<=num&&P[i].y==y){tree.Update(P[i].l,P[i].r,P[i].v,1,1,tot);i++;}
		Ans=max(Ans,tree.t[1].Max);
	}
	printf("%d\n",Ans+Sum);
	return 0;
}