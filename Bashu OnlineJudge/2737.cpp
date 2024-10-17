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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,cnt=1,tot,tp,scc;
int h[N],dis[N],q[N],vis[N];
int dfn[N],low[N],p[N],st[N],b[N];
struct edge{
	int to,next,data,fr;
}d[N*20];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z,x};
	h[x]=cnt;
}
bool BFS(){
	memset(dis,-1,sizeof(dis));
	int l=1,r=1;
	dis[S]=0;
	q[1]=S;
	while(l<=r){
		int x=q[l++];
		if(x==T)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]==-1&&d[i].data){
				dis[y]=dis[x]+1;
				q[++r]=y;
			}
		}
	}
	return false;
}
int DFS(int x,int maxx){
	int ans=0,dlt=0;
	if(x==T||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].data&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].data));
			if(dlt==0)dis[y]=-1;
			d[i].data-=dlt;
			d[i^1].data+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(){
	int ans=0;
	while(BFS())ans+=DFS(S,inf);
	return ans;
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	st[++tp]=x;p[x]=1;
	for(int i=h[x];i;i=d[i].next){
		if(!d[i].data)continue;
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		int k;
		scc++;
		do{
			k=st[tp--];
			b[k]=scc;
			p[k]=0;
		}while(k!=x);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	S=read();T=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);
		Add(y,x,0);
	}
	Dinic();
	for(int i=1;i<=n;i++){
		if(!dfn[i])Tarjan(i);
	}
	for(int i=2;i<=cnt;i+=2){
		int x=d[i].fr,y=d[i].to;
		if(!d[i].data&&b[x]!=b[y]){
			printf("1 ");
			if(b[x]==b[S]&&b[y]==b[T])printf("1\n");
			else printf("0\n");
		}
		else printf("0 0\n");
	}
	return 0;
}