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
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans1,ans2,cnt=1;
int h[N],vis[N],dis[N],pre[N];
struct edge{
	int to,next,flow,cost;
}d[N*2];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	queue<int>q;
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;q.push(s);
	while(q.size()){
		int x=q.front();q.pop();
		vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
				pre[y]=i;
			}
		}
	}
	if(dis[t]!=inf)return true;
	return false;
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
	ans1+=dlt;
	ans2+=dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		Add(i,i+n,1,0);
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x+n,y,1,z);
	}
	Edmonds_Karp(1+n,n);
	printf("%d %d",ans1,ans2);
	return 0;
}