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
ll n,c[200005],m;
ll l1[200005],r1[200005];
ll l2[200005],r2[200005];
struct node{
	ll x,y;
}a[200005];
ll lowbit(ll x){
	return (x&(-x));
}
void Add(ll x,ll y){
	for(ll i=x;i<=m;i+=lowbit(i)){
		c[i]+=y;
	}
}
ll Ask(ll x){
	if(x==0)return 0;
	ll ans=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll n=read();
	for(ll i=1;i<=n;i++){
		a[i].x=i;
		a[i].y=read();
		m=max(m,a[i].y);
	}
	ll ans=0;
	
	for(ll i=1;i<=n;i++){
		Add(a[i].y,1);
		l2[i]=Ask(a[i].y-1);
		r1[i]=i-Ask(a[i].y);
	}
	memset(c,0,sizeof(c));
	for(ll i=n;i>=1;i--){
		Add(a[i].y,1);
		r2[i]=Ask(a[i].y-1);
		l1[i]=(n-i+1)-Ask(a[i].y);
	}
	
	ll ans1=0,ans2=0;
	for(ll i=1;i<=n;i++){
		ans1+=l1[i]*r1[i];
		ans2+=l2[i]*r2[i];
	}
	printf("%lld %lld",ans1,ans2);
	return 0;
}