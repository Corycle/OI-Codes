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
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N];
struct Segment_Tree{
	struct Tree{int tag;}t[N*4];
	void Build(int p,int l,int r){
		if(l==r){
			t[p].tag=a[l];
			return;
		}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
	}
	void Add(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			t[p].tag+=z;
			return;
		}
		int mid=(l+r)>>1;
		Add(x,y,z,lson);
		Add(x,y,z,rson);
	}
	int Ask(int x,int p,int l,int r){
		if(x<l||x>r)return 0;
		if(l==r)return t[p].tag;
		int mid=(l+r)>>1;
		return Ask(x,lson)+Ask(x,rson)+t[p].tag;
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	for(int i=1;i<=n;i++){
		int op=read(),l=read(),r=read(),c=read();
		if(op==0)tree.Add(l,r,c,1,1,n);
		if(op==1)printf("%d\n",tree.Ask(r,1,1,n));
	}
	return 0;
}