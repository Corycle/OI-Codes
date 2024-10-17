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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<int,int>p1,p2;
int n,m,L,R,Root,Ans;
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*30];
	void Insert(int x,int &p,int l,int r){
		if(!p)p=++tot;t[p].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		if(x<=mid)Insert(x,t[p].l,l,mid);
		if(x>mid)Insert(x,t[p].r,mid+1,r);
	}
	int Query(int x,int p,int l,int r){
		if(!p||l==r)return 0;
		int mid=(l+r)>>1;
		if(x<=mid)return Query(x,t[p].l,l,mid);
		return t[t[p].l].sum+Query(x,t[p].r,mid+1,r);
	}
	int Find(int k,int p,int l,int r){
		if(l==r)return l;
		int mid=(l+r)>>1;
		int lsum=max(min(R,mid)-max(L,l)+1-t[t[p].l].sum,0);
		if(k<=lsum)return Find(k,t[p].l,l,mid);
		return Find(k-lsum,t[p].r,mid+1,r);
	}
}tree;
int Change(int x,int y){
	int pos=(p1.find(x)==p1.end()?x:p1[x]);
	int ans=pos-L+1-tree.Query(pos,Root,-inf,inf);
	p2[p1[y]=pos]=y;return ans;
}
int Update1(int x){
	int pos=(p1.find(x)==p1.end()?x:p1[x]);
	int ans=pos-L+1-tree.Query(pos,Root,-inf,inf);
	tree.Insert(pos,Root,-inf,inf);
	p2[p1[x]=--L]=x;return ans;
}
int Update2(int x){
	int pos=(p1.find(x)==p1.end()?x:p1[x]);
	int ans=pos-L+1-tree.Query(pos,Root,-inf,inf);
	tree.Insert(pos,Root,-inf,inf);
	p2[p1[x]=++R]=x;return ans;
}
int Query(int k){
	int x=tree.Find(k,Root,-inf,inf);
	int id=(p2.find(x)==p2.end()?x:p2[x]);
	return id;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();L=1;R=n;
	while(m--){
		int op=read(),x=read()-Ans;
		if(op==1)printf("%d\n",Ans=Change(x,read()-Ans));
		if(op==2)printf("%d\n",Ans=Update1(x));
		if(op==3)printf("%d\n",Ans=Update2(x));
		if(op==4)printf("%d\n",Ans=Query(x));
	}
	return 0;
}