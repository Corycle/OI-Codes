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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,dfn,tot;
struct Line{int l,r;}L[N];
struct Ques{int x,y,w;}q[N];
struct edge{int to,next;}d[N];
int h[N],fa[N],id[N],dep[N],sum[N],son[N],top[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
bool cmp(Line A,Line B){return A.l==B.l?A.r<B.r:A.l<B.l;}
void DFS1(int x,int depth){
	sum[x]=1;dep[x]=depth;
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
struct Heap{
	priority_queue<int>q1,q2;
	void Ins(int x){q1.push(x);}
	void Del(int x){q2.push(x);}
	int Top(){
		while(q2.size()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return q1.size()?q1.top():-1;
	}
};
struct Segment_Tree{
	Heap t[N*4];
	void Insert(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].Ins(z);return;}
		int mid=(l+r)>>1;
		Insert(x,y,z,lson);
		Insert(x,y,z,rson);
	}
	void Delete(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].Del(z);return;}
		int mid=(l+r)>>1;
		Delete(x,y,z,lson);
		Delete(x,y,z,rson);
	}
	int Query(int x,int p,int l,int r){
		if(x<l||x>r)return -inf;
		if(l==r)return t[p].Top();
		int mid=(l+r)>>1,ans=-inf;
		ans=max(ans,Query(x,lson));
		ans=max(ans,Query(x,rson));
		return max(ans,t[p].Top());
	}
}tree;
void Solve(int l,int r,int data,int opt){
	if(l>r)return;
	if(opt==0)tree.Insert(l,r,data,1,1,n);
	if(opt==1)tree.Delete(l,r,data,1,1,n);
}
void Update(int x,int y,int z,int opt){
	tot=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		L[++tot]=(Line){id[top[x]],id[x]};
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	L[++tot]=(Line){id[x],id[y]};
	int lst=1;sort(L+1,L+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		Solve(lst,L[i].l-1,z,opt);
		lst=L[i].r+1;
	}
	Solve(lst,n,z,opt);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=m;i++){
		int opt=read();
		if(opt==0){
			q[i].x=read();q[i].y=read();q[i].w=read();
			Update(q[i].x,q[i].y,q[i].w,opt);
		}
		if(opt==1){int t=read();Update(q[t].x,q[t].y,q[t].w,opt);}
		if(opt==2)printf("%d\n",tree.Query(id[read()],1,1,n));
	}
	return 0;
}