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
const ll Mod=998244353;
const ll N=4005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,cnt;
ll h[N],G[N],fa[N];
ll sum[N],C[N][N],F[N][N];
struct edge{ll to,next;}d[N*2];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(ll x){
	F[x][1]=1;sum[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;DFS(y);
		memset(G,0,sizeof(ll)*(sum[x]+sum[y]+1));
		for(ll j=1;j<=sum[x];j++){
			for(ll k=0;k<=sum[y];k++){
				G[j+k]=(G[j+k]+F[x][j]*F[y][k]%Mod*C[j+k-1][k]%Mod)%Mod;
			}
		}
		sum[x]+=sum[y];
		for(ll j=0;j<=sum[x];j++)F[x][j]=G[j];
	}
	for(ll i=sum[x];i>=0;i--)F[x][i]=(F[x][i]+F[x][i+1])%Mod;
}
int main(){
//	freopen("B.in","r",stdin);
//	freopen("B.out","w",stdout);
	n=read();
	C[0][0]=1;
	for(ll i=1;i<=n;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
		}
	}
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1);
	printf("%lld",F[1][1]);
	return 0;
}