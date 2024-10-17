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
const int N=505;
const int M=N*N;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,S,T,dlt;
int h[M],dis[M],vis[M];
struct edge{
	int to,next,data;
}d[M*4];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct cmp{
	bool operator()(int x,int y){
		return dis[x]>dis[y];
	}
};
void SPFA(){
	priority_queue<int,vector<int>,cmp>q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.top();q.pop();
		vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
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
	n=read();
	S=0;T=n*n+1;
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++){
			int x=read();
			if(i==0)Add(j,T,x);
			else if(i==n)Add(S,(i-1)*n+j,x);
			else Add(i*n+j,(i-1)*n+j,x);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			int x=read();
			if(j==0)Add(S,(i-1)*n+1,x);
			else if(j==n)Add(i*n,T,x);
			else Add((i-1)*n+j,(i-1)*n+j+1,x);
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++){
			int x=read();
			if(i==0)Add(T,j,x);
			else if(i==n)Add((i-1)*n+j,S,x);
			else Add((i-1)*n+j,i*n+j,x);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			int x=read();
			if(j==0)Add((i-1)*n+1,S,x);
			else if(j==n)Add(T,i*n,x);
			else Add((i-1)*n+j+1,(i-1)*n+j,x);
		}
	}
	SPFA();
	printf("%d",dis[T]);
	return 0;
}