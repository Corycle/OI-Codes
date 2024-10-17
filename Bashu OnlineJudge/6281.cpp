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
const ll inf=0x3f3f3f3f;
const ll Mod=32767;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,Ans;
ll Ax,Ay,Az,Bx,By,Bz,fa[N];
struct Node1{ll x,val;}A[N],B[N];
struct Node2{ll x,y,val;}G[N];
bool cmp1(Node1 x,Node1 y){return x.val<y.val;}
bool cmp2(Node2 x,Node2 y){return x.val<y.val;}
ll Find(ll x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
ll Sqr(ll x){return x*x;}
int main(){
//	freopen("road.in","r",stdin);
//	freopen("road.out","w",stdout);
	n=read();
	A[1].val=read();A[2].val=read();Ax=read();Ay=read();Az=read();
	B[1].val=read();B[2].val=read();Bx=read();By=read();Bz=read();
	for(ll i=3;i<=n;i++){
		A[i].val=(Ax*A[i-1].val%Mod+Ay*A[i-2].val%Mod+Az)%Mod;
		B[i].val=(Bx*B[i-1].val%Mod+By*B[i-2].val%Mod+Bz)%Mod;
	}
	for(ll i=1;i<=n;i++)fa[i]=i;
	for(ll i=1;i<=n;i++)A[i].x=i;
	for(ll i=1;i<=n;i++)B[i].x=i;
	sort(A+1,A+n+1,cmp1);
	sort(B+1,B+n+1,cmp1);
	for(ll i=1;i<=n;i++){
		ll x=A[i].x,y=B[i].x;
		fa[Find(x)]=Find(y);
		Ans=max(Ans,Sqr(A[i].val)-Sqr(B[i].val));
	}
	for(ll i=1;i<n;i++){
		G[i]=(Node2){A[i+1].x,B[i].x,Sqr(A[i+1].val)-Sqr(B[i].val)};
	}
	sort(G+1,G+n,cmp2);
	for(ll i=1;i<n;i++){
		ll x=G[i].x,y=G[i].y;
		if(Find(x)==Find(y))continue;
		fa[Find(x)]=Find(y);
		Ans=max(Ans,G[i].val);
	}
	printf("%lld",Ans);
	return 0;
}