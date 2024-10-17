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
const int N=30005;
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
void Build(int num,int l,int r){
	if(l==r){
		t[num].sum=val[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(lson);
	Build(rson);
	Pushup(num);
}
void Add(int x,int y,int z,int num,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		t[num].bj+=z;
		t[num].sum+=(r-l+1)*z;
		return;
	}
	Pushdown(num,l,r);
	int mid=(l+r)>>1;
	Add(x,y,z,lson);
	Add(x,y,z,rson);
	Pushup(num);
}
void Ask(int x,int num,int l,int r){
	if(x<l||x>r)return;
	if(l==r){
		printf("%d\n",t[num].sum);
		return;
	}
	int mid=(l+r)>>1;
	Pushdown(num,l,r);
	Ask(x,lson);
	Ask(x,rson);
}
void Update(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Add(id[top[x]],id[x],z,1,1,n);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	Add(id[x],id[y],z,1,1,n);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		edge_add(x,y);
		edge_add(y,x);
	}
	dfs1(1,1);
	dfs2(1,1);
	for(int i=1;i<=n;i++)val[id[i]]=a[i];
	Build(1,1,n);
	while(m--){
		char op[5];
		scanf("%s",op);
		if(op[0]=='Q'){
			Ask(id[read()],1,1,n);
			continue;
		}
		int x=read(),y=read(),z=read();
		if(op[0]=='I')Update(x,y,z);
		if(op[0]=='D')Update(x,y,-z);
	}
	return 0;
}