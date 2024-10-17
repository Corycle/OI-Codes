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
char op[10];
int n,m,a[N];
struct Node{
	int a,b;
	void Init(){a=0;b=-inf;}
	int Calc(int x){return max(a+x,b);}
	friend Node max(Node A,Node B){return (Node){max(A.a,B.a),max(A.b,B.b)};}
	friend Node operator+(Node A,Node B){return (Node){max(-inf,A.a+B.a),max(A.b+B.a,B.b)};}
};
struct Tree{
	Node tag,Max;
	int Max1,Max2;
	void Init(){tag.Init();Max.Init();}
};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,Node A,Node B){
		t[p].Max=max(t[p].Max,t[p].tag+B);
		t[p].tag=t[p].tag+A;
		t[p].Max2=max(t[p].Max2,B.Calc(t[p].Max1));
		t[p].Max1=A.Calc(t[p].Max1);
	}
	void Pushdown(int p){
		update(p<<1,t[p].tag,t[p].Max);
		update(p<<1|1,t[p].tag,t[p].Max);
		t[p].Init();
	}
	void Pushup(int p){
		t[p].Max1=max(t[p<<1].Max1,t[p<<1|1].Max1);
		t[p].Max2=max(t[p<<1].Max2,t[p<<1|1].Max2);
	}
	void Build(int p,int l,int r){
		t[p].Init();
		if(l==r){t[p].Max1=t[p].Max2=a[l];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		Pushup(p);
	}
	void Update(int x,int y,Node v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);
		Pushup(p);
	}
	int Query(int x,int y,int type,int p,int l,int r){
		if(y<l||x>r)return -inf;
		if(x<=l&&r<=y)return (type==1?t[p].Max1:t[p].Max2);
		int mid=(l+r)>>1;Pushdown(p);
		return max(Query(x,y,type,lson),Query(x,y,type,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	m=read();
	while(m--){
		scanf("%s",op);
		int l=read(),r=read();
		if(op[0]=='Q')printf("%d\n",tree.Query(l,r,1,1,1,n));
		if(op[0]=='A')printf("%d\n",tree.Query(l,r,2,1,1,n));
		if(op[0]=='P')tree.Update(l,r,(Node){read(),-inf},1,1,n);
		if(op[0]=='C')tree.Update(l,r,(Node){-inf,read()},1,1,n);
	}
	return 0;
}