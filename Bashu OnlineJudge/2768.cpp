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
const int N=80005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int h[N],fa[N],val[N],dep[N];
int son[N],sum[N],top[N],id[N];
struct Tree{
	int maxx;
}t[N*4];
struct edge{
	int to,next;
}d[N*2];
struct Edge{
	int s,t,data;
}e[N];
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
void Pushup(int num){
	t[num].maxx=max(t[num<<1].maxx,t[num<<1|1].maxx);
}
void Build(int num,int l,int r){
	if(l==r){
		t[num].maxx=val[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(lson);
	Build(rson);
	Pushup(num);
}
void Change(int x,int y,int num,int l,int r){
	if(x<l||x>r)return;
	if(l==r){
		t[num].maxx=y;
		return;
	}
	int mid=(l+r)>>1;
	Change(x,y,lson);
	Change(x,y,rson);
	Pushup(num);
}
int Ask(int x,int y,int num,int l,int r){
	if(y<l||x>r)return 0;
	if(x<=l&&r<=y){
		return t[num].maxx;
	}
	int mid=(l+r)>>1;
	return max(Ask(x,y,lson),Ask(x,y,rson));
}
int Query(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=max(ans,Ask(id[top[x]],id[x],1,1,n));
		x=fa[top[x]];
	}
	if(x==y)return ans;
	if(dep[x]>dep[y])swap(x,y);
	return max(ans,Ask(id[son[x]],id[y],1,1,n));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n-1;i++){
		e[i].s=read();e[i].t=read();e[i].data=read();
		edge_add(e[i].s,e[i].t);
		edge_add(e[i].t,e[i].s);
	}
	dfs1(1,1);
	dfs2(1,1);
	for(int i=1;i<=n-1;i++){
		if(dep[e[i].s]<dep[e[i].t])swap(e[i].s,e[i].t);
		val[id[e[i].s]]=e[i].data;
//		Change(id[e[i].s],e[i].data,1,1,n);
	}
	Build(1,1,n);
	while(m--){
		int op=read(),x=read(),y=read();
		if(op==0){
			Change(id[e[x].s],y,1,1,n);
		}
		if(op==1){
			if(x==y)printf("-1\n");
			else printf("%d\n",Query(x,y));
		}
	}
	return 0;
}