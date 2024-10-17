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
const int M=22;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,Q,scc,tot,top,cnt=1;
int h[N],b[N],st[N],fa[N],dfn[N],low[N],vis[N],Ans[N],dep[N],sum[N],p[N][M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Tarjan(int x,int pre){
	int num=0;
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				scc++;num++;
				vis[x]=1;
				int k=0;
				do{
					k=st[top--];
					G[scc].push_back(k);
					b[k]=scc;
				}while(y!=k);
				G[scc].push_back(x);
				b[x]=scc;
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
	if(!pre)vis[x]=(num>1);
}
void ST(){
	int k=(int)(log(tot)/log(2));
	for(int i=1;i<=tot;i++)p[i][0]=fa[i];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=tot;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
void DFS1(int x,int depth){
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y,depth+1);
	}
}
void DFS2(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		DFS2(y);Ans[x]+=Ans[y];
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
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
	tot=scc;cnt=0;memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++)if(vis[i])b[i]=++tot;
	for(int i=1;i<=scc;i++){
		for(auto x:G[i]){
			if(vis[x]){Add(b[x],i);Add(i,b[x]);}
		}
	}
	DFS1(1,1);ST();
	while(Q--){
		int x=read(),y=read();
		if(!vis[x])sum[x]++;
		if(!vis[y])sum[y]++;
		x=b[x];y=b[y];
		int z=LCA(x,y);
		Ans[x]++;Ans[y]++;
		Ans[z]--;Ans[fa[z]]--;
	}
	DFS2(1);
	for(int i=1;i<=n;i++){
		printf("%d\n",vis[i]?Ans[b[i]]:sum[i]);
	}
	return 0;
}
