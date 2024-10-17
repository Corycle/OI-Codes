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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
struct Tree{
	ll sum;
}t[N*4];
struct Ques{
	ll l,r,type,val;
}q[N];
void Build(ll p,ll l,ll r){
	t[p].sum=1;
	if(l==r)return;
	ll mid=(l+r)>>1;
	Build(lson);
	Build(rson);
}
void Add(ll x,ll y,ll z,ll p,ll l,ll r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		t[p].sum=t[p].sum*z%m;
		return;
	}
	ll mid=(l+r)>>1;
	Add(x,y,z,lson);
	Add(x,y,z,rson);
}
void Solve(ll sum,ll p,ll l,ll r){
	sum=sum*t[p].sum%m;
	if(l==r){
		printf("%lld\n",sum);
		return;
	}
	ll mid=(l+r)>>1;
	Solve(sum,lson);
	Solve(sum,rson);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		memset(q,0,sizeof(q));
		n=read();m=read();
		for(ll i=1;i<=n;i++){
			ll op=read(),x=read();
			if(op==1){
				q[i].l=i;
				q[i].val=x;
				q[i].type=1;
			}
			else q[x].r=i;
		}
		Build(1,1,n);
		for(ll i=1;i<=n;i++){
			if(q[i].l&&!q[i].r)q[i].r=n+1;
			if(q[i].type){
				Add(q[i].l,q[i].r-1,q[i].val,1,1,n);
			}
		}
		Solve(1,1,1,n);
	}
	return 0;
}