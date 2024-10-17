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
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
struct Node{
	ll a,b;
	void Init(){a=0;b=-inf;}
	ll Calc(ll x){return max(a+x,b);}
	friend Node min(Node A,Node B){return (Node){min(A.a,B.a),min(A.b,B.b)};}
	friend Node max(Node A,Node B){return (Node){max(A.a,B.a),max(A.b,B.b)};}
	friend Node operator+(Node A,Node B){return (Node){max(A.a+B.a,-inf),max(A.b+B.a,B.b)};}
};
struct Tree{ll M1,M2;Node t1,t2;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,Node A,Node B){
		t[p].t2=max(t[p].t2,t[p].t1+B);
		t[p].t1=t[p].t1+A;
		t[p].M2=max(t[p].M2,B.Calc(t[p].M1));
		t[p].M1=A.Calc(t[p].M1);
	}
	void Pushdown(int p){
		update(p<<1,t[p].t1,t[p].t2);
		update(p<<1|1,t[p].t1,t[p].t2);
		t[p].t1.Init();t[p].t2.Init();
	}
	void Pushup(int p){
		t[p].M1=max(t[p<<1].M1,t[p<<1|1].M1);
		t[p].M2=max(t[p<<1].M2,t[p<<1|1].M2);
	}
	void Build(int p,int l,int r){
		t[p].t1.Init();t[p].t2.Init();
		if(l==r){t[p].M1=t[p].M2=a[l];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Update(int x,int y,Node z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,z,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,z,lson);Update(x,y,z,rson);Pushup(p);
	}
	ll Query(int x,int y,int p,int l,int r){
		if(l==r)return y?t[p].M2:t[p].M1;
		int mid=(l+r)>>1;Pushdown(p);
		return (x<=mid?Query(x,y,lson):Query(x,y,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read();
		if(op==1){int l=read(),r=read();tree.Update(l,r,(Node){+read(),0},1,1,n);}
		if(op==2){int l=read(),r=read();tree.Update(l,r,(Node){-read(),0},1,1,n);}
		if(op==3){int l=read(),r=read();tree.Update(l,r,(Node){-inf,read()},1,1,n);}
		if(op==4)printf("%lld\n",tree.Query(read(),0,1,1,n));
		if(op==5)printf("%lld\n",tree.Query(read(),1,1,1,n));
	}
	return 0;
}