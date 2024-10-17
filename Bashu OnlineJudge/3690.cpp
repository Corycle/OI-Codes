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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
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
int h[N],fa[N],val[N],dep[N],a[N];
int son[N],sum[N],top[N],id[N];
struct Tree{
	int sum,bj;
}t[N*4];
struct edge{
	int to,next;
}d[N*2];
void edge_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void dfs1(int x,int depth){
	sum[x]=1;
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		dfs1(y,depth+1);
		sum[x]+=sum[y];
		if(sum[y]>sum[son[x]])son[x]=y;
	}
}
void dfs2(int x,int tp){
	top[x]=tp;
	id[x]=++tot;
	if(son[x])dfs2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		dfs2(y,y);
	}
}
void update(int x,int num,int l,int r){
	t[num].bj+=x;
	t[num].sum+=(r-l+1)*x;
}
void Pushup(int num){
	t[num].sum=t[num<<1].sum+t[num<<1|1].sum;
}
void Pushdown(int num,int l,int r){
	if(!t[num].bj)return;
	int mid=(l+r)>>1;
	update(t[num].bj,lson);
	update(t[num].bj,rson);
	t[num].bj=0;
}
//void Build(int num,int l,int r){
//	if(l==r){
//		t[num].sum=val[l];
//		return;
//	}
//	int mid=(l+r)>>1;
//	Build(lson);
//	Build(rson);
//	Pushup(num);
//}
void Add(int x,int y,int num,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		t[num].bj++;
		t[num].sum+=(r-l+1);
		return;
	}
	Pushdown(num,l,r);
	int mid=(l+r)>>1;
	Add(x,y,lson);
	Add(x,y,rson);
	Pushup(num);
}
int Ask(int x,int y,int num,int l,int r){
	if(y<l||r<x)return 0;
	if(x<=l&&r<=y){
		return t[num].sum;
	}
	Pushdown(num,l,r);
	int mid=(l+r)>>1;
	return Ask(x,y,lson)+Ask(x,y,rson);
}
void Query(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=Ask(id[top[x]],id[x],1,1,n);
		x=fa[top[x]];
	}
	if(x==y){
		printf("%d\n",ans);
		return;
	}
	if(dep[x]>dep[y])swap(x,y);
	ans+=Ask(id[son[x]],id[y],1,1,n);
	printf("%d\n",ans);
}
void Update(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Add(id[top[x]],id[x],1,1,n);
		x=fa[top[x]];
	}
	if(x==y)return;
	if(dep[x]>dep[y])swap(x,y);
	Add(id[son[x]],id[y],1,1,n);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		edge_add(x,y);
		edge_add(y,x);
	}
	dfs1(1,1);
	dfs2(1,1);
//	Build(1,1,n);
	while(m--){
		char op[5];
		scanf("%s",op);
		int x=read(),y=read();
		if(op[0]=='Q')Query(x,y);
		if(op[0]=='P')Update(x,y);
	}
	return 0;
}