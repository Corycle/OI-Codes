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
const ll inf=1e14;
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
struct Tree{ll Min1,Min2,NumMin,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,ll x){t[p].tag+=x;t[p].Min1+=x;if(t[p].Min2!=inf)t[p].Min2+=x;}
	void Pushdown(int p){
		if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}
		t[p<<1].Min1=max(t[p<<1].Min1,t[p].Min1);
		t[p<<1|1].Min1=max(t[p<<1|1].Min1,t[p].Min1);
	}
	void Pushup(int p){
		int l=p<<1,r=p<<1|1;t[p].NumMin=0;
		t[p].Min1=min(t[l].Min1,t[r].Min1);
		t[p].Min2=min(t[l].Min2,t[r].Min2);
		if(t[p].Min1==t[l].Min1)t[p].NumMin+=t[l].NumMin;
		else t[p].Min2=min(t[p].Min2,t[l].Min1);
		if(t[p].Min1==t[r].Min1)t[p].NumMin+=t[r].NumMin;
		else t[p].Min2=min(t[p].Min2,t[r].Min1);
	}
	void Build(int p,int l,int r){
		if(l==r){t[p]=(Tree){a[l],inf,1,0};return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Add(int x,int y,ll val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Add(x,y,val,lson);Add(x,y,val,rson);Pushup(p);
	}
	void Max(int x,int y,ll val,int p,int l,int r){
		if(y<l||x>r||t[p].Min1>=val)return;
		if(x<=l&&r<=y&&t[p].Min2>val){t[p].Min1=val;return;}
		int mid=(l+r)>>1;Pushdown(p);
		Max(x,y,val,lson);Max(x,y,val,rson);Pushup(p);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return (t[p].Min1==0?t[p].NumMin:0);
		int mid=(l+r)>>1;Pushdown(p);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1){
			tree.Add(l,r,-inf,1,1,n);
			tree.Max(l,r,read(),1,1,n);
		}
		if(op==2){
			tree.Add(l,r,read(),1,1,n);
			tree.Max(l,r,0,1,1,n);
		}
		if(op==3)printf("%d\n",tree.Query(l,r,1,1,n));
	}
	return 0;
}