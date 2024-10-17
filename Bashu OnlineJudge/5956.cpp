#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,h[100005],dep[100005],p[100005][20];
struct edge{
	int to,next;
}d[200005];
void hqq_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void dfs(int x,int depth){
	int i,j,k;
	dep[x]=depth;
	for(i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		p[y][0]=x;
		dfs(y,depth+1);
	}
}
void ST(){
	int i,j,k=int(log(n)/log(2));
	for(j=1;j<=k;j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int lca(int x,int y){
	int i,j,k;
	if(dep[x]<dep[y])swap(x,y);
	k=int(log(dep[x])/log(2));
	for(k;k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	k=int(log(dep[x])/log(2));
	for(k;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];
			y=p[y][k];
		}
	}
	return p[x][0];
}
int dist(int x,int y){
	return dep[x]+dep[y]-dep[lca(x,y)]*2;
}
bool pd(int x,int y,int a,int b){
	int chy=lca(x,y),ccl=lca(a,b);
	int dis1=dep[x]+dep[y]-dep[chy]*2;
	int dis2=dep[a]+dep[b]-dep[ccl]*2;
	if(dis1==dist(ccl,x)+dist(ccl,y))return true;
	if(dis2==dist(chy,a)+dist(chy,b))return true;
	return false;
}
int main(){
//	freopen("inter.in","r",stdin);
//	freopen("inter.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<n;i++){
		int x=read(),y=read();
		hqq_add(x,y);
		hqq_add(y,x);
	}
	memset(p,-1,sizeof(p));
	dfs(1,1);
	ST();
	int m=read();
	while(m--){
		int x=read(),y=read(),a=read(),b=read();
		if(pd(x,y,a,b))printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}