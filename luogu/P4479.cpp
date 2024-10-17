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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
ll m,b[N];
struct Point{int x,y,id;ll t;}P[N];
bool cmp(Point A,Point B){return A.t!=B.t?A.t<B.t:A.x<B.x;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Clear(){for(int i=1;i<=n;i++)c[i]=0;}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
ll Count(ll k){
	ll ans=0;tree.Clear();
	for(int i=1;i<=n;i++)P[i].t=P[i].y-P[i].x*k;
	sort(P+1,P+n+1,cmp);
	for(int i=1;i<=n;i++){
		ans+=tree.Ask(P[i].id-1);
		tree.Add(P[i].id,1);
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){P[i].x=read();P[i].y=read();b[i]=P[i].x;}
	sort(b+1,b+n+1);
	int tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)P[i].id=lower_bound(b+1,b+tot+1,P[i].x)-b;
	int l=-1e9,r=1e9,ans=-inf;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Count(mid)>=m){ans=mid;l=mid+1;}
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}
