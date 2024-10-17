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
int n,m,flag,a[N];
struct Tree{
	int ls,rs,ans,sum;
	void Init(int x){ls=rs=ans=sum=x;}
	friend Tree operator+(Tree A,Tree B){
		Tree C;
		C.sum=A.sum+B.sum;
		C.ls=max(A.ls,A.sum+B.ls);
		C.rs=max(B.rs,B.sum+A.rs);
		C.ans=max(A.rs+B.ls,max(A.ans,B.ans));
		return C;
	}
};
Tree Ans;
struct Segment_Tree{
	Tree t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p].Init(a[l]);return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);t[p]=t[p<<1]+t[p<<1|1];
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Ans=(flag?Ans+t[p]:t[p]);flag=1;return;}
		int mid=(l+r)>>1;Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	m=read();
	while(m--){
		flag=0;Ans.Init(0);
		int l=read(),r=read();
		tree.Query(l,r,1,1,n);
		printf("%d\n",Ans.ans);
	}
	return 0;
}
