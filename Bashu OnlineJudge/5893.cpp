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
const int Lim=1e9;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int a[N],h[N],fa[N],Root[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Ques{int k,id;};
vector<Ques>F[N];
struct Tree{int l,r;ll sum,tot;};
struct Segment_Tree{
	int tot;
	Tree t[N*60];
	void Insert(int x,int &p,int l,int r){
		if(!p)p=++tot;t[p].sum+=x;t[p].tot++;
		if(l==r)return;int mid=(l+r)>>1;
		if(x<=mid)Insert(x,t[p].l,l,mid);
		if(x>mid)Insert(x,t[p].r,mid+1,r);
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		int p=++tot;
		t[p].sum=t[x].sum+t[y].sum;
		t[p].tot=t[x].tot+t[y].tot;
		t[p].l=Merge(t[x].l,t[y].l);
		t[p].r=Merge(t[x].r,t[y].r);
		return p;
	}
	ll Query(int k,int p,int l,int r){
		if(!p||!k)return 0;
		if(l==r)return t[p].sum/t[p].tot*k;
		if(t[p].tot<=k)return t[p].sum;
		int mid=(l+r)>>1;
		if(k<=t[t[p].r].tot)return Query(k,t[p].r,mid+1,r);
		return t[t[p].r].sum+Query(k-t[t[p].r].tot,t[p].l,l,mid);
	}
}tree;
void DFS(int x,int fa){
	tree.Insert(a[x],Root[x],0,Lim);
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
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,0);
	for(int i=1;i<=m;i++){
		int x=read(),k=read();
		printf("%lld\n",tree.Query(k,Root[x],0,Lim));
	}
	return 0;
}