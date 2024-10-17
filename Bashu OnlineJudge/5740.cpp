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
const int Sta=(1<<20)-1;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
bool Belong(int x,int y){return (x|y)==y;}
struct Tree{
	int Max,s1,s2,tag1,tag2;
	void Init(int x){Max=s1=s2=x;}
	void And(int x){Max&=x;s1&=x;s2&=x;tag1&=x;tag2&=x;}
	void Or(int x){Max|=x;s1|=x;s2|=x;tag1|=x;tag2|=x;}
};
struct Segment_Tree{
	Tree t[N*4];
	void Pushup(int p){
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
		t[p].s1=t[p<<1].s1&t[p<<1|1].s1;
		t[p].s2=t[p<<1].s2|t[p<<1|1].s2;
	}
	void Pushdown(int p){
		if(t[p].tag1!=Sta){
			t[p<<1].And(t[p].tag1);
			t[p<<1|1].And(t[p].tag1);
			t[p].tag1=Sta;
		}
		if(t[p].tag2){
			t[p<<1].Or(t[p].tag2);
			t[p<<1|1].Or(t[p].tag2);
			t[p].tag2=0;
		}
	}
	void Build(int p,int l,int r){
		t[p].tag1=Sta;t[p].tag2=0;
		if(l==r){t[p].Init(a[l]);return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		Pushup(p);
	}
	void Update(int x,int y,int z,int op,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			int A=t[p].s1,B=t[p].s2,C=A|(B^Sta),z1=z^Sta,z2=z;
			if(op==1&&(l==r||Belong(z1,C))){t[p].And(z);return;}
			if(op==2&&(l==r||Belong(z2,C))){t[p].Or(z);return;}
		}
		int mid=(l+r)>>1;
		Pushdown(p);
		Update(x,y,z,op,lson);
		Update(x,y,z,op,rson);
		Pushup(p);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].Max;
		int mid=(l+r)>>1;Pushdown(p);
		return max(Query(x,y,lson),Query(x,y,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1)tree.Update(l,r,read(),op,1,1,n);
		if(op==2)tree.Update(l,r,read(),op,1,1,n);
		if(op==3)printf("%d\n",tree.Query(l,r,1,1,n));
	}
	return 0;
}