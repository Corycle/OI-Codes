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
const ll M=1000005;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tmp,top;
ll h[N],st[N],vis[N];
struct edge{ll to,next,dist;}d[M];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
bool BFS(ll k){
	for(ll i=1;i<=n;i++)vis[i]=0;
	st[top=1]=1;vis[1]=1;
	while(top){
		ll x=st[top--];
		for(ll i=h[x];i;i=d[i].next){
			ll y=d[i].to;
			if((tmp&d[i].dist)==tmp){
				if(!vis[y]){
					vis[y]=1;st[++top]=y;
					if(y==n)return true;
				}
			}
		}
	}
	return false;
}
int main(){
//	freopen("graph.in","r",stdin);
//	freopen("graph.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	ll Ans=0;
	for(ll i=63;i>=1;i--){
		tmp=Ans|(1ll<<(i-1));
		if(BFS(i))Ans|=(1ll<<(i-1));
	}
	printf("%lld",Ans);
	return 0;
}