#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,rt,cnt,tot;
int h[N],son[N],val[N],root[N];
int fa[N],dep[N],top[N],sum[N];
struct edge{int to,next;}d[N*2];
struct ques{int op,x,y,z;}q[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Segment_Tree{
	int tot;
	struct Tree{int l,r,sum;}t[N*20];
	void Insert(int &x,int y,int val,int l,int r){
		x=++tot;t[x]=t[y];t[x].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		if(val<=mid)Insert(t[x].l,t[y].l,val,l,mid);
		else Insert(t[x].r,t[y].r,val,mid+1,r);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(l==r)return t[y].sum-t[x].sum;
		int mid=(l+r)>>1,Sum=t[t[y].l].sum-t[t[x].l].sum;
		if(p<=mid)return Ask(t[x].l,t[y].l,p,l,mid);
		else return Sum+Ask(t[x].r,t[y].r,p,mid+1,r);
	}
}tree;
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;
	tree.Insert(root[x],root[fa[x]],val[x],1,n);
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==son[x])continue;
		DFS2(y,y);
	}
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])return x;
	return y;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		fa[i]=read();
		if(!fa[i])rt=i;
		else Add(fa[i],i);
	}
	m=read();
	for(int i=1;i<=n;i++)val[i]=m;
	for(int i=1;i<=m;i++){
		q[i].op=read();q[i].x=read();
		if(q[i].op==1){
			q[i].y=read();
			q[i].z=read();
		}
		if(q[i].op==2)val[q[i].x]=i;
	}
	DFS1(rt,1);
	DFS2(rt,rt);
	for(int i=1;i<=m;i++){
		if(q[i].op==1){
			int x=q[i].x,y=q[i].y;
			int c=q[i].z,z=lca(x,y);
			printf("%d ",dep[x]+dep[y]-dep[z]*2+1);
			if(i-c-1<=0){printf("0\n");continue;}
			int ans=(val[z]<i-c);
			ans+=tree.Ask(root[z],root[x],i-c-1,1,n);
			ans+=tree.Ask(root[z],root[y],i-c-1,1,n);
			printf("%d\n",ans);
		}
	}
	return 0;
}