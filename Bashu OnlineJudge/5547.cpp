#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
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
const ll inf=0x3f3f3f3f3f3f3f3f;
const ll N=200005;
inline ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot;
ll f[N][2],g[N][2];
ll val[N],h[N],fa[N],id[N],ed[N];
ll pos[N],sum[N],son[N],top[N],Sum[N];
struct edge{ll to,next;}d[N*2];
inline void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
/*==========可删堆==========*/
struct Heap{
	priority_queue<ll>q1,q2;
	inline void Push(ll x){q1.push(x);}
	inline void Erase(ll x){q2.push(x);}
	inline ll Top(){
		while(q2.size()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		if(!q1.size())return 0;
		return q1.top();
	}
}S[N];
/*==========矩阵乘法==========*/
struct Matrix{ll a[3][3];}F[N],P;
inline Matrix Matrix_Multi(Matrix A,Matrix B){
	Matrix C;int i,j;
	C.a[0][0]=-inf;C.a[0][1]=-inf;C.a[0][2]=0;
	C.a[1][0]=-inf;C.a[1][1]=0;C.a[1][2]=-inf;
	C.a[2][0]=-inf;C.a[2][1]=-inf;C.a[2][2]=0;//其实要修改的只有以下四项 
	i=0;j=0;for(register int k=0;k<3;k++)C.a[i][j]=max(C.a[i][j],A.a[i][k]+B.a[k][j]);
	i=0;j=2;for(register int k=0;k<3;k++)C.a[i][j]=max(C.a[i][j],A.a[i][k]+B.a[k][j]);
	i=1;j=0;for(register int k=0;k<3;k++)C.a[i][j]=max(C.a[i][j],A.a[i][k]+B.a[k][j]);
	i=1;j=2;for(register int k=0;k<3;k++)C.a[i][j]=max(C.a[i][j],A.a[i][k]+B.a[k][j]);
	return C;
}
/*==========树链剖分==========*/
/*
	Sum1=∑f[y][1]
	Sum2=∑f[l][1]
	Max1=max{f[y][0]}
	Max2=max{f[l][0]}
	f[x][1]=max{0,val[x]+Sum1}
	f[x][0]=max{f[x][1],Max1}
	g[x][1]=max{0,val[x]+Sum2}
	g[x][0]=max{g[x][1],Max2}
*/
inline void DFS1(ll x,ll depth){
	sum[x]=1;
	ll Max=0;
	for(register int i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
		Sum[x]+=f[y][1];//DP
		Max=max(Max,f[y][0]);
	}
	f[x][1]=max(0ll,val[x]+Sum[x]);
	f[x][0]=max(f[x][1],Max);
}
inline void DFS2(ll x,ll tp){
	Sum[x]=0;
	pos[id[x]=++tot]=x;
	top[x]=tp;ed[tp]=tot;//ed[tp]表示这条链的最后一个节点的位置 
	if(son[x])DFS2(son[x],tp);
	for(register int i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
		Sum[x]+=f[y][1];//DP
		S[x].Push(f[y][0]);
	}
	g[x][1]=val[x]+Sum[x];
	g[x][0]=S[x].Top();
}
/*==========线段树==========*/
struct Segment_Tree{
	Matrix t[N*4];
	inline void Pushup(ll p){
		t[p]=Matrix_Multi(t[p<<1],t[p<<1|1]);
	}
	inline void Build(ll p,ll l,ll r){
		if(l==r){t[p]=F[pos[l]];return;}
		ll mid=(l+r)>>1;
		Build(lson);
		Build(rson);
		Pushup(p);
	}
	inline void Change(ll x,ll p,ll l,ll r){
		if(l==r){t[p]=F[pos[l]];return;}
		ll mid=(l+r)>>1;
		if(x<=mid)Change(x,lson);
		else Change(x,rson);
		Pushup(p);
	}
	inline Matrix Ask(ll x,ll y,ll p,ll l,ll r){
		if(x<=l&&r<=y)return t[p];
		ll mid=(l+r)>>1;
		if(y<=mid)return Ask(x,y,lson);
		if(x>mid)return Ask(x,y,rson);
		return Matrix_Multi(Ask(x,y,lson),Ask(x,y,rson));
	}
}tree;
/*==========动态DP操作==========*/
inline Matrix Ask(ll x){
	return Matrix_Multi(tree.Ask(id[x],ed[top[x]],1,1,n),P);
}
inline void Change(ll x,ll data){
	F[x].a[0][0]+=data-val[x];
	F[x].a[1][0]=F[x].a[0][0];
	val[x]=data;
	while(x){
		Matrix fx=Ask(top[x]);
		tree.Change(id[x],1,1,n);
		Matrix fy=Ask(top[x]);
		x=fa[top[x]];if(!x)break;
		F[x].a[0][0]-=fx.a[0][0];
		F[x].a[1][0]-=fx.a[0][0];
		F[x].a[0][0]+=fy.a[0][0];
		F[x].a[1][0]+=fy.a[0][0];
		S[x].Erase(fx.a[1][0]);
		S[x].Push(fy.a[1][0]);
		F[x].a[1][2]=S[x].Top();
	}
}
int main(){
//	freopen("sum.in","r",stdin);
//	freopen("sum.out","w",stdout);
	P.a[0][0]=0;P.a[0][1]=-inf;P.a[0][2]=-inf;
	P.a[1][0]=0;P.a[1][1]=-inf;P.a[1][2]=-inf;
	P.a[2][0]=0;P.a[2][1]=-inf;P.a[2][2]=-inf;
	n=read();m=read();
	for(register int i=1;i<=n;i++)val[i]=read();
	for(register int i=2;i<=n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	for(register int x=1;x<=n;x++){
		F[x].a[0][0]=g[x][1];F[x].a[0][1]=-inf;F[x].a[0][2]=0;
		F[x].a[1][0]=g[x][1];F[x].a[1][1]=0;F[x].a[1][2]=g[x][0];
		F[x].a[2][0]=-inf;F[x].a[2][1]=-inf;F[x].a[2][2]=0;
	}
	tree.Build(1,1,n);
	while(m--){
		char op[1];
		scanf("%s",op);
		if(op[0]=='M'){
			ll x=read(),y=read();
			Change(x,y);
		}
		if(op[0]=='Q'){
			ll x=read();
			printf("%lld\n",Ask(x).a[1][0]);
		}
	}
	return 0;
}