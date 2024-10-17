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
const ll inf=1e18;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,Ans,top,st[N];
ll w[N],g[N],a[N],b[N],c[N],d[N];
struct Tree{ll d1,d2,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,ll x){t[p].d2+=x;t[p].tag+=x;}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Pushup(int p){
		t[p].d1=max(t[p<<1].d1,t[p<<1|1].d1);
		t[p].d2=max(t[p<<1].d2,t[p<<1|1].d2);
	}
	void Build(int p,int l,int r){
		if(l==r){t[p]=(Tree){-inf,-inf,0};return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Change(int x,ll val,int p,int l,int r){
		if(l==r){t[p]=(Tree){val,val,0};return;}
		int mid=(l+r)>>1;Pushdown(p);
		x<=mid?Change(x,val,lson):Change(x,val,rson);Pushup(p);
	}
	void Update(int x,int y,ll val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,val,lson);Update(x,y,val,rson);Pushup(p);
	}
	int Query(int x,int y,ll val,int p,int l,int r){
		if(l==r)return l;
		int mid=(l+r)>>1;Pushdown(p);
		if(x>mid)return Query(x,y,val,rson);
		if(y<=mid)return Query(x,y,val,lson);
		if(t[p<<1|1].d1+K>=max(val,t[p<<1].d2))return Query(x,y,max(val,t[p<<1].d2),rson);
		return Query(x,y,val,lson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<n;i++)a[i]=a[i-1]+(w[i]=read());
	for(int i=1;i<=n;i++)b[i]=b[i-1]+(g[i]=read());
	for(int i=1;i<=n;i++)c[i]=a[i-1]-b[i-1];
	for(int i=1;i<=n;i++)d[i]=b[i]-a[i-1];
	tree.Build(1,1,n);
	st[0]=n+1;
	for(int i=n;i>=1;i--){
		while(top&&c[i]>=c[st[top]]){
			if(top>1)tree.Update(st[top-1]-1,n,-(c[st[top-1]]-c[st[top]]),1,1,n);
			top--;
		}
		st[++top]=i;
		tree.Change(i,d[i],1,1,n);
		if(top>1)tree.Update(st[top-1]-1,n,c[st[top-1]]-c[st[top]],1,1,n);
		int l=1,r=top,pos=n;
		while(l<=r){
			int mid=(l+r)>>1;
			if(c[st[mid]]-c[i]<=K){r=mid-1;pos=st[mid-1]-1;}
			else l=mid+1;
		}
		Ans=max(Ans,tree.Query(i,pos,-inf,1,1,n)-i+1);
	}
	printf("%d",Ans);
	return 0;
}
