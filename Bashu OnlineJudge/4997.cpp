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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int id[N],ed[N],fa[N],pos[N],son[N];
int h[N],dep[N],sum[N],top[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Tree{
	int a[2][2];
	void Init(){memset(a,-0x3f,sizeof(a));}
	friend Tree operator*(Tree A,Tree B){
		Tree C;C.Init();
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				for(int k=0;k<2;k++){
					C.a[i][j]=max(C.a[i][j],A.a[i][k]+B.a[k][j]);
				}
			}
		}
		return C;
	}
}F[N];
struct Segment_Tree{
	Tree t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p]=F[pos[l]];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=t[p<<1]*t[p<<1|1];
	}
	void Change(int x,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p]=F[pos[l]];return;}
		int mid=(l+r)>>1;
		Change(x,lson);Change(x,rson);
		t[p]=t[p<<1]*t[p<<1|1];
	}
	Tree Ask(int x,int y,int p,int l,int r){
		if(x<=l&&r<=y)return t[p];
		int mid=(l+r)>>1;
		if(y<=mid)return Ask(x,y,lson);
		if(x>mid) return Ask(x,y,rson);
		return Ask(x,y,lson)*Ask(x,y,rson);
	}
}tree;
Tree Query(int x){
	return tree.Ask(id[x],ed[x],1,1,n);
}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;
	pos[id[x]=++tot]=x;ed[tp]=tot;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
void Update(int x){
	F[x].a[1][0]=1;
	while(x){
		Tree t1=Query(top[x]);
		tree.Change(id[x],1,1,n);
		Tree t2=Query(top[x]);
		x=fa[top[x]];if(!x)break;
		int F01=max(t1.a[0][0],t1.a[0][1]);
		int F11=max(t1.a[1][0],t1.a[1][1]);
		int F02=max(t2.a[0][0],t2.a[0][1]);
		int F12=max(t2.a[1][0],t2.a[1][1]);
		F[x].a[0][0]+=max(F02,F12)-max(F01,F11);
		F[x].a[0][1]+=max(F02,F12)-max(F01,F11);
		F[x].a[1][0]+=F02-F01;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	F[1].a[1][0]=1;
	for(int i=1;i<=n;i++)F[i].a[1][1]=-inf;
	for(int i=2;i<=n;i++)Add(fa[i]=read()+1,i);
	DFS1(1,1);DFS2(1,1);
	/*
		f[x][0]=\sum{max(f[y][0],f[y][1])};
		f[x][1]=1+\sum{f[y][0]};
		
		g[x][0]=\sum{max(f[lson][0],f[lson][1])};
		g[x][1]=1+\sum{f[lson][0]};
		f[x][0]=g[x][0]+max{f[hson][0],f[hson][1]};
		
		f[x][0]=max{g[x][0]+f[hson][0],g[x][0]+f[hson][1]};
		f[x][1]=g[x][1]+f[hson][0];
		
		| f[x][0] |   | g[x][0] g[x][0] |   | f[h][0] |
		|         | = |                 | * |         |
		| f[x][1] |   | g[x][1]  -inf   |   | f[h][1] |
	*/
	tree.Build(1,1,n);
	for(int i=2;i<=n;i++){
		Update(i);
		Tree Ans=Query(1);
		printf("%d\n",max(max(Ans.a[0][0],Ans.a[0][1]),max(Ans.a[1][0],Ans.a[1][1])));
	}
	return 0;
}