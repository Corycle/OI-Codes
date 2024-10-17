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
int n,m,type,Ans,a[N];
struct Tree{int Max,Ans;};
struct Segment_Tree{
	Tree t[N*4];
	int Query(int x,int p,int l,int r){
		if(l==r)return a[l]-l>x?x+l:inf;
		int mid=(l+r)>>1;
		if(t[p<<1|1].Max<=x)return Query(x,lson);
		return min(t[p].Ans,Query(x,rson));
	}
	void Pushup(int p,int l,int r){
		int mid=(l+r)>>1;
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
		t[p].Ans=Query(t[p<<1|1].Max,lson);
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].Max=a[l]-l;return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		Pushup(p,l,r);
	}
	void Update(int x,int p,int l,int r){
		if(l==r){t[p].Max=a[l]-l;return;}
		int mid=(l+r)>>1;
		if(x<=mid)Update(x,lson);
		if(x>mid)Update(x,rson);
		Pushup(p,l,r);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();type=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	printf("%d\n",Ans=tree.Query(tree.t[1].Max-n,1,1,n)+n);
	while(m--){
		int x=read()^(type*Ans);
		int y=read()^(type*Ans);
		a[x]=y;tree.Update(x,1,1,n);
		printf("%d\n",Ans=tree.Query(tree.t[1].Max-n,1,1,n)+n);
	}
	return 0;
}