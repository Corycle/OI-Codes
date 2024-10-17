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
using namespace std;
const int inf=0x3f3f3f3f;
const int M=2e5+5;
const int N=4e4+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,cnt,tot;
int h[N],b[N],L[N],R[N],fa[N],dep[N],top[N],son[N],sum[N],Ans[N];
struct edge{int to,next;}d[N*2];
struct Node{int op,x,sy,ty,k,v,id;}P[M],t1[M],t2[M];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
bool cmp(Node A,Node B){return A.x!=B.x?A.x<B.x:A.op<B.op;}
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
	top[x]=tp;L[x]=++tot;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y!=fa[x]&&y!=son[x])DFS2(y,y);
	}
	R[x]=tot;
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int Pre(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		if(fa[top[x]]==y)return top[x];
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?son[x]:son[y];
}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	int Query(int l,int r){return Ask(r)-Ask(l-1);}
}tree;
void Solve(int ql,int qr,int l,int r){
	if(l==r){
		for(int i=ql;i<=qr;i++)if(P[i].op==2)Ans[P[i].id]=b[l];
		return;
	}
	int mid=(l+r)>>1,p1=0,p2=0;
	for(int i=ql;i<=qr;i++){
		if(P[i].op==1){
			if(P[i].k<=mid){
				tree.Add(P[i].sy,P[i].v);
				tree.Add(P[i].ty+1,-P[i].v);
				t1[++p1]=P[i];
			}
			else t2[++p2]=P[i];
		}
		if(P[i].op==2){
			int tmp=tree.Ask(P[i].sy);
			if(P[i].k<=tmp)t1[++p1]=P[i];
			else{P[i].k-=tmp;t2[++p2]=P[i];}
		}
	}
	int pos=ql-1,qmid=ql+p1-1;
	for(int i=1;i<=p1;i++)P[++pos]=t1[i];
	for(int i=1;i<=p2;i++)P[++pos]=t2[i];
	if(ql<=qmid)Solve(ql,qmid,l,mid);
	if(qmid<qr)Solve(qmid+1,qr,mid+1,r);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	tot=0;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),k=read(),z=LCA(x,y);b[++b[0]]=k;
		if(L[x]>L[y])swap(x,y);
		if(z!=x){
			P[++tot]=(Node){1,L[x],L[y],R[y],k,1,0};
			P[++tot]=(Node){1,R[x]+1,L[y],R[y],k,-1,0};
		}
		else{
			int p=Pre(x,y);
			if(L[p]>1){
				P[++tot]=(Node){1,1,L[y],R[y],k,1,0};
				P[++tot]=(Node){1,L[p],L[y],R[y],k,-1,0};
			}
			if(R[p]<n){
				P[++tot]=(Node){1,L[y],R[p]+1,n,k,1,0};
				P[++tot]=(Node){1,R[y]+1,R[p]+1,n,k,-1,0};
			}
		}
	}
	sort(b+1,b+b[0]+1);b[0]=unique(b+1,b+b[0]+1)-b-1;
	for(int i=1;i<=tot;i++)P[i].k=lower_bound(b+1,b+b[0]+1,P[i].k)-b;
	for(int i=1;i<=Q;i++){
		int x=read(),y=read(),k=read();
		if(L[x]>L[y])swap(x,y);
		P[++tot]=(Node){2,L[x],L[y],0,k,0,i};
	}
	sort(P+1,P+tot+1,cmp);
	Solve(1,tot,1,b[0]);
	for(int i=1;i<=Q;i++)printf("%d\n",Ans[i]);
	return 0;
}