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
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt1,cnt2;
ll h1[N],h2[N];
ll top[N],dep[N],son[N];
ll Max[N],sum[N],val[N];
struct edge{
	ll to,next;
}d[N],e[N];
void Add1(ll x,ll y){
	d[++cnt1]=(edge){y,h1[x]};
	h1[x]=cnt1;
}
void Add2(ll x,ll y){
	e[++cnt2]=(edge){y,h2[x]};
	h2[x]=cnt2;
}
void DFS1(ll x,ll depth){
	dep[x]=Max[x]=depth;
	for(ll i=h1[x];i;i=d[i].next){
		ll y=d[i].to;
		DFS1(y,depth+val[y]);
		if(Max[y]>Max[son[x]])son[x]=y;
	}
	Max[x]=max(Max[x],Max[son[x]]);
}
void DFS2(ll x,ll tp){
	top[x]=tp;
	sum[x]=val[x];
	if(son[x]){
		DFS2(son[x],tp);
		sum[x]+=sum[son[x]];
	}
	for(ll i=h1[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==son[x])continue;
		DFS2(y,y);
		Add2(tp,y);
	}
}
struct cmp{
	bool operator()(ll x,ll y){
		return sum[x]<sum[y];
	}
};
void Solve(){
	priority_queue<ll,vector<ll>,cmp>q;
	ll ans=0;q.push(1);
	while(q.size()){
		ll x=q.top();q.pop();
		ans+=sum[x];
		if(!(--m))break;
		for(ll i=h2[x];i;i=e[i].next){
			q.push(e[i].to);
		}
	}
	printf("%lld",ans);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)val[i]=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add1(x,y);
	}
	DFS1(1,val[1]);
	DFS2(1,1);
	Solve();
	return 0;
}
/*
6 4
4 3 2 1 9 5
1 2
2 3
2 4
4 6
1 5
*/