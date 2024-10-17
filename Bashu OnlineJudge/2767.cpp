#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
struct Segment_Tree{
	struct tree{int sum,lmax,rmax,ans;}t[N*4];
	void pushup(int p){
		t[p].sum=t[p*2].sum+t[p*2+1].sum;
		t[p].lmax=max(t[p*2].sum+t[p*2+1].lmax,t[p*2].lmax);
		t[p].rmax=max(t[p*2+1].sum+t[p*2].rmax,t[p*2+1].rmax);
		t[p].ans=max(t[p*2].rmax+t[p*2+1].lmax,max(t[p*2].ans,t[p*2+1].ans));
	}
	void Build(int p,int l,int r){
		if(l==r){
			t[p].sum=t[p].ans=a[l];
			t[p].lmax=t[p].rmax=a[l];
			return;
		}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);pushup(p);
	}
	void Add(int x,int y,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){
			t[p].sum=t[p].ans=y;
			t[p].lmax=t[p].rmax=y;
			return;
		}
		int mid=(l+r)>>1;
		Add(x,y,lson);
		Add(x,y,rson);
		pushup(p);
	}
	int Ask(int x,int y,int k,int p,int l,int r){
		if(y<l||r<x)return 0;
		if(x<=l&&r<=y){
			if(k==1)return t[p].lmax;//由该段左端点 l 开始的最大子段和 
			if(k==2)return t[p].rmax;//由该段右端点 r 开始的最大子段和 
			if(k==3)return t[p].ans;//不与该段 l，r 两端点相交的区间最大子段和 
			if(k==4)return t[p].sum;//sum，即所有数之和 
		}
		int mid=(l+r)>>1;
		if(y<=mid)return Ask(x,y,k,lson);
		if(x>mid) return Ask(x,y,k,rson);
		if(k==1)return max(Ask(x,y,1,lson),Ask(x,y,4,lson)+Ask(x,y,1,rson));
		if(k==2)return max(Ask(x,y,2,rson),Ask(x,y,2,lson)+Ask(x,y,4,rson));
		if(k==3)return max(Ask(x,y,2,lson)+Ask(x,y,1,rson),max(Ask(x,y,3,lson),Ask(x,y,3,rson)));
		if(k==4)return Ask(x,y,4,lson)+Ask(x,y,4,rson);
	}
}tree;
int main(){
//	freopen("park.in","r",stdin);
//	freopen("park.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	while(m--){
		i=read();j=read();k=read();
		if(i==2)tree.Add(j,k,1,1,n);
		else{
			if(j>k)swap(j,k);
			int ans=-inf;
			ans=max(ans,tree.Ask(j,k,1,1,1,n));
			ans=max(ans,tree.Ask(j,k,2,1,1,n));
			ans=max(ans,tree.Ask(j,k,3,1,1,n));
			ans=max(ans,tree.Ask(j,k,4,1,1,n));
			printf("%d\n",ans);
		}
	}
	return 0;
}