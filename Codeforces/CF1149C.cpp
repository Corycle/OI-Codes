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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char s[N];
struct Tree{
	int Ans,sum,Max,lmax,rmin,lans,rans;
	void Init(int x){Ans=Max=lans=rans=1;sum=x;lmax=max(x,0);rmin=min(x,0);}
	friend Tree operator+(Tree A,Tree B){
		Tree C;
		C.sum=A.sum+B.sum;
		C.lmax=max(A.lmax,A.sum+B.lmax);
		C.rmin=min(B.rmin,B.sum+A.rmin);
		C.Max=max(A.Max+B.sum,B.Max-A.sum);
		C.lans=max(A.lans,max(B.lans-A.sum,A.Max+B.lmax));
		C.rans=max(B.rans,max(A.rans+B.sum,B.Max-A.rmin));
		C.Ans=max(max(A.Ans,B.Ans),max(A.rans+B.lmax,B.lans-A.rmin));
		return C;
	}
};
struct Segment_Tree{
	Tree t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p].Init(s[l]=='('?1:-1);return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);t[p]=t[p<<1]+t[p<<1|1];
	}
	void Update(int x,int p,int l,int r){
		if(l==r){t[p].Init(s[l]=='('?1:-1);return;}
		int mid=(l+r)>>1;(x<=mid?Update(x,lson):Update(x,rson));t[p]=t[p<<1]+t[p<<1|1];
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=(read()-1)*2;m=read();scanf("%s",s+1);
	tree.Build(1,1,n);
	printf("%d\n",tree.t[1].Ans);
	while(m--){
		int l=read(),r=read();
		swap(s[l],s[r]);
		tree.Update(l,1,1,n);
		tree.Update(r,1,1,n);
		printf("%d\n",tree.t[1].Ans);
	}
	return 0;
}
