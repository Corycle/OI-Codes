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
const int N=300005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,rt,cnt,tot,top;
struct edge{int to,next;}d[N*2];
int h[N],fa[N],dep[N],sum[N],vis[N],tmp[N];
int a[N],st[N],dfn[N],Ans[N],pre[N],p[N][M];
bool cmp(int x,int y){return dfn[x]<dfn[y];}
void Add(int x,int y){
	if(x==y)return;
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
}
struct Node{
	int dis,id;
	friend bool operator<(Node A,Node B){
		return A.dis!=B.dis?A.dis<B.dis:A.id<B.id;
	}
}F[N];
/*========Prepare========*/
void DFS(int x,int depth){
	dep[x]=depth;dfn[x]=++tot;sum[x]=1;
	for(auto y:G[x]){
		if(y==p[x][0])continue;
		p[y][0]=x;
		DFS(y,depth+1);
		sum[x]+=sum[y];
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
int Dist(int x,int y){
	return dep[x]+dep[y]-dep[LCA(x,y)]*2;
}
/*========Solve========*/
void Build(){
	sort(a+1,a+m+1,cmp);
	st[top=1]=a[1];cnt=0;
	for(int i=2;i<=m;i++){
		int lca=LCA(st[top],a[i]);
		while(top>=2&&dep[lca]<=dep[st[top-1]]){
			Add(st[top-1],st[top]);top--;
		}
		if(st[top]!=lca){Add(lca,st[top]);st[top]=lca;}
		st[++top]=a[i];
	}
	while(top>=2){Add(st[top-1],st[top]);top--;}
	rt=st[1];
}
void DFS1(int x){
	F[x]=(Node){inf,0};
	if(vis[x])F[x]=(Node){0,x};
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS1(y);
		int dist=F[y].dis+dep[y]-dep[x];
		F[x]=min(F[x],(Node){dist,F[y].id});
	}
}
void DFS2(int x,Node dlt){
	F[x]=min(dlt,F[x]);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		int dist=F[x].dis+dep[y]-dep[x];
		DFS2(y,(Node){dist,F[x].id});
	}
}
void DFS3(int x){
	Ans[F[x].id]+=sum[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		for(int k=(int)(log(dep[y])/log(2));k>=0;k--){
			if(dep[y]-(1<<k)>dep[x])y=p[y][k];
		}
		int z=y;y=d[i].to;
		Ans[F[x].id]-=sum[z];
		pre[y]=z;
		DFS3(y);
	}
}
void DFS4(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(F[x].id==F[y].id)Ans[F[x].id]+=sum[pre[y]]-sum[y];
		else{
			int lca=LCA(F[x].id,F[y].id),z=y;
			for(int k=(int)(log(dep[z])/log(2));k>=0;k--){
				if(dep[p[z][k]]<dep[lca])continue;
				Node A=(Node){dep[p[z][k]]+dep[F[x].id]-dep[lca]*2,F[x].id};
				Node B=(Node){dep[p[z][k]]+dep[F[y].id]-dep[p[z][k]]*2,F[y].id};
				if(B<A)z=p[z][k];
			}
			Ans[F[x].id]+=sum[pre[y]]-sum[z];
			Ans[F[y].id]+=sum[z]-sum[y];
		}
		DFS4(y);
	}
}
void Clear(int x){
	for(int i=h[x];i;i=d[i].next)Clear(d[i].to);
	h[x]=vis[x]=pre[x]=Ans[x]=0;F[x]=(Node){0,0};
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	DFS(1,1);ST();
	int T=read();
	while(T--){
		m=read();
		for(int i=1;i<=m;i++)a[i]=read();
		for(int i=1;i<=m;i++)vis[a[i]]=1;
		for(int i=1;i<=m;i++)tmp[i]=a[i];
		Build();
		DFS1(rt);DFS2(rt,F[rt]);
		DFS3(rt);DFS4(rt);
		Ans[F[rt].id]+=sum[1]-sum[rt];
		for(int i=1;i<=m;i++)printf("%d ",Ans[tmp[i]]);
		printf("\n");Clear(rt);
	}
	return 0;
}