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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
struct Tree{int Min,Max,tag;ll sum;};
struct Segment_Tree{
	Tree t[N*4];
	int Calc(int x,int p){return floor(1.0*x/p)-x;}
	void update(int p,int l,int r,int x){
		t[p].Min+=x;t[p].Max+=x;t[p].tag+=x;t[p].sum+=(r-l+1)*x;
	}
	void Pushdown(int p,int l,int r){
		if(t[p].tag){
			int mid=(l+r)>>1;
			update(lson,t[p].tag);
			update(rson,t[p].tag);
			t[p].tag=0;
		}
	}
	void Pushup(int p){
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
		t[p].Min=min(t[p<<1].Min,t[p<<1|1].Min);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].Min=t[p].Max=t[p].sum=a[l];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Update1(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,l,r,z);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update1(x,y,z,lson);Update1(x,y,z,rson);Pushup(p);
	}
	void Update2(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y&&Calc(t[p].Min,z)==Calc(t[p].Max,z)){
			update(p,l,r,Calc(t[p].Min,z));
			return;
		}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update2(x,y,z,lson);Update2(x,y,z,rson);Pushup(p);
	}
	int Query1(int x,int y,int p,int l,int r){
		if(y<l||x>r)return inf;
		if(x<=l&&r<=y)return t[p].Min;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return min(Query1(x,y,lson),Query1(x,y,rson));
	}
	ll Query2(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return Query2(x,y,lson)+Query2(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read(),l=read()+1,r=read()+1;
		if(op==1)tree.Update1(l,r,read(),1,1,n);
		if(op==2)tree.Update2(l,r,read(),1,1,n);
		if(op==3)printf("%d\n",tree.Query1(l,r,1,1,n));
		if(op==4)printf("%lld\n",tree.Query2(l,r,1,1,n));
	}
	return 0;
}