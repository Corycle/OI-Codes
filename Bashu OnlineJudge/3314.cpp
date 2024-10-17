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
const int N=10005;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[M][M];
int dx[4]={1,1,-1,-1};
int dy[4]={1,-1,1,-1};
int h[N],dis[N],vis[N],id[M][M];
int n,m,p,A,B,tot,Flow,Cost,cnt=1;
struct edge{int to,next,flow,cost;}d[N*20];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=1;i<=tot;i++){dis[i]=inf;vis[i]=0;}
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
	if(x==t||!maxx)return maxx;
	int ans=0;vis[x]=1;
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
		for(int i=1;i<=tot;i++)vis[i]=0;
		int dlt=DFS(s,inf,t);
		Flow+=dlt;Cost+=dlt*dis[t];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	p=read();A=read();B=read();
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)id[i][j]=++tot;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='*')continue;
			for(int k=0;k<4;k++){
				int x=i+dx[k]*A,y=j+dy[k]*B;
				if(x<1||x>n||y<1||y>m||a[x][y]=='*')continue;
				Add(id[i][j],id[x][y],inf,1);
			}
			for(int k=0;k<4;k++){
				int x=i+dx[k]*B,y=j+dy[k]*A;
				if(x<1||x>n||y<1||y>m||a[x][y]=='*')continue;
				Add(id[i][j],id[x][y],inf,1);
			}
		}
	}
	int S=++tot,T=++tot;
	for(int i=1;i<=p;i++){int x=read(),y=read();Add(S,id[x][y],1,0);}
	for(int i=1;i<=p;i++){int x=read(),y=read();Add(id[x][y],T,1,0);}
	ZKW(S,T);printf("%d",Cost);
	return 0;
}