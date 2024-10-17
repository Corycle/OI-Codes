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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Flag,a[N];
struct Node{
	int l,r,tag,Max1,Max2,flag;
	void Init(){l=r=tag=Max1=Max2=flag=0;}
	void Prepare(int x){l=r=Max1=x;Max2=-inf;}
	friend Node operator+(Node A,Node B){
		Node C;C.Init();
		C.l=A.l;C.r=B.r;C.tag=0;
		C.Max1=max(A.Max1,B.Max1);
		C.Max2=max(A.Max2,B.Max2);
		C.flag=A.flag|B.flag|(A.r<B.l);
		if(A.Max1!=C.Max1)C.Max2=max(C.Max2,A.Max1);
		if(B.Max1!=C.Max1)C.Max2=max(C.Max2,B.Max1);
		return C;
	}
};
Node Ans;
struct Segment_Tree{
	Node t[N*4];
	void update(int p,int v){
		t[p].Max1+=v;
		t[p].l+=v;t[p].r+=v;t[p].tag+=v;
		if(t[p].Max2!=-inf)t[p].Max2+=v;
	}
	void updateMin(int p,int v){
		if(t[p].l==t[p].Max1)t[p].l=v;
		if(t[p].r==t[p].Max1)t[p].r=v;
		t[p].Max1=v;
	}
	void Pushdown(int p){
		if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}
		if(t[p].Max1<t[p<<1].Max1)updateMin(p<<1,t[p].Max1);
		if(t[p].Max1<t[p<<1|1].Max1)updateMin(p<<1|1,t[p].Max1);
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].Prepare(a[l]);return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Add(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Add(x,y,v,lson);Add(x,y,v,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Min(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r||t[p].Max1<=v)return;
		if(x<=l&&r<=y&&t[p].Max2<v){updateMin(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Min(x,y,v,lson);Min(x,y,v,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Ans=(Flag?Ans+t[p]:t[p]);Flag=1;return;}
		int mid=(l+r)>>1;Pushdown(p);
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1)tree.Add(l,r,read(),1,1,n);
		if(op==2)tree.Min(l,r,read(),1,1,n);
		if(op==3){
			Ans.Init();Flag=0;
			tree.Query(l,r,1,1,n);
			printf("%d\n",Ans.flag?r-l+1:1);
		}
	}
	return 0;
}