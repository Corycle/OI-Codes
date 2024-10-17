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
const int Mod=998244353;
const int N=(1<<20)+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,tot;
struct Point{
	int x,y;
	friend Point operator-(Point A,Point B){return (Point){A.x-B.x,A.y-B.y};}
	friend Point operator+(Point A,Point B){return (Point){A.x+B.x,A.y+B.y};}
	friend ll operator*(Point A,Point B){return 1ll*A.x*B.x+1ll*A.y*B.y;}
	friend ll operator^(Point A,Point B){return 1ll*A.x*B.y-1ll*A.y*B.x;}
	friend bool operator<(Point A,Point B){return A.x<B.x||(A.x==B.x&&A.y<B.y);}
}P[N];
ll Cross(Point A,Point B,Point C){return (A-C)^(B-C);}
struct Node{
	int n;
	vector<Point>a;
	void Clear(){n=0;vector<Point>tmp;swap(a,tmp);}
	void Init(Point A){Clear();n=1;a.resize(2);a[1]=A;}
	void Insert(Point A){
		while(n>=2&&Cross(a[n-1],a[n],A)>=0)n--;
		a[++n]=A;
	}
	ll Query(Point A){
		int l=1,r=n-1,pos=1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(a[mid]*A<=a[mid+1]*A){
				l=mid+1;pos=mid+1;
			}
			else r=mid-1;
		}
		return a[pos]*A;
	}
	friend Node operator+(Node A,Node B){
		Node C;C.n=0;
		C.a.resize(A.n+B.n+1);
		int p1=1,p2=1;
		while(p1<=A.n&&p2<=B.n){
			if(A.a[p1]<B.a[p2])C.Insert(A.a[p1++]);
			else C.Insert(B.a[p2++]);
		}
		while(p1<=A.n)C.Insert(A.a[p1++]);
		while(p2<=B.n)C.Insert(B.a[p2++]);
		return C;
	}
};
int lst[40],pre[N],F[N];
struct Segment_Tree{
	Node t[N];
	void Pushup(int p){t[p]=t[p<<1]+t[p<<1|1];}
	void Build(int dep,int p,int l,int r){
		t[p].Clear();
		if(l==r)return;int mid=(l+r)>>1;
		F[p]=1;pre[p]=lst[dep];lst[dep]=p;
		Build(dep+1,lson);Build(dep+1,rson);
	}
	void Insert(int x,int p,int l,int r){
		if(l==r){P[l].x=read();P[l].y=read();t[p].Init(P[l]);return;}
		int mid=(l+r)>>1;
		(x<=mid?Insert(x,lson):Insert(x,rson));
		if(x==r&&F[pre[p]]){Pushup(pre[p]);F[pre[p]]=0;}
	}
	void Delete(int x,int p,int l,int r){
		t[p].Clear();
		if(l==r)return;int mid=(l+r)>>1;
		(x<=mid?Delete(x,lson):Delete(x,rson));
		if(x==r)F[p]=1;
	}
	void Query(int x,int y,Point A,int p,int l,int r){
		if(x<=l&&r<=y&&!F[p]){Ans=max(Ans,t[p].Query(A));return;}
		int mid=(l+r)>>1;
		if(x<=mid)Query(x,y,A,lson);
		if(y>mid)Query(x,y,A,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	read();
	while(1){
		n=read();
		if(!n)break;
		int Lim=1<<((int)ceil(log2(n)));
		memset(lst,0,sizeof(lst));
		tree.Build(1,1,1,Lim);
		int Answer=0;tot=0;
		for(int i=1;i<=n;i++){
			int op=read();
			if(op==1)tree.Insert(++tot,1,1,Lim);
			if(op==2)tree.Delete(tot--,1,1,Lim);
			if(op==3){
				Ans=-1e18;
				int l=read(),r=read();
				int x=read(),y=read();
				Point tmp=(Point){-y,x};
				tree.Query(l,r,tmp,1,1,Lim);
				Answer^=((Ans%Mod+Mod)%Mod);
			}
		}
		printf("%d\n",Answer);
	}
	return 0;
}