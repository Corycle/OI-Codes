#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int M=10005;
const int N=505;
int read(){ 
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans=inf,sum;
int p[N][20],g[N][20];
int f[N],h[N],cnt,vis[N],dis[N];
struct edge{int to,next,data;}d[M*2];
struct Edge{int s,t,data,flag;}e[M*2];
bool cmp(Edge x,Edge y){
	return x.data<y.data;
}
bool cmp1(Edge x,Edge y){
	if(x.flag!=y.flag)return x.flag<y.flag;
	return x.data<y.data;
}
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
int find(int x){
	if(x==f[x])return x;
	f[x]=find(f[x]);
	return f[x];
}
void MST(){
	int num=1;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++){
		int x=find(e[i].s);
		int y=find(e[i].t);
		if(x!=y){
			num++;
			f[x]=y;
			e[i].flag=1;
			sum+=e[i].data;
			Add(e[i].s,e[i].t,e[i].data);
		}
		if(num==n)break;
	}
}
void dfs(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		dis[y]=dis[x]+1;
		p[y][0]=x;
		g[y][0]=d[i].data;
		dfs(y);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]==-1)continue;
			int T=p[i][j-1];
			p[i][j]=p[T][j-1];
			g[i][j]=max(g[i][j-1],g[T][j-1]);
		}
	}
}
int lca(int x,int y){
	if(dis[x]<dis[y])swap(x,y);
	int k=(int)(log(dis[x])/log(2));
	for(k;k>=0;k--){
		if(dis[x]-(1<<k)>=dis[y])x=p[x][k];
	}
	k=(int)(log(dis[x])/log(2));
	if(x==y)return x;
	for(k;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];y=p[y][k];
		}
	}
	return p[x][0];
}
int Ask(int x,int y){
	int tmp=0;
	if(dis[x]<dis[y])swap(x,y);
	int k=(int)(log(dis[x]-dis[y])/log(2));
	for(k;k>=0;k--){
		if(dis[x]-(1<<k)>=dis[y]){
			tmp=max(tmp,g[x][k]);
			x=p[x][k];
		}
	}
	return tmp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].data=read();
	}
	MST();
	dis[1]=1;
	dfs(1);ST();
	sort(e+1,e+m+1,cmp1);
	for(int i=1;i<=m;i++){
		if(e[i].flag)break;
		int k=lca(e[i].s,e[i].t);
		int sum1=Ask(e[i].s,k);
		int sum2=Ask(e[i].t,k);
		int v1=max(sum1,sum2);
		ans=min(ans,sum-v1+e[i].data);
	}
	printf("%d",ans);
	return 0;
}