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
int n,m1,m2,cnt=1;
int h[N],vis[N],dis[N];
struct edge{
	int to,next,flow;
}d[N*20];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	queue<int>q;
	memset(vis,0,sizeof(vis));
	memset(dis,-1,sizeof(dis));
	q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0,dlt=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
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
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m1=read();m2=read();
	int S=0,T=n+n+m1+m2+1;
	/*
		1~n:				x
		n+1~n+n:			x'
		n+n+1~n+n+m1:		foods
		n+n+m1+1~n+n+m1+m2:	drinks
	*/
	for(int i=1;i<=m1;i++)Add(S,n+n+i,1);
	for(int i=1;i<=m2;i++)Add(n+n+m1+i,T,1);
	for(int i=1;i<=n;i++){
		Add(i,i+n,1);
		int num1=read(),num2=read();
		for(int j=1;j<=num1;j++){
			int x=read();
			Add(n+n+x,i,1);
		}
		for(int j=1;j<=num2;j++){
			int x=read();
			Add(n+i,n+n+m1+x,1);
		}
	}
	printf("%d",Dinic(S,T));
	return 0;
}