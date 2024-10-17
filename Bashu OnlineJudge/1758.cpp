/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
using namespace std;
const ll inf=0x3f3f3f3f;
const ll M=4e6;
const ll N=10;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll n,m,Ans;
ll tot[2],k[2][N],p[2][N],a[2][M];
inline ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot;
		tot=tot*tot;
		y>>=1;
	}
	return ans;
}
inline void DFS(ll depth,ll sum,ll type){
	if(depth>tot[type]){
		a[type][++a[type][0]]=sum;
		return;
	}
	for(ll i=1;i<=m;i++){
		DFS(depth+1,sum+k[type][depth]*Pow(i,p[type][depth]),type);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		if(i<=n/2){tot[0]++;k[0][tot[0]]=read();p[0][tot[0]]=read();}
		if(i>n/2){tot[1]++;k[1][tot[1]]=-read();p[1][tot[1]]=read();}
	}
	DFS(1,0,0);DFS(1,0,1);
	sort(a[0]+1,a[0]+a[0][0]+1);
	sort(a[1]+1,a[1]+a[1][0]+1);
	for(ll i=1;i<=a[0][0];i++){
		ll l=lower_bound(a[1]+1,a[1]+a[1][0]+1,a[0][i])-a[1];
		ll r=upper_bound(a[1]+1,a[1]+a[1][0]+1,a[0][i])-a[1]-1;
		if(l<=r)Ans+=r-l+1;
	}
	printf("%lld",Ans);
	return 0;
}