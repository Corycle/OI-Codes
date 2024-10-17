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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N];
int n,m,p1,p2,top;
int a[N],L[N],R[N],st[N];
struct Ques{int l,r,id;}Q[N];
bool cmpL(Ques A,Ques B){return A.l>B.l;}
bool cmpR(Ques A,Ques B){return A.r<B.r;}
struct Tree{ll sum,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int l,int r,ll val){
		t[p].tag+=val;
		t[p].sum+=(r-l+1)*val;
	}
	void Pushdown(int p,int l,int r){
		if(t[p].tag){
			int mid=(l+r)>>1;
			update(lson,t[p].tag);
			update(rson,t[p].tag);
			t[p].tag=0;
		}
	}
	void Clear(int p,int l,int r){
		t[p]=(Tree){0,0};
		if(l==r)return;
		int mid=(l+r)>>1;
		Clear(lson);Clear(rson);
	}
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,l,r,val);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update(x,y,val,lson);Update(x,y,val,rson);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
	}
	ll Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree;
vector<pii>G1[N],G2[N];
void Prepare(){
	a[0]=a[n+1]=inf;
	st[top=1]=0;
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<=a[i])top--;
		L[i]=st[top];st[++top]=i;
	}
	st[top=1]=n+1;
	for(int i=n;i>=1;i--){
		while(top&&a[st[top]]<=a[i])top--;
		R[i]=st[top];st[++top]=i;
	}
	for(int i=1;i<=n;i++){
		G1[L[i]].push_back(mp(R[i],i));
		G2[R[i]].push_back(mp(L[i],i));
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p1=read();p2=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		Q[i].id=i;
		Q[i].l=read();
		Q[i].r=read();
		Ans[i]=1ll*(Q[i].r-Q[i].l)*p1;
	}
	Prepare();
	sort(Q+1,Q+m+1,cmpR);
	for(int r=1,p=1;r<=n;r++){
		for(auto x:G2[r])tree.Update(x.fst,x.fst,p1,1,1,n);
		for(auto x:G2[r])tree.Update(x.fst+1,x.scd-1,p2,1,1,n);
		while(p<=m&&Q[p].r==r){Ans[Q[p].id]+=tree.Query(Q[p].l,Q[p].r,1,1,n);p++;}
	}
	tree.Clear(1,1,n);
	sort(Q+1,Q+m+1,cmpL);
	for(int l=n,p=1;l>=1;l--){
		for(auto x:G1[l])tree.Update(x.scd+1,x.fst-1,p2,1,1,n);
		while(p<=m&&Q[p].l==l){Ans[Q[p].id]+=tree.Query(Q[p].l,Q[p].r,1,1,n);p++;}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}