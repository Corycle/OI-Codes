#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,blk,num;
ll a[N],t[N],st[N],ed[N],pos[N],dlt[N];
void Reset(ll x){
	for(ll i=st[x];i<=ed[x];i++)t[i]=a[i];
	sort(t+st[x],t+ed[x]+1);
}
ll Ask(ll l,ll r,ll c){
	ll ans=-inf,x=pos[l],y=pos[r];
	if(x==y)for(ll i=l;i<=r;i++){if(a[i]+dlt[pos[i]]<c)ans=max(ans,a[i]+dlt[pos[i]]);}
	else{
		for(ll i=l;i<=ed[x];i++)if(a[i]+dlt[pos[i]]<c)ans=max(ans,a[i]+dlt[pos[i]]);
		for(ll i=st[y];i<=r;i++)if(a[i]+dlt[pos[i]]<c)ans=max(ans,a[i]+dlt[pos[i]]);
		for(ll i=x+1;i<=y-1;i++){
			ll p=lower_bound(t+st[i],t+ed[i]+1,c-dlt[i])-t-1;
			if(st[i]<=p&&p<=ed[i])ans=max(ans,t[p]+dlt[i]);
		}
	}
	if(ans==-inf)ans=-1;
	return ans;
}
void Add(ll l,ll r,ll c){
	ll x=pos[l],y=pos[r];
	if(x==y)for(ll i=l;i<=r;i++)a[i]+=c;
	else{
		for(ll i=l;i<=ed[x];i++)a[i]+=c;
		for(ll i=st[y];i<=r;i++)a[i]+=c;
		for(ll i=x+1;i<=y-1;i++)dlt[i]+=c;
	}
	Reset(x);Reset(y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();blk=num=(ll)(sqrt(n));
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=num;i++){st[i]=ed[i-1]+1;ed[i]=ed[i-1]+blk;}
	if(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=n;}
	for(ll i=1;i<=num;i++){
		for(ll j=st[i];j<=ed[i];j++){
			pos[j]=i;
		}
	}
	for(ll i=1;i<=num;i++)Reset(i);
	for(ll i=1;i<=n;i++){
		ll op=read(),l=read(),r=read(),c=read();
		if(op==0)Add(l,r,c);
		if(op==1)printf("%lld\n",Ask(l,r,c));
	}
	return 0;
}