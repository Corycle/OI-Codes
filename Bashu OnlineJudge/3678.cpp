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
ll n,cnt,tot,maxx,S,T;
ll h[N],dis[N],vis[N];
ll Line[N],Max[N],lst[N];
struct edge{
	ll to,next,data;
}d[N*2];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS1(ll x,ll fa,ll len){
	vis[x]=1;
	if(len>maxx){maxx=len;S=x;}
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa)continue;
		if(vis[y])continue;
		DFS1(y,x,len+d[i].data);
	}
}
void DFS2(ll x,ll fa,ll len){
	lst[x]=fa;dis[x]=len;
	if(len>maxx){maxx=len;T=x;}
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa)continue;
		DFS2(y,x,len+d[i].data);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<n;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	memset(vis,0,sizeof(vis));DFS1(1,0,0);maxx=0;
	memset(vis,0,sizeof(vis));DFS2(S,0,0);
	memset(vis,0,sizeof(vis));
	for(ll i=T;i;i=lst[i]){
		Line[++tot]=i;
		vis[i]=1;
	}
	for(ll i=1;i<=tot;i++){
		maxx=0;
		ll x=Line[i];
		DFS1(x,0,0);
		Max[x]=maxx;
	}
	ll p=tot,Ans=0;
//	for(int i=1;i<=tot;i++)cout<<Line[i]<<" ";cout<<endl;
//	for(int i=1;i<=tot;i++)cout<<dis[Line[i]]<<" ";cout<<endl;
//	for(int i=1;i<=tot;i++)cout<<Max[Line[i]]<<" ";cout<<endl;
	for(ll i=1;i<=tot;i++){
		ll x=Line[i];
		if(dis[x]==Max[x]){
			p=i;break;
		}
	}
	for(ll i=p;i>=1;i--){
		ll x=Line[i];
		if(dis[T]-dis[x]==Max[x])break;
		Ans++;
	}
	printf("%lld\n",dis[T]);
	printf("%lld\n",Ans);
	return 0;
}