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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Flow,Cost,cnt=1;
int h[N],vis[N],dis[N],pre[N],down[N];
struct edge{int to,next,flow,cost;}d[N*100];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	memset(dis,0x3f,sizeof(dis));
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
	return dis[t]<inf;
}
void Adjust(int s,int t){
	int p=0,dlt=inf;
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		dlt=min(dlt,d[p].flow);
	}
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		d[p].flow-=dlt;
		d[p^1].flow+=dlt;
	}
	Flow+=dlt;
	Cost+=dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	Flow=Cost=0;
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	int sum=0;
	for(int i=1;i<=n;i++){
		int k=read();
		while(k--){
			int x=read(),y=read();//Add(i->x,down=1,up=inf,y);
			down[i]--;down[x]++;
			Add(i,x,inf,y);
			sum+=y;
		}
	}
	for(int i=2;i<=n;i++)Add(i,1,inf,0);
	int S=n+1,T=n+2;
	for(int i=1;i<=n;i++){
		if(down[i]>0)Add(S,i,down[i],0);
		if(down[i]<0)Add(i,T,-down[i],0);
	}
	Edmonds_Karp(S,T);
	printf("%d\n",Cost+sum);
	return 0;
}