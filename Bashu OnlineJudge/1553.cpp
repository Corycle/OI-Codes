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
const int N=400005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,tot,scc,cnt=1;
int h[N],H[N],b[N],fa[N],st[N],dep[N],vis[N],dfn[N],low[N],p[N][M];
struct edge{int to,next;}d[N*2],e[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Addedge(int x,int y){
	e[++cnt]=(edge){y,H[x]};
	H[x]=cnt;
}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;
	st[++top]=x;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		if(i==(pre^1))continue;
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int k=0;scc++;
		do{
			k=st[top--];
			b[k]=scc;
			vis[k]=0;
		}while(x!=k);
	}
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=H[x];i;i=e[i].next){
		int y=e[i].to;
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
int Dist(int x,int y){
	return dep[x]+dep[y]-dep[LCA(x,y)]*2;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	cnt=0;
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
	for(int x=1;x<=n;x++){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(b[x]!=b[y]){
				Addedge(b[x],b[y]);
			}
		}
	}
	DFS(1,1);ST();
	int T=read();
	while(T--)printf("%d\n",Dist(b[read()],b[read()]));
	return 0;
}