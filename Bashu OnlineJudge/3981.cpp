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
const ll inf=1e18;
const int N=4e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char s[10];
int n,m,qx,qy,tot,type,pos[N];
struct Point{
	ll x,y;
	friend Point operator-(Point A,Point B){return (Point){A.x-B.x,A.y-B.y};}
	friend Point operator+(Point A,Point B){return (Point){A.x+B.x,A.y+B.y};}
	friend double operator*(Point A,Point B){return A.x*B.x+A.y*B.y;}
	friend double operator^(Point A,Point B){return A.x*B.y-A.y*B.x;}
	friend bool operator<(Point A,Point B){return A.x<B.x||(A.x==B.x&&A.y<B.y);}
};
ll Cross(Point A,Point B,Point C){return (A-C)^(B-C);}
struct Node{
	int n;
	vector<Point>a;
	void Clear(){n=0;a.clear();}
	void Init(Point A){n=1;a.resize(2);a[1]=A;}
	void Insert(Point A){while(n>=2&&Cross(a[n-1],a[n],A)>=0)n--;a[++n]=A;}
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
struct Tree{Node a[2];};
struct Segment_Tree{
	Tree t[N*4];
	ll Query(int p){
		return max(t[p].a[0].Query((Point){qx,qy}),t[p].a[1].Query((Point){-qx,-qy}));
	}
	void Build(int p,int l,int r){
		if(l==r){pos[l]=p;return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
	}
	ll Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return -inf;
		if(x<=l&&r<=y)return Query(p);
		int mid=(l+r)>>1;
		return max(Query(x,y,lson),Query(x,y,rson));
	}
	void Insert(int p,int x,int y){
		t[p].a[0].Init((Point){x,y});
		t[p].a[1].Init((Point){-x,-y});
		while((p&1)&&p!=1){
			p>>=1;
			t[p].a[0]=t[p<<1].a[0]+t[p<<1|1].a[0];
			t[p].a[1]=t[p<<1].a[1]+t[p<<1|1].a[1];
		}
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	scanf("%s",s);type=(s[0]!='E');
	tree.Build(1,1,n);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		if(s[0]=='A'){
			qx=read()^(type*(Ans&0x7fffffff));
			qy=read()^(type*(Ans&0x7fffffff));
			tree.Insert(pos[++tot],qx,qy);
		}
		if(s[0]=='Q'){
			qx=read()^(type*(Ans&0x7fffffff));
			qy=read()^(type*(Ans&0x7fffffff));
			int l=read()^(type*(Ans&0x7fffffff));
			int r=read()^(type*(Ans&0x7fffffff));
			printf("%lld\n",Ans=tree.Query(l,r,1,1,n));
		}
	}
	return 0;
}