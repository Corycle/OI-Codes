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
const ll INF=1e18;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
ll a[N],Ans;
struct Segment_Tree{
	ll t[N*4];
	void Build(int p,int l,int r){
		if(l==r){
			Ans+=abs(a[l]);
			if(l>1)t[p]=max(0ll,a[l])+max(0ll,-a[l-1]);
			return;
		}
		int mid=(l+r)>>1;Build(lson);Build(rson);t[p]=min(t[p<<1],t[p<<1|1]);
	}
	void Update(int x,int v,int p,int l,int r){
		if(l==r){
			Ans+=abs(a[l]+v)-abs(a[l]);a[l]+=v;
			if(l>1)t[p]=max(0ll,a[l])+max(0ll,-a[l-1]);
			if(v&&x<n-1)Update(x+1,0,1,1,n-1);
			return;
		}
		int mid=(l+r)>>1;
		x<=mid?Update(x,v,lson):Update(x,v,rson);t[p]=min(t[p<<1],t[p<<1|1]);
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
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)a[i]=a[i+1]-a[i];
	tree.Build(1,1,n-1);
	m=read();
	while(m--){
		int op=read(),l=read(),r=read(),x=read();
		if(op==1){
			if(l==r){
				ll ans=Ans;
				if(l<n)ans=ans-abs(a[l])+abs(a[l]-x);
				if(l>1)ans=ans-abs(a[l-1])+abs(a[l-1]+x);
				printf("%lld\n",ans);
			}
			else{
				ll ans=2*(x-tree.Query(max(l,2),r,1,1,n-1));
				if(l==1)ans=max(ans,abs(a[l]-x)-abs(a[l]));
				if(r==n)ans=max(ans,abs(a[r-1]+x)-abs(a[r-1]));
				printf("%lld\n",Ans+max(0ll,ans));
			}
		}
		else{
			if(l>1)tree.Update(l-1,x,1,1,n-1);
			if(r<n)tree.Update(r,-x,1,1,n-1);
		}
	}
	return 0;
}
