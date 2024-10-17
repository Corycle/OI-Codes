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
int n,m,S,T,cnt=1;
int h[N],dis[N],down[N];
struct edge{
	int to,next,flow,type;
}d[M*40];
void Add(int x,int y,int z,int t){
	d[++cnt]=(edge){y,h[x],z,t};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,t};h[y]=cnt;
}
bool BFS(){
	memset(dis,-1,sizeof(dis));
	queue<int>q;
	q.push(S);
	dis[S]=0;
	while(q.size()){
		int x=q.front();
		q.pop();
		if(x==T)return true;
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
int DFS(int x,int maxx){
	int ans=0,dlt=0;
	if(x==T||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow));
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(){
	int ans=0;
	while(BFS())ans+=DFS(S,inf);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	S=0;T=n+1;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),b=read(),c=read();
		Add(x,y,c-b,1);//1=Ô­Ê¼±ß 
		down[x]-=b;down[y]+=b;
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		if(down[i]>0){
			Add(S,i,down[i],0);
			sum+=down[i];
		}
		if(down[i]<0)Add(i,T,-down[i],0);
	}
	Add(n,1,inf,0);
	Dinic();
	int ans=d[cnt].flow;
	for(int i=2;i<=cnt;i++){
		if(!d[i].type)d[i].flow=0;
	}
	S=1;T=n;
	ans+=Dinic();
	printf("%d",ans);
	return 0;
}
