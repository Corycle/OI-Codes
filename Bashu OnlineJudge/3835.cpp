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
int n,m,cnt;
int a[N],b[N],h[N],fa[N],Root[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*60];
	void Insert(int x,int &p,int l,int r){
		if(!p)p=++tot;t[p].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		if(x<=mid)Insert(x,t[p].l,l,mid);
		if(x>mid)Insert(x,t[p].r,mid+1,r);
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		int p=++tot;
		t[p].sum=t[x].sum+t[y].sum;
		t[p].l=Merge(t[x].l,t[y].l);
		t[p].r=Merge(t[x].r,t[y].r);
		return p;
	}
	int Query(int k,int p,int l,int r){
		if(l==r)return l;
		int mid=(l+r)>>1;
		if(k<=t[t[p].l].sum)return Query(k,t[p].l,l,mid);
		return Query(k-t[t[p].l].sum,t[p].r,mid+1,r);
	}
}tree;
void DFS(int x,int fa){
	tree.Insert(a[x],Root[x],1,n);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		Root[x]=tree.Merge(Root[x],Root[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	for(int i=1;i<=n;i++)b[a[i]]=i;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,0);
	m=read();
	for(int i=1;i<=m;i++){
		int x=read(),k=read();
		printf("%d\n",b[tree.Query(k,Root[x],1,n)]);
	}
	return 0;
}