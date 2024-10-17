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
const ll inf=1e18;
const int N=1e4+5;
const int M=31;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,tot,cnt=1;
int h[N],a[N],dis[N],id[N][M];
struct edge{int to,next;ll flow;}d[N*M];
void Add(int x,int y,ll z){
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
ll DFS(int x,ll maxn,int t){
	if(x==t||!maxn)return maxn;
	ll ans=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			ll dlt=DFS(y,min(maxn,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxn-=dlt;ans+=dlt;
			if(!maxn)return ans;
		}
	}
	return ans;
}
ll Dinic(int s,int t){
	ll ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
void AddEdge(int x,int y){
	for(int i=0;i<31;i++){
		Add(id[x][i],id[y][i],1<<i);
		Add(id[y][i],id[x][i],1<<i);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++)for(int j=0;j<31;j++)id[i][j]=++tot;
	for(int i=1;i<=m;i++)AddEdge(read(),read());
	for(int i=1;i<=n;i++)a[i]=-1;
	for(int i=1;i<=K;i++){int x=read();a[x]=read();}
	for(int i=1;i<=n;i++){
		for(int j=0;j<31;j++){
			if(a[i]!=-1){
				int c=(a[i]>>j)&1;
				if(c==0)Add(id[i][j],T,inf);
				if(c==1)Add(S,id[i][j],inf);
			}
		}
	}
	ll Ans=Dinic(S,T);
	printf("%lld",Ans);
	return 0;
}