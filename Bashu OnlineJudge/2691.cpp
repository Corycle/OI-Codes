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
const int N=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,scc,top;
int h[N],H[N],p[N],b[N],st[N];
int dis[N],val[N],dfn[N],low[N],sum[N];
struct edge{int to,next,flow;}d[N*100];
struct Edge{int to,next;}e[N*100];
int id(int x,int y){return (x-1)*m+y;}
void Addedge(int x,int y){
	e[++cnt]=(Edge){y,H[x]};H[x]=cnt;
}
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	st[++top]=x;p[x]=1;
	for(int i=H[x];i;i=e[i].next){
		int y=e[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		int k=0;scc++;
		do{
			k=st[top--];
			sum[scc]++;
			b[k]=scc;
			p[k]=0;
		}while(k!=x);
	}
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			val[id(i,j)]=read();
			int num=read();
			while(num--){
				int x=read()+1,y=read()+1;
				Addedge(id(i,j),id(x,y));
			}
			if(j!=1)Addedge(id(i,j),id(i,j-1));
		}
	}
	for(int i=1;i<=n*m;i++){
		if(!dfn[i])Tarjan(i);
	}
	cnt=1;
	int S=n*m+1,T=n*m+2,ans=0;
	for(int i=1;i<=n*m;i++){
		if(sum[b[i]]>1)val[i]=-inf;
	}
	for(int i=1;i<=n*m;i++){
		if(val[i]>=0){
			ans+=val[i];
			Add(S,i,val[i]);
		}
		else{
			Add(i,T,-val[i]);
		}
	}
	for(int x=1;x<=n*m;x++){
		for(int i=H[x];i;i=e[i].next){
			int y=e[i].to;
			Add(y,x,inf);
		}
	}
	printf("%d",ans-Dinic(S,T));
	return 0;
}