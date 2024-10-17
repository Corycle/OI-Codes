#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,ans,tot,num,cnt;
int f[N][2],g[N][2][2];
int h[N],st[N],Circle[N];
int dfn[N],low[N],val[N],vis[N];
struct edge{
	int to,next;
}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Tarjan(int x,int fa){
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		if(!dfn[y]){
			Tarjan(y,x);
			low[x]=min(low[x],low[y]);
		}
		else{
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		int k=0;
		if(st[top]==x){
			top--;
			return;
		}
		do{
			k=st[top--];
			Circle[++num]=k;
			vis[k]=1;
		}while(k!=x);
	}
}
void DFS(int x,int fa){
	f[x][1]=val[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y]||y==fa)continue;
		DFS(y,x);
		f[x][0]+=max(f[y][0],f[y][1]);
		f[x][1]+=f[y][0];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)val[i]=read();
	for(int i=1;i<=n;i++){
		int x=read()+1,y=read()+1;
		Add(x,y);Add(y,x);
	}
	Tarjan(1,0);
	for(int i=1;i<=num;i++)DFS(Circle[i],0);
	g[1][0][0]=f[Circle[1]][0];
	g[1][1][1]=f[Circle[1]][1];
	for(int i=2;i<=num;i++){
		int x=Circle[i];
		g[i][0][0]=f[x][0]+max(g[i-1][0][0],g[i-1][1][0]);
		g[i][0][1]=f[x][0]+max(g[i-1][0][1],g[i-1][1][1]);
		g[i][1][0]=f[x][1]+g[i-1][0][0];
		g[i][1][1]=f[x][1]+g[i-1][0][1];
	}
	ans=max(g[num][0][0],max(g[num][0][1],g[num][1][0]));
	double K;
	scanf("%lf",&K);
	printf("%.1lf",ans*K);
	return 0;
}