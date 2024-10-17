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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,ans1,ans2,cnt=1;
int h[N],pre[N],vis[N],dis[N];
struct edge{
	int to,next,flow,cost;
}d[N*500],e[N*500];
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
	ans1+=dlt;
	ans2+=dis[T]*dlt;
}
void Edmonds_Karp(){
	ans1=ans2=0;
	while(SPFA())Adjust();
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	S=0;T=n+m+1;
	for(int i=1;i<=n;i++)Add(S,i,read(),0);
	for(int i=1;i<=m;i++)Add(i+n,T,read(),0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();
			Add(i,j+n,inf,x);
		}
	}
	memcpy(e,d,sizeof(e));
	Edmonds_Karp();
	printf("%d\n",ans2);
	memcpy(d,e,sizeof(d));
	for(int i=2;i<=cnt;i++)d[i].cost*=-1;
	Edmonds_Karp();
	printf("%d\n",-ans2);
	return 0;
}