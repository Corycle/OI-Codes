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
const ll inf=9e18;
const ll N=1000005;
const ll M=25;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,Ans;
ll b[M][N],f[N],q[N],a[N],id[N];
bool cmp(ll x,ll y){return (a[x]==a[y]?x<y:a[x]<a[y]);}
ll Sum(ll x){return (1+x)*x/2;}
ll F(ll x){return f[x]-Sum(x);}
void CDQ(ll l,ll r,ll depth){
	if(l==r){
		ll p=id[l];
		f[p]=max(f[p],a[p]-Sum(p-1));
		Ans=max(Ans,f[p]-Sum(n-p));
		return;
	}
	ll mid=(l+r)>>1;
	CDQ(l,mid,depth+1);
	ll pos=l-1,L=1,R=1;
	for(ll i=mid+1;i<=r;i++){
		ll x=b[depth+1][i];
		while(pos<mid&&b[depth+1][pos+1]<x){
			ll y=b[depth+1][++pos];
			while(L<R&&(F(y)-F(q[R-1]))*(q[R-1]-q[R])<=(F(q[R])-F(q[R-1]))*(q[R-1]-y))R--;
			q[++R]=y;
		}
		while(L<R&&(F(q[L])-F(q[L+1]))<=x*(q[L+1]-q[L]))L++;
		if(L<=R)f[x]=max(f[x],f[q[L]]+a[x]-Sum(x-q[L]-1));
	}
	CDQ(mid+1,r,depth+1);
}
void Divide(ll l,ll r,ll depth){
	if(l==r){b[depth][l]=id[l];return;}
	ll mid=(l+r)>>1;
	Divide(l,mid,depth+1);
	Divide(mid+1,r,depth+1);
	ll pos=l,t1=l,t2=mid+1;
	while(t1<=mid&&t2<=r){
		if(b[depth+1][t1]<=b[depth+1][t2])b[depth][pos++]=b[depth+1][t1++];
		else b[depth][pos++]=b[depth+1][t2++];
	}
	while(t1<=mid)b[depth][pos++]=b[depth+1][t1++];
	while(t2<=r)b[depth][pos++]=b[depth+1][t2++];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Ans=-Sum(n);
	for(ll i=1;i<=n;i++){
		a[i]=read();
		f[i]=-inf;
		id[i]=i;
	}
	sort(id+1,id+n+1,cmp);
	Divide(1,n,1);
	CDQ(1,n,1);
	printf("%lld",Ans);
	return 0;
}