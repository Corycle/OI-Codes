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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
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
int n,m,top;
vector<int>b[N];
vector<pii>Q[N];
int a[N],st[N],Ans[N];
struct Tree{int tag,Max,val;};
struct Semgent_Tree{
	Tree t[N*4];
	void update(int p,int x){t[p].tag=max(t[p].tag,x);t[p].Max=max(t[p].Max,t[p].val+x);}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Build(int p,int l,int r){
		if(l==r){t[p].val=a[l];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
		t[p].val=max(t[p<<1].val,t[p<<1|1].val);
	}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
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
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		while(top&&a[st[top]]<a[i])b[st[top--]].push_back(i);
		b[st[top]].push_back(i);
		st[++top]=i;
	}
	m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		Q[l].push_back(mp(r,i));
	}
	tree.Build(1,1,n);
	for(int i=n;i>=1;i--){
		for(auto x:b[i])if(x*2-i<=n)tree.Update(x*2-i,n,a[i]+a[x],1,1,n);
		for(auto tmp:Q[i])Ans[tmp.scd]=tree.Query(i,tmp.fst,1,1,n);
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}