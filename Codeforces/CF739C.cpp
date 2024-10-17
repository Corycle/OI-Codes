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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
struct Tree{
	ll l,r,tag;
	int s,fl,fr,tl,tr,ans;
	void Clear(){l=r=s=fl=fr=tl=tr=tag=ans=0;}
	void Init(int x){l=r=x;s=fl=fr=tl=tr=ans=1;}
	friend Tree operator+(Tree A,Tree B){
		Tree C;C.Clear();
		C.ans=max(A.ans,B.ans);
		C.l=A.l;C.r=B.r;C.s=A.s+B.s;
		C.ans=max(C.ans,A.r>B.l?A.tr+B.fl:A.tr);
		C.ans=max(C.ans,A.r<B.l?A.fr+B.tl:B.tl);
		C.fl=(A.fl<A.s?A.fl:A.s+(A.r>B.l?B.fl:0));
		C.fr=(B.fr<B.s?B.fr:B.s+(A.r<B.l?A.fr:0));
		C.tl=max((A.tl<A.s?A.tl:A.s+(A.r>B.l?B.fl:0)),(A.fr<A.s?0:A.s+(A.r<B.l?B.tl:0)));
		C.tr=max((B.tr<B.s?B.tr:B.s+(A.r<B.l?A.fr:0)),(B.fl<B.s?0:B.s+(A.r>B.l?A.tr:0)));
		return C;
	}
};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,ll v){t[p].tag+=v;t[p].l+=v;t[p].r+=v;}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Build(int p,int l,int r){
		if(l==r){t[p].Init(a[l]);return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);
		t[p]=t[p<<1]+t[p<<1|1];
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
		int l=read(),r=read(),v=read();
		tree.Update(l,r,v,1,1,n);
		printf("%d\n",tree.t[1].ans);
	}
	return 0;
}
