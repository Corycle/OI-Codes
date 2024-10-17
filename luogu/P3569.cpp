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
struct Node{int a[2];}P[N];
struct Tree{
	Node L,R;bool a[2][2];
	bool Check(){return a[0][0]|a[0][1]|a[1][0]|a[1][1];}
	void Init(Node l,Node r){L=l;R=r;a[0][0]=a[1][1]=1;a[0][1]=a[1][0]=0;}
	friend Tree operator+(Tree A,Tree B){
		Tree C;C.Init(A.L,B.R);memset(C.a,0,sizeof(C.a));
		for(int l1=0;l1<2;l1++){
			for(int l2=0;l2<2;l2++){
				for(int r1=0;r1<2;r1++){
					for(int r2=0;r2<2;r2++){
						C.a[l1][r2]|=(A.a[l1][l2]&B.a[r1][r2]&(A.R.a[l2]<=B.L.a[r1]));
					}
				}
			}
		}
		return C;
	}
};
struct Segment_Tree{
	Tree t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p].Init(P[l],P[l]);return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);t[p]=t[p<<1]+t[p<<1|1];
	}
	void Update(int x,int p,int l,int r){
		if(l==r){t[p].Init(P[l],P[l]);return;}
		int mid=(l+r)>>1;x<=mid?Update(x,lson):Update(x,rson);t[p]=t[p<<1]+t[p<<1|1];
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){P[i].a[0]=read();P[i].a[1]=read();}
	tree.Build(1,1,n);
	m=read();
	while(m--){
		int x=read(),y=read();swap(P[x],P[y]);
		tree.Update(x,1,1,n);tree.Update(y,1,1,n);
		puts(tree.t[1].Check()?"TAK":"NIE");
	}
	return 0;
}
