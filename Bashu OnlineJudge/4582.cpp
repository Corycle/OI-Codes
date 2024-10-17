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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt=1,h[N],dis[N];
struct edge{int to,next,flow;}d[N];
int id(int x,int y){return (x-1)*m+y;}
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
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
	int ans=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
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
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	int S=n*m+1,T=n*m+2,ans=0;tot=T;
	/*第i行第j列的同学选择文科获得的喜悦值*/
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();
			Add(S,id(i,j),x);
			ans+=x;
		}
	}
	/*第i行第j列的同学选择理科获得的喜悦值*/
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();
			Add(id(i,j),T,x);
			ans+=x;
		}
	}
	/*第i行第j列的同学与第i+1行第j列的同学同时选择文科获得的额外喜悦值*/
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			int x=read();
			ans+=x;tot++;
			Add(S,tot,x);
			Add(tot,id(i,j),inf);
			Add(tot,id(i+1,j),inf);
		}
	}
	/*第i行第j列的同学与第i+1行第j列的同学同时选择理科获得的额外喜悦值*/
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			int x=read();
			ans+=x;tot++;
			Add(tot,T,x);
			Add(id(i,j),tot,inf);
			Add(id(i+1,j),tot,inf);
		}
	}
	/*第i行第j列的同学与第i行第j+1列的同学同时选择文科获得的额外喜悦值*/
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			int x=read();
			ans+=x;tot++;
			Add(S,tot,x);
			Add(tot,id(i,j),inf);
			Add(tot,id(i,j+1),inf);
		}
	}
	/*第i行第j列的同学与第i行第j+1列的同学同时选择理科获得的额外喜悦值*/
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			int x=read();
			ans+=x;tot++;
			Add(tot,T,x);
			Add(id(i,j),tot,inf);
			Add(id(i,j+1),tot,inf);
		}
	}
	printf("%d",ans-Dinic(S,T));
	return 0;
}