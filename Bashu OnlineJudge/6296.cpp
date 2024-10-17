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
const ll N=500005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,lst,a[N];
struct BIT_Tree{
	const ll Lim=5e5;ll c[N];
	ll lowbit(ll x){return x&(-x);}
	void Add(ll x,ll y){for(;x<=Lim;x+=lowbit(x))c[x]+=y;}
	ll Ask(ll x){ll tmp=0;for(;x>=1;x-=lowbit(x))tmp+=c[x];return tmp;}
	void Update(ll l,ll r,ll addv){Add(l,addv);Add(r+1,-addv);}
}tree;
int main(){
//	freopen("patrick.in","r",stdin);
//	freopen("patrick.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++){
		if(a[i-1]<a[i])tree.Update(a[i-1]+1,a[i],1);
	}
	char op[5];
	while(m--){
		scanf("%s",op);
		ll pos=read()^lst;
		if(op[0]=='Q'){
			lst=tree.Ask(pos);
			printf("%lld\n",lst);
		}
		if(op[0]=='C'){
			if(a[pos-1]<a[pos])tree.Update(a[pos-1]+1,a[pos],-1);
			if(a[pos]<a[pos+1])tree.Update(a[pos]+1,a[pos+1],-1);
			a[pos]=read()^lst;
			if(a[pos-1]<a[pos])tree.Update(a[pos-1]+1,a[pos],1);
			if(a[pos]<a[pos+1])tree.Update(a[pos]+1,a[pos+1],1);
		}
	}
	return 0;
}