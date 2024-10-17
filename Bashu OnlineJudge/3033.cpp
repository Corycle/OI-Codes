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
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num,blk;
ll t[N],w[N],pos[N];
ll st[1005],ed[1005],dlt[1005];
void Reset(ll x){
	for(int i=st[x];i<=ed[x];i++)t[i]=w[i];
	sort(t+st[x],t+ed[x]+1);
}
void Ask(ll l,ll r,ll c){
	ll ans=0,x=pos[l],y=pos[r];
	if(x==y)for(int i=l;i<=r;i++)ans+=(w[i]+dlt[pos[i]]>=c);
	else{
		for(int i=l;i<=ed[x];i++)ans+=(w[i]+dlt[pos[i]]>=c);
		for(int i=st[y];i<=r;i++)ans+=(w[i]+dlt[pos[i]]>=c);
		for(int i=x+1;i<=y-1;++i){
			ans+=ed[i]-(lower_bound(t+st[i],t+ed[i]+1,c-dlt[i])-t)+1;
		}
	}
	printf("%lld\n",ans);
}
void Add(ll l,ll r,ll c){
	ll x=pos[l],y=pos[r];
	if(x==y)for(int i=l;i<=r;i++)w[i]+=c;
	else{
		for(int i=l;i<=ed[x];i++)w[i]+=c;
		for(int i=st[y];i<=r;i++)w[i]+=c;
		for(int i=x+1;i<=y-1;i++)dlt[i]+=c;
	}
	Reset(x);Reset(y);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)w[i]=read();
	num=blk=(int)(sqrt(n));
	for(int i=1;i<=num;i++){
		st[i]=ed[i-1]+1;
		ed[i]=ed[i-1]+blk;
	}
	if(ed[num]<n){
		num++;
		st[num]=ed[num-1]+1;
		ed[num]=n;
	}
	for(int i=1;i<=num;i++){
		for(int j=st[i];j<=ed[i];j++){
			pos[j]=i;
		}
		Reset(i);
	}
	while(m--){
		char op[2];
		scanf("%s",op);
		ll x=read(),y=read(),c=read();
		if(op[0]=='A')Ask(x,y,c);
		if(op[0]=='M')Add(x,y,c);
	}
	return 0;
}