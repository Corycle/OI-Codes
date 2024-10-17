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
const int Lim=1000000000;
const int inf=0x3f3f3f3f;
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,tot,L[N],R[N],b[N];
struct Segment_Tree{
	struct Tree{int s,tag,sum[2];}t[N*4];
	void Pushup(int p){
		t[p].s=t[p<<1].s+t[p<<1|1].s;
		t[p].sum[0]=t[p<<1].sum[0]+t[p<<1|1].sum[0];
		t[p].sum[1]=t[p<<1].sum[1]+t[p<<1|1].sum[1];
	}
	void update(int p,int l,int r,int addv){
		t[p].tag+=addv;
		t[p].s=b[r+1]-b[l];
		t[p].sum[1]=t[p].sum[0];
		t[p].sum[0]=0;
	}
	void Pushdown(int p,int l,int r){
		if(t[p].tag){
			int mid=(l+r)>>1;
			update(lson,t[p].tag);
			update(rson,t[p].tag);
			t[p].tag=0;
		}
	}
	void Build(int p,int l,int r){
		t[p].sum[0]=b[r+1]-b[l];if(l==r)return;
		int mid=(l+r)>>1;Build(lson);Build(rson);
	}
	void Update(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,l,r,1);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update(x,y,lson);Update(x,y,rson);Pushup(p);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum[1];
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		L[i]=read();
		R[i]=read()-1;
		b[++tot]=L[i];
		b[++tot]=R[i];
		b[++tot]=R[i]+1;
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	b[tot+1]=Lim;tree.Build(1,1,tot);
	for(int i=1;i<=n;i++){
		L[i]=lower_bound(b+1,b+tot+1,L[i])-b;
		R[i]=lower_bound(b+1,b+tot+1,R[i])-b;
		tree.Update(L[i],R[i],1,1,tot);
	}
	int Max=0;
	for(int i=1;i<=n;i++){
		Max=max(Max,tree.t[1].s-tree.Query(L[i],R[i],1,1,tot));
	}
	printf("%d",Max);
	return 0;
}