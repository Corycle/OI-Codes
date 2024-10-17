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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,cnt=1;
int h[N],dis[N],q[N],vis[N],p[N];
struct edge{
	int to,next,data;
}d[N*20];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
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
void dfs(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].data&&!vis[y])dfs(y);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	m=read();n=read();
	S=0;T=n+m+1;
	int ans=0;
	for(int i=1;i<=m;i++){
		int data=read();
		ans+=data;
		Add(S,i,data);
		Add(i,S,0);
		while(1){
			int x=read();
			if(!x)break;
			Add(i,x+m,inf);
			Add(x+m,i,0);
		}
	}
	for(int i=1;i<=n;i++){
		Add(i+m,T,read());
		Add(T,i+m,0);
	}
	ans-=Dinic();
	dfs(S);
	for(int x=1;x<=m;x++){
		if(vis[x]){
			printf("%d ",x);
			for(int i=h[x];i;i=d[i].next){
				int y=d[i].to;
				p[y]=1;
			}
		}
	}
	printf("\n");
	for(int i=1;i<=n;i++){
		if(p[i+m])printf("%d ",i);
	}
	printf("\n");
	printf("%d",ans);
	return 0;
}