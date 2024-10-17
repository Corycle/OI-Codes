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
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Flag;
struct Node{
	int num,ans,l1,r0,lans,rans;
	void Clear(){num=ans=l1=r0=lans=rans=0;}
	void Init(int c){num=ans=lans=rans=1;c?l1=1:r0=1;}
	friend Node operator+(Node A,Node B){
		Node C;C.Clear();
		C.num=A.num+B.num;
		C.l1=(A.l1==A.num?A.num+B.l1:A.l1);
		C.r0=(B.r0==B.num?B.num+A.r0:B.r0);
		C.lans=max((A.lans==A.num?A.lans+B.l1:A.lans),(A.r0==A.num?A.num+B.lans:0));
		C.rans=max((B.rans==B.num?B.rans+A.r0:B.rans),(B.l1==B.num?B.num+A.rans:0));
		C.ans=max(max(C.lans,C.rans),max(max(A.ans,B.ans),max(A.rans+B.l1,A.r0+B.lans)));
		return C;
	}
};
Node Answer;
struct Tree{
	int tag;Node A,B;
	void Init(int c){tag=0;A.Init(c);B.Init(c^1);}
};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p){t[p].tag^=1;swap(t[p].A,t[p].B);}
	void Pushdown(int p){if(t[p].tag){update(p<<1);update(p<<1|1);t[p].tag=0;}}
	void Pushup(int p){t[p].A=t[p<<1].A+t[p<<1|1].A;t[p].B=t[p<<1].B+t[p<<1|1].B;}
	void Build(int p,int l,int r){
		if(l==r){t[p].Init(s[l]=='>'?0:1);return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Update(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,lson);Update(x,y,rson);Pushup(p);
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Answer=Flag?Answer+t[p].A:t[p].A;Flag=1;return;}
		int mid=(l+r)>>1;Pushdown(p);
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();scanf("%s",s+1);
	tree.Build(1,1,n);
	while(m--){
		Answer.Clear();Flag=0;
		int l=read(),r=read();
		tree.Update(l,r,1,1,n);
		tree.Query(l,r,1,1,n);
		printf("%d\n",Answer.ans);
	}
	return 0;
}
