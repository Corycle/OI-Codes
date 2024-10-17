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
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
priority_queue<int>q;
int n,m,tot,a[N],Ans[N],vis[N];
struct Segment_Tree{
	int t[N*4];
	void Pushup(int p){t[p]=(a[t[p<<1]]>a[t[p<<1|1]]?t[p<<1]:t[p<<1|1]);}
	void Build(int p,int l,int r){
		if(l==r){t[p]=l;return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Update(int x,int p,int l,int r){
		if(l==r){t[p]=l;return;}
		int mid=(l+r)>>1;(x<=mid?Update(x,lson):Update(x,rson));Pushup(p);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p];
		int mid=(l+r)>>1;
		int ansl=Query(x,y,lson);
		int ansr=Query(x,y,rson);
		return a[ansl]>a[ansr]?ansl:ansr;
	}
}tree;
bool Check(int x){
	if(!x||vis[x])return false;
	return tree.Query(x-m+1,x+m-1,1,1,n)==x;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();tot=n;
	for(int i=1;i<=n;i++)a[i]=read();tree.Build(1,1,n);
	for(int i=1;i<=n;i++)if(Check(i)){vis[i]=1;q.push(i);}
	while(q.size()){
		int x=q.top();q.pop();
		Ans[x]=tot;tot--;a[x]=-inf;tree.Update(x,1,1,n);
		int l=tree.Query(x-m+1,x-1,1,1,n);if(Check(l)){vis[l]=1;q.push(l);}
		int r=tree.Query(x+1,x+m-1,1,1,n);if(Check(r)){vis[r]=1;q.push(r);}
	}
	for(int i=1;i<=n;i++)printf("%d\n",Ans[i]);
	return 0;
}
