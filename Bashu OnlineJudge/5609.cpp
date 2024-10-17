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
const int N=200005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,tot,top,Ans,root,Flag;
int a[N],h[N],fa[N],st[N],dep[N],dfn[N],vis[N],p[N][M];
struct edge{int to,next;}d[N];
bool cmp(int x,int y){return dfn[x]<dfn[y];}
void Addedge(int x,int y){G[x].push_back(y);}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int depth){
	dep[x]=depth;dfn[x]=++tot;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int i=1;i<=n;i++)p[i][0]=fa[i];
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
void Build(){
	sort(a+1,a+m+1,cmp);st[top=1]=a[1];
	for(int i=2;i<=m;i++){
		int lca=LCA(st[top],a[i]);
		while(top>=2&&dep[lca]<=dep[st[top-1]]){Addedge(st[top-1],st[top]);top--;}
		if(lca!=st[top]){Addedge(lca,st[top]);st[top]=lca;}
		st[++top]=a[i];
	}
	while(top>=2){Addedge(st[top-1],st[top]);top--;}
	root=st[top];
}
void Solve(int x){
	int num=0;
	if(vis[x]&&vis[fa[x]])Flag=0;
	for(auto y:G[x]){
		Solve(y);
		if(vis[x]&&vis[y])Ans++;
		if(!vis[x])num+=vis[y];
	}
	if(num==1)vis[x]=1;
	else Ans+=(num>1);
}
void Clear(int x){
	for(auto y:G[x])Clear(y);
	G[x].clear();vis[x]=0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);ST();
	int T=read();
	while(T--){
		m=read();
		for(int i=1;i<=m;i++)a[i]=read();
		for(int i=1;i<=m;i++)vis[a[i]]=1;
		Build();Ans=0;Flag=1;
		Solve(root);Clear(root);
		printf("%d\n",Flag?Ans:-1);
	}
	return 0;
}