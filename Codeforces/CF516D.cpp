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
const int inf=0x3f3f3f3f;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[N],dis[N];
int n,m,cnt,h[N],p[N],fa[N],sum[N],prt[N];
struct edge{int to,next,dist;}d[N*2];
bool cmp(int x,int y){return f[x]<f[y];}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void DFS(int x,int Fa){
	f[x]=max(f[x],dis[x]);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa)continue;
		dis[y]=dis[x]+d[i].dist;
		DFS(y,x);
	}
}
void Union(int x,int y){x=Find(x);y=Find(y);fa[x]=y;sum[y]+=sum[x];}
void Solve(ll L){
	int ans=0;
	for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}
	for(int i=n,j=n;i>=1;i--){
		while(f[p[j]]>f[p[i]]+L){sum[Find(p[j])]--;j--;}
		ans=max(ans,sum[Find(p[i])]);
		Union(p[i],prt[p[i]]);
	}
	printf("%d\n",ans);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	int S=0;DFS(1,0);for(int i=1;i<=n;i++)if(dis[i]>dis[S])S=i;dis[S]=0;
	int T=0;DFS(S,0);for(int i=1;i<=n;i++)if(dis[i]>dis[T])T=i;dis[T]=0;
	DFS(T,0);
	for(int x=1;x<=n;x++){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(f[y]<f[x])prt[x]=y;
			else prt[y]=x;
		}
	}
	for(int i=1;i<=n;i++)p[i]=i;
	sort(p+1,p+n+1,cmp);
	int Case=read();
	while(Case--)Solve(read());
	return 0;
}
