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
const int N=200005;
const int M=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Graph{
	int cnt,h[N];
	struct edge{
		int from,to,next;
	}d[N];
	void Add(int x,int y){
		d[++cnt]=(edge){x,y,h[x]};
		h[x]=cnt;
	}
	void Init(){
		cnt=1;
		memset(h,0,sizeof(h));
	}
}G1,G2;
int n,m,q,tot,top;
int v[N],pre[N],dfn[N],low[N],flag[N];
int fa[N],st[N],dep[N],f[N][2],g[N][2][2];
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	for(int i=G1.h[x];i;i=G1.d[i].next){
		int y=G1.d[i].to;
		if(i==(pre[x]^1))continue;
		if(!dfn[y]){
			st[++top]=i;
			pre[y]=i;Tarjan(y);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]){//树边 
				st[top--];
				G2.Add(x,y);
				G2.Add(y,x);
			}
			if(dfn[x]==low[y]){//回来了是个环 
				int sum=0,num=0;
				while(1){
					int j=st[top--];
					v[++num]=G1.d[j].from;
					if(G1.d[j].from==x&&G1.d[j].to==y)break;
				}
				flag[++n]=1;
				for(int j=1;j<=num;j++){
					int fx=v[j];
					G2.Add(n,fx);
					G2.Add(fx,n);
				}
			}
		}
		else if(dfn[x]>dfn[y]){
			st[++top]=i;
			low[x]=min(low[x],dfn[y]);
		}
	}
}
void DFS(int x,int depth){
	if(!flag[x])f[x][1]=1;
	int num=0;dep[x]=depth;
	for(int i=G2.h[x];i;i=G2.d[i].next){
		int y=G2.d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
		if(!flag[x]){
			f[x][1]+=f[y][0];//0不选 1选 
			f[x][0]+=max(f[y][0],f[y][1]);
		}
	}
	if(flag[x]){//将x的所有儿子看做一条链
		for(int i=G2.h[x];i;i=G2.d[i].next){
			int y=G2.d[i].to;
			if(y!=fa[x])v[++num]=y;
		}
		for(int i=1;i<=num;i++){
			int fx=v[i];
			g[i][0][0]=g[i][0][1]=0;
			g[i][1][0]=g[i][1][1]=0;
			if(i==1){
				//g[x][i][j] i表示v[x]是否选 j表示v[1]是否选 
				g[i][0][0]=f[fx][0];
				g[i][1][1]=f[fx][1];
			}
			else{
				g[i][0][0]=f[fx][0]+max(g[i-1][0][0],g[i-1][1][0]);
				g[i][0][1]=f[fx][0]+max(g[i-1][0][1],g[i-1][1][1]);
				g[i][1][0]=f[fx][1]+g[i-1][0][0];
				g[i][1][1]=f[fx][1]+g[i-1][0][1];
			}
		}
		f[x][0]=max(f[x][0],g[num][0][0]);
		f[x][1]=max(f[x][1],max(g[num][0][0],g[num][0][1]));
		f[x][1]=max(f[x][1],max(g[num][1][0],g[num][1][1]));
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	G1.Init();G2.Init();
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		G1.Add(x,y);G1.Add(y,x);
	}
	Tarjan(1);DFS(1,1);
	printf("%d\n",max(f[1][0],f[1][1]));
	return 0;
}