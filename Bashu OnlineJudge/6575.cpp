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
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N],b[N];
int n,m,K,cnt;
int h[N],fa[N],Root[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Tree{int l,r;ll sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*20];
	void Change(int x,ll val,int &p,int l,int r){
		if(!p)p=++tot;
		if(l==r){t[p].sum=val;return;}
		int mid=(l+r)>>1;
		if(x<=mid)Change(x,val,t[p].l,l,mid);
		if(x>mid)Change(x,val,t[p].r,mid+1,r);
		t[p].sum=t[t[p].l].sum+t[t[p].r].sum;
	}
	void Update(int x,ll val,int &p,int l,int r){
		if(!p)p=++tot;
		if(l==r){t[p].sum+=val;return;}
		int mid=(l+r)>>1;
		if(x<=mid)Update(x,val,t[p].l,l,mid);
		if(x>mid)Update(x,val,t[p].r,mid+1,r);
		t[p].sum=t[t[p].l].sum+t[t[p].r].sum;
	}
	ll Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
		return Query(x,y,t[p].l,l,mid)+Query(x,y,t[p].r,mid+1,r);
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		t[x].sum=t[x].sum+t[y].sum;
		t[x].l=Merge(t[x].l,t[y].l);
		t[x].r=Merge(t[x].r,t[y].r);
		return x;
	}
	int Insert(int x,int y,int p,int l,int r){
		if(y<l||x>r)return p;
		if(x<=l&&r<=y)return 0;
		int mid=(l+r)>>1;
		t[p].l=Insert(x,y,t[p].l,l,mid);
		t[p].r=Insert(x,y,t[p].r,mid+1,r);
		t[p].sum=t[t[p].l].sum+t[t[p].r].sum;
		return t[p].sum?p:0;
	}
}tree;
void DFS(int x){
	ll sum=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS(y);
		if(a[x])sum+=tree.Query(1,a[x],Root[y],1,K);
		Root[x]=tree.Merge(Root[x],Root[y]);
	}
	if(a[x]){
		int l=a[x]+1,r=K,pos=a[x];
		while(l<=r){
			int mid=(l+r)>>1;
			if(tree.Query(1,mid,Root[x],1,K)<=b[x]+sum){
				pos=mid;l=mid+1;
			}
			else r=mid-1;
		}
		ll val=0;
		if(pos!=K)val=tree.Query(1,pos+1,Root[x],1,K);
		if(pos!=a[x])Root[x]=tree.Insert(a[x]+1,pos,Root[x],1,K);
		tree.Update(a[x],b[x],Root[x],1,K);
		if(pos!=K)tree.Change(pos+1,val-b[x]-sum,Root[x],1,K);
	}
}
int main(){
//	freopen("magic.in","r",stdin);
//	freopen("magic.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=2;i<=n;i++)Add(fa[i]=read(),i);
	for(int i=1;i<=m;i++){
		int x=read();
		a[x]=read();b[x]=read();
	}
	DFS(1);
	printf("%lld",tree.t[Root[1]].sum);
	return 0;
}