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
const int N=3005;
const int M=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,cnt,ans=inf;
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
	q.push(1);dis[1]=0;
	while(q.size()){
		int x=q.top();
		q.pop();
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
	for(i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		for(k=0;k<=p;k++){
			edge_add(x+k*n,y+k*n,z);
			edge_add(y+k*n,x+k*n,z);
			if(k!=p){
				edge_add(x+k*n,y+k*n+n,z/2);
				edge_add(y+k*n,x+k*n+n,z/2);
			}
		}
	}
	dijkstra();
	for(k=0;k<=p;k++){
		if(dis[n*k+n]!=inf)ans=min(ans,dis[n*k+n]);
	}
	printf("%d",ans);
	return 0;
}