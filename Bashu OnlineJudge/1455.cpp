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
const int inf=0x3f3f3f3f;
const int N=110005;
const int M=2500005;
int read(){
	int S=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){S=S*10+c-'0';c=getchar();}
	return S*f;
}
int n,m,p;
int cnt,S,T,ans=inf;
int h[N],dis[N],vis[N];
struct edge{
	int to,next,data;
}d[M];
void edge_add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct cmp{
	bool operator()(int x,int y){
		return dis[x]>dis[y];
	}
};
priority_queue<int,vector<int>,cmp>q;
void dijkstra(){
	int i,j,k;
	memset(dis,0x3f,sizeof(dis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.top();
		q.pop();
		vis[x]=0;
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].data){
				dis[y]=dis[x]+d[i].data;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();p=read();
	S=read()+1;T=read()+1;
	for(i=1;i<=m;i++){
		int x=read()+1,y=read()+1,z=read();
		for(k=0;k<=p;k++){
			edge_add(x+k*n,y+k*n,z);
			edge_add(y+k*n,x+k*n,z);
			if(k!=p){
				edge_add(x+k*n,y+k*n+n,0);
				edge_add(y+k*n,x+k*n+n,0);
			}
		}
	}
	dijkstra();
	for(k=0;k<=p;k++){
		if(dis[n*k+T]!=inf)ans=min(ans,dis[n*k+T]);
	}
	printf("%d",ans);
	return 0;
}