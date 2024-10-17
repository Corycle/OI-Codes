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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
map<int,int>lst;
int a[N],Ans[N],nxt[N],mex[N];
struct Ques{int l,r,id;}q[N];
bool cmp(Ques A,Ques B){
	if(A.l==B.l)return A.r<B.r;
	return A.l<B.l;
}
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
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
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
	for(int i=1;i<=m;i++){
		q[i].l=read();
		q[i].r=read();
		q[i].id=i;
	}
	int t=1;q[0].l=1;
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;i++){
		for(int j=q[i-1].l;j<q[i].l;j++){
			tree.Update(j,nxt[j]-1,a[j],1,1,n);
		}
		Ans[q[i].id]=tree.Ask(q[i].r,1,1,n);
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}