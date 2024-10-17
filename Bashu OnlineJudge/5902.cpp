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
const ll Mod=1e9+7;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt;
ll h[N],c[N],f[N][4];
struct edge{ll to,next;}d[N*2];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
}
void DFS(ll x,ll fa){
	if(!c[x])f[x][1]=f[x][2]=f[x][3]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa)continue;DFS(y,x);
		f[x][1]=f[x][1]*(f[y][2]+f[y][3])%Mod;
		f[x][2]=f[x][2]*(f[y][1]+f[y][3])%Mod;
		f[x][3]=f[x][3]*(f[y][1]+f[y][2])%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<n;i++){ll x=read(),y=read();Add(x,y);Add(y,x);}
	for(ll i=1;i<=m;i++){ll x=read(),y=read();c[x]=y;f[x][y]=1;}
	DFS(1,0);
	printf("%lld",(f[1][1]+f[1][2]+f[1][3])%Mod);
	return 0;
}