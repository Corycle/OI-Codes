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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,m1,m2,cnt,tot,top,root;
int h[N],a[N],b[N],q[N],v[N],st[N],fa[N],dep[N],dfn[N],p[N][M];
struct edge{int to,next;}d[N*2];
bool cmp(int x,int y){return dfn[x]<dfn[y];}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Node{
	int x,v,dis;
	friend Node operator+(Node A,int dis){A.dis+=dis;return A;}
	friend bool operator<(Node A,Node B){
		int x=(int)(ceil(1.0*A.dis/A.v));
		int y=(int)(ceil(1.0*B.dis/B.v));
		return x!=y?x<y:b[A.x]<b[B.x];
	}
}F[N];
void DFS(int x,int depth){
	dep[x]=depth;dfn[x]=++tot;p[x][0]=fa[x];
	int k=(int)(log(depth)/log(2));
	for(int i=1;i<=k;i++){
		if(p[x][i-1])p[x][i]=p[p[x][i-1]][i-1];
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
void Build(){
	sort(a+1,a+m+1);
	m=unique(a+1,a+m+1)-a-1;
	sort(a+1,a+m+1,cmp);
	st[top=1]=a[1];
	for(int i=2;i<=m;i++){
		int lca=LCA(a[i],st[top]);
		while(top>=2&&dep[st[top-1]]>=dep[lca]){G[st[top-1]].push_back(st[top]);top--;}
		if(lca!=st[top]){G[lca].push_back(st[top]);st[top]=lca;}
		st[++top]=a[i];
	}
	while(top>=2){G[st[top-1]].push_back(st[top]);top--;}
	root=st[top];
}
void DFS1(int x){
	if(b[x]>0)F[x]=(Node){x,v[x],0};
	int num=G[x].size();
	for(int i=0;i<num;i++){
		int y=G[x][i];
		int dis=dep[y]-dep[x];
		DFS1(y);
		F[x]=min(F[x],F[y]+dis);
	}
}
void DFS2(int x){
	int num=G[x].size();
	for(int i=0;i<num;i++){
		int y=G[x][i];
		int dis=dep[y]-dep[x];
		F[y]=min(F[y],F[x]+dis);
		DFS2(y);
	}
}
void Clear(int x){
	int num=G[x].size();
	for(int i=0;i<num;i++)Clear(G[x][i]);
	G[x].clear();b[x]=v[x]=0;
	F[x]=(Node){0,1,inf};
}
int main(){
//	freopen("virus.in","r",stdin);
//	freopen("virus.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=n;i++)F[i]=(Node){0,1,inf};
	DFS(1,1);
	int Q=read();
	while(Q--){
		m1=read();m2=read();m=m1+m2;
		for(int i=1;i<=m1;i++){int x=read();a[i]=x;b[x]=i;v[x]=read();}
		for(int i=1;i<=m2;i++){int x=read();a[i+m1]=x;q[i]=x;}
		Build();DFS1(root);DFS2(root);
		for(int i=1;i<=m2;i++){
			printf("%d ",b[F[q[i]].x]);
		}
		printf("\n");
		Clear(root);
	}
	return 0;
}