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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,tot,Ans;
int a[N],b[N],c[N],h[N],f[N],fa[N];
int p1[N],p2[N],rt[N],root[N*20];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Segment_Tree{
	int tot;
	struct Tree{int l,r,Max;}t[N*330];
	void Update(int &x,int y,int pos,int l,int r){
		x=++tot;t[x]=t[y];
		if(l==r){t[x].Max=max(t[x].Max,f[pos]);return;}
		int mid=(l+r)>>1;
		if(b[pos]<=mid)Update(t[x].l,t[y].l,pos,l,mid);
		if(b[pos]>mid)Update(t[x].r,t[y].r,pos,mid+1,r);
		t[x].Max=max(t[t[x].l].Max,t[t[x].r].Max);
	}
	int Ask(int x,int ql,int qr,int l,int r){
		if(!x||qr<l||ql>r)return 0;
		if(ql<=l&&r<=qr)return t[x].Max;
		int mid=(l+r)>>1,ans=0;
		ans=max(ans,Ask(t[x].l,ql,qr,l,mid));
		ans=max(ans,Ask(t[x].r,ql,qr,mid+1,r));
		return ans;
	}
}tree;
struct Node{int l,r;}t[N*20];
void Insert(int &x,int y,int pos,int l,int r){
	x=++tot;t[x]=t[y];
	tree.Update(root[x],root[y],pos,1,p2[0]);
	if(l==r)return;int mid=(l+r)>>1;
	if(a[pos]<=mid)Insert(t[x].l,t[y].l,pos,l,mid);
	if(a[pos]>mid)Insert(t[x].r,t[y].r,pos,mid+1,r);
}
int Ask(int x,int pos,int ql,int qr,int l,int r){
	if(!x||qr<l||ql>r)return 0;
	if(ql<=l&&r<=qr)return tree.Ask(root[x],b[pos],p2[0],1,p2[0]);
	int mid=(l+r)>>1,ans=0;
	ans=max(ans,Ask(t[x].l,pos,ql,qr,l,mid));
	ans=max(ans,Ask(t[x].r,pos,ql,qr,mid+1,r));
	return ans;
}
void DFS(int x){
	f[x]=Ask(rt[fa[x]],x,a[x],p1[0],1,p1[0])+c[x];
	Insert(rt[x],rt[fa[x]],x,1,p1[0]);
	Ans=max(Ans,f[x]);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
	}
}
int main(){
//	freopen("study.in","r",stdin);
//	freopen("study.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		p1[++p1[0]]=a[i]=read();
		p2[++p2[0]]=b[i]=read();
		c[i]=read();
	}
	sort(p1+1,p1+p1[0]+1);p1[0]=unique(p1+1,p1+p1[0]+1)-p1-1;
	sort(p2+1,p2+p2[0]+1);p2[0]=unique(p2+1,p2+p2[0]+1)-p2-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(p1+1,p1+p1[0]+1,a[i])-p1;
		b[i]=lower_bound(p2+1,p2+p2[0]+1,b[i])-p2;
	}
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1);
	printf("%d",Ans);
	return 0;
}