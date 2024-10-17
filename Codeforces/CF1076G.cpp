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
const int M=32;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,Flag,a[N];
struct Node{
	int a[M];
	void Init(){for(int i=0;i<M;i++)a[i]=0;}
	friend Node operator+(Node A,Node B){
		Node C;C.Init();
		for(int i=0;i<(1<<m);i++)C.a[i]=A.a[B.a[i]];
		return C;
	}
};
Node F0,F1,Answer;
struct Tree{
	int tag;Node A,B;
	void Init(int x){tag=0;A=(x&1)?F1:F0;B=(x&1)?F0:F1;}
};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p){t[p].tag^=1;swap(t[p].A,t[p].B);}
	void Pushdown(int p){if(t[p].tag){update(p<<1);update(p<<1|1);t[p].tag=0;}}
	void Pushup(int p){t[p].A=t[p<<1].A+t[p<<1|1].A;t[p].B=t[p<<1].B+t[p<<1|1].B;}
	void Build(int p,int l,int r){
		if(l==r){t[p].Init(a[l]);return;}
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
	n=read();m=read();Q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<(1<<m);i++){
		F0.a[i]=(i>>1)|(1<<(m-1));
		F1.a[i]=(i>>1)|(1<<(m-1));
		if(i==(1<<m)-1)F1.a[i]=(i>>1);
	}
	tree.Build(1,1,n);
	while(Q--){
		int op=read(),l=read(),r=read();
		if(op==1)if(read()&1)tree.Update(l,r,1,1,n);
		if(op==2){
			Answer.Init();Flag=0;tree.Query(l,r,1,1,n);
			printf("%d\n",(Answer.a[(1<<m)-1]&(1<<(m-1)))?1:2);
		}
	}
	return 0;
}
