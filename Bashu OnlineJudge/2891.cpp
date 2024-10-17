/*====Corycle====*/
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
const int M=200005;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,tot,cnt;
struct Edge{int s,t;}e[M];
int h[N],v[N],A[N],B[N],dis[N];
struct edge{int to,next,flow;}d[M];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	for(int i=1;i<=tot;i++)dis[i]=-1;
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
	if(x==t||!maxx)return maxx;
	int ans=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
void Build(){
	for(int i=1;i<=tot;i++)h[i]=0;cnt=1;
	for(int i=1;i<=n;i++)Add(A[i],B[i],v[i]);
	for(int i=1;i<=m;i++){
		int x=e[i].s,y=e[i].t;
		Add(B[x],A[y],inf);
		Add(B[y],A[x],inf);
	}
}
int Dinic(int s,int t){
	Build();
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();S=read();T=read();
	for(int i=1;i<=n;i++){A[i]=++tot;B[i]=++tot;v[i]=read();}
	for(int i=1;i<=m;i++){e[i].s=read();e[i].t=read();}
	int sum=Dinic(A[S],B[T]),tmp=0;
	for(int i=1;i<=n;i++){
		int p=v[i];v[i]=0;tmp+=p;
		if(Dinic(A[S],B[T])+tmp==sum){
			printf("%d ",i);
		}
		else{tmp-=p;v[i]=p;}
	}
	return 0;
}