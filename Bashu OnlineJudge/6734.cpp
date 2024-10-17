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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int Root[N],fa[N*40],sum[N*40];
struct Tree{int l,r;};
struct Segment_Tree{
	int tot;
	Tree t[N*40];
	void Build(int &p,int l,int r){
		p=++tot;
		if(l==r){fa[p]=l;sum[p]=1;return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
	}
	void Update(int x,int f,int s,int &p,int l,int r){
		t[++tot]=t[p];p=tot;
		if(l==r){fa[p]=f;sum[p]=s;return;}
		int mid=(l+r)>>1;
		x<=mid?Update(x,f,s,lson):Update(x,f,s,rson);
	}
	int Query(int x,int p,int l,int r){
		if(l==r)return p;int mid=(l+r)>>1;
		return (x<=mid?Query(x,lson):Query(x,rson));
	}
}tree;
int Find(int x,int rt){
	int f=tree.Query(x,rt,1,n);
	return x==fa[f]?f:Find(fa[f],rt);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	tree.Build(Root[0],1,n);
	for(int i=1;i<=m;i++){
		int op=read();Root[i]=Root[i-1];
		if(op==1){
			int x=Find(read()^Ans,Root[i]);
			int y=Find(read()^Ans,Root[i]);
			if(fa[x]!=fa[y]){
				if(sum[x]>sum[y])swap(x,y);
				tree.Update(fa[x],fa[y],sum[x],Root[i],1,n);
				tree.Update(fa[y],fa[y],sum[x]+sum[y],Root[i],1,n);
			}
		}
		if(op==2)Root[i]=Root[read()^Ans];
		if(op==3){
			int x=Find(read()^Ans,Root[i]);
			int y=Find(read()^Ans,Root[i]);
			printf("%d\n",Ans=(fa[x]==fa[y]));
		}
	}
	return 0;
}