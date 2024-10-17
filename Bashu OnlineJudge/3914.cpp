#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,d,top;
ll a[N],X[N],sum[N];
struct node{ll x,y;}st[N];
double G(node a,node b){
	return (double)(a.y-b.y)/(a.x-b.x);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();d=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		X[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	double ans=0;
	for(ll i=1;i<=n;i++){
		node t=(node){d*i,sum[i-1]};
		while(top&&G(st[top],st[top-1])>G(t,st[top]))top--;
		st[++top]=t;t=(node){X[i]+d*i,sum[i]};
		//维护下凸壳 
		ll l=1,r=top;
		while(l+3<=r){
			ll mid1=l+(r-l)/3;
			ll mid2=r-(r-l)/3;
			if(G(st[mid1],t)<=G(st[mid2],t))l=mid1;
			else r=mid2;
		}
		double Max=-inf;
		for(ll j=l;j<=r;j++){
			Max=max(Max,G(st[j],t));
		}
		ans+=Max;
	}
	printf("%.0lf",ans);
	return 0;
}
/*
	https://blog.csdn.net/ssoi_hta/article/details/8994560
*/