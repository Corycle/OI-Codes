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
const ll inf=0x3f3f3f3f;
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,p,T,tot,Ans,a[N],b[N];
ll L0[N],L1[N],R0[N],R1[N];
struct Tree{ll sum,tot;};
struct Segment_Tree{
	Tree t[N*4];
	void Update(ll x,ll y,ll p,ll l,ll r){
		if(x<l||x>r)return;
		t[p].sum+=b[x]*y;t[p].tot+=y;
		if(l==r)return;ll mid=(l+r)>>1;
		Update(x,y,lson);Update(x,y,rson);
	}
	ll Ask(ll k,ll p,ll l,ll r){
		if(l==r)return min(k,t[p].tot)*b[l];
		ll mid=(l+r)>>1;
		if(k<=t[p<<1|1].tot)return Ask(k,rson);
		return Ask(k-t[p<<1|1].tot,lson)+t[p<<1|1].sum;
	}
}tree;
void Divide(ll l,ll r,ll ql,ll qr,ll *F,ll f){
	ll mid=(l+r)>>1,pos=ql;
	for(ll i=ql;i<=qr;i++){
		ll t=mid-(i-p)*f;
		tree.Update(a[i],1,1,1,tot);
		if(t>=0){
			ll tmp=tree.Ask(t,1,1,tot);
			if(tmp>F[mid]){F[mid]=tmp;pos=i;}
		}
	}
	for(ll i=pos;i<=qr;i++)tree.Update(a[i],-1,1,1,tot);
	if(r>mid)Divide(mid+1,r,pos,qr,F,f);
	for(ll i=ql;i<pos;i++)tree.Update(a[i],-1,1,1,tot);
	if(l<mid)Divide(l,mid-1,ql,pos,F,f);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();p=read()+1;T=read();
	for(ll i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);tot=unique(b+1,b+n+1)-b-1;
	for(ll i=1;i<=n;i++)a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	Divide(0,T,p,n,R0,1);
	Divide(0,T,p,n,R1,2);
	if(p!=1){
		p=n-(p-1)+1;
		reverse(a+1,a+n+1);
		Divide(0,T,p,n,L0,1);
		Divide(0,T,p,n,L1,2);
	}
	Ans=R0[T];
	for(ll i=0;i<=T-2;i++)Ans=max(Ans,L1[i]+R0[T-i-2]);
	for(ll i=0;i<=T-1;i++)Ans=max(Ans,R1[i]+L0[T-i-1]);
	printf("%lld",Ans);
	return 0;
}