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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const ll inf=0x3f3f3f3f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,ans,a[10005];
ll c[10005][1005];
ll lowbit(ll x){
	return x&(-x);
}
void Add(ll x,ll y,ll z){
	for(ll i=x;i<=n;i+=lowbit(i)){
		for(ll j=y;j<=1000;j+=lowbit(j)){
			c[i][j]+=z;
		}
	}
}
ll Ask(ll x,ll y){
	ll tot=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		for(ll j=y;j>=1;j-=lowbit(j)){
			tot+=c[i][j];
		}
	}
	return tot;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		ll x=i,y=read();
		Add(x,y,1);
		ans+=Ask(x-1,1000)-Ask(x-1,y);
		a[x]=y;
	}
	while(m--){
		ll x=read(),y=a[x];
		ll tot1=Ask(x-1,1000)-Ask(x-1,y)+Ask(n,y-1)-Ask(x,y-1);
		Add(x,y,-1);
		a[x]=y=read();
		Add(x,y,1);
		ll tot2=Ask(x-1,1000)-Ask(x-1,y)+Ask(n,y-1)-Ask(x,y-1);
		ans=ans-tot1+tot2;
		printf("%lld\n",ans);
	}
	return 0;
}