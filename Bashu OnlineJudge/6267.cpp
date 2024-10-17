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
const int N=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt=1,Flow,Cost;
int h[N],cd[N],dis[N],vis[N];
struct Edge{int s,t,A,B;}e[N];
struct edge{int to,next,flow,cost;}d[N*20];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=0;i<=t;i++){dis[i]=inf;vis[i]=0;}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return dis[t]!=inf;
}
int DFS(int x,int maxx,int t){
	int ans=0;
	if(x==t||!maxx)return maxx;
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&!vis[y]&&dis[y]==dis[x]+d[i].cost){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
void ZKW(int s,int t){
	Flow=Cost=0;
	while(SPFA(s,t)){
		for(int i=0;i<=t;i++)vis[i]=0;
		int dlt=DFS(s,inf,t);
		if(Cost+dlt*dis[t]>m){
			Flow+=(m-Cost)/dis[t];
			break;
		}
		else{Flow+=dlt;Cost+=dlt*dis[t];}
	}
}
int main(){
//	freopen("protoss.in","r",stdin);
//	freopen("protoss.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		e[i].s=read();e[i].t=read();
		e[i].A=read();e[i].B=read();
		cd[e[i].s]++;
	}
	int S=0,T=n+1;
	for(int i=1;i<=n;i++){
		if(!cd[i])Add(i,T,inf,0);
		Add(e[i].s,e[i].t,e[i].A,0);
		Add(e[i].s,e[i].t,e[i].B-e[i].A,1);
	}
	ZKW(S,T);
	printf("%d",Flow);
	return 0;
}