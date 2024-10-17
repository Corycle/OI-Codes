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
const int N=1005;
int n,m,h[N],cnt,dis[N],d1[N],vis[N],p[N][11];
struct edge{
	int to,next,data;
}d[N*2];
void hqq_add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void dfs(int x,int dep){
	int i,j,k;
	vis[x]=1;d1[x]=dep;
	for(i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!vis[y]){
			dis[y]=dis[x]+d[i].data;
			p[y][0]=x;
			dfs(y,dep+1);
		}
	}
}
void lca_init(){
	int i,j,k;
	k=int(log(n)/log(2));
	for(j=1;j<=k;j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int lca(int x,int y){
	int i,j,k;
	if(d1[x]<d1[y])swap(x,y);
	k=int(log(d1[x])/log(2));
	for(k;k>=0;k--){
		if(d1[x]-(1<<k)>=d1[y])x=p[x][k];
	}
	if(x==y)return x;
	k=int(log(d1[x])/log(2));
	for(k;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];
			y=p[y][k];
		}
	}
	return p[x][0];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		hqq_add(x,y,z);
		hqq_add(y,x,z);
	}
	memset(p,-1,sizeof(p));
	dfs(1,1);
	lca_init();
	for(i=1;i<=m;i++){
		int x=read(),y=read();
		int z=lca(x,y);
		printf("%d\n",dis[x]+dis[y]-2*dis[z]);
	}
	return 0;
}