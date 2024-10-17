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
using namespace std;
const int inf=0x3f3f3f3f;
const int Maxn=1e6+5;
const int N=3e5+5;
const int M=22;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
#define Lson t[px].l,t[py].l,l,mid
#define Rson t[px].r,t[py].r,mid+1,r
int n,m,Q,Root[N];
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*M];
	void Update(int x,int &p,int l,int r){
		t[++tot]=t[p];p=tot;t[p].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		x<=mid?Update(x,lson):Update(x,rson);
	}
	int Ask(int x,int y,int px,int py,int l,int r){
		if(y<l||x>r||!(t[py].sum-t[px].sum))return 0;
		if(x<=l&&r<=y)return t[py].sum-t[px].sum;
		int mid=(l+r)>>1;
		return Ask(x,y,Lson)+Ask(x,y,Rson);
	}
	int Ask1(int x,int y,int px,int py,int l,int r){
		if(y<l||x>r||!(t[py].sum-t[px].sum))return -1;
		if(l==r)return l;int mid=(l+r)>>1;
		int tmp=Ask1(x,y,Rson);
		return tmp!=-1?tmp:Ask1(x,y,Lson);
	}
	int Ask2(int x,int y,int px,int py,int l,int r){
		if(y<l||x>r||!(t[py].sum-t[px].sum))return -1;
		if(l==r)return l;int mid=(l+r)>>1;
		int tmp=Ask2(x,y,Lson);
		return tmp!=-1?tmp:Ask2(x,y,Rson);
	}
}tree;
int main(){
//	freopen("snow.in","r",stdin);
//	freopen("snow.out","w",stdout);

	return 0;
}
