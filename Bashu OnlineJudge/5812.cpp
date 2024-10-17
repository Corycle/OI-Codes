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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,b[N];
struct Node{int l,r,val;}P[N];
bool cmp(Node A,Node B){return A.val<B.val;}
struct Tree{int Max,tag;};
struct Segment_tree{
	Tree t[N*4];
	void update(int p,int v){t[p].Max+=v;t[p].tag+=v;}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Ans=inf;
	for(int i=1;i<=n;i++){
		P[i].l=read();P[i].r=read();
		P[i].val=P[i].r-P[i].l;
		b[++b[0]]=P[i].l;
		b[++b[0]]=P[i].r;
	}
	sort(P+1,P+n+1,cmp);
	sort(b+1,b+b[0]+1);b[0]=unique(b+1,b+b[0]+1)-b-1;
	for(int i=1,p=1;i<=n;i++){
		P[i].l=lower_bound(b+1,b+b[0]+1,P[i].l)-b;
		P[i].r=lower_bound(b+1,b+b[0]+1,P[i].r)-b;
		tree.Update(P[i].l,P[i].r,1,1,1,b[0]);
		while(tree.t[1].Max==m){
			tree.Update(P[p].l,P[p].r,-1,1,1,b[0]);
			Ans=min(Ans,P[i].val-P[p].val);
			p++;
		}
	}
	printf("%d",(Ans==inf?-1:Ans));
	return 0;
}