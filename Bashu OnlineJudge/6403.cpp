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
const int N=500005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,K,cnt,tot;
int h[N],fa[N],id[N],sum[N],dep[N],son[N],top[N];
struct Node{int x,y,v;}P[N];
struct edge{int to,next;}d[N*2];
bool cmp(Node A,Node B){return A.v<B.v;}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
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
	top[x]=tp;id[x]=++tot;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
struct Segment_Tree{
	int t[N*4];
	void Build(int p,int l,int r){
		t[p]=inf;
		if(l==r)return;
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			t[p]=min(t[p],z);
			return;
		}
		int mid=(l+r)>>1;
		Update(x,y,z,lson);
		Update(x,y,z,rson);
	}
	int Ask(int x,int p,int l,int r){
		if(x<l||x>r)return inf;
		if(l==r)return t[p];
		int mid=(l+r)>>1;
		return min(min(Ask(x,lson),Ask(x,rson)),t[p]);
	}
}tree;
struct Line{int l,r;}L[N];
bool Cmp(Line A,Line B){return A.l!=B.l?A.l<B.l:A.r<B.r;}
void Update(int x,int y,int z){
	int num=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		L[++num]=(Line){id[top[x]],id[x]};
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	L[++num]=(Line){id[x],id[y]};
	L[0]=(Line){0,0};
	L[num+1]=(Line){n+1,n+1};
	sort(L+1,L+num+1,Cmp);
	for(int i=1;i<=num+1;i++){
		if(L[i-1].r+1<=L[i].l-1){
			tree.Update(L[i-1].r+1,L[i].l-1,z,1,1,n);
		}
	}
}
struct Ques{int op,x,ans;}Q[N];
int main(){
//	freopen("path.in","r",stdin);
//	freopen("path.out","w",stdout);
	n=read();K=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=K;i++){
		P[i].x=read();
		P[i].y=read();
		P[i].v=read();
	}
	int pos=0;
	sort(P+1,P+K+1,cmp);
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	for(int i=1;i<=m;i++){
		Q[i].op=read();
		if(!Q[i].op)pos++;
		else Q[i].x=read();
	}
	for(int i=pos+1;i<=K;i++)Update(P[i].x,P[i].y,P[i].v);
	for(int i=m;i>=1;i--){
		if(Q[i].op==0){
			Update(P[pos].x,P[pos].y,P[pos].v);
			pos--;
		}
		if(Q[i].op==1){
			Q[i].ans=tree.Ask(id[Q[i].x],1,1,n);
		}
	}
	for(int i=1;i<=m;i++){
		if(Q[i].op==1){
			printf("%d\n",Q[i].ans!=inf?Q[i].ans:-1);
		}
	}
	return 0;
}