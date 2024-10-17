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
using namespace std;
const int inf=0x3f3f3f3f;
const int Lim=1e9;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,tot,L[N],R[N],b[N];
struct Ques{int op,x,a,b;}Q[N];
void DFS(int x,int fa){L[x]=++cnt;for(auto y:G[x])if(y!=fa)DFS(y,x);R[x]=cnt;}
struct Node{
	int a,b;
	ll Calc(ll x){return a*x+b;}
};
struct Tree{int l,r;Node F;};
struct LC_Segment_Tree{
	#define lson t[p].l,l,mid
	#define rson t[p].r,mid+1,r
	int tot;
	Tree t[N*150];
	void Update(Node F,int &p,int l,int r){
		if(!p){p=++tot;t[p].F=F;return;}
		if(l==r)return;int mid=(l+r)>>1;
		if(t[p].F.Calc(b[mid])<F.Calc(b[mid]))swap(t[p].F,F);
		if(t[t[p].l].F.Calc(b[l])<=F.Calc(b[l]))Update(F,lson);
		if(t[t[p].r].F.Calc(b[r])<=F.Calc(b[r]))Update(F,rson);
	}
	ll Query(int x,int p,int l,int r){
		if(!p)return -inf;int mid=(l+r)>>1;
		return max(t[p].F.Calc(b[x]),(x<=mid?Query(x,lson):Query(x,rson)));
	}
	#undef lson
	#undef rson
}sgt;
struct Segment_Tree{
	#define lson p<<1,l,mid
	#define rson p<<1|1,mid+1,r
	int Root[N*4];
	void Update(int x,int y,Node F,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){sgt.Update(F,Root[p],1,b[0]);return;}
		int mid=(l+r)>>1;Update(x,y,F,lson);Update(x,y,F,rson);
	}
	ll Query(int pos,int x,int p,int l,int r){
		if(l==r)return sgt.Query(x,Root[p],1,b[0]);int mid=(l+r)>>1;
		return max(sgt.Query(x,Root[p],1,b[0]),(pos<=mid?Query(pos,x,lson):Query(pos,x,rson)));
	}
	#undef lson
	#undef rson
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	DFS(1,0);
	m=read();
	for(int i=1;i<=m;i++){
		Q[i].op=read();Q[i].x=read();Q[i].a=read();
		if(Q[i].op==1)Q[i].b=read();
		if(Q[i].op==2)b[++b[0]]=Q[i].a;
	}
	sort(b+1,b+b[0]+1);b[0]=unique(b+1,b+b[0]+1)-b-1;
	for(int i=1;i<=m;i++){
		int op=Q[i].op,x=Q[i].x;
		if(op==1){int a=Q[i].a,b=Q[i].b;tree.Update(L[x],R[x],(Node){a,b},1,1,n);}
		if(op==2)printf("%lld\n",max(tree.Query(L[x],lower_bound(b+1,b+b[0]+1,Q[i].a)-b,1,1,n),0ll));
	}
	return 0;
}
