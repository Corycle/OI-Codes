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
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=100005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll n,m,blk,num;
ll w[N],t[N],st[N],ed[N],pos[N],dlt[N];
void Pushup(ll x){
	if(dlt[x]==-inf)return;
	for(ll i=st[x];i<=ed[x];i++)w[i]=dlt[x];
	dlt[x]=-inf;
}
void Reset(ll x){
	for(ll i=st[x];i<=ed[x];i++)t[i]=(dlt[x]!=-inf?dlt[x]:w[i]);
	sort(t+st[x],t+ed[x]+1);
}
void Prepare(){
	blk=num=(ll)(sqrt(n));
	for(ll i=1;i<=num;i++){st[i]=ed[i-1]+1;ed[i]=ed[i-1]+blk;}
	if(ed[num]<n){num++;st[num]=ed[num-1]+1;ed[num]=n;}
	for(ll i=1;i<=num;i++){
		for(ll j=st[i];j<=ed[i];j++)pos[j]=i;
		Reset(i);
	}
}
ll Count1(ll x,ll l,ll r,ll data){
	if(dlt[x]!=-inf)return dlt[x]>data?0:(r-l+1);
	ll cnt=0;
	for(ll i=l;i<=r;i++)cnt+=(w[i]<=data);
	return cnt;
}
ll Count2(ll x,ll l,ll r,ll data){
	if(dlt[x]!=-inf)return dlt[x]>data?0:(r-l+1);
	return upper_bound(t+l,t+r+1,data)-t-l;
}
ll Ask(ll l,ll r,ll data){
	ll ans=0,x=pos[l],y=pos[r];
	if(x==y)ans+=Count1(x,l,r,data);
	else{
		ans+=Count1(x,l,ed[x],data);
		ans+=Count1(y,st[y],r,data);
		for(ll i=x+1;i<=y-1;i++){
			ans+=Count2(i,st[i],ed[i],data);
		}
	}
	return ans;
}
void Change(ll l,ll r,ll data){
	ll x=pos[l],y=pos[r];
	Pushup(x);Pushup(y);
	if(x==y)for(ll i=l;i<=r;i++)w[i]=data;
	else{
		for(ll i=l;i<=ed[x];i++)w[i]=data;
		for(ll i=st[y];i<=r;i++)w[i]=data;
		for(ll i=x+1;i<=y-1;i++)dlt[i]=data;
	}
	Reset(x);Reset(y);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){w[i]=read();dlt[i]=-inf;}
	Prepare();
	m=read();
	while(m--){
		ll op=read();
		ll x=read(),y=read(),z=read();
		if(op==0)Change(x,y,z);
		if(op==1)printf("%lld\n",Ask(x,y,z));
	}
	return 0;
}