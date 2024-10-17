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
const int N=3000005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,S,T,cnt;
int h[N],vis[N],dis[N];
struct edge{int to,next,id;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct Node{int x,d;};
bool operator<(Node A,Node B){return A.d>B.d;}
void Dijkstra(int s,int t){
	for(int i=1;i<=n;i++){dis[i]=inf;vis[i]=0;}
	priority_queue<Node>q;q.push((Node){s,0});dis[s]=0;
	while(!q.empty()){
		int x=q.top().x;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>max(dis[x],d[i].id)){
				dis[y]=max(dis[x],d[i].id);
				q.push((Node){y,dis[y]});
			}
		}
	}
	printf("%d ",dis[t]);
}
int main(){
//	freopen("road.in","r",stdin);
//	freopen("road.out","w",stdout);
	n=read();m=read();S=read();T=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),t=read();
		if(t==0)Add(y,x,i);Add(x,y,i);
	}
	Dijkstra(S,T);
	Dijkstra(T,S);
	return 0;
}