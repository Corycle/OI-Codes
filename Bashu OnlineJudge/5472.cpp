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
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=30005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<ll>G[N];
ll n,m,tot,Ans;
ll a[N],r[N],fa[N],Fa[N],Sum[N],Size[N];
struct Node{
	ll x,Sum,Size;
	friend bool operator<(Node A,Node B){
		return A.Sum*B.Size>B.Sum*A.Size;
	}
};
ll Find(ll x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void DFS(ll x,ll prt){
	Fa[x]=prt;
	for(auto y:G[x]){
		if(y!=prt)DFS(y,x);
	}
}
ll Solve(ll sx){
	ll ans=0;DFS(sx,0);
	priority_queue<Node>q;
	for(ll i=1;i<=n;i++){
		fa[i]=i;Sum[i]=a[i];Size[i]=1;
		q.push((Node){i,Sum[i],Size[i]});
	}
	while(q.size()){
		ll x=q.top().x,siz=q.top().Size;q.pop();
		if(x==sx||siz!=Size[x])continue;
		ll fx=Find(Fa[x]);ans+=Sum[x]*Size[fx];
		fa[x]=fx;Size[fx]+=Size[x];Sum[fx]+=Sum[x];
		if(Find(sx)!=fx)q.push((Node){fx,Sum[fx],Size[fx]});
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(ll i=1;i<=n;i++){a[i]=read();r[i]=read();tot+=a[i];}
	for(ll i=1;i<=n;i++)if(r[i])Ans=max(Ans,Solve(i)+tot);
	printf("%lld",Ans);
	return 0;
}