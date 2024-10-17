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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
struct Segment_Tree{
	int t[N*4];
	void Build(int p,int l,int r){
		t[p]=-inf;if(l==r)return;
		int mid=(l+r)>>1;Build(lson);Build(rson);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p]=max(t[p],z);return;}
		int mid=(l+r)>>1;
		Update(x,y,z,lson);Update(x,y,z,rson);
	}
	void Query(int b,int p,int l,int r){
		b=max(b,t[p]);
		if(l==r){a[l]=(b==-inf?0:l+b);return;}
		int mid=(l+r)>>1;Query(b,lson);Query(b,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	tree.Build(1,1,n);
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),x=read();
		tree.Update(l,r,x-l,1,1,n);
	}
	tree.Query(-inf,1,1,n);
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}