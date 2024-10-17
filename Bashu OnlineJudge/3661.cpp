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
const double eps=1e-2;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,tot,cnt=1;
int h[N],vis[N],dis[N],Ans[N];
struct Edge{int s,t;double data;}e[N];
struct edge{int to,next;double data;}d[N];
void Add(int x,int y,double z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
bool BFS(){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==T)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]==-1&&d[i].data>0){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
double DFS(int x,double maxx){
	double ans=0,dlt=0;
	if(x==T||maxx==0)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dis[y]==dis[x]+1&&d[i].data>0){
			dlt=DFS(y,min(maxx,d[i].data));
			if(dlt==0)dis[y]=-1;
			d[i].data-=dlt;
			d[i^1].data+=dlt;
			ans+=dlt;maxx-=dlt;
			if(maxx==0)return ans;
		}
	}
	return ans;
}
double Dinic(){
	double ans=0;
	while(BFS())ans+=DFS(S,inf);
	return ans;
}
double Check(double x){
	cnt=1;
	memset(h,0,sizeof(h));
	memset(vis,0,sizeof(vis));
	double ans=0;
	for(int i=1;i<=m;i++){
		if(e[i].data<x){
			ans+=e[i].data-x;
			vis[i]=1;
		}
		else Add(e[i].s,e[i].t,e[i].data-x);
	}
	return ans+Dinic();
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		scanf("%lf",&e[i].data);
	}
	S=1;T=n;
	double l=0,r=1e7,ans=0;
	while(r-l>eps){
		double mid=(l+r)/2.0;
		if(Check(mid)<0){
			ans=mid;
			r=mid;
		}
		else l=mid;
	}
	for(int i=1;i<=m;i++){
		if((dis[e[i].s]!=-1)^(dis[e[i].t]!=-1))vis[i]=1;
		if(vis[i])Ans[++tot]=i;
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++){
		printf("%d ",Ans[i]);
	}
	return 0;
}