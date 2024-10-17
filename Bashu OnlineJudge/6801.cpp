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
const int inf=2147483647;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt=1,Flow,Cost;
int h[N],dis[N],vis[N],pre[N];
struct edge{int to,next,flow,cost;}d[N];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=1;i<=n;i++){dis[i]=inf;vis[i]=pre[i]=0;}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return dis[t]!=inf;
}
void Adjust(int s,int t){
	int dlt=inf;
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		dlt=min(dlt,d[pre[i]].flow);
	}
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		d[pre[i]].flow-=dlt;
		d[pre[i]^1].flow+=dlt;
	}
	Flow+=dlt;Cost+=dlt*dis[t];
}
void Edmonds_Karp(int s,int t){while(SPFA(s,t))Adjust(s,t);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){int x=read(),y=read(),f=read(),c=read();Add(x,y,f,c);}
	Edmonds_Karp(1,n);
	printf("%d %d\n",Flow,Cost);
	return 0;
}