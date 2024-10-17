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
const ll Mod=998244353;
const ll Mul=131;
const ll N=10005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,a[N],P[N];
struct Segment_Tree{
	struct Tree{ll Hash1,Hash2;}t[N*4];
	void Init(){memset(t,0,sizeof(t));}
	void Pushup(ll p,ll l,ll r,ll mid){
		t[p].Hash1=(t[p<<1].Hash1*P[r-mid]%Mod+t[p<<1|1].Hash1)%Mod;
		t[p].Hash2=(t[p<<1|1].Hash2*P[mid-l+1]%Mod+t[p<<1].Hash2)%Mod;
	}
	void Change(ll x,ll p,ll l,ll r){
		if(x<l||x>r)return;
		if(l==r){t[p].Hash1=t[p].Hash2=1;return;}
		ll mid=(l+r)>>1;
		Change(x,lson);Change(x,rson);
		Pushup(p,l,r,mid);
	}
	ll Ask1(ll x,ll y,ll p,ll l,ll r){
		if(x<=l&&r<=y)return t[p].Hash1;
		ll mid=(l+r)>>1;
		if(y<=mid)return Ask1(x,y,lson);
		if(x>mid) return Ask1(x,y,rson);
		ll L=Ask1(x,y,lson),R=Ask1(x,y,rson);
		return (L*P[min(r,y)-mid]%Mod+R)%Mod;
	}
	ll Ask2(ll x,ll y,ll p,ll l,ll r){
		if(x<=l&&r<=y)return t[p].Hash2;
		ll mid=(l+r)>>1;
		if(y<=mid)return Ask2(x,y,lson);
		if(x>mid) return Ask2(x,y,rson);
		ll L=Ask2(x,y,lson),R=Ask2(x,y,rson);
		return (R*P[mid-max(x,l)+1]%Mod+L)%Mod;
	}
}tree;
int main(){
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	ll T=read();P[0]=1;
	for(ll i=1;i<=10000;i++)P[i]=P[i-1]*Mul%Mod;
	while(T--){
		ll flag=0;n=read();tree.Init();
		for(ll i=1;i<=n;i++)a[i]=read();
		for(ll i=1;i<=n;i++){
			tree.Change(a[i],1,1,n);
			if(a[i]==1||a[i]==n)continue;
			int len=min(a[i]-1,n-a[i]);
			ll Hash1=tree.Ask1(a[i]-len,a[i]-1,1,1,n);
			ll Hash2=tree.Ask2(a[i]+1,a[i]+len,1,1,n);
			if(Hash1!=Hash2){flag=1;break;}
		}
		if(flag)printf("Y\n");
		else printf("N\n");
	}
	return 0;
}