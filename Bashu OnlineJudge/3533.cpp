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
#define inf 0x3f3f3f3f
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=(s<<1)+(s<<3)+(c^'0');c=getchar();}
	return s*f;
}
ll n,m,a[1000005];
bool flag;
struct tree{
	ll minn,bj;
}t[4000005];
void build(ll num,ll l,ll r){
	if(l==r){
		t[num].minn=a[l];
		return;
	}
	ll mid=(l+r)>>1;
	build(lson);
	build(rson);
	t[num].minn=min(t[num<<1].minn,t[num<<1|1].minn);
}
void pushdown(ll num){
	t[num<<1].bj+=t[num].bj;
	t[num<<1|1].bj+=t[num].bj;
	t[num].bj=0;
}
void add(ll x,ll y,ll z,ll num,ll l,ll r){
	if(x>r||y<l)return;
	if(x<=l&&r<=y){
		t[num].minn-=t[num].bj+z;
		if(l!=r){
			t[num<<1].bj+=t[num].bj+z;
			t[num<<1|1].bj+=t[num].bj+z;
		}
		t[num].bj=0;
		return;
	}
	if(t[num].bj)pushdown(num);
	ll mid=(l+r)>>1;
	add(x,y,z,lson);
	add(x,y,z,rson);
	t[num].minn=min(t[num].minn,min(t[num<<1].minn-t[num<<1].bj,t[num<<1|1].minn-t[num<<1|1].bj));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	for(ll i=1;i<=m;i++){
		ll z=read(),x=read(),y=read();
		add(x,y,z,1,1,n);
		if(t[1].minn<0){
			printf("-1\n%lld",i);
			return 0;
		}
	}
	printf("0");
	return 0;
}