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
ll n,m;
ll c0[100005],c1[100005],s[100005];
ll lowbit(ll x){
	return (x&(-x));
}
void Add(ll c[],ll x,ll y){
	for(ll i=x;i<=n;i+=lowbit(i)){
		c[i]+=y;
	}
}
ll Ask(ll c[],ll x){
	ll ans=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
ll Sum(ll x){
	return s[x]+(x+1)*Ask(c0,x)-Ask(c1,x);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		s[i]=s[i-1]+read();
	}
	while(m--){
		char p[1];
		scanf("%s",p);
		if(p[0]=='Q'){
			ll l=read(),r=read();
			ll ans=Sum(r)-Sum(l-1);
			printf("%lld\n",ans);
		}
		if(p[0]=='C'){
			ll l=read(),r=read(),x=read();
			Add(c0,l,x);
			Add(c0,r+1,-x);
			Add(c1,l,l*x);
			Add(c1,r+1,-(r+1)*x);
		}
	}
	return 0;
}