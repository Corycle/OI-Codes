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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt,Ans,a[N],b[N];
struct Node{int y,l,r,t;}P[N];
bool cmp(Node A,Node B){return A.y!=B.y?A.y<B.y:(A.t!=B.t?A.t<B.t:(A.l!=B.l?A.l<B.l:A.r<B.r));}
struct Tree{int Max,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int v){t[p].Max+=v;t[p].tag+=v;}
	void Pushup(int p){t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);Pushup(p);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int num=read();
		for(int j=1;j<=num;j++)a[j]=b[++tot]=read();a[num+1]=a[1];
		for(int j=3;j<=num+1;j+=2)P[++cnt]=(Node){a[j-1],a[j-2],a[j],(a[j-2]<a[j]?1:-1)};
	}
	sort(b+1,b+tot+1);tot=unique(b+1,b+tot+1)-b-1;sort(P+1,P+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		P[i].l=lower_bound(b+1,b+tot+1,P[i].l)-b;
		P[i].r=lower_bound(b+1,b+tot+1,P[i].r)-b;
		int l=min(P[i].l,P[i].r),r=max(P[i].l,P[i].r);
		tree.Update(l,r-1,P[i].t,1,1,tot);
		Ans=max(Ans,tree.t[1].Max);
	}
	printf("%d\n",Ans);
	return 0;
}
