#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,g[1005],ans[1005][1005],dep[1005],cnt,h[1005],vis[1005],p[1005][25],maxx[1005][25];
struct mst_edge{
	int s,t,data;
}d[50005];
struct edge{
	int to,next,data;
}e[2005];
void hqq_add(int x,int y,int z){
	e[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
bool cmp(mst_edge x,mst_edge y){
	return x.data<y.data;
}
int Find(int x){
	return x==g[x]?x:g[x]=Find(g[x]);
}
void Kruskal(){
	int i,j,k;
	int num=1;
	for(i=1;i<=n;i++)g[i]=i;
	for(i=1;i<=m;i++){
		int x=Find(d[i].s),y=Find(d[i].t);
		if(x!=y){
			num++;
			g[x]=y;
			hqq_add(d[i].s,d[i].t,d[i].data);
			hqq_add(d[i].t,d[i].s,d[i].data);
			if(num==n)return;
		}
	}
}
void dfs(int x,int depth){
	int i,j,k;
	vis[x]=1;dep[x]=depth;
	for(i=h[x];i;i=e[i].next){
		int y=e[i].to;
		if(vis[y])continue;
		p[y][0]=x;
		maxx[y][0]=e[i].data;
		dfs(y,depth+1);
	}
}
void lca_init(){
	int i,j,k;
	for(j=1;j<=int(log(n)/log(2));j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=-1){
				p[i][j]=p[p[i][j-1]][j-1];
				maxx[i][j]=max(maxx[i][j-1],maxx[p[i][j-1]][j-1]);
			}
		}
	}
}
int lca_maxx(int x,int y){
	int i,j,k;
	int ans=0;
	if(dep[x]<dep[y])swap(x,y);
	k=int(log(dep[x])/log(2));
	for(k;k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y]){
			ans=max(ans,maxx[x][k]);
			x=p[x][k];
		}
	}
	if(x==y)return ans;
	k=int(log(dep[x])/log(2));
	for(k;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			ans=max(ans,max(maxx[x][k],maxx[y][k]));
			x=p[x][k];
			y=p[y][k];
		}
	}
	return max(ans,max(maxx[x][0],maxx[y][0]));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		d[i].s=read();
		d[i].t=read();
		d[i].data=read();
	}
	sort(d+1,d+m+1,cmp);
	memset(p,-1,sizeof(p));
	Kruskal();
	for(i=1;i<=n;i++){
		if(!dep[i])dfs(i,1);
	}
	lca_init();
	m=read();
	while(m--){
		int x=read(),y=read();
		if(Find(x)!=Find(y)){
			printf("-1\n");
			continue;
		}
		printf("%d\n",lca_maxx(x,y));
	}
	return 0;
}