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
const int N=100005;
const int M=40;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,tot,dfn;
struct Edge{int x,y;}E[N];
struct edge{int to,next;}d[N*2];
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
int h[N],L[N],R[N],fa[N],dep[N],root[N],p[N][M];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Tree{int l,r,sum;};
struct Segment_Tree{
	Tree t[N*M];
	void Insert(int x,int y,int &p,int l,int r){
		t[++tot]=t[p];p=tot;
		if(l==r){t[p].sum+=y;return;}
		int mid=(l+r)>>1;
		if(x<=mid)Insert(x,y,t[p].l,l,mid);
		if(x>mid)Insert(x,y,t[p].r,mid+1,r);
		t[p].sum=t[t[p].l].sum+t[t[p].r].sum;
	}
	int Query(int x,int y,int lca,int pre,int ql,int qr,int l,int r){
		if(qr<l||ql>r)return 0;
		if(ql<=l&&r<=qr)return t[x].sum+t[y].sum-t[lca].sum-t[pre].sum;
		int mid=(l+r)>>1,ans=0;
		ans+=Query(t[x].l,t[y].l,t[lca].l,t[pre].l,ql,qr,l,mid);
		ans+=Query(t[x].r,t[y].r,t[lca].r,t[pre].r,ql,qr,mid+1,r);
		return ans;
	}
}tree;
void DFS1(int x,int depth){
	L[x]=++dfn;
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y,depth+1);
	}
	R[x]=++dfn;
}
void DFS2(int x){
	root[x]=root[fa[x]];
	for(auto y:G[x]){
		tree.Insert(L[y],1,root[x],1,n*2);
		tree.Insert(R[y],-1,root[x],1,n*2);
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y!=fa[x])DFS2(y);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int i=1;i<=n;i++)p[i][0]=fa[i];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
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
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=m;i++){
		E[i].x=read();E[i].y=read();
		G[E[i].x].push_back(E[i].y);
	}
	ll A=0,B=1ll*m*(m-1)/2;
	DFS1(1,1);DFS2(1);ST();
	for(int i=1;i<=m;i++){
		int x=E[i].x,y=E[i].y;int lca=LCA(x,y);
		A+=tree.Query(root[x],root[y],root[lca],root[fa[lca]],L[lca],L[x],1,n*2);
		A+=tree.Query(root[x],root[y],root[lca],root[fa[lca]],L[lca],L[y],1,n*2);
		A-=tree.Query(root[x],root[y],root[lca],root[fa[lca]],L[lca],L[lca],1,n*2);
	}
	A-=m;
	ll Gcd=gcd(A,B);A/=Gcd;B/=Gcd;
	printf("%lld/%lld",A,B);
	return 0;
}