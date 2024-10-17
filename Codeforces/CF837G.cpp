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
const int Lim=1e9;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,Root[N];
struct Functions{
	ll k,b;
	ll Calc(int x){return k*x+b;}
	friend Functions operator+(Functions A,Functions B){return (Functions){A.k+B.k,A.b+B.b};}
};
struct Node{int l,r;Functions F;};
struct Segment_Tree{
	int tot;
	Node t[N*100];
	void Update(int x,int y,Functions F,int &p,int l,int r){
		t[++tot]=t[p];p=tot;
		if(x<=l&&r<=y){t[p].F=t[p].F+F;return;}
		int mid=(l+r)>>1;
		if(x<=mid)Update(x,y,F,lson);
		if(y>mid) Update(x,y,F,rson);
	}
	ll Query(int x,int p,int l,int r){
		if(!p)return 0;
		if(l==r)return t[p].F.Calc(x);int mid=(l+r)>>1;
		return (x<=mid?Query(x,lson):Query(x,rson))+t[p].F.Calc(x);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int X1=read(),X2=read(),Y1=read(),a=read(),b=read(),Y2=read();
		Root[i]=Root[i-1];
		if(1<=X1)tree.Update(1,X1,(Functions){0,Y1},Root[i],1,Lim);
		if(X1+1<=X2)tree.Update(X1+1,X2,(Functions){a,b},Root[i],1,Lim);
		if(X2+1<=Lim)tree.Update(X2+1,Lim,(Functions){0,Y2},Root[i],1,Lim);
	}
	m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),x=(read()+Ans)%Lim;
		printf("%lld\n",Ans=tree.Query(x,Root[r],1,Lim)-tree.Query(x,Root[l-1],1,Lim));
	}
	return 0;
}
