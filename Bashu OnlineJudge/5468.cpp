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
const ll M=10000005;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,mod,cnt,tot,Min,Ans,Root;
ll a[N],h[N],sum[N],vis[N],Cnt[M];
struct edge{ll to,next;}d[N*2];
struct Node{ll x,sum,Max;}P[N];
bool cmp(Node A,Node B){return A.Max<B.Max;}
void Add(ll x,ll y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Find(ll x,ll fa,ll num){
	ll S=0;sum[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void DFS(ll x,ll fa,ll Sum,ll Max){
	sum[x]=1;
	P[++tot]=(Node){x,Sum,Max};
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa||vis[y])continue;
		DFS(y,x,Sum+a[y],max(Max,a[y]));
		sum[x]+=sum[y];
	}
}
void Calc(ll x,ll addv,ll pre,ll f){
	tot=0;
	DFS(x,0,a[x]+addv,max(a[x],a[pre]));
	sort(P+1,P+tot+1,cmp);
	for(ll i=1;i<=tot;i++){
		ll tmp=a[pre]+P[i].Max-P[i].sum;
		Ans+=f*Cnt[(tmp%mod+mod)%mod];
		Cnt[P[i].sum%mod]++;
	}
	for(ll i=1;i<=tot;i++)Cnt[P[i].sum%mod]--;
}
void Divide(ll x,ll num){
	Min=inf;Root=0;Find(x,0,num);
	x=Root;vis[x]=1;Calc(x,0,x,1);
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(vis[y])continue;
		Calc(y,a[x],x,-1);
		Divide(y,sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();mod=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(ll i=1;i<=n;i++)a[i]=read();
	Divide(1,n);
	printf("%lld",Ans+n);
	return 0;
}