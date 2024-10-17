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
int a[N],h[N],fa[N],id[N];
int pos[N],sum[N],dep[N],son[N],top[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
struct Segment_Tree{
	struct Tree{int sum;}t[N*4];
	void Pushup(int p){
		t[p].sum=t[p<<1].sum^t[p<<1|1].sum;
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].sum=a[pos[l]];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		Pushup(p);
	}
	void Change(int x,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p].sum=a[pos[l]];return;}
		int mid=(l+r)>>1;
		Change(x,lson);Change(x,rson);
		Pushup(p);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
		return Ask(x,y,lson)^(Ask(x,y,rson));
	}
}tree;
void Update(int x,int y){
	a[x]=y;
	tree.Change(id[x],1,1,n);
}
int Ask(int x,int y){
	int sum=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		sum^=tree.Ask(id[top[x]],id[x],1,1,n);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	sum^=tree.Ask(id[x],id[y],1,1,n);
	return sum;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	while(m--){
		int op=read(),x=read(),y=read();
		if(op==1)Update(x,y);
		if(op==2)printf("%d\n",Ask(x,y));
	}
	return 0;
}