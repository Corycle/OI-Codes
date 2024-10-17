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
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=50005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt;
ll h[N],p[N],vis[N],sum[N];
struct edge{
	ll to,next,data;
}d[N*4];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void Insert(ll x){
	for(ll i=62;i>=0;i--){
		if((x>>i)&1){
			if(!p[i]){p[i]=x;break;}
			x^=p[i];
		}
	}
}
ll Ask(ll x){
	ll ans=x;
	for(ll i=62;i>=0;i--){
		if(ans<(ans^p[i]))ans^=p[i];
	}
	return ans;
}
void DFS(ll x,ll Sum){
	sum[x]=Sum;vis[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(!vis[y])DFS(y,Sum^d[i].data);
		else Insert(Sum^d[i].data^sum[y]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS(1,0);
	printf("%lld",Ask(sum[n]));
	return 0;
}
/*
5 7
1 2 2
1 3 2
2 4 1
2 5 1
4 5 3
5 3 4
4 3 2
*/