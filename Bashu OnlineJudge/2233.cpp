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
const int N=1005;
const int M=N*N;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T;
int Ans,cnt=1;
int vis[N],dis[N];
int h[N],down[N],pre[N];
struct edge{
	int to,next,flow,cost;
}d[N*50];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(){
	queue<int>q;
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	memset(dis,0x3f,sizeof(dis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.front();
		q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;
				pre[y]=i;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
	if(dis[T]<inf)return true;
	return false;
}
void Adjust(){
	int p=0,dlt=inf;
	for(int i=T;i!=S;i=d[p^1].to){
		p=pre[i];
		dlt=min(dlt,d[p].flow);
	}
	for(int i=T;i!=S;i=d[p^1].to){
		p=pre[i];
		d[p].flow-=dlt;
		d[p^1].flow+=dlt;
	}
	Ans+=dis[T]*dlt;
}
void Edmonds_Karp(){
	while(SPFA())Adjust();
}
int main(){
//	freopen("tour.in","r",stdin);
//	freopen("tour.out","w",stdout);
	n=read();m=read();
	S=n*2+5;T=n*2+6;
	int s1=n*2+1,t1=n*2+2;
	int s2=n*2+3,t2=n*2+4;
	Add(s1,s2,m,0);
	Add(t2,t1,m,0);
	Add(t1,s1,inf,0);
	for(int i=1;i<=n;i++){
		int x=read();
		down[i]-=x;
		down[i+n]+=x;
//		Add(i,i+n,0,0);
		Add(s2,i,inf,0);
		Add(i+n,t2,inf,0);
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int x=read();
			if(x!=-1)Add(i+n,j,inf,x);
		}
	}
	for(int i=1;i<=n*2;i++){
		if(down[i]>0)Add(S,i,down[i],0);
		if(down[i]<0)Add(i,T,-down[i],0);
	}
	Edmonds_Karp();
	printf("%d",Ans);
	return 0;
}
/*
6 1
1 1 1 0 0 1
2 6 8 5 0
8 2 4 1
6 1 0
4 -1
4
*/