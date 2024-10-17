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
const int N=250005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,ans1,ans2,cnt1,cnt2=1;
int dis[N],q[N],vis[N],h1[N],h2[N];
struct edge{
	int to,next,data,c;
}d[N],e[N];
void Add(int x,int y,int z,int w){
	e[++cnt1]=(edge){y,h1[x],z,w};
	h1[x]=cnt1;
}
void edge_add(int x,int y,int z){
	d[++cnt2]=(edge){y,h2[x],z,0};
	h2[x]=cnt2;
}
void SPFA(){
	queue<int>q;
	memset(dis,0x3f,sizeof(dis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.front();q.pop();
		vis[x]=0;
		for(int i=h1[x];i;i=e[i].next){
			int y=e[i].to;
			if(dis[y]>dis[x]+e[i].data){
				dis[y]=dis[x]+e[i].data;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	ans1=dis[T];
}
bool BFS(){
	memset(dis,-1,sizeof(dis));
	int l=1,r=1;
	dis[S]=0;
	q[1]=S;
	while(l<=r){
		int x=q[l++];
		if(x==T)return true;
		for(int i=h2[x];i;i=d[i].next){
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
	for(int i=h2[x];i;i=d[i].next){
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
void Build(){
	memset(vis,0,sizeof(vis));
	for(int x=1;x<=n;x++){
		for(int i=h1[x];i;i=e[i].next){
			int y=e[i].to;
			if(dis[y]==dis[x]+e[i].data){
				edge_add(x,y,e[i].c);
				edge_add(y,x,0);
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	S=1;T=n;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		int z=read(),w=read();
		Add(x,y,z,w);
		Add(y,x,z,w);
	}
	SPFA();
	Build();
	ans2=Dinic();
	printf("%d\n%d",ans1,ans2);
	return 0;
}