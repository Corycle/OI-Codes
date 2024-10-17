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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
struct Tree{double Max;int ans;};
struct Segment_Tree{
	Tree t[N*4];
	int Query(double x,int p,int l,int r){
		if(l==r)return t[p].Max>x;
		int mid=(l+r)>>1;
		if(t[p<<1].Max<=x)return Query(x,rson);
		return t[p].ans-t[p<<1].ans+Query(x,lson);
	}
	void Pushup(int p,int l,int r){
		int mid=(l+r)>>1;
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
		t[p].ans=t[p<<1].ans+Query(t[p<<1].Max,rson);
	}
	void Update(int x,double y,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p].Max=y;t[p].ans=1;return;}
		int mid=(l+r)>>1;
		Update(x,y,lson);Update(x,y,rson);
		Pushup(p,l,r);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		tree.Update(x,(double)y/x,1,1,n);
		printf("%d\n",tree.t[1].ans);
	}
	return 0;
}