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
const int N=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,D,cnt=1,h[N],dis[N];
struct Edge{int s,t,data;}e[N*40];
struct edge{int to,next,flow;}d[N*40];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]==-1&&d[i].flow){
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
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].data=read();
	}
	S=read();T=read();D=read();
	int ans=0;
	memset(h,0,sizeof(h));cnt=1;
	for(int i=1;i<=m;i++){
		if(e[i].data<D){
			Add(e[i].s,e[i].t,1);
			Add(e[i].t,e[i].s,1);
		}
	}
	ans+=Dinic(S,T);
	memset(h,0,sizeof(h));cnt=1;
	for(int i=1;i<=m;i++){
		if(e[i].data>D){
			Add(e[i].s,e[i].t,1);
			Add(e[i].t,e[i].s,1);
		}
	}
	ans+=Dinic(S,T);
	printf("%d",ans);
	return 0;
}
