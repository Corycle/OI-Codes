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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int M=60;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<int,int>root;
int n,m,dfn,cnt,tot,Ans;
int a[N],h[N],id[N],fa[N],dep[N],son[N],sum[N],top[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
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
	top[x]=tp;id[x]=++dfn;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
struct Tree{int l,r,sum;};
struct Segment_Tree{
	Tree t[N*M];
	void Update(int x,int y,int &p,int l,int r){
		if(!p)p=++tot;
		if(l==r){t[p].sum+=y;return;}
		int mid=(l+r)>>1;
		if(x<=mid)Update(x,y,lson);
		if(x>mid) Update(x,y,rson);
		t[p].sum=t[t[p].l].sum+t[t[p].r].sum;
	}
	int Ask(int x,int y,int p,int l,int r){
		if(!p||y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
		return Ask(x,y,lson)+Ask(x,y,rson);
	}
}tree;
void Query(int x,int y,int t){
	Ans=0;
	if(!root[t])return;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		Ans+=tree.Ask(id[top[x]],id[x],root[t],1,n);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	Ans+=tree.Ask(id[x],id[y],root[t],1,n);
}
char s[M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=n;i++){
		tree.Update(id[i],1,root[a[i]],1,n);
	}
	while(m--){
		scanf("%s",s);
		if(s[0]=='Q'){
			int x=read()^Ans,y=read()^Ans;
			int t=read()^Ans;Query(x,y,t);
			printf("%d\n",Ans);
		}
		if(s[0]=='C'){
			int x=read()^Ans,t=read()^Ans;
			tree.Update(id[x],-1,root[a[x]],1,n);
			tree.Update(id[x],1,root[t],1,n);
			a[x]=t;
		}
	}
	return 0;
}