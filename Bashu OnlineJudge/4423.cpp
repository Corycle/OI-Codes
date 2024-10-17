/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
#define Mex(x) (tree.Ask(x,1,1,n))
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int a[N],Ans[N],lst[N],nxt[N],mex[N];
struct Answer{int l,r;double val;}P[N];
struct Segment_Tree{
	struct Tree{int Min;}t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p].Min=mex[l];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p].Min=inf;
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			t[p].Min=min(t[p].Min,z);
			return;
		}
		int mid=(l+r)>>1;
		Update(x,y,z,lson);
		Update(x,y,z,rson);
	}
	int Ask(int x,int p,int l,int r){
		if(x<l||x>r)return inf;
		if(l==r)return t[p].Min;
		int mid=(l+r)>>1,ans=t[p].Min;
		ans=min(ans,Ask(x,lson));
		ans=min(ans,Ask(x,rson));
		return ans;
	}
}tree;
int root[N],tot;
double Min[N*20];
struct Tree{int l,r;}t[N*20];
void Insert(int &x,int y,int pos,double val,int l,int r){
	x=++tot;t[x]=t[y];Min[x]=min(Min[y],val);
	if(l==r)return;int mid=(l+r)>>1;
	if(pos<=mid)Insert(t[x].l,t[y].l,pos,val,l,mid);
	else Insert(t[x].r,t[y].r,pos,val,mid+1,r);
}
double Ask(int x,int ql,int qr,int l,int r){
	if(qr<l||ql>r||!x)return 1;
	if(ql<=l&&r<=qr)return Min[x];
	int mid=(l+r)>>1;
	return min(Ask(t[x].l,ql,qr,l,mid),Ask(t[x].r,ql,qr,mid+1,r));
}
int Find(int x){
	int Max=Mex(x);
	int l=x+1,r=n,ans=x;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Mex(mid)<=Max){
			l=mid+1;
			ans=mid;
		}
		else r=mid-1;
	}
	return ans;
}
int main(){
//	freopen("rich.in","r",stdin);
//	freopen("rich.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		nxt[lst[a[i]]]=i;lst[a[i]]=i;
		for(int j=mex[i-1];j<=n;j++){
			if(!lst[j]){mex[i]=j;break;}
		}
	}
	for(int i=1;i<=n;i++)if(!nxt[i])nxt[i]=n+1;
	tree.Build(1,1,n);
	for(int i=1;i<=n;i++){
		int x=i;
		while(x<=n){
			int y=Find(x);
			int A=Mex(x),B=x-i+1;
			double val=(double)(B+1-A)/(B+1+A);
			P[++cnt]=(Answer){i,x,val};x=y+1;
		}
		if(i+1<=nxt[i]-1)tree.Update(i+1,nxt[i]-1,a[i],1,1,n);
	}
	Min[0]=1;
	for(int i=cnt;i>=1;i--){
		Insert(root[P[i].l],root[P[i+1].l],P[i].r,P[i].val,1,n);
	}
	while(m--){
		int l=read(),r=read();
		printf("%.8lf\n",Ask(root[l],1,r,1,n));
	}
	return 0;
}