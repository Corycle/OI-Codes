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
#include<set>
#define ll long long
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
#define set_it set<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
set<int>S[N];
int n,m,tot,cnt,Ans,type;
int h[N],fa[N],dep[N],sum[N],son[N];
int a[N],id[N],pos[N],top[N],root[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
/*========Tree Chain Partition========*/
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
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
/*========Segment Tree========*/
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;Tree t[N*400];
	void Add(int x,int y,int &p,int l,int r){
		if(!p)p=++tot;t[p].sum+=y;
		if(l==r)return;int mid=(l+r)>>1;
		if(x<=mid)Add(x,y,lson);
		if(x>mid)Add(x,y,rson);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(!p||y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
		return Ask(x,y,lson)+Ask(x,y,rson);
	}
}tree;
/*========BIT========*/
int lowbit(int x){return x&(-x);}
void Add(int x,int c,int addv){
	for(;c<=n;c+=lowbit(c)){
		tree.Add(id[x],addv,root[c],1,n);
	}
}
int Query(int x,int c){
	int ans=0;
	for(;c>=1;c-=lowbit(c)){
		ans+=tree.Ask(id[x],id[x]+sum[x]-1,root[c],1,n);
	}
	return ans;
}
/*========Operation========*/
void Insert(int x,int c){
	Add(x,c,1);
	S[c].insert(id[x]);
	set_it p=S[c].find(id[x]),lst=p,nxt=p;
	if(p!=S[c].begin()){lst=--p;p++;}
	if(p!=--S[c].end()){nxt=++p;p--;}
	int l=pos[*lst],r=pos[*nxt];
	if(l!=x)Add(LCA(l,x),c,-1);
	if(r!=x)Add(LCA(r,x),c,-1);
	if(l!=x&&r!=x)Add(LCA(l,r),c,1);
}
void Delete(int x,int c){
	Add(x,c,-1);
	set_it p=S[c].find(id[x]),lst=p,nxt=p;
	if(p!=S[c].begin()){lst=--p;p++;}
	if(p!=--S[c].end()){nxt=++p;p--;}
	int l=pos[*lst],r=pos[*nxt];
	if(l!=x)Add(LCA(l,x),c,1);
	if(r!=x)Add(LCA(r,x),c,1);
	if(l!=x&&r!=x)Add(LCA(l,r),c,-1);
	S[c].erase(p);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();type=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=n;i++)Insert(i,a[i]);
	while(m--){
		int op=read();
		if(op==1){
			int x=read()^(type*Ans);
			int l=read()^(type*Ans);
			int r=read()^(type*Ans);
			Ans=Query(x,r)-Query(x,l-1);
			printf("%d\n",Ans);
		}
		if(op==2){
			int x=read()^(type*Ans);
			int c=read()^(type*Ans);
			Delete(x,a[x]);
			Insert(x,a[x]=c);
		}
	}
	return 0;
}