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
const int N=500005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num,Ans,Root[N];
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*M];
	void Insert(int &x,int y,int pos,int l,int r){
		x=++tot;t[x]=t[y];t[x].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid)Insert(t[x].l,t[y].l,pos,l,mid);
		if(pos>mid)Insert(t[x].r,t[y].r,pos,mid+1,r);
	}
	void Query(int x,int y,int l,int r){
		if(l==r){num=t[y].sum-t[x].sum;Ans=l;return;}
		int lsum=t[t[y].l].sum-t[t[x].l].sum;
		int rsum=t[t[y].r].sum-t[t[x].r].sum;
		int mid=(l+r)>>1;
		if(lsum>=rsum)Query(t[x].l,t[y].l,l,mid);
		if(lsum<rsum)Query(t[x].r,t[y].r,mid+1,r);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int x=read()+1;
		tree.Insert(Root[i],Root[i-1],x,1,n);
	}
	while(m--){
		int l=read(),r=read();num=Ans=0;
		tree.Query(Root[l-1],Root[r],1,n);
		if(num*2<=(r-l+1))puts("-1");
		else printf("%d\n",Ans-1);
	}
	return 0;
}