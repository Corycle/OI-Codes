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
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,cnt,Ans,Sum,h[N],deg[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct Tree{
	int s[N],fa[N],id[N],pos[N],p[N][M],g[N][M];
	int dis[N],pre[N],son[N],Max[N],sum[N],top[N];
	int tot,Root;
	void dfs(int x,int Fa){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y==Fa)continue;
			dis[y]=dis[x]+d[i].dist;
			dfs(y,x);
		}
	}
	void DFS(int x){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y==fa[x])continue;
			pre[y]=d[i].dist;fa[y]=x;DFS(y);
			if(Max[x]<Max[y]+d[i].dist){
				Max[x]=Max[y]+d[i].dist;
				son[x]=y;
			}
		}
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y==fa[x]||y==son[x])continue;
			pos[++tot]=y;s[y]=Max[y]+d[i].dist;
		}
	}
	void ST(){
		for(int i=1;i<=n;i++){p[i][0]=fa[i];g[i][0]=pre[i];}
		for(int j=1;j<M;j++){
			for(int i=1;i<=n;i++){
				p[i][j]=p[p[i][j-1]][j-1];
				g[i][j]=g[p[i][j-1]][j-1]+g[i][j-1];
			}
		}
	}
	void GetRoot(int x){
		dfs(x,0);Root=x;
		for(int i=1;i<=n;i++)if(dis[i]>dis[Root])Root=i;
		DFS(Root);ST();pos[++tot]=Root;s[Root]=Max[Root];
		sort(pos+1,pos+tot+1,[&](int x,int y){return s[x]>s[y];});
		for(int i=1;i<=tot;i++)sum[i]=sum[i-1]+s[pos[i]];
		for(int i=1;i<=tot;i++){
			int x=pos[i];
			while(x){id[x]=i;top[x]=pos[i];x=son[x];}
		}
	}
	int Solve1(int x,int y){
		int ans=Max[x];
		for(int k=M-1;k>=0;k--){
			if(id[p[x][k]]>=y){ans+=g[x][k];x=p[x][k];}
		}
		ans+=pre[x];
		return sum[y-1]+ans;
	}
	int Solve2(int x,int y){
		int ans=Max[x];
		for(int k=M-1;k>=0;k--){
			if(id[p[x][k]]>y){ans+=g[x][k];x=p[x][k];}
		}
		ans+=pre[x];
		return sum[y]-Max[fa[x]]+ans;
	}
	int Query(int x,int y){
		y=y*2-1;
		if(id[x]<=y)return sum[y];
		return max(Solve1(x,y),Solve2(x,y));
	}
}tree1,tree2;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		deg[x]++;deg[y]++;Sum+=z;
		Add(x,y,z);Add(y,x,z);
	}
	for(int i=1;i<=n;i++)K+=(deg[i]==1);
	tree1.GetRoot(1);
	tree2.GetRoot(tree1.Root);
	while(m--){
		int x=(read()+Ans-1)%n+1;
		int y=(read()+Ans-1)%n+1;
		if(y*2>=K)printf("%d\n",Ans=Sum);
		else printf("%d\n",Ans=max(tree1.Query(x,y),tree2.Query(x,y)));
	}
	return 0;
}
