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
const int Mod=1e9+7;
const int N=6e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num,cnt;
int h[N],fa[N],dep[N],p[N][M];
struct edge{int to,next;}d[N*2];
int id(int x,int t){return x+t*n;}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
struct Node{
	int fa[N];
	void Init(){for(int i=1;i<N;i++)fa[i]=i;}
	int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
}F1,F2;
void DFS(int x,int depth){
	dep[x]=depth;p[x][0]=fa[x];
	for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	return p[x][0];
}
int Pre(int x,int pre){
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--)if(dep[x]-(1<<k)>dep[pre])x=p[x][k];
	return x;
}
void Union(int x,int y){
	F1.fa[F1.Find(x)]=F1.Find(y);
	F2.fa[F2.Find(id(x,0))]=F2.Find(id(y,0));
	F2.fa[F2.Find(id(x,1))]=F2.Find(id(y,1));
}
void update(int x,int pre){
	x=F1.Find(x);
	while(dep[x]>dep[pre]+1){Union(x,fa[x]);x=F1.Find(fa[x]);}
}
void Update(int x,int y){
	int lca=LCA(x,y);update(x,lca);update(y,lca);
	if(x!=lca&&y!=lca){
		int p1=Pre(x,lca),p2=Pre(y,lca);
		F2.fa[F2.Find(id(p1,0))]=F2.Find(id(p2,1));
		F2.fa[F2.Find(id(p1,1))]=F2.Find(id(p2,0));
	}
}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();m=read();F1.Init();F2.Init();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	DFS(1,1);
	while(m--){int x=read(),y=read();Update(x,y);}
	for(int i=2;i<=n;i++)if(F2.Find(id(i,0))==F2.Find(id(i,1))){puts("0");return 0;}
	for(int i=2;i<=n;i++)if(F2.Find(id(i,0))==id(i,0))num++;
	printf("%d\n",Pow(2,num));
	return 0;
}