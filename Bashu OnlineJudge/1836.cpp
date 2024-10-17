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
const ll INF=1e18;
const int inf=0x3f3f3f3f;
const int N=4e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
ll b[N],Ans[N];
struct Node{int x,y,id;ll t;}P[N],Q[N];
bool cmp(Node A,Node B){return A.x<B.x;}
struct Segment_Tree{
	ll t[N*4];
	void Init(){memset(t,0x3f,sizeof(t));}
	void Update(int x,ll val,int p,int l,int r){
		if(l==r){t[p]=min(t[p],val);return;}int mid=(l+r)>>1;
		x<=mid?Update(x,val,lson):Update(x,val,rson);t[p]=min(t[p<<1],t[p<<1|1]);
	}
	ll Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return INF;
		if(x<=l&&r<=y)return t[p];
		int mid=(l+r)>>1;
		return min(Query(x,y,lson),Query(x,y,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){P[i].x=read();P[i].y=read();P[i].t=read();}
	for(int i=1;i<=m;i++){Q[i].x=read();Q[i].y=read();Q[i].id=i;}
	for(int i=1;i<=n;i++){b[++tot]=P[i].x;b[++tot]=P[i].y;}
	for(int i=1;i<=m;i++){b[++tot]=Q[i].x;b[++tot]=Q[i].y;}
	sort(b+1,b+tot+1);tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;i++){
		P[i].x=lower_bound(b+1,b+tot+1,P[i].x)-b;
		P[i].y=lower_bound(b+1,b+tot+1,P[i].y)-b;
	}
	for(int i=1;i<=m;i++){
		Q[i].x=lower_bound(b+1,b+tot+1,Q[i].x)-b;
		Q[i].y=lower_bound(b+1,b+tot+1,Q[i].y)-b;
	}
	sort(P+1,P+n+1,cmp);sort(Q+1,Q+m+1,cmp);
	for(int i=1;i<=m;i++)Ans[Q[i].id]=abs(b[Q[i].x]-b[Q[i].y]);
	tree.Init();
	for(int i=1,p=1;i<=m;i++){
		while(p<=n&&P[p].x<=Q[i].x){tree.Update(P[p].y,-b[P[p].x]-b[P[p].y]+P[p].t,1,1,tot);p++;}
		Ans[Q[i].id]=min(Ans[Q[i].id],b[Q[i].x]+b[Q[i].y]+tree.Query(1,Q[i].y,1,1,tot));
	}
	tree.Init();
	for(int i=1,p=1;i<=m;i++){
		while(p<=n&&P[p].x<=Q[i].x){tree.Update(P[p].y,-b[P[p].x]+b[P[p].y]+P[p].t,1,1,tot);p++;}
		Ans[Q[i].id]=min(Ans[Q[i].id],b[Q[i].x]-b[Q[i].y]+tree.Query(Q[i].y,tot,1,1,tot));
	}
	tree.Init();
	for(int i=m,p=n;i>=1;i--){
		while(p>=1&&P[p].x>=Q[i].x){tree.Update(P[p].y,b[P[p].x]-b[P[p].y]+P[p].t,1,1,tot);p--;}
		Ans[Q[i].id]=min(Ans[Q[i].id],-b[Q[i].x]+b[Q[i].y]+tree.Query(1,Q[i].y,1,1,tot));
	}
	tree.Init();
	for(int i=m,p=n;i>=1;i--){
		while(p>=1&&P[p].x>=Q[i].x){tree.Update(P[p].y,b[P[p].x]+b[P[p].y]+P[p].t,1,1,tot);p--;}
		Ans[Q[i].id]=min(Ans[Q[i].id],-b[Q[i].x]-b[Q[i].y]+tree.Query(Q[i].y,tot,1,1,tot));
	}
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}
