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
const int N=50005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Graph{
	int cnt,h[N];
	struct edge{
		int from,to,next,data;
	}d[N];
	void Add(int x,int y,int z){
		d[++cnt]=(edge){x,y,h[x],z};
		h[x]=cnt;
	}
	void Init(){
		cnt=1;
		memset(h,0,sizeof(h));
	}
}G1,G2;
int n,m,q,tot,top,num;
int dep[N],p[N][M],g[N][M];
int st[N],f1[N],f2[N],flag[N];
int v[N],pre[N],dfn[N],low[N];
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	for(int i=G1.h[x];i;i=G1.d[i].next){
		int y=G1.d[i].to,w=G1.d[i].data;
		if(i==(pre[x]^1))continue;
		if(!dfn[y]){
			st[++top]=i;
			pre[y]=i;Tarjan(y);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]){//树边 
				st[top--];
				G2.Add(x,y,w);
				G2.Add(y,x,w);
			}
			if(dfn[x]==low[y]){//回来了是个环 
				int sum=0;num=0;
				while(1){
					int j=st[top--];
					v[++num]=G1.d[j].from;
					sum+=G1.d[j].data;
					f1[G1.d[j].from]=sum;
					if(G1.d[j].from==x&&G1.d[j].to==y)break;
				}
				flag[++n]=1;
				for(int j=1;j<=num;j++){
					int fx=v[j];
					f2[fx]=sum-f1[fx];
					G2.Add(n,fx,min(f1[fx],f2[fx]));
					G2.Add(fx,n,min(f1[fx],f2[fx]));
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
	dep[x]=depth;
	for(int i=G2.h[x];i;i=G2.d[i].next){
		int y=G2.d[i].to,w=G2.d[i].data;
		if(y==p[x][0])continue;
		p[y][0]=x;g[y][0]=w;
		DFS(y,depth+1);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]){
				p[i][j]=p[p[i][j-1]][j-1];
				g[i][j]=g[p[i][j-1]][j-1]+g[i][j-1];
			}
		}
	}
}
int Dist(int x,int y){
	if(x==y)return 0;
	if(dep[x]<dep[y])swap(x,y);
	int Num=(int)(log(n)/log(2)),ans=0;
	for(int k=Num;k>=0;k--){
		if(dep[p[x][k]]>=dep[y]){
			ans+=g[x][k];x=p[x][k];
		}
	}
	if(x==y)return ans;
	for(int k=Num;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			ans+=g[x][k]+g[y][k];
			x=p[x][k];y=p[y][k];
		}
	}
	if(flag[p[x][0]]){
		ans+=min(min(f1[x]+f2[y],f2[x]+f1[y]),abs(f1[x]-f1[y]));
	}
	else ans+=g[x][0]+g[y][0];
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	G1.Init();G2.Init();
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		G1.Add(x,y,z);G1.Add(y,x,z);
	}
	Tarjan(1);DFS(1,1);ST();
	while(q--){
		int x=read(),y=read();
		printf("%d\n",Dist(x,y));
	}
	return 0;
}