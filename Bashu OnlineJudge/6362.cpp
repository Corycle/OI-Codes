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
const ll inf=0x3f3f3f3f;
const double Pi=acos(-1);
const double eps=1e-12;
const ll N=50005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double a[N];
ll n,m,tot,t[N];
struct Node{double x,y,b;ll pos;}P[N];
bool cmp(ll x,ll y){return P[x].b<P[y].b;}
struct BIT{
	ll c[N];
	ll lowbit(ll x){return x&(-x);}
	void Add(ll x){for(;x<=tot;x+=lowbit(x))c[x]++;}
	ll Ask(ll x){ll ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
ll Check(double mid){
	double k=0;
	if(mid<=Pi/2)k=tan(mid);
	else k=-tan(Pi-mid);
	ll ans=0;
	for(ll i=1;i<=n;i++){
		t[i]=i;
		P[i].b=P[i].y-P[i].x*k;
	}
	sort(t+1,t+n+1,cmp);
	if(k<0)for(ll i=1;i<=n/2;i++)swap(t[i],t[n-i+1]);
	for(ll i=1;i<=tot;i++)tree.c[i]=0;
	for(ll i=1;i<=n;i++){
		ans+=i-1-tree.Ask(P[t[i]].pos-1);
		tree.Add(P[t[i]].pos);
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		P[i].x=read();
		P[i].y=read();
		a[++tot]=P[i].y;
	}
	sort(a+1,a+tot+1);
	tot=unique(a+1,a+tot+1)-a-1;
	for(ll i=1;i<=n;i++){
		P[i].pos=lower_bound(a+1,a+tot+1,P[i].y)-a;
	}
	/*================*/
	m=(n-1)*n/2;
	double l=0,r=Pi,ans1=0,ans2=0;
	while(l+eps<r){
		double mid=(l+r)/2.0;
		if(Check(mid)>=(m+1)/2){ans1=mid;r=mid;}
		else l=mid;
	}
	if(m&1){printf("%.10lf",ans1);return 0;}
	/*================*/
	l=0;r=Pi;
	while(l+eps<r){
		double mid=(l+r)/2.0;
		if(Check(mid)<=(m+1)/2){ans2=mid;l=mid;}
		else r=mid;
	}
	printf("%.10lf",(ans1+ans2)/2.0);
	return 0;
}