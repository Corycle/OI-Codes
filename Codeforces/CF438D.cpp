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
struct Tree{int Max;ll sum;};
struct Segment_Tree{
	Tree t[N*4];
	void Pushup(int p){
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].Max=t[p].sum=a[l];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Update1(int x,int val,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p].Max=t[p].sum=val;return;}
		int mid=(l+r)>>1;Update1(x,val,lson);Update1(x,val,rson);Pushup(p);
	}
	void Update2(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r||t[p].Max<z)return;
		if(l==r){t[p].Max=t[p].sum=t[p].sum%z;return;}
		int mid=(l+r)>>1;Update2(x,y,z,lson);Update2(x,y,z,rson);Pushup(p);
	}
	ll Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
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
		if(op==1)printf("%lld\n",tree.Query(l,r,1,1,n));
		if(op==2)tree.Update2(l,r,read(),1,1,n);
		if(op==3)tree.Update1(l,r,1,1,n);
	}
	return 0;
}
