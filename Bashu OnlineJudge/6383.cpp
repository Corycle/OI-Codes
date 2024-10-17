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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,Mod,cnt;
vector<ll>G[N];
ll h[N],t1[N],t2[N],fa[N],Ans[N],vis[N];
struct edge{ll to,next,a,b,c;}d[N*2];
void Add(ll x,ll y,ll a,ll b,ll c){
	d[++cnt]=(edge){y,h[x],a,b,c};h[x]=cnt;
}
ll Find(ll x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void GetAns(ll s){
	queue<ll>q;q.push(s);
	t1[s]=1;t2[s]=0;vis[s]=1;
	while(q.size()){
		ll x=q.front();q.pop();
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(vis[y]){
				ll A=t1[x]*d[i].a%Mod;
				ll C=t1[y]*d[i].b%Mod;
				if((A+C)%Mod==0)continue;
				ll B=t2[x]*d[i].a%Mod;
				ll D=t2[y]*d[i].b%Mod;
				ll E=(d[i].c-B-D)%Mod;
				Ans[s]=E*Pow(A+C,Mod-2)%Mod;
				return;
			}
			else{
				vis[y]=1;q.push(y);
				ll A=t1[x]*d[i].a%Mod;
				ll B=t2[x]*d[i].a%Mod;
				ll inv=Pow(d[i].b,Mod-2);
				t1[y]=(-A*inv%Mod+Mod)%Mod;
				t2[y]=((d[i].c-B)%Mod*inv%Mod+Mod)%Mod;
			}
		}
	}
}
void Solve(ll s){
	GetAns(s);
	ll num=G[s].size();
	for(ll i=0;i<num;i++){
		vis[G[s][i]]=0;
	}
	queue<ll>q;q.push(s);vis[s]=1;
	while(q.size()){
		ll x=q.front();q.pop();
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if(vis[y])continue;
			q.push(y);vis[y]=1;
			Ans[y]=(d[i].c-Ans[x]*d[i].a%Mod)%Mod*Pow(d[i].b,Mod-2)%Mod;
		}
	}
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	n=read();Mod=read();
	for(ll i=1;i<=n;i++)fa[i]=i;
	for(ll i=1;i<=n;i++){
		ll x=read(),y=read();
		ll a=read(),b=read(),c=read();
		Add(x,y,a,b,c);Add(y,x,b,a,c);
		fa[Find(x)]=Find(y);
	}
	for(ll i=1;i<=n;i++)G[Find(i)].push_back(i);
	for(ll i=1;i<=n;i++)if(i==fa[i])Solve(i);
	for(ll i=1;i<=n;i++)printf("%lld\n",(Ans[i]%Mod+Mod)%Mod);
	return 0;
}