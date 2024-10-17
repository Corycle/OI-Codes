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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<ll,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int Lim=1e6+3;
const ll INF=1e18;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
pii Ans;
int n,m,Pos,a[N];
struct Tree{
	ll c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<N;x+=lowbit(x))c[x]+=y;}
	ll Ask(int x){ll ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	ll Query(int l,int r){return Ask(r)-Ask(l-1);}
}t1,t2;
void Update(int pos,int x){t1.Add(a[pos],x);t2.Add(a[pos],x*a[pos]);}
ll Calc(int x){
	ll v1=t1.Query(1,x)*x-t2.Query(1,x);
	ll v2=t2.Query(x,Lim)-t1.Query(x,Lim)*x;
	return v1+v2;
}
pii Solve(){
	int l=1,r=Lim-1,pos=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(t1.Query(1,mid)>=(m+1)/2){pos=mid;r=mid-1;}
		else l=mid+1;
	}
	return min(mp(Calc(pos+1),pos+1),mp(Calc(pos),pos));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Ans=mp(INF,0);
	for(int i=1;i<=n;i++)a[i]=read()+1;
	for(int i=1;i<=m;i++)Update(i,1);
	for(int i=1;i<=n-m+1;i++){
		pii tmp=Solve();if(Ans>tmp){Ans=tmp;Pos=i;}
		if(i+m<=n){Update(i,-1);Update(i+m,1);}
	}
	printf("%lld\n",Ans.fst);
//	for(int i=1;i<=m;i++)a[Pos+i-1]=Ans.scd;
//	for(int i=1;i<=n;i++)printf("%d\n",a[i]-1);
	return 0;
}
