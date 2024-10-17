#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
struct Matrix{int a[3][3];}F[N];
Matrix Multi(Matrix A,Matrix B){
	Matrix C;
	C.a[1][1]=C.a[1][2]=0;
	C.a[2][1]=C.a[2][2]=0;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=2;j++){
			for(int k=1;k<=2;k++){
				C.a[i][j]=max(C.a[i][j],A.a[i][k]+B.a[k][j]);
			}
		}
	}
	return C;
}
int n,m,cnt,tot;
int h[N],fa[N],id[N],ed[N],val[N],pos[N];
int sum[N],son[N],top[N],dep[N],f[N][2],g[N][2];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Segment_Tree{
	/*
		叶子节点的f和g一样，
		乘上父亲节点的g就得到父亲节点的g 
	*/
	Matrix t[N*4];
	void Pushup(int p){
		t[p]=Multi(t[p<<1],t[p<<1|1]);
	}
	void Build(int p,int l,int r){
		if(l==r){
			t[p]=F[pos[l]];
			return;
		}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		Pushup(p);
	}
	void Change(int x,int p,int l,int r){
		if(x<l||r<x)return;
		if(l==r){
			t[p]=F[pos[l]];
			return;
		}
		int mid=(l+r)>>1;
		Change(x,lson);Change(x,rson);
		Pushup(p);
	}
	Matrix Ask(int x,int y,int p,int l,int r){
		if(x<=l&&r<=y)return t[p];
		int mid=(l+r)>>1;
		if(y<=mid)return Ask(x,y,lson);
		if(x>mid)return Ask(x,y,rson);
		return Multi(Ask(x,y,lson),Ask(x,y,rson));
	}
}tree;
void DFS1(int x,int depth){
	f[x][1]=val[x];
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
		f[x][0]+=max(0,max(f[y][0],f[y][1]));
		f[x][1]+=max(0,f[y][0]);
	}
}
void DFS2(int x,int tp){
	g[x][1]=val[x];top[x]=tp;
	pos[id[x]=++tot]=x;ed[tp]=tot;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
		g[x][0]+=max(0,max(f[y][0],f[y][1]));
		g[x][1]+=max(0,f[y][0]);
	}
}
Matrix Ask(int x){
	return tree.Ask(id[x],ed[x],1,1,n);
}
void Change(int x,int y){
	F[x].a[2][1]+=y-val[x];val[x]=y;
	while(x){
		Matrix fx=Ask(top[x]);
		tree.Change(id[x],1,1,n);
		Matrix fy=Ask(top[x]);
		x=fa[top[x]];
		F[x].a[1][1]+=max(fy.a[1][1],fy.a[2][1])-max(fx.a[1][1],fx.a[2][1]);
		F[x].a[1][2]+=max(fy.a[1][1],fy.a[2][1])-max(fx.a[1][1],fx.a[2][1]);
		F[x].a[2][1]+=fy.a[1][1]-fx.a[1][1];
		F[x].a[2][2]=0;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)val[i]=read();
	for(int i=2;i<=n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=n;i++){
		F[i].a[1][1]=g[i][0];
		F[i].a[1][2]=g[i][0];
		F[i].a[2][1]=g[i][1];
		F[i].a[2][2]=0;
	}
	tree.Build(1,1,n);
	while(m--){
		int x=read(),y=read();
		Change(x,y);Matrix ans=Ask(1);
		printf("%d\n",max(ans.a[1][1],ans.a[2][1]));
	}
	return 0;
}