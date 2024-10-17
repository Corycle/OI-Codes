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
#define pii pair<int,ll>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N],dsum[N];
vector<pii>G[N],F[N];
int n,m,cnt,root,Root,Min;
int h[N],fa[N],pre[N],sum[N],vis[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
/*========Tree_Divide========*/
void Find(int x,int Fa,int num){
	int S=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void dfs(int x,int Fa,int dist,int p){
	sum[x]=1;F[x].push_back(mp(p,dist));
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa||vis[y])continue;
		dfs(y,x,dist+d[i].dist,p);
		sum[x]+=sum[y];
	}
}
int Divide(int x,int Fa,int num){
	Root=0;Min=inf;Find(x,0,num);
	x=Root;vis[x]=1;dfs(x,0,0,x);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		int p=Divide(y,x,sum[y]);
		G[x].push_back(mp(p,0));
		pre[p]=y;
	}
	return x;
}
/*========Operation========*/
void Update(int x,int dlt){
	int p=x;a[x]+=dlt;
	for(int i=F[x].size()-1;i>=0;i--)dsum[F[x][i].fst]+=dlt;
	for(int i=F[x].size()-1;i>=0;i--){
		int y=F[x][i].fst;
		for(int j=G[y].size()-1;j>=0;j--){
			if(G[y][j].fst==p){G[y][j].scd+=dlt*F[x][i].scd;break;}
		}
		p=y;
	}
}
int Find(int x){
	int p=x;
	for(auto y:G[x]){
		if(dsum[y.fst]*2-dsum[x]>0){
			int dlt=dsum[x]-dsum[y.fst];
			for(auto t:F[pre[y.fst]])dsum[t.fst]+=dlt;
			p=Find(y.fst);
			for(auto t:F[pre[y.fst]])dsum[t.fst]-=dlt;
		}
	}
	return p;
}
ll Query(int x){
	int p=x;ll ans=0;
	for(int i=F[x].size()-1;i>=0;i--){
		int y=F[x][i].fst;
		ans+=F[x][i].scd*a[y];
		for(auto j:G[y])if(j.fst!=p)ans+=F[x][i].scd*dsum[j.fst]+j.scd;
		p=y;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	root=Divide(1,0,n);
	for(int i=1;i<=m;i++){
		int x=read(),y=read();Update(x,y);
		printf("%lld\n",Query(Find(root)));
	}
	return 0;
}